#include "stack.h"

#include <chrono>
#include <iostream>

using namespace std;

void workWithStack(IStack& stack, int num_op) {
  for (int i = 0; i < num_op; ++i) {
    stack.push(i);
  }

  for (int i = 0; i < num_op; ++i) {
    stack.pop();
  }
}

int main() {
  int num_op = 1000000;

  std::chrono::time_point<std::chrono::system_clock> start, end;
  long elapsed_seconds = 0;
  start = std::chrono::system_clock::now();
  StackV stack_v;
  workWithStack(stack_v, num_op);
  end = std::chrono::system_clock::now();

  elapsed_seconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "Время выполнения StackV:" << elapsed_seconds << "ms\n";

  start = std::chrono::system_clock::now();
  StackL stack_l;
  workWithStack(stack_l, num_op);
  end = std::chrono::system_clock::now();

  elapsed_seconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "Время выполнения StackL:" << elapsed_seconds << "ms\n";

  return 0;
}
