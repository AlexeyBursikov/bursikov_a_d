#pragma once
#ifndef STACK_H
#define STACK_H

class Stack
{
  public:
    Stack();
    Stack(const Stack &);
    Stack& operator=(const Stack &);
    ~Stack();

    void push(int x);
    void pop();
    bool isEmpty();
    int top();

  private:
    void clear();
    void clone(const Stack& other);

    struct Leaf
    {
      int data_;
      Leaf * pnext_;

      Leaf(const int& data, Leaf * pnext)
      {
        data_ = data;
        pnext_ = pnext;
      }
      Leaf(const Leaf &) = default;
      Leaf& operator= (const Leaf &) = default;
      ~Leaf() = default;
    };

    Leaf* pTop_;
};

#endif STACK_H
