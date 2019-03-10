#pragma once

#include <exception>
#include <iterator>
#include <cassert>
#include <algorithm>

template<class T>
class LinkedList {

  class Node {
  public:

    Node(const T& value)
      : value(value)
      , next(nullptr)
      , prev(nullptr)
    {}

    T value;
    Node * next;
    Node * prev;

  };

public:

  class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    friend class LinkedList;

  public:

    explicit iterator(LinkedList& list, Node * start)
      : list(list)
      , current(start)
    {}

    T& operator*() const {
      assert(current != nullptr && "An attempt was made to dereference the end of a list.");
      return current->value;
    }

    T& operator->() const {
      assert(current != nullptr && "An attempt was made to dereference the end of a list.");
      return current->value;
    }

    iterator& operator=(const iterator& rhs) {
      current = rhs.current;
      list = rhs.list;
      return *this;
    }

    //post-fix
    iterator operator++(int) {
      if (current == nullptr) {
        return *this;
      }
      iterator ret = *this;
      current = current->next;
      return ret;
    }

    //prefix
    iterator& operator++() {
      if (current != nullptr) {
        current = current->next;
      }
      return *this;
    }

    //post-fix
    iterator operator--(int) {
      if (current == nullptr) {
        iterator ret = *this;
        current = list.back;
        return ret;
      }
      iterator ret = *this;
      current = current->prev;
      return ret;
    }

    //prefix
    iterator& operator--() {
      if (current != nullptr) {
        current = current->prev;
      }
      else {
        current = list.back;
      }
      return *this;
    }

    bool operator!=(const iterator & rhs) const {
      return (current != rhs.current);
    }

    bool operator==(const iterator & rhs) const {
      return (current == rhs.current);
    }

    ~iterator() {
      current = nullptr;
    }

  private:

    LinkedList& list;
    Node * current;

  };

  explicit LinkedList()
    : nodeCount(0)
    , front(nullptr)
    , back(nullptr)
  {}

  LinkedList(const LinkedList& rhs)
  {
    if (&rhs != this) {
      clear();
      copy_nodes(rhs);
    }

  }

  LinkedList& operator=(const LinkedList& rhs) {
    if (&rhs != this) {
      clear();
      copy_nodes(rhs);
    }
    return *this;
  }

  LinkedList& operator=(LinkedList&& rhs) {
    if (&rhs != this) {
      erase(begin(), end());

      front = rhs.front;
      back = rhs.back;
      nodeCount = rhs.nodeCount;

      rhs.front = nullptr;
      rhs.back = nullptr;
      rhs.nodeCount = 0;
      
    }
    return *this;
  }

  //TODO: make this argument const
  bool operator==(LinkedList& rhs) {

    if (&rhs == this) {
      return true;
    }

    if (nodeCount != rhs.nodeCount) {
      return false;
    }

    auto left = begin();
    auto right = rhs.begin();

    while (left != end()) {
      if (*left != *right) {
        return false;
      }
      ++left;
      ++right;
    }

    return true;

  }

  int size() const {
    return nodeCount;
  }

  bool empty() const {
    return (0 == nodeCount);
  }

  iterator begin() {
    return iterator(*this, front);
  }

  iterator end() {
    return iterator(*this, nullptr);
  }

  ////TODO: implement const iterators
  //const iterator begin() const {
  //  return iterator(*this, front);
  //}

  //const iterator end() const {
  //  return iterator(*this, nullptr);
  //}

  iterator push_front(const T& value) {
    Node * toAdd = new Node(value);
    toAdd->next = front;
    front = toAdd;
    ++nodeCount;
    if (1 == nodeCount) {
      back = front;
    }
    return iterator(*this, front);
  }

  iterator push_back(const T& value) {
    Node * toAdd = new Node(value);

    if (nullptr != back) {
      back->next = toAdd;
      toAdd->prev = back;
      back = toAdd;
    }
    else {
      front = back = toAdd; 
    }

    ++nodeCount;
    return iterator(*this, back);
  }

  iterator insert(iterator position, const T& value) {
    Node * toAdd = new Node(value);
    position.current->prev->next = toAdd;
    toAdd->prev = position.current->prev;
    position.current->prev = toAdd;
    toAdd->next = position.current;
    ++nodeCount;
    return iterator(*this, toAdd);
  }

  iterator erase(iterator position) {
    Node * toRemove = position.current;
    if (toRemove->prev == nullptr) {
      pop_front();
      return begin();
    }
    else if (toRemove->next == nullptr) {
      pop_back();
      return end();
    }

    toRemove->prev->next = toRemove->next;
    iterator nextPosition = iterator(*this, toRemove->next);
    delete toRemove;
    toRemove = NULL;
    --nodeCount;
    return nextPosition;

  }
  
  iterator erase(iterator start, iterator end) {
    while (start != end) {
     start = erase(start);
    }
    return end;
  }

  void clear() {
    erase(begin(), end());
    front = nullptr;
    back = nullptr;
    nodeCount = 0;
  }

  T pop_front() {
    if (0 == nodeCount) {
      throw std::out_of_range(
        "An attempt was made to pop_front from an empty list."
      );
    }
    Node * ret = front;
    front = front->next;

    if (1 == nodeCount) {
      back = front;
    }
    else {
      front->prev = nullptr;
    }
    T copy = ret->value;
    delete ret;
    ret = NULL;
    --nodeCount;
    return copy;
  }

  T pop_back() {
    if (0 == nodeCount) {
      throw std::out_of_range(
        "An attempt was made to pop_back from an empty list."
      );
    }
    Node * ret = back;
    back = back->prev;

    if (1 == nodeCount) {
      front = back;
    }
    else {
      back->next = nullptr;
    }
    T copy = ret->value;
    delete ret;
    ret = NULL;
    --nodeCount;
    return copy;
  }

  ~LinkedList()
  {
    erase(begin(), end());
  }

private:

  void copy_nodes(const LinkedList& rhs) {

    if (rhs.front == nullptr) {
      return;
    }

    push_back(rhs.front->value);
    Node * right_node = rhs.front->next;

    while (right_node != nullptr) {
      push_back(right_node->value);
      right_node = right_node->next;
    }
  }

  Node * front;
  Node * back;
  int nodeCount;

};


