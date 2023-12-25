/**
 * @Author: Yunkai Xia
 * @Date:   2022-11-18 11:04:43
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-22 18:41:31
 */
#pragma once

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no color needed
#include <spdlog/spdlog.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

static inline int NowDateToInt()
{
  time_t now;
  time(&now);

  // choose thread save version in each platform
  tm p;
#ifdef _WIN32
  localtime_s(&p, &now);
#else
  localtime_r(&now, &p);
#endif // _WIN32
  int now_date = (1900 + p.tm_year) * 10000 + (p.tm_mon + 1) * 100 + p.tm_mday;
  return now_date;
}

static inline int NowTimeToInt()
{
  time_t now;
  time(&now);
  // choose thread save version in each platform
  tm p;
#ifdef _WIN32
  localtime_s(&p, &now);
#else
  localtime_r(&now, &p);
#endif // _WIN32

  int now_int = p.tm_hour * 10000 + p.tm_min * 100 + p.tm_sec;
  return now_int;
}

template <typename T> // T表示任何可以被cout输出的类型
static inline void ColorCout_256(T t, const int ForeColor = 7,
                                 const int BackColor = 0)
{
  // ForeColor和BackColor的取值区间为[0,255]
  std::cout << "\033["
            << "38;5;" << ForeColor << "m";
  std::cout << "\033["
            << "48;5;" << BackColor << "m";
  std::cout << t << "\033[m";
}

class XLogger
{
public:
  static XLogger *getInstance()
  {
    static XLogger xlogger;
    return &xlogger;
  }
  bool getInitFlag() { return initedFlag_; }

  std::shared_ptr<spdlog::logger> getLogger() { return logger_; }
  bool init(std::string log_dir, std::string logger_name_prefix,
            std::string XLog_level = "debug", bool is_log_console = false)
  {
    if (initedFlag_)
    {
      return true;
    }
    std::string level = XLog_level;

    try
    {
      // logger name with timestamp
      int date = NowDateToInt();
      int time = NowTimeToInt();
      const std::string logger_name = logger_name_prefix +
                                      std::to_string(date) + "_" +
                                      std::to_string(time);

      if (is_log_console)
        logger_ = spdlog::stdout_color_mt(
            logger_name); // single thread console output faster
      else
        logger_ = spdlog::create_async<spdlog::sinks::rotating_file_sink_mt>(
            logger_name, log_dir + "/" + logger_name + ".log",
            500 * 1024 * 1024, 1000);
      logger_->set_pattern(
          "%Y-%m-%d %H:%M:%S [%l] [%s %#] %v"); // with timestamp,
                                                // filename and line number

      if (level == "trace")
      {
        logger_->set_level(spdlog::level::trace);
        logger_->flush_on(spdlog::level::trace);
      }
      else if (level == "debug")
      {
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::debug);
      }
      else if (level == "info")
      {
        logger_->set_level(spdlog::level::info);
        logger_->flush_on(spdlog::level::info);
      }
      else if (level == "warn")
      {
        logger_->set_level(spdlog::level::warn);
        logger_->flush_on(spdlog::level::warn);
      }
      else if (level == "error")
      {
        logger_->set_level(spdlog::level::err);
        logger_->flush_on(spdlog::level::err);
      }
      else
      {
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::debug);
      }
      initedFlag_ = true;
    }
    catch (const spdlog::spdlog_ex &ex)
    {
      std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
    return true;
  }

private:
  // make constructor private to avoid outside instance
  XLogger() = default;

  ~XLogger()
  {
    spdlog::drop_all(); // must do this
  }

  XLogger(const XLogger &) = delete;
  XLogger &operator=(const XLogger &) = delete;

private:
  std::shared_ptr<spdlog::logger> logger_;
  bool initedFlag_ = false;
};

// use embedded macro to support file and line number
// 涉及原始数据打印，最底层硬件相关
#define XLOG_TRACE(...)                                         \
  SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), \
                     spdlog::level::trace, __VA_ARGS__)
// 经过程序解算过程输出的，解算后数据打印
#define XLOG_DEBUG(...)                                         \
  SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), \
                     spdlog::level::debug, __VA_ARGS__)
// 程序运行过程，执行状态和执行流程打印
#define XLOG_INFO(...)                                          \
  SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), \
                     spdlog::level::info, __VA_ARGS__)
// 运行过程中抛出不致命异常时，一般为可恢复异常时的打印
#define XLOG_WARN(...)                                          \
  SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), \
                     spdlog::level::warn, __VA_ARGS__)
// 导致程序不能继续运行的问题输出打印
#define XLOG_ERROR(...)                                         \
  SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), \
                     spdlog::level::err, __VA_ARGS__)
