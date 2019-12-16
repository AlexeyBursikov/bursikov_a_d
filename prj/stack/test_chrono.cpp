#include <chrono>
#include <iostream>

#define WITH_TIMER
//#define WITH_LOG_INFO

#include "timer.h"

int main() {
  std::chrono::time_point<std::chrono::high_resolution_clock> start1;
  std::chrono::time_point<std::chrono::high_resolution_clock> end1;
  std::chrono::time_point<std::chrono::high_resolution_clock> start2;
  std::chrono::time_point<std::chrono::high_resolution_clock> end2;
  start2 = std::chrono::high_resolution_clock::now();
  start1 = std::chrono::high_resolution_clock::now();

  // smth

  end1 = std::chrono::high_resolution_clock::now();
  end2 = std::chrono::high_resolution_clock::now();

  long dur1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1)
          .count();
  long dur2 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2)
          .count();
  std::cout << "gen time1: " << dur1 << std::endl;

  std::cout << "gen time2: " << dur2 << std::endl;

  std::cout << "chrono timing time:" << dur2 - dur1 << std::endl;

  start1 = std::chrono::high_resolution_clock::now();

  { DECL_TIMER("f"); }

  end1 = std::chrono::high_resolution_clock::now();
  dur1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1)
             .count();

  std::cout << "timer creation time: " << dur1 << std::endl;
  PRINT_STAT(std::cout);
  return 0;
}
