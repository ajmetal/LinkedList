#pragma once

#include "LinkedList.h"

template <class T>
class Queue {

public:
  Queue()
  : list()
  { }

  void enqueue(const T& value) {
    list.push_back(value);
  }

  T dequeue() {
    return list.pop_front();
  }

  bool empty() const {
    return list.empty();
  }

  bool size() const
  {
    return list.size();
  }

private:
  LinkedList<T> list;

};
