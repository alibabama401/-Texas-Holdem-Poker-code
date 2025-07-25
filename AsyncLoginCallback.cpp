#include "AsyncLoginCallback.h"
#include "globe.h"
#include "LogComm.h"
#include "RouterServer.h"
#include "push.pb.h"

AsyncLoginCallback::AsyncLoginCallback(const XGameComm::TPackage &pkg, const CheckLoginTokenReq &req, const ConnStructPtr old)
    : tPkg(pkg), reqData(req), csOld(old)
{
    m_createTime = TNOWMS;
}

AsyncLoginCallback::~AsyncLoginCallback()
{

}

//
void AsyncLoginCallback::callback_checkLoginToken(tars::Int32 ret, const login::CheckLoginTokenResp &resp)
{
    int64_t iCostTime = TNOWMS - m_createTime;
    if (iCostTime > COST_MS)
    {
        ROLLLOG_WARN << "@iCostTime: " << iCostTime << endl;
    }

    if (csOld && csOld->current)
    {
        //推送登录广场成功消息
        XGameComm::TPackage t;
        t.set_iversion(tPkg.iversion());
        t.set_igameid(tPkg.igameid());
        t.set_sroomid(tPkg.sroomid());
        t.set_iroomserverid(tPkg.iroomserverid());

        auto ptuid = t.mutable_stuid();
        ptuid->set_luid(tPkg.stuid().luid());
        ptuid->set_stoken(tPkg.stuid().stoken());
        t.set_isequence(tPkg.isequence());
        t.set_iflag(tPkg.iflag());
        t.clear_vecmsghead();
        t.clear_vecmsgdata();

        auto mh = t.add_vecmsghead();
        mh->set_nmsgid(XGameComm::Eum_Comm_Msgid::E_MSGID_LOGIN_HALL_RESP);
        mh->set_nmsgtype(XGameComm::MSGTYPE::MSGTYPE_RESPONSE);

        XGameComm::TMsgRespLoginHall rspLoginHall;
        rspLoginHall.set_iresultid(ret);
        t.add_vecmsgdata(pbToString(rspLoginHall));

        string sMsgPack;
        CRouterHelper::Encode(t, sMsgPack);
        csOld->current->sendResponse(sMsgPack.c_str(), sMsgPack.length());
    }

    ROLLLOG_DEBUG << "----------->LoginSvr@RouterSvr result, uid: " << reqData.lUid << ", ret: " << ret << endl;

    if (ret == 0)
    {
        //记录连接映射
        if (csOld && csOld->current)
        {
            //用户映射关系
            csOld->iLoginTime = TNOW;
            csOld->tLastActiveTime = TNOW;
            g_app.SetUidToClientIDMap(csOld->current->getUId(), csOld->lUserId);
            g_connMap.update(csOld->lUserId, csOld);

            //通知@用户在线状态
            g_app.getOutPtr()->asyncRequest2PushUserState(reqData.lUid, csOld->current->getUId(), true);
            //用户上线通知@广场服
            g_app.getOutPtr()->asyncRequest2HallUserState(reqData.lUid, true);
        }
        else
        {
            if (csOld)
            {
                csOld->iLoginTime = 0;
                csOld->tLastActiveTime = 0;
            }

            LOG_WARN << "fatal error, uid: " << reqData.lUid  << ", csOld: " << csOld << endl;
        }
    }
    else
    {
        //断开用户连接
        if (csOld && csOld->current)
        {
            csOld->current->close();
        }
    }
}

void AsyncLoginCallback::callback_checkLoginToken_exception(tars::Int32 ret)
{
    if (csOld->current)
    {
        csOld->current->close();
    }

    ROLLLOG_ERROR << "|" << reqData.lUid << "|" << reqData.sToken << "|" << ret << "|" << endl;
}
