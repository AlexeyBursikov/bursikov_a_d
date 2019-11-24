#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

class Timer {
 public:
  static void printStat(std::ostream& str);

  Timer(std::string name);
  ~Timer();

  struct Stat {
    int count = 0;
    long long time = 0;
  };
  static std::unordered_map<std::string, Stat> time_table_;

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
  std::string name_;
};

#endif  // TIMER_H
