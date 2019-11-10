#include "stack.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void getStackStatPushPop(IStack& stack, std::ostream& str) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  int max_op = 1000000;
  int step = 100000;
  std::vector<long> push_time;
  std::vector<long> pop_time;

  for (int i = step; i <= max_op; i += step) {
    start = std::chrono::system_clock::now();
    for (int j = 0; j < i; ++j) {
      stack.push(j);
    }
    end = std::chrono::system_clock::now();
    push_time.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count());

    start = std::chrono::system_clock::now();
    for (int j = 0; j < i; ++j) {
      stack.pop();
    }
    end = std::chrono::system_clock::now();
    pop_time.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count());
  }

  str << "number of iterations: \t";
  for (int j = step; j <= max_op; j += step) {
    str << j << "\t";
  }
  str << std::endl;

  str << "push time, microseconds: \t";
  for (auto j : push_time) {
    str << j << "\t";
  }
  str << std::endl;

  str << "pop time, microseconds: \t";
  for (auto j : pop_time) {
    str << j << "\t";
  }
  str << std::endl;
}

template <class T>
void getStackStatCopy(std::ostream& str) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
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
    start = std::chrono::system_clock::now();
    stack2 = stack1;
    end = std::chrono::system_clock::now();
    clone_time.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count());
  }

  str << "number of item: \t";
  for (int j = step; j <= max_op; j += step) {
    str << j << "\t";
  }
  str << std::endl;

  str << "clone time, microseconds: \t";
  for (auto j : clone_time) {
    str << j << "\t";
  }
  str << std::endl;
}

int main() {
  std::fstream out_stream(
      "/media/alex/Новый том/Storage/bursikov_a_d/prj/stack/stat");
  if (!out_stream.is_open()) {
    std::cout << "could not open file" << std::endl;
    return -1;
  }

  StackV stack_v;
  out_stream << "StackV" << endl;
  getStackStatPushPop(stack_v, out_stream);
  getStackStatPushPop(stack_v, out_stream);
  getStackStatPushPop(stack_v, out_stream);
  getStackStatPushPop(stack_v, out_stream);
  getStackStatPushPop(stack_v, out_stream);
  out_stream << endl << endl;

  StackL stack_l;
  out_stream << "StackL" << endl;
  getStackStatPushPop(stack_l, out_stream);
  getStackStatPushPop(stack_l, out_stream);
  getStackStatPushPop(stack_l, out_stream);
  getStackStatPushPop(stack_l, out_stream);
  getStackStatPushPop(stack_l, out_stream);
  out_stream << endl << endl;

  StackSTD stack_std;
  out_stream << "StackSTD" << endl;
  getStackStatPushPop(stack_std, out_stream);
  getStackStatPushPop(stack_std, out_stream);
  getStackStatPushPop(stack_std, out_stream);
  getStackStatPushPop(stack_std, out_stream);
  getStackStatPushPop(stack_std, out_stream);
  out_stream << endl << endl;

  out_stream << "StackV" << endl;
  getStackStatCopy<StackV>(out_stream);
  out_stream << endl << endl;

  out_stream << "StackL" << endl;
  getStackStatCopy<StackL>(out_stream);
  out_stream << endl << endl;

  out_stream << "StackSTD" << endl;
  getStackStatCopy<StackSTD>(out_stream);
  out_stream << endl << endl;

  out_stream.close();
  return 0;
}
