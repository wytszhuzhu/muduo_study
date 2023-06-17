#include "muduo/base/Thread.h"
#include "muduo/base/CurrentThread.h"
#include "muduo/base/Exception.h"

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>


namespace muduo 
{
namespace CurrentThread
{
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread const char* t_threadName = "unknown";
    const bool sameType = std::is_same_v<int, pid_t>;
    BOOST_STATIC_ASSERT(sameType);
}

namespace detail
{
    // 线程真实ID
    pid_t gettid() {   
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }

    void afterFork() {
        muduo::CurrentThread::t_cachedTid = 0;
        muduo::CurrentThread::t_threadName = "main";
        CurrentThread::tid();
         // no need to call pthread_atfork(NULL, NULL, &afterFork);
    }

    class ThreadNameInitializer {
        public:
        ThreadNameInitializer() {
            muduo::CurrentThread::t_threadName = "main";
            CurrentThread::tid();
            pthread_atfork(NULL, NULL, &afterFork);
        }
    };
    ThreadNameInitializer init;
}
}

using namespace muduo;

void CurrentThread::cacheTid() {
    if (t_cachedTid == 0) {
        t_cachedTid = detail::gettid();
        int n = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid); // %5d + 一个空格 = 6
        assert(n == 6); (void) n;
    }
}

bool CurrentThread::isMainThread() {
    return tid() == ::getpid();
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(const ThreadFunc& func, const string& n)
: started_(0),
  pthreadId_(0),
  tid_(0),
  func_(func),
  name_(n)
 {
    numCreated_.increment();
}

Thread::~Thread() {

}

void Thread::start() {
    assert(!started_);
    started_ = true;
    errno = pthread_create(&pthreadId_, NULL, &startThread, this);
    if (errno != 0) {
         //LOG_SYSFATAL << "Failed in pthread_create";
    }
}

int Thread::join() {
    assert(started_);
    return pthread_join(pthreadId_, NULL);
}

void* Thread::startThread(void* obj) {
    Thread* thread = static_cast<Thread*>(obj);
    thread->runInThread();
    return NULL;
}

void Thread::runInThread() {
    tid_ = CurrentThread::tid();
    muduo::CurrentThread::t_threadName = name_.c_str();
    try {
        func_();
        muduo::CurrentThread::t_threadName = "finished";
    }
    catch (const Exception& ex)
  {
    muduo::CurrentThread::t_threadName = "crashed";
    fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
    fprintf(stderr, "reason: %s\n", ex.what());
    fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
    abort();
  }
  catch (const std::exception& ex)
  {
    muduo::CurrentThread::t_threadName = "crashed";
    fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
    fprintf(stderr, "reason: %s\n", ex.what());
    abort();
  }
  catch (...)
  {
    muduo::CurrentThread::t_threadName = "crashed";
    fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
    throw; // rethrow
  }
}