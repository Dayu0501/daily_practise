package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"math"
	"os"
	"sync"

	"github.com/emersion/go-imap"
	"github.com/emersion/go-imap/client"
)

var (
	server, email, password string
	workernum               int
	imapClient              *client.Client
	mailDirs                []string
	mailSumNums             uint32
	pagesize                int = 50
	start                   int
	stop                    int
)

type Pool struct {
	workerNum int
	road      chan *Car
	wg        sync.WaitGroup
}

//初始化这个对象
func NewPool(wn int) *Pool {
	return &Pool{workerNum: wn, road: make(chan *Car)}
}

//往channel添加具体任务
func (p *Pool) AddCar(f *Car) {
	p.road <- f
}

//goroutine去工作
func (p *Pool) work(workId int) {
	for f := range p.road {
		log.Println("workId:", workId, "start")
		f.do()
		log.Println("workId:", workId, "done")
	}
	p.wg.Done()
}

//创建goroutine等着接工作
func (p *Pool) Run() {
	for i := 0; i < p.workerNum; i++ {
		go p.work(i)
		p.wg.Add(1)
	}
	p.wg.Wait()
}

func (p *Pool) colse() {
	close(p.road)
}

var pool = NewPool(5)

func main() {
	go handleMail()
	pool.Run()
}
func handleMail() {
	//获取命令行参数
	//flag.StringVar(&server, "server", "", "imap服务地址(包含端口)")
	//flag.StringVar(&email, "email", "", "邮箱名")
	//flag.StringVar(&password, "password", "", "密码")
	//flag.Parse()
	//if flag.NFlag() < 3 {
	//	flag.PrintDefaults()
	//	os.Exit(1)
	//}
	server = "mail.em-data.com.cn:993"
	email = "yulichao@em-data.com.cn"
	password = "HON123456well"
	if server == "" || email == "" || password == "" {
		log.Fatal("服务器地址,用户名,密码,参数错误")
	}
	//连接imap服务
	fmt.Println("hhhhh")
	imapClient, err := client.Dial(server)
	if err != nil {
		fmt.Println("kkkkkkk")
		log.Fatal(err)
	}
	//登陆
	if err := imapClient.Login(email, password); err != nil {
		log.Fatal(err)
	}
	//创建邮件夹目录
	os.Mkdir(email, os.ModePerm)
	mailboxes := make(chan *imap.MailboxInfo, 20)
	go func() {
		imapClient.List("", "*", mailboxes)
	}()
	//列取邮件夹
	for m := range mailboxes {
		mailDirs = append(mailDirs, m.Name)
	}
	//循环邮件夹,创建邮件夹目录
	for _, mailDir := range mailDirs {
		//选中每个邮件夹
		mbox, err := imapClient.Select(mailDir, false)
		if err != nil {
			log.Fatal(err)
		}
		mailDirNums := mbox.Messages
		log.Printf("%s : %d", mailDir, mailDirNums)
		fileDir := fmt.Sprintf("%s/%s", email, mailDir)
		//创建邮件夹目录
		os.Mkdir(fileDir, os.ModePerm)
		mailSumNums += mailDirNums
	}
	log.Printf("总邮件数 : %d", mailSumNums)
	//循环邮件夹,读取每个邮件夹中的邮件

	for _, mailDir := range mailDirs {
		//选中每个邮件夹
		mbox, err := imapClient.Select(mailDir, false)
		if err != nil {
			log.Fatal(err)
		}
		if mbox.Messages == 0{
			continue
		}
		//循环该邮件夹中的邮件
		pagecount := int(math.Ceil(float64(mbox.Messages) / float64(pagesize)))
		for i := 1; i <= pagecount; i++ {
			if i == 1 {
				start = 1
			} else {
				start = (i-1)*pagesize + 1
			}
			stop = i * pagesize
			if stop > int(mbox.Messages) {
				stop = int(mbox.Messages)
			}
			car := Car{
				start:      start,
				stop:       stop,
				mailDir:    mailDir,
				imapClient: imapClient,
			}
			pool.AddCar(&car)
		}
	}
	pool.colse()
}

/*具体做的事通过这个来传递*/
type Car struct {
	start, stop int
	mailDir     string
	imapClient  *client.Client
}

//具体做事
func (c *Car) do() error {
	seqset := new(imap.SeqSet)
	seqset.AddRange(uint32(c.start), uint32(c.stop))
	section := &imap.BodySectionName{}
	items := []imap.FetchItem{section.FetchItem()}

	messages := make(chan *imap.Message, pagesize)
	go func() {
		c.imapClient.Fetch(seqset, items, messages)
	}()

	for msg := range messages {
		mailFile := fmt.Sprintf("%s/%s/%d.eml", email, c.mailDir, msg.SeqNum)
		r := msg.GetBody(section)
		if r != nil {
			body, _ := ioutil.ReadAll(r)
			f, _ := os.OpenFile(mailFile, os.O_RDWR|os.O_CREATE, 0766)
			f.Write(body)
			f.Close()
			log.Printf("%s :第 %d ", c.mailDir, msg.SeqNum)
		}
	}
	return nil
}
