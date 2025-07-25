#include "AsyncUserServerMapCallback.h"
#include "globe.h"
#include "LogComm.h"

//
using namespace JFGame;

AsyncUserServerMapCallback::AsyncUserServerMapCallback()
{
    m_createTime = TNOWMS;
}

AsyncUserServerMapCallback::~AsyncUserServerMapCallback()
{

}

AsyncUserServerMapCallback::AsyncUserServerMapCallback(const userservermap::OnlineReq &onlineReq): onlineReq(onlineReq)
{
    m_createTime = TNOWMS;
}

AsyncUserServerMapCallback::AsyncUserServerMapCallback(const userservermap::OfflineReq &onfflineReq): onfflineReq(onfflineReq)
{
    m_createTime = TNOWMS;
}

AsyncUserServerMapCallback::AsyncUserServerMapCallback(const userservermap::GetRoomStatusOfUserReq &getRoomStatusOfUserReq) : getRoomStatusOfUserReq(getRoomStatusOfUserReq)
{
    m_createTime = TNOWMS;
}

void AsyncUserServerMapCallback::callback_getRoomStatusOfUser(tars::Int32 ret,  const userservermap::GetRoomStatusOfUserResp &resp)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    ROLLLOG_DEBUG << "|" << getRoomStatusOfUserReq.uid << "|" << resp.roomId << "|" << resp.roomKey << "|" << ret << endl;
}

void AsyncUserServerMapCallback::callback_getRoomStatusOfUser_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "|" << getRoomStatusOfUserReq.uid << "|" << ret << endl;
}

void AsyncUserServerMapCallback::callback_offline(tars::Int32 ret)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    ROLLLOG_DEBUG << "|" << onfflineReq.uid << "|" << ret << endl;
}

void AsyncUserServerMapCallback::callback_offline_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "|" << onfflineReq.uid << "|" << ret << endl;
}

void AsyncUserServerMapCallback::callback_online(tars::Int32 ret)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    ROLLLOG_DEBUG << "|" << onlineReq.uid << "|" << ret << endl;
}

void AsyncUserServerMapCallback::callback_online_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "|" << onlineReq.uid << "|" << ret << endl;
}

