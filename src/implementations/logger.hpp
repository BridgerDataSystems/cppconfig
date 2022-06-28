#pragma once

#ifndef __H_LOGGER_CPPCONFIG__
#define __H_LOGGER_CPPCONFIG__

#include <ICPPLogger.hpp>

static __N_CPPLOGGER__::ICPPLogger* g_logger{ nullptr };

#define CHECKLOGGER	    if (g_logger) if (g_logger->IsInitialized())

#define TRACELOG(...)   CHECKLOGGER { g_logger->log(__N_CPPLOGGER__::SEVERITY_TRACE     , __VA_ARGS__); }
#define INFOLOG(...)    CHECKLOGGER { g_logger->log(__N_CPPLOGGER__::SEVERITY_INFO      , __VA_ARGS__); }
#define DEBUGLOG(...)   CHECKLOGGER { g_logger->log(__N_CPPLOGGER__::SEVERITY_DEBUG     , __VA_ARGS__); }
#define WARNLOG(...)    CHECKLOGGER { g_logger->log(__N_CPPLOGGER__::SEVERITY_WARNING   , __VA_ARGS__); }
#define ERRORLOG(...)   CHECKLOGGER { g_logger->log(__N_CPPLOGGER__::SEVERITY_ERROR     , __VA_ARGS__); }
#define FATALLOG(...)   CHECKLOGGER { g_logger->log(__N_CPPLOGGER__::SEVERITY_FATAL     , __VA_ARGS__); }

#endif // !__H_LOGGER_CPPCONFIG__
