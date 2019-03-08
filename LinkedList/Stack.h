#pragma once

#include "LinkedList.h"

template<class T>
class Stack {

public:
  Stack()
    : list()
  {}

  void push(const T& value)
  {
    list.push_front(value);
  }

  T pop()
  {
    return list.pop_front();
  }

  T& top()
  {
    return *list.begin();
  }

  bool empty() const
  {
    return list.empty();
  }

  int size() const
  {
    return list.size();
  }

private:

  LinkedList<T> list;

};
