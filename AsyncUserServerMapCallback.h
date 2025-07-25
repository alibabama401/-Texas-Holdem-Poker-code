#ifndef _ASYNC_USER_SERVER_MAP_CB_H_
#define _ASYNC_USER_SERVER_MAP_CB_H_

#include "UserServerMapServant.h"
#include "OuterFactoryImp.h"

//
using namespace JFGame;
using namespace userservermap;

/**
* 查询用户房间标识
*
*/
class AsyncUserServerMapCallback : public UserServerMapPrxCallback
{
public:
    AsyncUserServerMapCallback();
    ~AsyncUserServerMapCallback();

public:
    //
    AsyncUserServerMapCallback(const userservermap::OnlineReq &onlineReq);
    //
    AsyncUserServerMapCallback(const userservermap::OfflineReq &onfflineReq);
    //
    AsyncUserServerMapCallback(const userservermap::GetRoomStatusOfUserReq &getRoomStatusOfUserReq);

public:
    //
    virtual void callback_getRoomStatusOfUser(tars::Int32 ret,  const userservermap::GetRoomStatusOfUserResp &resp);
    //
    virtual void callback_getRoomStatusOfUser_exception(tars::Int32 ret);
    //
    virtual void callback_offline(tars::Int32 ret);
    //
    virtual void callback_offline_exception(tars::Int32 ret);
    //
    virtual void callback_online(tars::Int32 ret);
    //
    virtual void callback_online_exception(tars::Int32 ret);

private:
    //
    userservermap::OnlineReq onlineReq;
    //
    userservermap::OfflineReq onfflineReq;
    //
    userservermap::GetRoomStatusOfUserReq getRoomStatusOfUserReq;
    //
    int64_t m_createTime;
};

#endif


