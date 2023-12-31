#include "muduo/base/Exception.h"

#include <cxxabi.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdio.h>

using namespace muduo;

Exception::Exception(const char* msg)
: message_(msg)
 {
    fillStackTrace();
}

Exception::Exception(const string& msg)
  : message_(msg)
{
   fillStackTrace();
}

Exception::~Exception() throw() {

}

const char* Exception::what() const throw() {
    return message_.c_str();
}

const char* Exception::stackTrace() const throw()
{
  return stack_.c_str();
}

void Exception::fillStackTrace()
{
  const int len = 200;
  void* buffer[len];
  int nptrs = ::backtrace(buffer, len);  // 栈回溯，保存各个栈帧的地址;buffer这个指针指向了一个数组，数组中的每一项都是void *类型，用来保存函数的地址
  char** strings = ::backtrace_symbols(buffer, nptrs);// 根据地址，转成相应的函数符号； 返回的是指针的指针；
  if (strings)
  {
    for (int i = 0; i < nptrs; ++i)
    {
      // TODO demangle funcion name with abi::__cxa_demangle
      //stack_.append(strings[i]);
	  stack_.append(demangle(strings[i]));
      stack_.push_back('\n');
    }
    free(strings);
  }
}

string Exception::demangle(const char* symbol)
{
  size_t size;
  int status;
  char temp[128];
  char* demangled;
  //first, try to demangle a c++ name
  if (1 == sscanf(symbol, "%*[^(]%*[^_]%127[^)+]", temp)) {
    if (NULL != (demangled = abi::__cxa_demangle(temp, NULL, &size, &status))) {
      string result(demangled);
      free(demangled);
      return result;
    }
  }
  //if that didn't work, try to get a regular c symbol
  if (1 == sscanf(symbol, "%127s", temp)) {
    return temp;
  }
 
  //if all else fails, just return the symbol
  return symbol;
}


