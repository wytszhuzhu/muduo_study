#pragma once

#include "muduo/base/Atomic.h"
#include "muduo/base/Types.h"
#include <functional>
#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace muduo {

class Thread : boost::noncopyable {
    public:
    using ThreadFunc = std::function<void ()>;
    
    explicit Thread(const ThreadFunc&, const string& name = string());
    ~Thread();

    void start();
    int join();

    bool started() const {return started_;}
    pid_t tid() const {return tid_;}
    const string& name() const {return name_;}

    static int numCreated() {return numCreated_.get();}

    private:
    static void* startThread(void* thread);
    void runInThread();

    bool started_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    string name_;

    static AtomicInt32 numCreated_;
};


}

