#include "AsyncAssistantCallback.h"
#include "globe.h"
#include "LogComm.h"
#include "RouterServer.h"

AsyncAssistantCallback::AsyncAssistantCallback(const unsigned int iUid): m_iUid(iUid)
{
    m_createTime = TNOWMS;
}

AsyncAssistantCallback::~AsyncAssistantCallback()
{

}

void AsyncAssistantCallback::callback_reportUserOnlineStatus(tars::Int32 ret)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    if (ret == 0)
    {
        ROLLLOG_DEBUG << "|" << m_iUid << "|" << "report user status success" << endl;
    }
    else
    {
        ROLLLOG_ERROR << "|" << m_iUid << "|" << "report user status error" << endl;
    }
}

void AsyncAssistantCallback::callback_reportUserOnlineStatus_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "|" << m_iUid << "|" << ret << "|" << "report user status" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

// 查询沉迷状态
void AsyncAssistantCallback::callback_getUserOverPlayStatus(tars::Int32 ret, const assistant::GetUserOverPlayStatusResp &resp)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    if (ret == 0)
    {
        //ROLLLOG_DEBUG << "|" << m_iUid << "|" << "check addict user success" << endl;
#if 0
        //获取是否已经有连接记录
        ConnStructPtr cs = g_connMap.getCurrent(m_iUid);
        if (cs && cs->current)
        {
            //组包
            JFGameClientProto::TPackage tPack;
            tPack.stUid.lUid = (long)m_iUid;

            JFGameClientProto::TMsgHead mh;
            mh.nMsgID = JFGameClientProto::E_MSGID_ADDICT__NOTIFY;
            mh.nMsgType = JFGameClientProto::MSGTYPE_RESPONSE;
            tPack.vecMsgHead.push_back(mh);

            JFGameClientProto::TMsgRespAddict rsp;
            rsp.iOverPlayStatus = resp.overPlayStatus;
            vector<char> vecData;
            tobuffer(rsp, vecData);
            tPack.vecMsgData.push_back(vecData);

            // for test
            //ROLLLOG_DEBUG << "|" << m_iUid << "|" << "send addict user to client tPkg:" << printTars(tPack) << endl;

            //编码
            vector<char> vecOutBuffer;
            CRouterHelper::Encode(cs, tPack, vecOutBuffer, true);
            cs->current->sendResponse(vecOutBuffer.data(), vecOutBuffer.size());
        }
#endif
    }
    else
    {
        ROLLLOG_ERROR << "|" << m_iUid << "|" << "check addict user error." << endl;
    }
}

void AsyncAssistantCallback::callback_getUserOverPlayStatus_exception(tars::Int32 ret)
{
    ROLLLOG_ERROR << "|" << m_iUid << "|" << ret << "|" << "check addict user." << endl;
}
