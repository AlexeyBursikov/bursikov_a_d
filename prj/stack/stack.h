#pragma once
#ifndef STACK_H
#define STACK_H

#include <memory>
#include <stack>

class IStack {
 public:
  IStack() {}
  virtual ~IStack(){};

  virtual void push(int x) = 0;
  virtual void pop() = 0;
  virtual bool isEmpty() const = 0;
  virtual int top() const = 0;
};

////

class StackSTD : public IStack {
 public:
  StackSTD() = default;
  StackSTD(const StackSTD&) = default;
  StackSTD& operator=(const StackSTD&) = default;

  ~StackSTD() override;

  void push(int x) override;
  void pop() override;
  bool isEmpty() const override;
  int top() const override;

 private:
  std::stack<int> stack_;
};

////

class StackL : public IStack {
 public:
  StackL();
  StackL(const StackL&);
  StackL& operator=(const StackL&);

  ~StackL() override;

  void push(int x) override;
  void pop() override;
  bool isEmpty() const override;
  int top() const override;
  void swap(StackL& other) noexcept;

 private:
  void clear();

  struct Leaf {
    int data_;
    Leaf* pnext_;
    Leaf(const int& data, Leaf* pnext) {
      data_ = data;
      pnext_ = pnext;
    }
    Leaf(const Leaf&) = default;
    Leaf& operator=(const Leaf&) = default;
    ~Leaf() = default;
  };

  Leaf* pTop_;
};

////

class StackV : public IStack {
 public:
  StackV();
  StackV(const StackV&);
  StackV& operator=(const StackV&);

  ~StackV() override;

  void push(int x) override;
  void pop() override;
  bool isEmpty() const override;
  int top() const override;
  void swap(StackV& other) noexcept;

 private:
  void expand();

  static const int INIT_SIZE = 8;

  int* data_;
  int size_;
  int top_;
};

#endif
