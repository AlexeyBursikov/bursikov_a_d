#include "stack.h"

#include <iostream>
#include <stdexcept>
#include <vector>

StackSTD::~StackSTD() {}

void StackSTD::push(int x) { stack_.push(x); }
void StackSTD::pop() { stack_.pop(); }
bool StackSTD::isEmpty() const { return stack_.top(); }
int StackSTD::top() const { return stack_.top(); }

////

StackL::StackL() { pTop_ = nullptr; }

StackL::StackL(const StackL& other) {
  if (other.pTop_ == nullptr) {
    pTop_ = nullptr;
    return;
  }

  Leaf* newLeaf = new Leaf(*other.pTop_);
  newLeaf->pnext_ = nullptr;
  pTop_ = newLeaf;

  Leaf* pOther = other.pTop_;
  Leaf* pThis = pTop_;

  while (pOther->pnext_ != nullptr) {
    pOther = pOther->pnext_;
    newLeaf = new Leaf(*pOther);
    newLeaf->pnext_ = nullptr;

    pThis->pnext_ = newLeaf;

    pThis = pThis->pnext_;
  }
}

void StackL::swap(StackL& other) noexcept {
  std::swap(this->pTop_, other.pTop_);
}

StackL& StackL::operator=(const StackL& other) {
  StackL tmp(other);
  this->swap(tmp);
  return *this;
}

StackL::~StackL() { clear(); }

bool StackL::isEmpty() const { return pTop_ == nullptr; }

void StackL::push(int data) {
  Leaf* newLeaf = new Leaf(data, pTop_);
  pTop_ = newLeaf;
}

void StackL::pop() {
  if (!isEmpty()) {
    Leaf* tmp = pTop_->pnext_;
    delete pTop_;
    pTop_ = tmp;
  }
}

int StackL::top() const {
  if (isEmpty()) {
    throw std::out_of_range("retrieving item from empty stack");
  } else {
    return pTop_->data_;
  }
}

void StackL::clear() {
  while (pTop_ != nullptr) {
    Leaf* tmp = pTop_->pnext_;
    delete pTop_;
    pTop_ = tmp;
  }
}

////

StackV::StackV() {
  data_ = new int[INIT_SIZE];
  size_ = INIT_SIZE;
  top_ = -1;
}

StackV::StackV(const StackV& other) {
  data_ = new int[other.size_];
  size_ = other.size_;
  top_ = other.top_;
  for (int i = 0; i <= other.top_; ++i) {
    data_[i] = other.data_[i];
  }
}

void StackV::swap(StackV& other) noexcept {
  std::swap(this->size_, other.size_);
  std::swap(this->top_, other.top_);
  std::swap(this->data_, other.data_);
}

StackV& StackV::operator=(const StackV& other) {
  StackV tmp(other);
  this->swap(tmp);
  return *this;
}

StackV::~StackV() { delete[] data_; }

bool StackV::isEmpty() const { return top_ == -1; }

void StackV::push(int data) {
  if (top_ >= (size_ - 1)) {
    expand();
  }

  data_[++top_] = data;
}

void StackV::pop() {
  if (!isEmpty()) {
    --top_;
  }
}

int StackV::top() const {
  if (isEmpty()) {
    throw std::out_of_range("retrieving item from empty stack");
  } else {
    return data_[top_];
  }
}

void StackV::expand() {
  size_ *= 2;
  int* newData = new int[size_];
  for (int i = 0; i <= top_; ++i) {
    newData[i] = data_[i];
  }

  delete[] data_;
  data_ = newData;
}
