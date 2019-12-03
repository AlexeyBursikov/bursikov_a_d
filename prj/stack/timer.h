#pragma once
#ifndef TIMER_H
#define TIMER_H

#define WITH_TIMER

#include <atomic>
#include <boost/lockfree/queue.hpp>
#include <chrono>
#include <iostream>
#include <vector>
namespace tmr {

struct Stat {
  long long id_;
  std::atomic_llong count_;
  std::atomic_llong time_;

  Stat();
  ~Stat() = default;
};

class TimeLogger {
 public:
  static TimeLogger& instance() {
    static TimeLogger logger;
    return logger;
  }

  TimeLogger(const TimeLogger&) = delete;
  TimeLogger& operator=(const TimeLogger&) = delete;

  void addStat(const Stat* stat) { stat_list_.push_back(stat); }

  void printStat(std::ostream& out) {
    for (auto& i : stat_list_) {
      out << i->id_ << "\t | \t" << i->count_ << "\t | \t" << i->time_
          << std::endl;
    }
  }

 private:
  TimeLogger() = default;

  std::vector<const Stat*> stat_list_;
};

inline Stat::Stat() : count_(0), time_(0) {
  TimeLogger::instance().addStat(this);
};

constexpr long long compute_hash(const char* str) {
  constexpr int p = 31;
  constexpr long long m = 1e16;
  long long hash_value = 0;
  while (*str) {
    hash_value = (hash_value * p + (*str++ - 'a' + 1)) % m;
  }
  return hash_value;
}

template <long long t>
class Singleton {
 public:
  static Stat& instance() {
    static Stat obj;
    obj.id_ = t;
    return obj;
  }

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton() { instance(); }
};

template <class T>
class Timer {
 public:
  Timer() { start_ = std::chrono::high_resolution_clock::now(); }
  ~Timer() {
    end_ = std::chrono::high_resolution_clock::now();
    T::instance().count_++;
    T::instance().time_ +=
        std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - start_)
            .count();
  }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_;
};

}  // namespace tmr

#ifdef WITH_TIMER
#define PRINT_STAT(stream) ::tmr::TimeLogger::instance().printStat(stream);
#else
#define PRINT_STAT(stream)
#endif

#ifdef WITH_TIMER
#define DECL_TIMER(name)                               \
  constexpr char str[] = name;                         \
  constexpr long long hash = ::tmr::compute_hash(str); \
  ::tmr::Timer<::tmr::Singleton<hash>> timer;
#else
#define DECL_TIMER(name)
#endif

#endif  // TIMER_H
