#ifndef _ASYNCLOGGING_H_
#define _ASYNCLOGGING_H_
#include <atomic>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>
using namespace std;
// own
#include "noncopyable.hpp"
#include "CountDownLatch.hpp"
#include "LogFile.hpp"

namespace async
{
    class LogFile;
    class CountDownLatch;

    class AsyncLogging : noncopyable
    {
    private:
        AsyncLogging(const string &basename, size_t rollSize, int flushInterval = 3);

    public:
        static AsyncLogging *GetInstance()
        {
            static AsyncLogging Logger("async", 1024 * 10 * 64);
            return &Logger;
        }
    private:
        // 内置类信息
        LogFile output_;       // 定义日志文件对象
        CountDownLatch latch_; // 同步启动器
        const size_t rollSize_;       // 滚动大小
        const int flushInterval_;     // 定期（flushInterval_秒）将缓冲区的数据写到文件中  默认3
    private:
        // 线程控制
        std::unique_ptr<std::thread> pthread_; // 执行该异步日志记录器的线程
        void workthreadfunc();                 // 工作线程
        std::mutex mutex_;                     //
        std::condition_variable cond_;         //
    private:
        // 自身参数及数据信息
        std::atomic<bool> running_;        // 是否正在运行
        const string basename_;            // 日志filename名字
        std::string currentBuffer_;        // 当前的缓冲区
        std::vector<std::string> buffers_; // 数据缓冲区队列
    public:
        ~AsyncLogging();
        void append(const string &info);
        void append(const char *info, int len);
        void start();
        void stop();
        void flush();
    };
}
#endif