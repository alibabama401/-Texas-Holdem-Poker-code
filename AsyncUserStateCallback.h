#ifndef _ASYNC_USER_STATE_CB_H_
#define _ASYNC_USER_STATE_CB_H_

#include "HallServant.h"
#include "OuterFactoryImp.h"

//
using namespace hall;

/**
* 更新用户状态
*/
class AsyncUserStateCallback : public HallServantPrxCallback
{
public:
    AsyncUserStateCallback(long uid);
    ~AsyncUserStateCallback();

public:
    //
    void callback_RouterUserState(tars::Int32 ret,  const hall::RouterUserStateResp &resp);
    //
    void callback_RouterUserState_exception(tars::Int32 ret);

private:
    //用户标识
    long uid;
    //创建时间
    int64_t m_createTime;
};

#endif


