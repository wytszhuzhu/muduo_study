//
// Created by hugging on 2023/6/20.
//

#pragma once

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"
#include "boost/noncopyable.hpp"
#include <deque>
#include <assert.h>

namespace muduo {
    template<typename T>
    class BlockingQueue : boost::noncopyable {
    public:
        BlockingQueue()
        : mutex_(), notEmpty_(mutex_), queue_() {

        }

        void put(const T& x) {
            MutexLockGuard lock(mutex_);
            queue_.push_back(x);
            notEmpty_.notify();
        }

        void put(T&& x) {
            MutexLockGuard lock(mutex_);
            queue_.push_back(std::move(x));
            notEmpty_.notify();
        }

        T take() {
            MutexLockGuard lock(mutex_);
            while (queue_.empty()) {
                notEmpty_.wait();
            }
            assert(!queue_.empty());
            T front(std::move(queue_.front()));
            queue_.pop_front();
            return front;
        }

        size_t size() const {
            MutexLockGuard locK(mutex_);
            return queue_.size();
        }

    private:
        mutable MutexLock mutex_;
        Condition notEmpty_;
        std::deque<T> queue_;
    };
}



