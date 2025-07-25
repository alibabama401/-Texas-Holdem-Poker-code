#ifndef _ASYNC_GET_USER_CB_H_
#define _ASYNC_GET_USER_CB_H_

#include "HallServant.h"
#include "OuterFactoryImp.h"

//
using namespace hall;

/**
* 查询账户信息
*/
class AsyncGetUserCallback : public HallServantPrxCallback
{
public:
    AsyncGetUserCallback(long uid);
    ~AsyncGetUserCallback();

public:
    //
    void callback_getUser(tars::Int32 ret, const userinfo::GetUserResp &resp);
    //
    void callback_getUser_exception(tars::Int32 ret);

private:
    //用户标识
    unsigned long uid;
    //创建时间
    int64_t m_createTime;
};

#endif


