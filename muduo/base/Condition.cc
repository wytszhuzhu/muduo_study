#include "muduo/base/Condition.h"


#include <errno.h>
#include <pthread.h>

// returns true if time out, false otherwise. 指定时间没有获得mutex，返回ETIMEDOUT
bool muduo::Condition::waitForSeconds(int seconds) {
    timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += seconds;
    return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);
}