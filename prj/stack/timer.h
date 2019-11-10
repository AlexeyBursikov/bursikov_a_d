#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

class Timer {
  static std::unordered_map<std::string, long int> time_table_;
  static void printStat(std::ostream& str);

  Timer(std::string name);
  ~Timer();

  std::chrono::time_point<std::chrono::system_clock> start_;
  std::string name_;
};

#endif  // TIMER_H
