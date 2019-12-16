#pragma once
#ifndef TIMER_H
#define TIMER_H

//#define WITH_TIMER
//#define WITH_LOG_INFO

#include <atomic>
#include <boost/lockfree/queue.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <vector>

namespace tmr {

class Printable {
 public:
  virtual std::ostream& print(std::ostream& str) const = 0;
  virtual ~Printable() {}
};

class Logger {
 public:
  static Logger& instance() {
    static Logger logger;
    return logger;
  }

  void addData(const Printable* data) {
    mtx_.lock();
    data_list_.push_back(data);
    mtx_.unlock();
  }

  void printStat(std::ostream& out) {
#if defined(WITH_TIMER)
    out << std::setw(16) << "id"
        << "\t|\t" << std::setw(16) << "count"
        << "\t|\t" << std::setw(16) << "time"
        << "\t|\t" << std::setw(16) << "time / count" << std::endl;
#elif defined(WITH_LOG_INFO)
    out << std::setw(16) << "id"
        << "\t|\t" << std::setw(16) << "name"
        << "\t|\t" << std::setw(64) << "file"
        << "\t|\t" << std::setw(16) << "func" << std::endl;
#endif
    for (auto& i : data_list_) {
      i->print(out);
    }
  }

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

 private:
  Logger() = default;

  std::mutex mtx_;
  std::vector<const Printable*> data_list_;
};

constexpr unsigned long compute_hash(const char* str) {
  unsigned long hash = 5381;
  while (*str) {
    hash = ((hash << 5) + hash) + *str++;
  }
  return hash;
}

template <unsigned long id>
class Name : public Printable {
 public:
  const char* name_;
  const char* file_;
  const char* func_;

  static Name& instance(const char* name, const char* file, const char* func) {
    static Name<id> obj(name, file, func);
    return obj;
  }

  std::ostream& print(std::ostream& str) const override {
    str << std::setw(16) << id << "\t|\t" << std::setw(16) << name_ << "\t|\t"
        << std::setw(64) << file_ << "\t|\t" << std::setw(16) << func_
        << std::endl;
    return str;
  }

  Name(const Name&) = delete;
  Name& operator=(const Name&) = delete;

 private:
  Name(const char* name, const char* file, const char* func) {
    name_ = name;
    file_ = file;
    func_ = func;
    tmr::Logger::instance().addData(this);
  }
};

struct Stat {
  std::atomic_llong count_;
  std::atomic_llong time_;
};

template <unsigned long id>
class StatSingleton : public Printable, Stat {
 public:
  static Stat& instance() {
    static StatSingleton<id> obj;
    return obj;
  }

  std::ostream& print(std::ostream& str) const override {
    str << std::setw(16) << id << "\t|\t" << std::setw(16) << count_ << "\t|\t"
        << std::setw(16) << time_ << "\t|\t" << std::setw(16)
        << time_ * 1.0 / count_ << std::endl;
    return str;
  }

  ~StatSingleton() = default;
  StatSingleton(const StatSingleton&) = delete;
  StatSingleton& operator=(const StatSingleton&) = delete;

 private:
  StatSingleton() { tmr::Logger::instance().addData(this); }
};

class Timer {
 public:
  Timer(Stat* stat) {
    stat_ = stat;
    start_ = std::chrono::high_resolution_clock::now();
  }

  ~Timer() {
    stat_->time_ += std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::high_resolution_clock::now() - start_)
                        .count();
    stat_->count_++;
  }

 private:
  Stat* stat_;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

}  // namespace tmr

#if defined(WITH_TIMER)
#define PRINT_STAT(stream) ::tmr::Logger::instance().printStat(stream);
#elif defined(WITH_LOG_INFO)
#define PRINT_STAT(stream) ::tmr::Logger::instance().printStat(stream);
#else
#define PRINT_STAT(stream)
#endif

#if defined(WITH_TIMER)
#define DECL_TIMER(name)                                         \
  constexpr char str[] = name;                                   \
  constexpr unsigned long hash =                                 \
      ::tmr::compute_hash(__FILE__) ^ ::tmr::compute_hash(name); \
  ::tmr::Timer wgjprtsqaw(&::tmr::StatSingleton<hash>::instance());
#elif defined(WITH_LOG_INFO)
#define DECL_TIMER(name)                                         \
  constexpr unsigned long hash =                                 \
      ::tmr::compute_hash(__FILE__) ^ ::tmr::compute_hash(name); \
  ::tmr::Name<hash>::instance(name, __FILE__, __func__);
#else
#define DECL_TIMER(name)
#endif

#endif  // TIMER_H
