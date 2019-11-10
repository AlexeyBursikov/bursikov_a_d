#include "timer.h"

Timer::Timer(std::string name) {
  name_ = name;
  start_ = std::chrono::system_clock::now();
}

Timer::~Timer() {
  std::chrono::time_point<std::chrono::system_clock> end_ =
      std::chrono::system_clock::now();

  if (time_table_.find(name_) == time_table_.end()) {
    time_table_[name_] =
        std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_)
            .count();
  } else {
    time_table_[name_] +=
        std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_)
            .count();
  }
}

void Timer::printStat(std::ostream& str) {
  for (auto p : time_table_) {
    str << p.first << "\t|\t" << p.second << std::endl;
  }
}
