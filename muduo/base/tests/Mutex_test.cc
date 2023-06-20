////
//// Created by hugging on 2023/6/19.
////
#include <vector>
#include "muduo/base/Mutex.h"
#include "muduo/base/Thread.h"
#include "muduo/base/Timestamp.h"
#include <functional>
#include <memory>
#include <stdio.h>

using namespace muduo;
using namespace std;

MutexLock g_mutex;
vector<int> g_vec;
const int kCount = 10 * 1000 * 1000;

void ThreadFunc() {
    for (int i = 0; i < kCount; i++) {
        MutexLockGuard lock(g_mutex);
        g_vec.push_back(i);
    }
}

int main() {
    const int kMaxThreads = 8;
    g_vec.reserve(kMaxThreads * kCount);

    Timestamp start(Timestamp::now());
    for (int i = 0; i < kCount; i++) {
        g_vec.push_back(i);
    }

    printf("single thread without lock %f\n", timeDifference(Timestamp::now(), start));

    start = Timestamp::now();
    ThreadFunc();
    printf("single thread with lock %f\n", timeDifference(Timestamp::now(), start));

    for (int nthreads = 1; nthreads < kMaxThreads; ++nthreads) {
        vector<std::unique_ptr<Thread>> threads;
        g_vec.clear();
        start = Timestamp::now();
        for (int i = 0; i < nthreads; i++) {
            threads.emplace_back(new Thread(&ThreadFunc));
            threads.back()->start();
        }
        for (int i = 0; i < nthreads; i++) {
            threads[i]->join();
        }
        printf("%d thread(s) with lock %f\n", nthreads, timeDifference(Timestamp::now(), start));
    }
}




