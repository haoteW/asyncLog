
#include "Logger.hpp"
#include "LogCommon.hpp"

namespace tulun
{
void defaultOutput(const string &msg)
{
    size_t n = fwrite(msg.c_str(),1,msg.size(),stdout);
    
}
void defaultFlush()
{
    fflush(stdout);
}
Logger::OutputFunc Logger::output_ = defaultOutput;
Logger::FlushFunc  Logger::flush_ = defaultFlush;

void Logger::setOutput(OutputFunc out)
{
    output_ = out;
}
void Logger::setFlush(FlushFunc flush)
{
    flush_ = flush;
}
        
// [日志级别];[文件名称];[函数名称];[行号]  
Logger::Logger(tulun::LOG_LEVEL level,
                const string &filename,
                const string &funcname,
                const int line)
    :impl_(level,filename,funcname,line)
{
}
Logger::~Logger()
{
    impl_<<"\n";
    output_(impl_.toStringWithColor());
    if(impl_.getLogLevel() == LOG_LEVEL::FATAL)
    {
        flush_();
        fprintf(stderr,"Process exit");
        exit(1);
        //abort();
    }
}

LogMessage & Logger::stream()
{
    return impl_;
}


void Logger::setLogLevel(LOG_LEVEL level)
{
    s_level_ = level;
}
LOG_LEVEL Logger::getLogLevel()
{
    return  s_level_;
}
    
LOG_LEVEL Logger::s_level_ = LOG_LEVEL::INFO;  // 日志级别

}