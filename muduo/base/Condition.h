#pragma once

#include "muduo/base/Mutex.h"
#include "boost/noncopyable.hpp"
#include <boost/core/noncopyable.hpp>
#include <pthread.h>

namespace muduo {
    class Condition : boost::noncopyable {
    public:
        explicit Condition(MutexLock& mutex) : mutex_(mutex) {
            pthread_cond_init(&pcond_, NULL);
        }

        ~Condition() {
            pthread_cond_destroy(&pcond_);
        }
        /* 一个或多个线程等待某个布尔表达式为真，即等待别的线程“唤醒”它。条件变量的学名叫管程（monitor）。
         * Java Object内置的wait()、notify()、notifyAll()是条件变量。
         * 条件变量，等待某个谓词成立，发射信号，必须先锁住，然后wait会解锁(别的线程可以使用mutex), 返回时解锁*/
        void wait() {
            pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
        }

        bool waitForSeconds(int seconds);

        void notify() {
            pthread_cond_signal(&pcond_);
        }

        void notifyAll() {
            pthread_cond_broadcast(&pcond_);
        }
    private:
        MutexLock& mutex_;
        pthread_cond_t pcond_;
    };
}