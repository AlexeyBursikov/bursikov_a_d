#pragma once
#ifndef STACK_H
#define STACK_H
#include <memory>

class StackL
{
  public:
    StackL();
    StackL(const StackL &);
    StackL& operator=(const StackL &);
    ~StackL();

    void push(int x);
    void pop();
    bool isEmpty();
    int top();

  private:
    void clear();
    void clone(const StackL& other);

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

class StackV
{
public:
  StackV();
  StackV(const StackV &);
  StackV& operator=(const StackV &);
  ~StackV() = default;

  void push(int x);
  void pop();
  bool isEmpty();
  int top();

private:
  void expand();
  void clone(const StackV& other);

  static const int INIT_SIZE = 10;

  std::unique_ptr<int[]> data_;
  int size_;
  int top_;
};

#endif STACK_H
