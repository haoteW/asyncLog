

#include "LogCommon.hpp"
#include "LogMessage.hpp"
#include "Timestamp.hpp"
#include <sstream>
using namespace std;
namespace tulun
{

    // std::string Header;   // [时间戳];[日志级别];[文件名称];[函数名称];[行号]
    // std::string m_text;  // 正文信息

    //              [日志级别];[文件名称];[函数名称];[行号]
    LogMessage::LogMessage(LOG_LEVEL level, const string &filename, const string &funcname, int linenumber)
        : m_level(level),
        m_Header(FillHeader(level, filename, funcname, linenumber, false)),
        m_HeaderWithColor(FillHeader(level, filename, funcname, linenumber, true))
    {
    }

    std::string LogMessage::FillHeader(LOG_LEVEL level, const string &filename, const string &funcname, int linenumber, bool colored)
    {
        std::string fileName = filename;
        int pos = 0;
        for (int i = fileName.length() - 1; i >= 0; --i)
        {
            if (fileName[i] == '/')
            {
                pos = i;
                break;
            }
        }
        fileName = fileName.substr(pos + 1, fileName.length() - pos);
        std::stringstream ss;
        ss << formatFieldWithColor(DEFAULT_COLOR, 0, "", MicroTimestamp::now().toFormattedString() , colored);

        COLOR_NUMBER logColorNumber = LogLevelColor[level];
        std::string logLevelType = LLtoStr[static_cast<int>(level)];
        ss << formatFieldWithColor(logColorNumber, 1, "", "[" + logLevelType + "]", colored);
        // 文件名称
        COLOR_NUMBER fileColor = LogFeildColor[FILE_NAME];
        ss << formatFieldWithColor(fileColor, 1, "", "[" + fileName + "]", colored);

        // 函数名称
        COLOR_NUMBER functionColor = LogFeildColor[FUNCTION_NAME];
        ss << formatFieldWithColor(functionColor, 1, "", "[" + funcname + "]", colored);

        // 行号
        COLOR_NUMBER lineColor = LogFeildColor[LINE_NUMBER];
        ss << formatFieldWithColor(lineColor, 1, " : ", "[" + std::to_string(linenumber) + "]", colored);
        
        return ss.str();
    }

    // 格式化颜色
    std::string LogMessage::formatFieldWithColor(COLOR_NUMBER colorNumber, bool dark, const std::string delimiter, const std::string fieldName, bool colored)
    {
        std::stringstream ss;
        if (colored)
        {
            ss << "\033[" << dark << ";" << colorNumber << "m";
        }
        ss << fieldName; // 重置属性
        if (colored)
        {
            ss << "\033[0m";
        }
        ss << delimiter;

        return ss.str();
    }
    const string LogMessage::toStringWithColor() const
    {
        return m_HeaderWithColor + m_text;
    }
    const string LogMessage::toString() const
    {
        return m_Header + m_text;
    }

    LOG_LEVEL LogMessage::getLogLevel() const
    {
        return m_level;
    }

}