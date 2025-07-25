#ifndef _ASYNC_LOGOUT_CB_H_
#define _ASYNC_LOGOUT_CB_H_

#include "LoginServant.h"
#include "LoginProto.h"

//
#include "servant/Application.h"
#include "OuterFactoryImp.h"

//
using namespace tars;
using namespace JFGame;
using namespace login;

/**
* Logout验证
*/
class AsyncLogoutCallback : public LoginServantPrxCallback
{
public:
    AsyncLogoutCallback(const UserLogoutReq &req);
    ~AsyncLogoutCallback();

public:
    //
    void callback_Logout(tars::Int32 ret, const login::UserLogoutResp &resp);
    //
    void callback_Logout_exception(tars::Int32 ret);

private:
    //请求数据
    UserLogoutReq reqData;
    //创建时间
    int64_t m_createTime;
};

#endif


