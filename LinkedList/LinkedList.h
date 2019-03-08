#pragma once

#include <exception>
#include <iterator>
#include <cassert>

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

  class linked_list_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    friend class LinkedList;

  public:

    linked_list_iterator(LinkedList& list, Node * start)
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

    linked_list_iterator& operator=(const linked_list_iterator& rhs) {
      current = rhs.current;
      list = rhs.list;
      return *this;
    }

    //post-fix
    linked_list_iterator& operator++(int) {
      if (current == nullptr) {
        return *this;
      }
      linked_list_iterator& ret = *this;
      current = current->next;
      return ret;
    }

    //prefix
    linked_list_iterator& operator++() {
      if (current != nullptr) {
        current = current->next;
      }
      return *this;
    }

    //post-fix
    linked_list_iterator& operator--(int) {
      if (current == nullptr) {
        return *this;
      }
      linked_list_iterator& ret = *this;
      current = current->prev;
      return ret;
    }

    //prefix
    linked_list_iterator& operator--() {
      if (current != nullptr) {
        current = current->prev;
      }
      return *this;
    }

    bool operator!=(const linked_list_iterator & rhs) const {
      return (current != rhs.current);
    }

    bool operator==(const linked_list_iterator & rhs) const {
      return (current == rhs.current);
    }

    ~linked_list_iterator() {
      current = nullptr;
    }

  private:

    LinkedList& list;
    Node * current;

  };

  typedef linked_list_iterator iterator;

  LinkedList()
    : nodeCount(0)
    , front(nullptr)
    , back(nullptr)
  {}

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

  Node * front;
  Node * back;
  int nodeCount;

};


