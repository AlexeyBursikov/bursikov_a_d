#include "timer.h"
#include <mutex>

std::unordered_map<std::string, Timer::Stat> Timer::time_table_ =
    std::unordered_map<std::string, Timer::Stat>();

Timer::Timer(std::string name) {
  name_ = name;
  start_ = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  end = std::chrono::system_clock::now();

  Stat& val = Timer::time_table_[name_];
  val.time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_)
                  .count();
  ;
  val.count += 1;
}

void Timer::printStat(std::ostream& str) {
  for (auto p : Timer::time_table_) {
    str << p.first << "\t|\t" << p.second.count << "\t|\t" << p.second.time
        << std::endl;
  }
}
