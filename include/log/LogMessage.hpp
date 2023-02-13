#ifndef __LOG_MESSAGE_H__
#define __LOG_MESSAGE_H__
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "LogCommon.hpp"

namespace async
{
    class LogMessage
    {
    private:
        std::string m_Header; // [时间戳];[日志级别];[文件名称];[函数名称];[行号]
        std::string m_HeaderWithColor;
        std::string m_text; // 正文信息
        LOG_LEVEL m_level;

    public:
        LOG_LEVEL getLogLevel() const;
        std::string FillHeader(LOG_LEVEL level, const string &filename, const string &funcname, int linenumber, bool colored);
    public:
        //              [日志级别];[文件名称];[函数名称];[行号]
        LogMessage(LOG_LEVEL level, const string &filename, const string &funcname, int linenumber);
        const string toString() const;
        const string toStringWithColor() const;

        // 格式化颜色
        std::string formatFieldWithColor(COLOR_NUMBER colorNumber, bool dark,
                                         const std::string delimiter, const std::string fieldName, bool colored);
        //  添加正文信息
        template <typename T>
        LogMessage &operator<<(const T &text)
        {
            stringstream ss;
            ss << " : " << text;
            m_text += ss.str();
            return *this;
        }
    };
}

#endif
