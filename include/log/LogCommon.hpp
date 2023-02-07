

#ifndef __LOGCOMMON_H
#define __LOGCOMMON_H

#include <unordered_map>
namespace tulun
{
    class copyable
    {
    };

    class nocopyable
    {
    public:
        nocopyable(const nocopyable &) = delete;
        nocopyable &operator=(const nocopyable &) = delete;

    public:
        nocopyable() {}
        ~nocopyable() {}
    };

    static const int SMALL_BUF_LEN = 128;
    static const int MEDIAN_BUF_LEN = 512;
    static const int LARGE_BUF_LEN = 1024;

    enum class LOG_LEVEL
    {
        TRACE = 0,      // 跟踪，追踪
        DEBUG,          // 调试
        INFO,           // 信息
        WARN,           // 警告
        ERROR,          // 错误
        FATAL,          // 致命错误
        NUM_LOG_LEVELS, // 日志级别数
    };

    static const char *LLtoStr[] =
        {
            "TRACE", // 0
            "DEBUG", // 1
            "INFO",
            "WARN",
            "ERROR",
            "FATAL",
            "NUM_LOG_LEVELS",
    };

    enum COLOR_NUMBER
    {
        DEFAULT_COLOR = 0,
        INFO_COLOR = 36,
        ERROR_COLOR = 35,
        DEBUG_COLOR = 32,
        FATAL_COLOR = 31,
        LINE_COLOR = 32,
        FUNCTION_COLOR = 34,
        FILE_COLOR = 35,
    };

    enum LOG_FEILD
    {
        LINE_NUMBER = 0,
        FUNCTION_NAME,
        FILE_NAME
    };

    // unordered_map hash表 存取  查找时间复杂度O(1)
    // 这张表表示的 日志级别到对应颜色的映射关系
    static std::unordered_map<LOG_LEVEL, COLOR_NUMBER> LogLevelColor = {
        {tulun::LOG_LEVEL::INFO, INFO_COLOR},
        {tulun::LOG_LEVEL::ERROR, ERROR_COLOR},
        {tulun::LOG_LEVEL::DEBUG, DEBUG_COLOR},
        {tulun::LOG_LEVEL::FATAL, FATAL_COLOR}};

    // 这张表表示的 字段(file function line)到对应颜色的映射关系
    static std::unordered_map<LOG_FEILD, COLOR_NUMBER> LogFeildColor = {
        {LINE_NUMBER, LINE_COLOR},
        {FUNCTION_NAME, FUNCTION_COLOR},
        {FILE_NAME, FILE_COLOR}};

}
#endif