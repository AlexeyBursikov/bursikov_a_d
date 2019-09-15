#pragma once
#include <list>

class Stack
{
  public:
    Stack();
    Stack(const Stack &) = default;
    ~Stack() = default;

    Stack &operator=(const Stack &) = default;

    void push(int x);
    void pop();
    bool isEmpty();
    int top();

  private:
    std::list<int> data_;
    size_t size_;
};

