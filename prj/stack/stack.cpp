#include "stack.h"
#include <stdexcept>

Stack::Stack()
{
    pTop_ = nullptr;
}

Stack::Stack(const Stack& other){
    *this = other;
}

Stack& Stack::operator=(const Stack& other){
    clone(other);
    return *this;
}

Stack::~Stack(){
    clear();
}

bool Stack::isEmpty()
{
    return pTop_ == nullptr;
}

void Stack::push(int data)
{
    Leaf* newLeaf = new Leaf(data, pTop_);
    pTop_ = newLeaf;
}

void Stack::pop()
{
    if (!isEmpty()) {
        Leaf* tmp = pTop_->pnext_;
        delete pTop_;
        pTop_ = tmp;
    }

}

int Stack::top()
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

void Stack::clear(){
    while (pTop_ != nullptr) {
        pop();
    }
}

void Stack::clone(const Stack& other){
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
