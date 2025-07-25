#include "AsyncUserStateCallback.h"
#include "RouterServer.h"
#include "globe.h"
#include "LogComm.h"

//
using namespace JFGame;

AsyncUserStateCallback::AsyncUserStateCallback(long uid): uid(uid)
{
    m_createTime = TNOWMS;
}

AsyncUserStateCallback::~AsyncUserStateCallback()
{

}

void AsyncUserStateCallback::callback_RouterUserState(tars::Int32 ret,  const hall::RouterUserStateResp &resp)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    if (ret == 0)
    {
        auto cs = g_connMap.getCurrent(uid);
        if (cs && cs->current)
        {
            if (resp.state == 1)//上线
            {
                cs->stUser.deviceID = resp.deviceID;
                cs->stUser.deviceType = resp.deviceType;
                cs->stUser.platform = resp.platform;
                cs->stUser.channnelID = resp.channnelID;
                cs->stUser.areaID = resp.areaID;
                cs->stUser.isRobot = resp.isRobot;
            }
            else//下线
            {

            }
        }

        ROLLLOG_DEBUG << "router user state ok, uid: " << uid << ", resp: " << printTars(resp) << endl;
    }
    else
    {
        ROLLLOG_DEBUG << "router user state err, uid: " << uid << ", ret: " << ret << endl;
    }
}

void AsyncUserStateCallback::callback_RouterUserState_exception(tars::Int32 ret)
{
    ROLLLOG_DEBUG << "router user state exception, uid: " << uid << ", ret: " << ret << endl;
}