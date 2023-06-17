#pragma once

#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace muduo {

    namespace detail {
        template<typename T>
        class AtomicIntergerT : boost::noncopyable {
            public:
                AtomicIntergerT() : value_(0) {}
                //  // 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回操作之前*ptr的值
                T get() {
                    return __sync_val_compare_and_swap(&value_, 0, 0);  
                }
                // 将x的值加到value_,并返回value_的旧值
                T getAndAdd(T x) {
                    return __sync_fetch_and_add(&value_, x);
                }

                T addAndGet(T x) {
                    return getAndAdd(x) + x;
                }

                T incrementAndGet() {
                    return addAndGet(1);
                }

                T decrementAndGet() {
                    return addAndGet(-1);
                }

                void add(T x) {
                    getAndAdd(x);
                }

                void increment() {
                    incrementAndGet();
                }

                void decrement() {
                    return decrementAndGet();
                }
                //  将valnewvalueue写入value_，对value_加锁，并返回操作之前value_的值。即，try spinlock语义
                T getAndSet(T newvalue) {
                    return __sync_lock_test_and_set(&value_, newvalue);
                }

            private:
            volatile T value_;
        };
    }
    using AtomicInt32 = detail::AtomicIntergerT<int32_t>;
    using AtomicInt64 = detail::AtomicIntergerT<int64_t>;
}