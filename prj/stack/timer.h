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

// struct Stat {
//  std::string name;
//  int count = 0;
//  long long time = 0;
//};

// class TimeListener {
// public:
//  static TimeListener& Instance() {
//    static TimeListener instance;
//    return instance;
//  }

//  void printStat(std::ostream& str);
//  void addStat(const Stat& stat);

//  TimeListener(const TimeListener& other) = delete;
//  TimeListener& operator=(const TimeListener& other) = delete;

// private:
//  TimeListener(){};

//  boost::lockfree::queue<Stat> queue_;
//  std::unordered_map<std::string, Stat> stat_table_;
//  std::mutex static_mutex_;
//};

// class Timer {
// public:
//  static void printStat(std::ostream& str);

//  Timer(const std::string& name);
//  ~Timer();

//  void setListener(TimeListener* listener) { listener_ = listener; }
//  void removeListener() { listener_ = nullptr; }

// private:
//  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
//  std::chrono::time_point<std::chrono::high_resolution_clock> end_;
//  const std::string name_;

//  TimeListener* listener_ = nullptr;
//};

//#ifdef WITH_TIMER
//#define DEF_TIMER(name) \
//  class name : public Timer {}
//#else
//#define DEF_TIMER(name)
//#endif

//#ifdef WITH_TIMER
//#define DECL_TIMER(name) Timer time(name);
//#else
//#define DECL_TIMER(name)
//#endif

//#ifdef WITH_TIMER
//#define PRINT_STAT(stream) Timer::printStat(stream)
//#else
//#define PRINT_STAT(stream)
//#endif

struct Stat {
  long long id_;
  std::atomic_llong count_;
  std::atomic_llong time_;

  Stat();
  virtual ~Stat();
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
