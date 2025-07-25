#ifndef _ASYNC_LOGIN_CB_H_
#define _ASYNC_LOGIN_CB_H_

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
* Login验证
*/
class AsyncLoginCallback : public LoginServantPrxCallback
{
public:
    AsyncLoginCallback(const XGameComm::TPackage &pkg, const CheckLoginTokenReq &req, const ConnStructPtr old);
    ~AsyncLoginCallback();

public:
    //
    void callback_checkLoginToken(tars::Int32 ret, const login::CheckLoginTokenResp &resp);
    //
    void callback_checkLoginToken_exception(tars::Int32 ret);

private:
    //包头信息
    XGameComm::TPackage tPkg;
    //请求数据
    CheckLoginTokenReq reqData;
    //已有连接对象
    ConnStructPtr csOld;
    //创建时间
    int64_t m_createTime;
};

#endif


