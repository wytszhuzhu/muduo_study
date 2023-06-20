////
//// Created by hugging on 2023/6/19.
////
//
//#pragma once
//
//#include "muduo/base/CurrentThread.h"
//#include "boost/noncopyable.hpp"
//#include <assert.h>
//#include <boost/core/noncopyable.hpp>
//#include <mutex>
//#include <pthread.h>
//
//namespace muduo {
//    class MutexLock : boost::noncopyable {
//    public:
//        MutexLock() : holder_(0) {
//            int ret = pthread_mutex_init(&mutex_, NULL);
//            assert(ret == 0); (void) ret;
//        }
//
//        ~MutexLock() {
//            assert(holder_ == 0);
//            int ret = pthread_mutex_destroy(&mutex_);
//            assert(ret == 0); (void) ret;
//        }
//        // holder_要么等于0， 要么被锁住了，等于锁住的线程的tid
//        bool isLockedByThisThread() {
//            return holder_ == CurrentThread::tid();
//        }
//        // 其作用是先计算表达式expression的值为假(即为0),那么它就先向stderr打印一条出错信息，然后通过条用abort来终止程序
//        void assertLocked() {
//            assert(isLockedByThisThread());
//        }
//
//        void lock() {
//            pthread_mutex_lock(&mutex_);
//            holder_ = CurrentThread::tid();
//        }
//
//        void unlock() {
//            holder_ = 0;
//            pthread_mutex_unlock(&mutex_);
//        }
//
//        pthread_mutex_t* getPthreadMutex() {
//            return &mutex_;
//        }
//
//
//    private:
//        pthread_mutex_t mutex_;
//        pid_t holder_;
//    };
//
//    class MutexLockGuard : boost::noncopyable {
//    public:
//        explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex){
//            mutex_.lock();
//        }
//
//        ~MutexLockGuard() {
//            mutex_.unlock();
//        }
//
//    private:
//        MutexLock& mutex_;
//    };
//}

// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_MUTEX_H
#define MUDUO_BASE_MUTEX_H

#include <muduo/base/CurrentThread.h>
#include <boost/noncopyable.hpp>
#include <assert.h>
#include <pthread.h>

namespace muduo
{

    class MutexLock : boost::noncopyable
    {
    public:
        MutexLock()
                : holder_(0)
        {
            int ret = pthread_mutex_init(&mutex_, NULL);
            assert(ret == 0); (void) ret;
        }

        ~MutexLock()
        {
            assert(holder_ == 0);
            int ret = pthread_mutex_destroy(&mutex_);
            assert(ret == 0); (void) ret;
        }

        bool isLockedByThisThread()
        {
            return holder_ == CurrentThread::tid();
        }

        void assertLocked()
        {
            assert(isLockedByThisThread());
        }

        // internal usage

        void lock()
        {
            pthread_mutex_lock(&mutex_);
            holder_ = CurrentThread::tid();
        }

        void unlock()
        {
            holder_ = 0;
            pthread_mutex_unlock(&mutex_);
        }

        pthread_mutex_t* getPthreadMutex() /* non-const */
        {
            return &mutex_;
        }

    private:

        pthread_mutex_t mutex_;
        pid_t holder_;
    };

    class MutexLockGuard : boost::noncopyable
    {
    public:
        explicit MutexLockGuard(MutexLock& mutex)
                : mutex_(mutex)
        {
            mutex_.lock();
        }

        ~MutexLockGuard()
        {
            mutex_.unlock();
        }

    private:

        MutexLock& mutex_;
    };

}

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

#endif  // MUDUO_BASE_MUTEX_H
