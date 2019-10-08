#include <iostream>
#include <chrono>
#include "stack.h"

using namespace std;

void workWithStackL()
{
    int num = 10000000;
    StackL s;
    for (int i = 0; i < num; ++i){
      s.push(i);
    }

    for (int i = 0; i < num; ++i){
      s.pop();
    }
}

void workWithStackV()
{
    int num = 10000000;
    StackV s;
    for (int i = 0; i < num; ++i){
      s.push(i);
    }

    for (int i = 0; i < num; ++i){
      s.pop();
    }
}

int main()
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  int elapsed_seconds = 0;
  start = std::chrono::system_clock::now();
  workWithStackV();
  end = std::chrono::system_clock::now();

  elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

  std::cout << "Время выполнения StackL:" << elapsed_seconds << "ms\n";

  start = std::chrono::system_clock::now();
  workWithStackL();
  end = std::chrono::system_clock::now();

  elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

  std::cout << "Время выполнения StackV:" << elapsed_seconds << "ms\n";

   return 0;
}
