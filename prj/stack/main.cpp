#include "stack.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

//#define WITH_TIMER
//#define WITH_LOG_INFO

#include "timer.h"

void getStackStatPushPop(st::IStack& stack, std::ostream& str) {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  int ops = 1000000;
  int step = 100000;
  int iter = 100;
  std::vector<long long> push_time;
  std::vector<long long> pop_time;

  for (int k = 0; k < iter; ++k) {
    for (int i = step; i <= ops; i += step) {
      start = std::chrono::high_resolution_clock::now();
      for (int j = 0; j < step; ++j) {
        stack.push(j);
      }
      end = std::chrono::high_resolution_clock::now();
      push_time.push_back(
          std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
              .count());
    }

    for (int i = step; i <= ops; i += step) {
      start = std::chrono::high_resolution_clock::now();
      for (int j = 0; j < step; ++j) {
        stack.pop();
      }
      end = std::chrono::high_resolution_clock::now();
      pop_time.push_back(
          std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
              .count());
    }
  }

  str << "number of iterations: \t";
  for (int k = 0; k < iter; ++k) {
    for (int j = step; j <= ops; j += step) {
      str << ops * k + j << "\t";
    }
  }
  str << std::endl;

  str << "push time, nanoseconds: \t";
  long long time = 0;
  for (auto j : push_time) {
    time += j;
    str << time << "\t";
  }
  str << std::endl;

  str << "pop time, nanoseconds: \t";
  time = 0;
  for (auto j : pop_time) {
    time += j;
    str << time << "\t";
  }

  str << std::endl;
}

template <class T>
void getStackStatCopy(std::ostream& str) {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  T stack1;
  T stack2;
  int max_op = 1000000;
  int step = 100000;
  std::vector<long> clone_time;

  int j = 0;
  for (int i = step; i <= max_op; i += step) {
    for (; j < i; ++j) {
      stack1.push(j);
    }

    start = std::chrono::high_resolution_clock::now();
    stack2 = stack1;
    end = std::chrono::high_resolution_clock::now();

    clone_time.push_back(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count());
  }

  str << "number of item: \t";
  for (int j = step; j <= max_op; j += step) {
    str << j << "\t";
  }
  str << std::endl;

  str << "clone time, nanoseconds: \t";
  for (auto j : clone_time) {
    str << j << "\t";
  }
  str << std::endl;
}

void genInd(int n, std::vector<int>& v) {
  DECL_TIMER("genIndTimer");
  for (int i = 0; i < n; ++i) {
    v.push_back(i);
  }
}

int main() {
  std::stringstream ssV;
  std::stringstream ssL;
  std::stringstream ssSTD;
  std::stringstream ssVC;
  std::stringstream ssLC;
  std::stringstream ssSTDC;
  std::vector<std::thread> threads;

  st::StackV stack_v;
  std::thread thV(getStackStatPushPop, std::ref(stack_v), std::ref(ssV));
  threads.push_back(std::move(thV));

  st::StackL stack_l;
  std::thread thL(getStackStatPushPop, std::ref(stack_l), std::ref(ssL));
  threads.push_back(std::move(thL));

  st::StackSTD stack_std;
  std::thread thSTD(getStackStatPushPop, std::ref(stack_std), std::ref(ssSTD));
  threads.push_back(std::move(thSTD));

  std::thread thVC(getStackStatCopy<st::StackV>, std::ref(ssVC));
  threads.push_back(std::move(thVC));

  std::thread thLC(getStackStatCopy<st::StackL>, std::ref(ssLC));
  threads.push_back(std::move(thLC));

  std::thread thSTDC(getStackStatCopy<st::StackSTD>, std::ref(ssSTDC));
  threads.push_back(std::move(thSTDC));

  for (auto& i : threads) {
    i.join();
  }

  std::fstream out_stream("../stat");
  if (!out_stream.is_open()) {
    std::cout << "could not open file" << std::endl;
    return -1;
  }

  out_stream << "StackV" << std::endl;
  out_stream << ssV.str();
  out_stream << std::endl;
  out_stream << ssVC.str();
  out_stream << std::endl << std::endl;

  out_stream << "StackL" << std::endl;
  out_stream << ssL.str();
  out_stream << std::endl;
  out_stream << ssLC.str();
  out_stream << std::endl << std::endl;

  out_stream << "StackSTD" << std::endl;
  out_stream << ssSTD.str();
  out_stream << std::endl;
  out_stream << ssSTDC.str();
  out_stream << std::endl << std::endl;

  out_stream.close();

  PRINT_STAT(std::cout);

  return 0;
}
