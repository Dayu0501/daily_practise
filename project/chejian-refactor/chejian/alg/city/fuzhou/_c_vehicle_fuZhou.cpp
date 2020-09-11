#include "_c_vehicle_fuZhou.h"
#include "alg/_c_algTaskCenter.h"

#ifdef OCCI_MODULE
#include "base/occi/occi_db_wrapper.h"
#endif


bool _c_vehicle_fuZhou::subLoadAlgTask() {

#if 0
    _c_photo *ph{nullptr};
    _c_photo *ph1{nullptr};
    for (auto item : algTaskVector) {
        if (!item) {
            printf("********** subLoadAlgTask item is null !\n");

            continue;
        }
		
		

        if (item->algCode == "0351") {
            ph = new _c_photo();
            ph->algCode = "0320";
            ph->algName = "0320";

            if (videoCheckInfo.isNeedLoadVideoInfo)
                loadVehicleVideoInfo();
            else
                videoCheckInfo.shiPinDownloadIsFinished = true;

            ph->loadUuid();
            ph->photoUrl = item->photoUrl;
            ph->cheLiangUid = uuid;
            ph->algTaskInit();

            ph->localPath = "/"+baseTool::getDangTianRiQi()+"/"+ ph->algName;
            ph->localPath += "_"+ haoPaiHaoMa;
            ph->localPath += "_"+ cheLiangShiBieDaiHao;
            ph->pVideoCheckInfo = &videoCheckInfo;
        } else if (item->algCode == "0110") {
            ph1 = new _c_photo();
            ph1->algCode = "0325";
            ph1->algName = "0325";

            if (videoCheckInfo.isNeedLoadVideoInfo)
                loadVehicleVideoInfo();
            else
                videoCheckInfo.shiPinDownloadIsFinished = true;
				
            ph1->loadUuid();
            ph1->photoUrl = item->photoUrl;
            ph1->cheLiangUid = uuid;
            ph1->algTaskInit();
			
            ph1->localPath = "/"+baseTool::getDangTianRiQi()+"/"+ ph1->algName;
            ph1->localPath += "_"+ haoPaiHaoMa;
            ph1->localPath += "_"+ cheLiangShiBieDaiHao;
            ph1->pVideoCheckInfo = &videoCheckInfo;
        }
    }
    if (ph) {
            algTaskVector.push_back(ph);
            zhaoPianClassVector.push_back(ph);
        }
		
    if (ph1) {
        algTaskVector.push_back(ph1);
        zhaoPianClassVector.push_back(ph1);
    }

#endif

#ifdef OCCI_MODULE


	printf("88888888888888 chepaihao is %s, chejianhao is %s \n", haoPaiHaoMa.c_str(), cheLiangShiBieDaiHao.c_str());
	
	string username{"JESSE"};                        //�û���
	string password{"456789"};                        //����
	string connstring{"192.168.20.51:1521/orcl"};    //�����ַ���
	
	std::cout << "aaaaaaaaaaaaaaaa" << std::endl;
	Occi_db_wrapper dbObj = Occi_db_wrapper(username.c_str(), password.c_str(), connstring.c_str());
	Occi_db_wrapper::initialize(true, "AL32UTF8", "AL32UTF8");
	
	std::cout << "0000000000000000000" << std::endl;
	
	if (!dbObj.connect()) {
		cout << "connect create failed!" << endl;
		
    return true;
	}
	
	cout << "connect create successful!" << endl;
	
	string strSelect{"select TYMZP from NAN WHERE ID = 4"};
	if (!(dbObj.createStatement(strSelect.c_str()) && dbObj.executeQuery())) {
		std::cout << "createStatement() or executeQuery() fail!" << std::endl;
		dbObj.disconnect();
		return true;
	}
	
	std::cout << "11111111111111111" << std::endl;
	
	while (dbObj.NotEndFetch()) {
		unsigned int len;
		unsigned char *photo_buff = dbObj.getBlob(1, len);
		
		std::cout << "22222222222" << std::endl;
		if (photo_buff == nullptr) {
			std::cout << "Photo blob data is NULL" << std::endl;
			break;
		}
		
		std::cout << "3333333333333" << std::endl;
		
		_c_photo *ph2{nullptr};
		ph2 = new _c_photo();
		ph2->algCode = "J";
		ph2->algName = "J";
		
		
		string dir{"/home/fuzhou/localpicweb/"};
		string fileName =  ph2->algCode + "_" + haoPaiHaoMa + "_" + cheLiangShiBieDaiHao;
		string localPath = baseTool::fun_write_new_file(dir, fileName, photo_buff, len);
		
		cout << "local Path is " << localPath << endl;
		
		ph2->loadUuid();
		ph2->photoUrl = std::string("http://127.0.0.1:8080/localpicweb/") + baseTool::getDangTianRiQi() + "/" + fileName;
		ph2->cheLiangUid = uuid;
		ph2->algTaskInit();
		
		ph2->localPath = "/" + baseTool::getDangTianRiQi() + "/" + ph2->algName;
		ph2->localPath += "_" + haoPaiHaoMa;
		ph2->localPath += "_" + cheLiangShiBieDaiHao;
		ph2->pVideoCheckInfo = &videoCheckInfo;
		
		algTaskVector.push_back(ph2);
		zhaoPianClassVector.push_back(ph2);
	}
#endif

	return true;
}
