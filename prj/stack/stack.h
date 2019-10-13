#pragma once
#ifndef STACK_H
#define STACK_H

#include <memory>

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

 private:
  void clear();
  void clone(const StackL& other);

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

  ~StackV() override = default;

  void push(int x) override;
  void pop() override;
  bool isEmpty() const override;
  int top() const override;

 private:
  void expand();
  void clone(const StackV& other);

  static const int INIT_SIZE = 10;

  std::unique_ptr<int[]> data_;
  int size_;
  int top_;
};

#endif STACK_H
