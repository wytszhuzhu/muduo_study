#pragma once

#include <stdint.h>
#include <string>
#include <string.h>

#ifndef NDEBUG
#include <assert.h>
#endif


//  reason of cast https://blog.csdn.net/xiaoC_fantasy/article/details/79570788
namespace muduo {
    using std::string;

    inline void memZero(void *p, size_t n) {
        memset(p, 0, n);
    }

    template<typename to, typename from>
    inline to implicit_cast(from const &f) {
        return f;
    }

    template<typename to, typename from>
    inline to down_cast(from* f) {
        if (false) {
            implicit_cast<from*, to>(0);
        }

        #if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
        assert(f == NULL || dynamic_cast<to>(f) != NULL); // null可以转型, 如果dynamic转型为null则代表不能转型，断言失败
        #endif
        return static_cast<to>(f);
    }
}