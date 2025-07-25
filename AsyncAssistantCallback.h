#ifndef _ASYNC_ASSISTANT_CB_H_
#define _ASYNC_ASSISTANT_CB_H_

#include "AssistantServant.h"
#include "AssistantProto.h"
#include "OuterFactoryImp.h"

//
using namespace JFGame;
using namespace assistant;

/**
* 防沉迷
*/
class AsyncAssistantCallback : public AssistantPrxCallback
{
public:
    AsyncAssistantCallback(const unsigned int iUid);
    ~AsyncAssistantCallback();

public:
    //
    void callback_reportUserOnlineStatus(tars::Int32 ret);
    //
    void callback_reportUserOnlineStatus_exception(tars::Int32 ret);
    //
    void callback_getUserOverPlayStatus(tars::Int32 ret, const assistant::GetUserOverPlayStatusResp &resp);
    //
    void callback_getUserOverPlayStatus_exception(tars::Int32 ret);

private:
    //用户标识
    unsigned int m_iUid;
    //创建时间
    int64_t m_createTime;
};

#endif


