package main

import (
	"github.com/emersion/go-imap"
	"github.com/emersion/go-imap/client"
	"log"
)

const (
	server   = "mail.em-data.com.cn:993"
	username = "yulichao@em-data.com.cn"
	password = "HON123456well"
)

func main() {
	var c *client.Client
	var err error
	log.Println("Connecting to server...")
	c, err = client.DialTLS(server, nil)

	//连接失败报错
	if err != nil {
		log.Fatal(err)
	}
	log.Println("Connected")

	//登陆
	if err := c.Login(username, password); err != nil {
		log.Fatal(err)
	}
	log.Println("Logged in")
	mailboxes := make(chan *imap.MailboxInfo, 20)
	go func() {
		c.List("", "*", mailboxes)
	}()

	//列取邮件夹
	for m := range mailboxes {
		mbox, err := c.Select(m.Name, false)
		if err != nil {
			log.Fatal(err)
		}
		to := mbox.Messages
		log.Printf("%s : %d", m.Name, to)
	}
}
