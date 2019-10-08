#include "stack.h"
#include <stdexcept>
#include <vector>


StackL::StackL()
{
    pTop_ = nullptr;
}

StackL::StackL(const StackL& other){
    *this = other;
}

StackL& StackL::operator=(const StackL& other){
    clone(other);
    return *this;
}

StackL::~StackL(){
    clear();
}

bool StackL::isEmpty()
{
    return pTop_ == nullptr;
}

void StackL::push(int data)
{
    Leaf* newLeaf = new Leaf(data, pTop_);
    pTop_ = newLeaf;
}

void StackL::pop()
{
    if (!isEmpty()) {
        Leaf* tmp = pTop_->pnext_;
        delete pTop_;
        pTop_ = tmp;
    }

}

int StackL::top()
{
    if (isEmpty())
    {
        throw std::out_of_range("retrieving item from empty stack");
    }
    else
    {
        return pTop_->data_;
    }
}

void StackL::clear(){
    while (pTop_ != nullptr) {
        pop();
    }
}

void StackL::clone(const StackL& other){
    if (pTop_ == other.pTop_)
        return;

    if (other.pTop_ == nullptr) {
        pTop_ = nullptr;
        return;
    }

    Leaf* newLeaf = new Leaf(*other.pTop_);
    newLeaf->pnext_ = nullptr;
    pTop_ = newLeaf;

    Leaf* pOther = other.pTop_->pnext_;
    Leaf* pThis = pTop_;

    while (pOther != nullptr) {
        Leaf* newLeaf = new Leaf(*pOther);
        newLeaf->pnext_ = nullptr;
        pThis->pnext_ = newLeaf;
        pOther = pOther->pnext_;
        pThis = newLeaf;
    }
}

/////////////////////////////////

StackV::StackV()
{
    data_.reset(new int[INIT_SIZE]);
    size_ = INIT_SIZE;
    top_ = -1;
}

StackV::StackV(const StackV& other)
{
    *this = other;
}

StackV& StackV::operator=(const StackV& other)
{
    clone(other);
    return *this;
}


bool StackV::isEmpty()
{
    return top_== -1;
}

void StackV::push(int data)
{
    if (top_ >= size_ - 1) {
        expand();
    }

    data_[++top_] = data;
}

void StackV::pop()
{
    if (!isEmpty()) {
        --top_;
    }
}

int StackV::top()
{
    if (isEmpty())
    {
        throw std::out_of_range("retrieving item from empty stack");
    }
    else
    {
        return data_[top_];
    }
}

void StackV::expand()
{
    size_ *= 2;
    std::unique_ptr<int[]> newData(new int[size_]);
    for (int i = 0; i <= top_; ++i) {
        newData[i] = data_[i];
    }

    data_.swap(newData);
}

void StackV::clone(const StackV& other)
{
    if (data_ == other.data_)
        return;

    if (other.data_ == nullptr) {
        data_ = nullptr;
        return;
    }

    data_ = std::unique_ptr<int[]>(new int[other.size_]);
    size_ = other.size_;
    top_ = other.top_;

    for (int i = 0; i <= other.top_; ++i) {
        data_[i] = other.data_[i];
    }
}
