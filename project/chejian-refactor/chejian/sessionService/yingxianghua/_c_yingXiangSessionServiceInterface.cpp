#include "_c_yingXiangSessionService.h"
#include "base/soapApi/soapApi.h"
#include "base/json/json.h"
#include "base/json/reader.h"
#include "base/http/HttpClient.h"
#include "base/baseTool.h"
#include <ctime>
#include <sstream>
#include <dirent.h>
#include "base/occi/occi_db_wrapper.h"

//解析返回的lsh信息
int _c_yingXiangSessionService::AnalyseLshReturn(char *pLshReturn,std::vector<std::string>& pVector)
{
    Json::Reader reader;
    Json::Value valueRoot;
    if(!reader.parse(pLshReturn, valueRoot))
    {
        return -1;
    }

    //读取参数
    string iRes = valueRoot["res"].asString();
    string msg = valueRoot["msg"].asString();
    string data = valueRoot["data"].toStyledString();
    Json::Value valueData;
    if(!reader.parse(data, valueRoot))
    {
        return -1;
    }
    for(int i = 0; i < valueRoot.size(); ++i)
    {
        string lsh = valueRoot[i]["lsh"].asString();
        string lszt = valueRoot[i]["lszt"].asString();
        pVector.push_back(lsh);
    }
    return valueRoot.size();
}


int _c_yingXiangSessionService::queryLiuShuiHao(std::vector<std::string> *pVector)
{
    //清空vector（防止分配已使用内存）
    pVector->clear();
    HttpClient httpClient;
    std::string uri = "http://" + _yingXiangStartUpParam.soapIp + ":" + _yingXiangStartUpParam.soapPort + _yingXiangStartUpParam.soapUrl;
    std::stringstream url;
    url<<"?a="<<_queryParam.accountID<<"&db="<<_queryParam.targetDB<<"&q={\"token\":\"" << _yingXiangStartUpParam.soapNum << "\",\"who\":\"SHYK\",\"api\":\"queryVerify\",\"ver\":\"1\"}";
    printf("uri is: %s\n", uri.c_str());
    httpClient.InitData(uri.c_str(),REQUEST_POST_FLAG, const_cast<char *>(HTTP_CONTENT_TYPE_URL_ENCODED),url.str().c_str());
    httpClient.startHttpClient();
    if(!httpClient.ResponseData.empty())
    {
        LOG(SOAP,INFO,"queryLiuShuiHao : %s\n", httpClient.ResponseData.c_str());
        return AnalyseLshReturn(const_cast<char*>(httpClient.ResponseData.c_str()),*pVector);
    }
    return 0;
}


void _c_yingXiangSessionService::deRepeatLiuShuiHao(std::vector<std::string> *pVector, std::vector<std::string> *pNewVector)
{
    //此处去重需要先判断流水号是否重复，如果重复判断根据上次进入系统时间是否超过 _timeOutMilliseconds 设置的时间，超过则更新时间(updateInSystemTime())进入后续逻辑，否则丢弃
    pNewVector->clear();
    //遍历查询到的流水号
    for (unsigned int i = 0; i < pVector->size(); i++) {

        //是否重复的标记位
        bool isRepeat = false;
        //遍历已审核过的流水号
        LOG(COMMON,INFO,"_lshVector size is:%d\n",_lshVector.size());
        for (unsigned int j = 0; j < _lshVector.size(); j++) {
            //检测流水号是否相同
            if(_lshVector[j].check((*pVector)[i]))
            {
                //将是否重复标记位设置位true
                isRepeat = true;
                LOG(COMMON,INFO,"repeat lsh:%s\n",(*pVector)[i].c_str());
                //判断进入系统时间是否超时
                if(_lshVector[j].getInSystemTime() > _timeOutMilliseconds)
                {
                    LOG(COMMON,INFO,"timeOut lsh:%s\n",(*pVector)[i].c_str());
                    //已超时则更新进入系统时间
                    _lshVector[j].updateInSystemTime();
//                    pNewVector->push_back((*pVector)[i]);
                }
                break;
            }
        }

        //如果是新流水号则将流水号插入到已审核的流水号vector
        if(!isRepeat)
        {
            LOG(COMMON,INFO,"new lsh:%s\n",(*pVector)[i].c_str());
            lshVectorMember lsh_new((*pVector)[i]);
            _lshVector.push_back(lsh_new);
            pNewVector->push_back((*pVector)[i]);
        }
    }
}


bool _c_yingXiangSessionService::AnalyseVehicleReturn(char *pVehicleReturn, _c_yingXiangVehicle *pVehicle)
{
    Json::Reader reader;
    Json::Value valueRoot;
    if(!reader.parse(pVehicleReturn,valueRoot))
    {
        return false;
    }

    //读取参数
    string iRes = valueRoot["res"].asString();
    string msg = valueRoot["msg"].asString();
    string data = valueRoot["data"].toStyledString();
    Json::Value valueData;
    cout << data <<endl;
    if(!reader.parse(data,valueData))
    {
        return false;
    }

    pVehicle->liuShuiHao = valueData["lsh"].asString();
    pVehicle->haoPaiHaoMa = valueData["hphm"].asString();
    pVehicle->cheLiangShiBieDaiHao = valueData["clsbdh"].asString();
    pVehicle->cheLiangPinPaiZhongWen = valueData["clpp1"].asString();
    pVehicle->cheLiangXingHao = valueData["clxh"].asString();
    pVehicle->cheLiangPinPaiYingWen = valueData["clpp2"].asString();
    pVehicle->guoChanJinKou = valueData["gcjk"].asString();
    pVehicle->zhiZaoGuo = valueData["zzg"].asString();
    pVehicle->zhiZaoChangMingCheng = valueData["zzcmc"].asString();
    pVehicle->faDongJiHao = valueData["fdjh"].asString();
    pVehicle->cheLiangLeiXing = valueData["cllx"].asString();
    pVehicle->cheShenYanSe = valueData["csys"].asString();
    pVehicle->faZhengJiGuan = valueData["fzjg"].asString();
    pVehicle->guanLiBuMen = valueData["glbm"].asString();
    pVehicle->faHeGeZhengRiQi = valueData["fhgzrq"].asString();
    pVehicle->baoXianZhongZhiRiQi = valueData["bxzzrq"].asString();
    pVehicle->diYanBiaoJi = valueData["dybj"].asString();
    pVehicle->cheLiangLaiYuan = valueData["clly"].asString();
    pVehicle->faDongJiXingHao = valueData["fdjxh"].asString();
    pVehicle->ranLiangZhongLei = valueData["rlzl"].asString();
    pVehicle->shiFouXinNengYuanQiChe = valueData["sfxny"].asString();
    pVehicle->xinNengYuanZhongLei = valueData["xnyzl"].asString();
    pVehicle->paiLiang = valueData["pl"].asString();
    pVehicle->gongLv = valueData["gl"].asString();
    pVehicle->zhuanXiangXingShi = valueData["zxxs"].asString();
    pVehicle->cheWaiKuoChang = valueData["cwkc"].asString();
    pVehicle->cheWaiKuoKuan = valueData["cwkk"].asString();
    pVehicle->cheWaiKuoGao = valueData["cwkg"].asString();
    pVehicle->huoXiangNeiBuChangDu = valueData["hxnbcd"].asString();
    pVehicle->huoXiangNeiBuKuanDu = valueData["hxnbkd"].asString();
    pVehicle->huoXiangNeiBuGaoDu = valueData["hxnbgd"].asString();
    pVehicle->gangBanTanPianShu = valueData["gbthps"].asString();
    pVehicle->zhouShu = valueData["zs"].asString();
    pVehicle->zhouJu = valueData["zj"].asString();
    pVehicle->qianLunJu = valueData["qlj"].asString();
    pVehicle->houLunJu = valueData["hlj"].asString();
    pVehicle->lunTaiGuiGe = valueData["ltgg"].asString();
    pVehicle->lunTaiShu = valueData["lts"].asString();
    pVehicle->zongZhiLiang = valueData["zzl"].asString();
    pVehicle->zhengBeiZhiLiang = valueData["zbzl"].asString();
    pVehicle->heDingZaiZhiLiang = valueData["hdzzl"].asString();
    pVehicle->heDingZaiKe = valueData["hdzk"].asString();
    pVehicle->zhunQianYinZhiLiang = valueData["zqyzl"].asString();
    pVehicle->qianPaiZaiKe = valueData["qpzk"].asString();
    pVehicle->houPaiZaiKe = valueData["hpzk"].asString();
    pVehicle->bianHao = valueData["bh"].asString();
    pVehicle->diPanID = valueData["dpid"].asString();
    pVehicle->huanBaoDaBiaoQingKuang = valueData["hbdbqk"].asString();
    pVehicle->chuChangRiQi = valueData["ccrq"].asString();
    pVehicle->huoDeFangShi = valueData["hdfs"].asString();
    pVehicle->laiLiPingZheng1 = valueData["llpz1"].asString();
    pVehicle->pingZhengBianHao1 = valueData["pzbh1"].asString();
    pVehicle->laiLiPingZheng2 = valueData["llpz2"].asString();
    pVehicle->pingZhengBianHao2 = valueData["pzbh2"].asString();
    pVehicle->xiaoShouDanWei = valueData["xsdw"].asString();
    pVehicle->xiaoShouJiaGe = valueData["xsjg"].asString();
    pVehicle->xiaoShouRiQi = valueData["xsrq"].asString();
    pVehicle->jinKouPingZheng = valueData["jkpz"].asString();
    pVehicle->jinKouPingZhengHaoMa = valueData["jkpzhm"].asString();
    pVehicle->heGeZhengBianHao = valueData["hgzbh"].asString();
    pVehicle->naShuiZhengMing = valueData["nszm"].asString();
    pVehicle->naShuiZhengMingBianHao = valueData["nszmbh"].asString();
    pVehicle->xiangGuanZiLiao = valueData["xgzl"].asString();
    pVehicle->qianMoBianHao = valueData["qmbh"].asString();
    pVehicle->houMoBianHao = valueData["hmbh"].asString();
    pVehicle->baoXianPingZhengHao = valueData["bxpzh"].asString();
    pVehicle->baoXianJinEr = valueData["bxje"].asString();
    pVehicle->shengXiaoRiQi = valueData["sxrq"].asString();
    pVehicle->zhongZhiRiQi = valueData["zzrq"].asString();
    pVehicle->baoXianGongSi = valueData["bxgs"].asString();
    pVehicle->suoYouQuan = valueData["syq"].asString();
    pVehicle->shenFenZhengMingMingCheng = valueData["sfzmmc"].asString();
    pVehicle->shenFenZhengMingHaoMa = valueData["sfzmhm"].asString();
    pVehicle->suoYouRen = valueData["syr"].asString();
    pVehicle->shouJiHaoMa = valueData["sjhm"].asString();
    pVehicle->shiYongXingZhi = valueData["syxz"].asString();
    pVehicle->zhuSuoDiZhiXingZhengQuHua = valueData["zsxzqh"].asString();
    pVehicle->zhuSuoXiangXiDiZhi = valueData["zsxxdz"].asString();
    pVehicle->youZhengBianMa1 = valueData["yzbm1"].asString();
    pVehicle->lianXiDianHua = valueData["lxdh"].asString();
    pVehicle->zanZhuZheng = valueData["zzz"].asString();
    pVehicle->zanZhuXingZhengQuHua = valueData["zzxzqh"].asString();
    pVehicle->zanZhuXiangXiDiZhi = valueData["zzxxdz"].asString();
    pVehicle->youZhengBianMa2 = valueData["yzbm2"].asString();
    pVehicle->yeWuLeiXing = valueData["ywlx"].asString();
    pVehicle->yeWuYuanYin = valueData["ywyy"].asString();
    pVehicle->diPanHeGeZhengBianHao = valueData["dphgzbh"].asString();
    pVehicle->dianZiYouXiang = valueData["dzyx"].asString();
    pVehicle->zhongDianCheLiangXinXi = valueData["zdclxx"].asString();
    pVehicle->daiLiRenXingMing = valueData["dlrxm"].asString();
    pVehicle->daiLiRenShenFenZhengMingHaoMa = valueData["dlrsfzmhm"].asString();
    pVehicle->daiLiRenShouJiHaoMa = valueData["dlrsjhm"].asString();
    pVehicle->daiLiRenSuoShuDanWei = valueData["dlrssdw"].asString();
    pVehicle->JBRID = valueData["jbrid"].asString();
    pVehicle->JBR = valueData["jbr"].asString();
    pVehicle->shangPaiCheGuanSuo = valueData["spcgs"].asString();
    pVehicle->yuYueShangPaiShiJian = valueData["yyspsj"].asString();
    pVehicle->jiDongCheDongJiRenID = valueData["jdcdjrid"].asString();
    pVehicle->jiDongCheDongJiRenXingMing = valueData["jdcdjrxm"].asString();
    pVehicle->jiDongCheDongJiBuMen = valueData["jdcdjbm"].asString();
    pVehicle->jiDongCheDengJiShiJian = valueData["jdcdjsj"].asString();
    pVehicle->suoYouRenDengJiShiJian = valueData["syrdjsj"].asString();
    pVehicle->suoShuDanWei = valueData["ssdw"].asString();
    pVehicle->zhuangTai = valueData["zt"].asString();
    pVehicle->beiZhu = valueData["bz"].asString();
    pVehicle->chuanShuBiaoJi = valueData["csbj"].asString();
    pVehicle->jinKouPingZhengQianFaRiQi = valueData["jkpzqfrq"].asString();
    pVehicle->jiLuZhuangTai = valueData["jlzt"].asString();
    pVehicle->shenFenZhengMingYouXiaoQiShi = valueData["sfzmyxqs"].asString();
    pVehicle->shenFenZhengMingYouXiaoQiZhi = valueData["sfzmyxqz"].asString();
    pVehicle->haoPaiZhongLei = valueData["hpzl"].asString();
    pVehicle->shiFouZanZhuRenKou = valueData["sfzzrk"].asString();
    pVehicle->gengXinShiJian = valueData["gxsj"].asString();
    pVehicle->shiFouChangZhuRenKou = valueData["sfczrk"].asString();
    pVehicle->youHao = valueData["yh"].asString();
    pVehicle->zhouHe = valueData["zh"].asString();
    pVehicle->zaiZhiLiangLiYongXiShu = valueData["zzllyxs"].asString();
    pVehicle->banGuaCheAnZuoZuiDaYunXuZhiLiang = valueData["bgcazzdyxzzl"].asString();
    pVehicle->zuiGaoSheJiShiSu = valueData["zgsjss"].asString();
    pVehicle->cheLiangZhiZaoRiQi = valueData["clzzrq"].asString();
    pVehicle->shiFouDaiLi = valueData["sfdl"].asString();
    pVehicle->youJiDiZhi = valueData["yjdz"].asString();
    pVehicle->xuHao = valueData["xh"].asString();
    pVehicle->zhuHeTongHao = valueData["zhth"].asString();
    pVehicle->diYaHeTongHao = valueData["dyhth"].asString();
    pVehicle->diYaJinEr = valueData["dyje"].asString();
    pVehicle->diYaDengJiRiQi = valueData["dydjrq"].asString();
    pVehicle->diYaJingBanRen = valueData["dyjbr"].asString();
    pVehicle->diYaQuanRen = valueData["dyqr"].asString();
    pVehicle->diYaQuanRenShenFenZhengMingMingCheng = valueData["dyqrsfzmmc"].asString();
    pVehicle->diYaQuanRenShenFenZhengMingHaoMa = valueData["dyqrsfzmhm"].asString();
    pVehicle->diYaQuanRenXingZhengQuHua = valueData["dyqrxzqh"].asString();
    pVehicle->diYaQuanRenXiangXiDiZhi = valueData["dyqrxxdz"].asString();
    pVehicle->diYaQuanRenYouZhengBianMa = valueData["dyqryzbm"].asString();
    pVehicle->diYaQuanRenLianXiDianHua = valueData["dyqrlxdh"].asString();
    pVehicle->jieChuRiQi = valueData["jcqr"].asString();
    pVehicle->diYaGuanLiBuMen = valueData["dyglbm"].asString();
    pVehicle->jiLuSuoShuFuWuZhan = valueData["jlssfwz"].asString();
    pVehicle->jiLuSuoShuCheGuanSuo = valueData["jlsscgs"].asString();
//    string tuPian = valueData["tp"].toStyledString();
//    Json::Value tuPianValue;
//    if(!reader.parse(tuPian,tuPianValue))
//    {
//        return false;
//    }
//    for(size_t i = 0;i < tuPianValue.size();++i)
//    {
//        _c_photo* pfilePhotoInfo = new _c_photo();
//        pfilePhotoInfo->algCode = tuPianValue[i]["tplx"].asString();
//        pVehicle->zhaoPianClassVector.push_back(pfilePhotoInfo);
//        //pfilePhotoInfo->dbWork();
//    }
    string filePath = httpPath + getDangTianRiQi() + "/";
    if (CreatPath(filePath))
    {
        int count = getOraclePhoto(pVehicle);
        cout << "count is:" << count << endl;
    }
    return true;
}

std::string _c_yingXiangSessionService::getDangTianRiQi()
{
    std::string nowTime;
    time_t t = time(NULL);
    tm *st = localtime(&t);
    char tmpArray[64] = { 0 };
    sprintf(tmpArray, "%d-%02d-%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

    nowTime = tmpArray;

    return nowTime;
}

bool _c_yingXiangSessionService::CreatPath(string path)
{
    if(access(path.c_str(),F_OK)!=0)
    {
        if(mkdir(path.c_str(),S_IRWXU|S_IRWXG|S_IRWXO))
        {
            cout << "mkdir error:" << path << endl;
            return false;
        }
    }
    cout << path << endl;
    return true;
}

//读取数据库照片并保存到java web服务目录下
int _c_yingXiangSessionService::getOraclePhoto(_c_yingXiangVehicle *pVehicle)
{
    int count = 0;
//    const char *user = "JESSE";
//    const char *pwd = "456789";
//    const char *db = "192.168.20.51:1521/orcl";
    const char *user = _yingXiangStartUpParam.remoteIp.c_str();
    const char *pwd = _yingXiangStartUpParam.remotePort.c_str();
    const char *db = _yingXiangStartUpParam.soapPhotoUri.c_str();

    Occi_db_wrapper *occiObj = new Occi_db_wrapper(user, pwd, db);
    occiObj->initialize(true, "AL32UTF8", "AL32UTF8");

    std::cout << "wrapper create!" << std::endl;
    if (occiObj->connect() == false)
    {
        std::cout << "connect create failed!" << std::endl;
        return 0;
    }
    std::cout << "connect create successful!" << std::endl;

    std::string sql;
//    sql = "SELECT ZP FROM JESSE.YK_SCAN_IMG_TEST WHERE LSH = '202004230001' AND ZPZL = '0113'";
    sql = "SELECT * FROM JESSE.YK_SCAN_IMG_TEST WHERE LSH = '";//202004230001'";
    sql += pVehicle->liuShuiHao + "'";
    if (!(occiObj->createStatement(sql.c_str()) && occiObj->executeQuery()))
    {
        std::cout << "createStatement() or executeQuery() fail!" << std::endl;
        occiObj->disconnect();
        return 0;
    }
    while (occiObj->NotEndFetch())
    {
        unsigned int length;
        unsigned char *photo_buff = occiObj->getBlob(3, length);
        std::string photo_lx = occiObj->getString(2);
        if (photo_buff == NULL)
        {
            std::cout << "Photo blob data is NULL" << std::endl;
            break;
        }
        std::string photo_name;
        char tmpArray[128] = { 0 };
        sprintf(tmpArray, "%s_%s_%02d", pVehicle->liuShuiHao.c_str(), photo_lx.c_str(), count + 1);
        photo_name = tmpArray;
        std::string photo_path = httpPath + getDangTianRiQi() + "/" + photo_name;
        FILE *fp = std::fopen(photo_path.data(), "wb");
        if (fp)
        {
            std::fseek(fp, 0, SEEK_SET);
            std::fwrite(photo_buff, 1, length, fp);
            std::fflush(fp);
            std::fclose(fp);
            free(photo_buff);
            count++;
            _c_photo* pfilePhotoInfo = new _c_photo();
            pfilePhotoInfo->algCode = photo_lx;
            pfilePhotoInfo->photoUrl = "http://127.0.0.1:7000/yingxiang/" + getDangTianRiQi() + "/" + photo_name;
            pVehicle->zhaoPianClassVector.push_back(pfilePhotoInfo);
        }
    }
    std::cout << count << std::endl;
//    occiObj->terminateStatement();
//    occiObj->disconnect();
//    occiObj->finish();
    delete occiObj;
    return count;
}

//遍历文件夹
void _c_yingXiangSessionService::getDirs(std::string path, std::vector<std::string>& files)
{
    DIR *dir;
    struct dirent * ptr;
    std::string x, dirPath;
    dir = opendir((char *)path.c_str()); //打开一个目录
    while((ptr = readdir(dir)) != NULL) //循环读取目录数据
    {
        x = ptr->d_name;
        dirPath = path + "/" + x;
        printf("d_name : %s\n", dirPath.c_str()); //输出文件绝对路径
//        struct stat buf;
//        stat(dirPath.c_str(), &buf);
//        if (buf.st_mode == S_IFDIR)
        if(strcmp(".", ptr->d_name) == 0 || strcmp("..", ptr->d_name) == 0)
        {
            continue;
        }
        if (ptr->d_type == DT_DIR)
        {
            files.push_back(dirPath);
            printf("file_name : %s\n", dirPath.c_str());
        }
    }
    closedir(dir);//关闭目录指针
}

//判断文件夹是否需要删除
bool _c_yingXiangSessionService::isSevenDays(std::string cuCiDengJiRiQi)
{
    std::string djrq = cuCiDengJiRiQi;
    if (djrq == "")
    {
        return false;
    }
    printf("cuCiDengJiRiQi:%s\n",cuCiDengJiRiQi.c_str());
    int djrq_year = std::stoi(djrq.substr(0, 4));
    int djrq_month = std::stoi(djrq.substr(5, 2));
    int djrq_day = std::stoi(djrq.substr(8, 2));

    time_t t = time(NULL);
    tm *st = localtime(&t);

    /* 先判断年，年相同的情况下，判断月；月相同的情况下，判断日 */
    if ((st->tm_year + 1900 - djrq_year) > 0)
    {
        return true;
    }
    else if (((st->tm_mon + 1) - djrq_month) > 1)
    {
        return true;
    }
    else if (((st->tm_mon + 1) - djrq_month) == 1)
    {
        if (djrq_day < 23)
        {
            return true;
        }
        else if (st->tm_mday > 7)
        {
            return true;
        }
        else if ((st->tm_mday + 30 - djrq_day) > 7)
        {
            return true;
        }
    }
    else if ((st->tm_mon + 1) == djrq_month)
    {
        if (st->tm_mday - djrq_day > 7)
        {
            return true;
        }
    }
    return false;
}

//递归删除一个文件夹
int _c_yingXiangSessionService::remove_dir(const char *dir)
{
    char cur_dir[] = ".";
    char up_dir[] = "..";
    char dir_name[128];
    DIR *dirp;
    struct dirent *dp;
    struct stat dir_stat;

    // 参数传递进来的目录不存在，直接返回
    if ( 0 != access(dir, F_OK) ) {
        return 0;
    }

    // 获取目录属性失败，返回错误
    if ( 0 > stat(dir, &dir_stat) ) {
        perror("get directory stat error");
        return -1;
    }

    if ( S_ISREG(dir_stat.st_mode) )
    {	// 普通文件直接删除
        remove(dir);
    }
    else if ( S_ISDIR(dir_stat.st_mode) )
    {	// 目录文件，递归删除目录中内容
        dirp = opendir(dir);
        while ( (dp=readdir(dirp)) != NULL )
        {
            // 忽略 . 和 ..
            if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) )
            {
                continue;
            }

            sprintf(dir_name, "%s/%s", dir, dp->d_name);
            remove_dir(dir_name);   // 递归调用
        }
        closedir(dirp);

        rmdir(dir);		// 删除空目录
    }
    else
    {
        perror("unknow file type!");
    }
    return 0;
}

//遍历文件夹，判断哪些文件需要删除
void _c_yingXiangSessionService::delDirs()
{
    std::vector<std::string> files;
    getDirs(httpPath, files);
    printf("dir count is: %d\n", static_cast<int>(files.size()));
    std::string data;
    data = getDangTianRiQi();
    printf("%s\n", data.c_str());
    for(auto &p:files)
    {
        if(isSevenDays(p.substr(p.size() - 10)))
        {
            remove_dir(p.c_str());
            printf("delete %s\n", p.c_str());
        }
    }
}

_c_yingXiangVehicle * _c_yingXiangSessionService::queryVehicleInfo(std::string liuShuiHao)
{
    HttpClient httpClient;
//    std::string uri = "http://"+m_httpParam.remoteIp+":"+m_httpParam.remotePort+m_httpParam.uri;
    std::string uri = "http://"+_yingXiangStartUpParam.soapIp + ":" + _yingXiangStartUpParam.soapPort + _yingXiangStartUpParam.soapUrl;
    std::stringstream url;
    url << "?a=" << _queryParam.accountID << "&db="<< _queryParam.targetDB << "&q={\"token\":\"n\",\"who\":\"SHYK\",\"ver\":\"1\",\"api\":\"queryApprovalDetail\",\"lsh\":\"" << liuShuiHao << "\"}";
    httpClient.InitData(uri.c_str(),REQUEST_POST_FLAG, HTTP_CONTENT_TYPE_URL_ENCODED,url.str().c_str());
    httpClient.startHttpClient();

    _c_yingXiangVehicle *pVehicle = NULL;
    if(!httpClient.ResponseData.empty())
    {
        LOG(SOAP,INFO,"queryVehicleInfo : %s\n", httpClient.ResponseData.c_str());
        pVehicle = new _c_yingXiangVehicle();
        if(pVehicle!=NULL)
        {
            if(!AnalyseVehicleReturn(const_cast<char*>(httpClient.ResponseData.c_str()),pVehicle))
            {
                delete pVehicle;
                pVehicle = NULL;
            }
            pVehicle->javaFlat = "0";
        }
    }

    return pVehicle;
}

bool _c_yingXiangSessionService::deRepeatVehicleInfo(_c_yingXiangLshInfo &_VehicleInfo)
{
    uint16_t _oCrc16 = 0;
    uint16_t _nCrc16 = _VehicleInfo.getCheckKey();

    for (unsigned int i = 0; i < _yxLshInfoVector.size(); i++)
    {
        _oCrc16 = _yxLshInfoVector[i].getCheckKey();
        if (_nCrc16 == _oCrc16)
            return false;
    }

    //没有重复就返回true
    return true;
}

bool _c_yingXiangSessionService::vehicleSetDisposeEnd(_c_object *pObject)
{
    bool ret = false;
    //通过guid找到对应的_c_vehicleInfo,保存对应车辆的照片结果信息
    for (unsigned int i = 0; i < _yxLshInfoVector.size(); i++)
    {
        cout << "vector guid is:" << _yxLshInfoVector[i].getGuid() << endl;
        cout << "object uuid is:" << pObject->uuid << endl;
        if (_yxLshInfoVector[i].getGuid() == pObject->uuid)
        {
            LOG(COMMON,INFO,"locate vehicle with uuid: %s\n", _yxLshInfoVector[i].getGuid().c_str());
            _yxLshInfoVector[i].setDisposeEnd((_c_yingXiangVehicle *)pObject);
            ret = true;
            break;
        }
    }

    if (!ret){
        _c_yingXiangVehicle *_pVehicle = (_c_yingXiangVehicle *)pObject;
        LOG(COMMON,ERR,"vehicle %s[%s] __guid dismatch, set dispose failed\n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str());
    }

    return ret;
}

bool _c_yingXiangSessionService::repeatVehicleDisponse(_c_object *pObject)
{
    //根据_checkKey获取车辆相关PHOTO信息，写回pVehicle
    bool ret = false;
    _c_yingXiangVehicle *_pVehicle = (_c_yingXiangVehicle *)pObject;
    _c_yingXiangLshInfo _VehicleInfo(_pVehicle);
    for (unsigned int i = 0; i < _yxLshInfoVector.size(); i++)
    {
        if (_yxLshInfoVector[i].getCheckKey() == _VehicleInfo.getCheckKey())
        {
            LOG(COMMON,INFO,"get vehicle %s[%s] with keycode: 0x%x\n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str(),_yxLshInfoVector[i].getCheckKey());
            ret = _yxLshInfoVector[i].getVehiclePhotoInfo(_pVehicle);
            return ret;
        }
    }

    LOG(COMMON,ERR,"error :repetitive vehicle %s[%s] _checkKey dismatch! \n", _pVehicle->liuShuiHao.c_str(), _pVehicle->uuid.c_str());

    return ret;
}

void _c_yingXiangSessionService::freeUnusefulRepeatedVehicleInfo(_c_object *pObject)
{
     _c_yingXiangVehicle *pVehicle = (_c_yingXiangVehicle *)pObject;
     _c_photo *pPhoto = NULL;
     //先把原来的照片相关信息释放掉
     for (unsigned int i = 0; i < pVehicle->zhaoPianClassVector.size(); i++)
     {
         pPhoto = pVehicle->zhaoPianClassVector[i];
         if (pPhoto != NULL)
         {
             delete pPhoto;
             pPhoto = NULL;
         }
     }
     pVehicle->zhaoPianClassVector.clear();
}

void _c_yingXiangSessionService::clearCache()
{
    _lshVector.clear();
    _yxLshInfoVector.clear();
}


void _c_yingXiangSessionService::photoResultReply(const _c_yingXiangVehicle *p_vehicle)
{
    //数据段封装
    Json::Value value;
    value["token"] = "n";
    value["who"] = "SZLP";
    value["ver"] = "1";
    value["api"] = "autoVerifyApproval";
    value["lsh"] = p_vehicle->liuShuiHao;
    Json::Value shjg;
    for (unsigned int i = 0; i < p_vehicle->zhaoPianClassVector.size(); i++)
    {
        //图片数据结果赋值
//        p_vehicle->zhaoPianClassVector[i]->jieGuo = p_vehicle->zhaoPianClassVector[i]->result;
//        p_vehicle->zhaoPianClassVector[i]->shenMeYuanYin = p_vehicle->zhaoPianClassVector[i]->reason;

        {
            //返回结果赋值
            Json::Value shjgValue;
            shjgValue["tplx"] = p_vehicle->zhaoPianClassVector[i]->algCode;
            shjgValue["jg"] = p_vehicle->zhaoPianClassVector[i]->result;
            shjgValue["sm"] = p_vehicle->zhaoPianClassVector[i]->reason;
            shjg.append(shjgValue);
        }
    }
    value["shjg"] = shjg;

    //数据序列化并发送
    HttpClient httpClient;
    std::string uri = "http://" + _yingXiangStartUpParam.soapIp + ":" + _yingXiangStartUpParam.soapPort + _yingXiangStartUpParam.soapUrl;
    Json::FastWriter writer;
    std::string strSend = writer.write(value);
    std::string url;
    url = "?a=123&db=TEST1&q=" + strSend;
    httpClient.InitData(uri.c_str(),REQUEST_POST_FLAG, const_cast<char *>(HTTP_CONTENT_TYPE_URL_ENCODED),url.c_str());
    httpClient.startHttpClient();

    LOG(SOAP,INFO,"The result json message has been send: \n %s---------------------\n",url.c_str());

}
