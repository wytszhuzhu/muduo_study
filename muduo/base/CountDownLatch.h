#pragma once

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"
#include <boost/core/noncopyable.hpp>
#include <boost/noncopyable.hpp>

namespace muduo {
    class CountDownLatch : boost::noncopyable  {
    public:
        explicit CountDownLatch(int count);

        void wait();

        void countDown();

        int getCount() const;

    private:
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;
    };
}
