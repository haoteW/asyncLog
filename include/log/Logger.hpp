
#ifndef _LOGGER_H_
#define _LOGGER_H_
//C++
#include<functional> // function
#include<string>
using namespace std;

//own
#include"LogCommon.hpp"
#include "LogMessage.hpp"

namespace async
{

class Logger
{
public:
    // using OutputFunc = void (*)(const char *msg,int len);
    // using FlushFunc = void(*)();
    using OutputFunc = std::function< void (const std::string &msg) >;
    using FlushFunc =  std::function<void()>;
    static OutputFunc output_;
    static FlushFunc  flush_;
public:
   static void setOutput(OutputFunc);
   static void setFlush(FlushFunc);
private:
    LogMessage impl_;         
     // 日志级别
public:
    // [日志级别];[文件名称];[函数名称];[行号]  
    Logger(async::LOG_LEVEL level,const string &name,const string &func,const int line);
    ~Logger();
    LogMessage & stream();
    static void setLogLevel(LOG_LEVEL level);
    static LOG_LEVEL getLogLevel();
private:
    static LOG_LEVEL s_level_;
};  

//日志屏蔽
#define LOG(LEVEL) if(async::Logger::getLogLevel()<= async::LOG_LEVEL::LEVEL) \
    async::Logger(async::LOG_LEVEL::LEVEL,__FILE__,__func__,__LINE__).stream()

#define LOG_WARN LOG(WARN)
#define LOG_FATAL LOG(FATAL)
#define LOG_INFO LOG(INFO)
#define LOG_DEBUG LOG(DEBUG)
#define LOG_TRACE LOG(TRACE)

//#define LOG_FATAL async::Logger(async::LOG_LEVEL::FATAL,__FILE__,__func__,__LINE__).stream()



}
#endif 