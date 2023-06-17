#pragma once

/*__thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。
__thread变量每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。
简单来说，就是每个用该修饰符修饰的变量在每个线程中都会有存在。*/


namespace muduo {
namespace CurrentThread {
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread const char* t_threadName;
    void cacheTid();

    inline int tid() {
        if (t_cachedTid == 0) {
            cacheTid();
        }
        return t_cachedTid;
    }

    inline const char* tidString() {
        return t_tidString;
    }

    inline const char* name() {
        return t_threadName;
    }

    bool isMainThread();
}
}