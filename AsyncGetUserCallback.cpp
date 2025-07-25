#include "AsyncGetUserCallback.h"
#include "RouterServer.h"
#include "globe.h"
#include "LogComm.h"

//
using namespace JFGame;

AsyncGetUserCallback::AsyncGetUserCallback(long uid): uid(uid)
{
    m_createTime = TNOWMS;
}

AsyncGetUserCallback::~AsyncGetUserCallback()
{

}

void AsyncGetUserCallback::callback_getUser(tars::Int32 ret, const userinfo::GetUserResp &resp)
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
            cs->stUser.deviceID = resp.deviceID;
            cs->stUser.deviceType = resp.deviceType;
            cs->stUser.platform = resp.platform;
            cs->stUser.channnelID = resp.channnelID;
            cs->stUser.areaID = resp.areaID;
            cs->stUser.isRobot = resp.isRobot;
        }

        ROLLLOG_DEBUG << "get user ok, uid: " << uid << ", resp: " << printTars(resp) << endl;
    }
    else
    {
        ROLLLOG_DEBUG << "get user err, uid: " << uid << ", ret: " << ret << endl;
    }
}

void AsyncGetUserCallback::callback_getUser_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "get user exception, uid: " << uid << ", ret: " << ret << endl;
}