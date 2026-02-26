#include <memory>
#include <string>
#include <cpplog.hpp>

#include "log.h"
#include "prop.h"

static std::unique_ptr<cpplog::FileLogger> m_pLog;

std::string WideCharToMultiByteConvenience(const WCHAR wstr[])
{
    int sizeInBytes = WideCharToMultiByte(CP_UTF8,
                                          0,
                                          wstr,
                                          -1,
                                          NULL,
                                          0, NULL, NULL);
    std::string str;
    str.resize(sizeInBytes);
    (void)WideCharToMultiByte(CP_UTF8,
                              0,
                              wstr,
                              -1,
                              &(str[0]),
                              sizeInBytes, NULL, NULL);
    return str;
}

void logStart(void)
{
    m_pLog = NULL;

    std::string logName = WideCharToMultiByteConvenience(LOGNAME);
    m_pLog = std::make_unique<cpplog::FileLogger>(logName);
}

void logStop(void)
{
    if (NULL != m_pLog)
    {
        m_pLog.reset();
    }
}

void logTrace(const WCHAR wmsg[])
{
    if (NULL == m_pLog)
    {
        return;
    }

    std::string msg = WideCharToMultiByteConvenience(wmsg);
    LOG_TRACE(*(m_pLog)) << msg << std::endl;
}

void logDebug(const WCHAR wmsg[])
{
    if (NULL == m_pLog)
    {
        return;
    }

    std::string msg = WideCharToMultiByteConvenience(wmsg);
    LOG_DEBUG(*(m_pLog)) << msg << std::endl;
}

void logInfo(const WCHAR wmsg[])
{
    if (NULL == m_pLog)
    {
        return;
    }

    std::string msg = WideCharToMultiByteConvenience(wmsg);
    LOG_INFO(*(m_pLog)) << msg << std::endl;
}

void logWarn(const WCHAR wmsg[])
{
    if (NULL == m_pLog)
    {
        return;
    }

    std::string msg = WideCharToMultiByteConvenience(wmsg);
    LOG_WARN(*(m_pLog)) << msg << std::endl;
}

void logError(const WCHAR wmsg[])
{
    if (NULL == m_pLog)
    {
        return;
    }

    std::string msg = WideCharToMultiByteConvenience(wmsg);
    LOG_ERROR(*(m_pLog)) << msg << std::endl;
}

void logFatal(const WCHAR wmsg[])
{
    if (NULL == m_pLog)
    {
        return;
    }

    std::string msg = WideCharToMultiByteConvenience(wmsg);
    LOG_FATAL(*(m_pLog)) << msg << std::endl;
}
