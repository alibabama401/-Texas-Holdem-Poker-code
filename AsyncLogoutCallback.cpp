#include "AsyncLogoutCallback.h"
#include "globe.h"
#include "LogComm.h"
#include "RouterServer.h"
#include "push.pb.h"

AsyncLogoutCallback::AsyncLogoutCallback(const UserLogoutReq &req) : reqData(req)
{
    m_createTime = TNOWMS;
}

AsyncLogoutCallback::~AsyncLogoutCallback()
{

}

void AsyncLogoutCallback::callback_Logout(tars::Int32 ret, const login::UserLogoutResp &resp)
{
    ROLLLOG_DEBUG << "|" << reqData.uid << "|" << reqData.sRemoteIP << "|" << ret << "|" << endl;
}

void AsyncLogoutCallback::callback_Logout_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "|" << reqData.uid << "|" << reqData.sRemoteIP << "|" << ret << "|" << endl;
}
