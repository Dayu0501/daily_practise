#ifndef _C_SESSIONCENTER_H
#define _C_SESSIONCENTER_H
#include "base/baseInc.h"
#include "base/dataCenter.h"
#include "base/_c_session.h"
#include "alg/_c_algTaskCenter.h"

#define OUTOFLICENCE "智能审核系统已到期，请联系售后人员"

class _c_sessionCenter{
public:
    _c_sessionCenter(_c_algTaskCenter *pAlgTaskCenter);
    //启动会话管理线程
    bool stratSessionCenter();
    //查询待管理会话数据
    bool queryData();
    //检测会话状态
    bool checkSession();
    //检测是否关闭
    bool isClose();
    //校验license是否过期 true未过期，false过期
    bool checkLicense();

    void handleLicenseOutOfDate(_c_session *pSession);

    threadInfo *getSessionCenterThread() {return &SessionCenterThread;}
    threadInfo *getSessionCheckThread() {return &SessionCheckThread;}
private:
//    std::thread *_pSessionCenterThread;
//    std::thread *_pSessionCheckThread;
    threadInfo SessionCenterThread;
    threadInfo SessionCheckThread;

    _c_algTaskCenter *_pAlgTaskCenter;
	std::string _curWorkDate{""};
	bool _licenseOk{false};
};

#endif // _C_SESSIONCENTER_H
