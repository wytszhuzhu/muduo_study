#pragma once

#include <muduo/base/Types.h>
#include <exception>

/* 自定义异常类 https://blog.csdn.net/xiaoguyin_/article/details/79845079

 C++函数声明后面加throw()的作用！https://blog.csdn.net/to_baidu/article/details/53763683
 throw()不能抛出异常 , throw(int) 只能抛出指定类型异常 throw(...)可以抛出任何异常 */
 
namespace muduo {
    class Exception : public  std::exception {
        public:
        explicit Exception(const char* what) ;
        explicit Exception(const string& what);
        virtual ~Exception() throw();
        virtual const char* what() const throw(); // 替换 const noexcept
        const char* stackTrace() const throw();

        private:
        void fillStackTrace();
        string demangle(const char* symbol);

        string message_;
        string stack_;
    };
}

