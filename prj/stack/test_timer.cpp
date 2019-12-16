#include <iostream>
#include <thread>
#include <vector>

#define WITH_TIMER
//#define WITH_LOG_INFO

#include "timer.h"

void workFun() { DECL_TIMER("workFun"); }

void runFun(int n, std::vector<long>& times) {
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  for (int i = 0; i < n; i++) {
    start = std::chrono::high_resolution_clock::now();
    workFun();
    end = std::chrono::high_resolution_clock::now();
    times.push_back(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count());
  }
}

int main() {
  const int num_threads = 1;
  const int num_ops = 1000000;
  std::vector<std::thread> threads;
  std::vector<std::vector<long>> times_vec(num_threads);

  for (int i = 0; i < num_threads; i++) {
    std::thread th(runFun, num_ops, ref(times_vec[i]));
    threads.push_back(std::move(th));
  }

  for (auto& i : threads) {
    i.join();
  }

  long long full = 0;

  for (auto& times : times_vec) {
    for (auto& time : times) {
      full += time;
    }
  }
  std::cout << "full:" << full << std::endl;

  long long aver = full / (num_ops * num_threads);
  std::cout << "aver:" << aver << std::endl;

  long long disp = 0;
  for (auto& times : times_vec) {
    for (auto& time : times) {
      disp += (time - aver) * (time - aver);
    }
  }
  disp = disp / (num_ops * num_threads);
  std::cout << "disp:" << disp << std::endl;

  PRINT_STAT(std::cout);

  return 0;
}
