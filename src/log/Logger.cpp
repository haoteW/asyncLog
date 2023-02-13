
#include "Logger.hpp"
#include "LogCommon.hpp"
#include "AsyncLogging.hpp"

namespace async
{

    async::LOG_LEVEL initLogLevel()
    {
        if (::getenv("async::LOG_TRACE"))
        {
            return async::LOG_LEVEL::TRACE;
        }
        else if (::getenv("async::LOG_DEBUG"))
        {
            return LOG_LEVEL::DEBUG;
        }
        else
        {
            return async::LOG_LEVEL::INFO;
        }
    }

    void defaultOutput(const string &msg)
    {
        size_t n = fwrite(msg.c_str(), 1, msg.size(), stdout);
    }
    void defaultFlush()
    {
        fflush(stdout);
    }
    Logger::OutputFunc Logger::output_ = defaultOutput;
    Logger::FlushFunc Logger::flush_ = defaultFlush;

    void Logger::setOutput(OutputFunc out)
    {
        output_ = out;
    }
    void Logger::setFlush(FlushFunc flush)
    {
        flush_ = flush;
    }

    // [日志级别];[文件名称];[函数名称];[行号]
    Logger::Logger(async::LOG_LEVEL level,
                   const string &filename,
                   const string &funcname,
                   const int line)
        : impl_(level, filename, funcname, line)
    {
    }
    Logger::~Logger()
    {
        impl_ << "\n";
        output_(impl_.toString());
        cout << impl_.toStringWithColor();
        if (impl_.getLogLevel() == LOG_LEVEL::FATAL)
        {
            flush_();
            fprintf(stderr, "Process exit");
            exit(1);
            // abort();
        }
    }

    LogMessage &Logger::stream()
    {
        return impl_;
    }

    void Logger::setLogLevel(LOG_LEVEL level)
    {
        s_level_ = level;
    }
    LOG_LEVEL Logger::getLogLevel()
    {
        return s_level_;
    }

    void writefile(const string &info)
    {
        AsyncLogging::GetInstance()->append(info);
    }
    void flushfile()
    {
        AsyncLogging::GetInstance()->flush();
    }


    LOG_LEVEL Logger::s_level_ = initLogLevel();  // 日志级别
}