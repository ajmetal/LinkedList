#pragma once

#include <exception>
#include <cassert>
#include <algorithm>

template<class T>
class LinkedList {

  class Node {
  public:

    T value;
    Node * next;
    Node * prev;

    Node(const T& value, Node * next = nullptr, Node * prev = nullptr)
      : value(value)
      , next(next)
      , prev(prev)
    {}

  };

public:

  class const_iterator {
    friend class LinkedList<T>;

  public:

    const_iterator(Node * start = nullptr)
      : current(start)
    { }

    const T& operator*() const {
      return get_value();
    }

    const T& operator->() const {
      return get_value();
    }

    //prefix
    const_iterator& operator++() {
      if (current != nullptr) {
        current = current->next;
      }
      return *this;
    }

    //post-fix
    const_iterator operator++(int) {
      if (current == nullptr) {
        return *this;
      }
      const_iterator ret = *this;
      ++(*this);
      return ret;
    }

    ////prefix
    //const_iterator& operator--() {
    //  if (current != nullptr) {
    //    current = current->prev;
    //  }
    //  else {
    //    current = list.back;
    //  }
    //  return *this;
    //}

    ////post-fix
    //const_iterator operator--(int) {
    //  if (current == nullptr) {
    //    const_iterator ret = *this;
    //    current = list.back;
    //    return ret;
    //  }
    //  const_iterator ret = *this;
    //  --(*this);
    //  return ret;
    //}

    bool operator!=(const const_iterator & rhs) const {
      return (current != rhs.current);
    }

    bool operator==(const const_iterator & rhs) const {
      return (current == rhs.current);
    }

    ~const_iterator() {
      current = nullptr;
    }

  protected:

    T& get_value() const {
      assert(current != nullptr && "An attempt was made to dereference the end of a list.");
      return current->value;
    }

    Node * current;

  };

  class iterator : public const_iterator {
    
  public:

    iterator(Node * start = nullptr) 
      : const_iterator{ start } {
      this->current = start;
    }

    T& operator*() {
      return const_iterator::get_value();
    }

    T& operator->() {
      return const_iterator::get_value();
    }

    //post-fix
    iterator operator++(int) {
      if (this->current == nullptr) {
        return *this;
      }
      iterator ret = *this;
      this->current = this->current->next;
      return ret;
    }

    //prefix
    iterator& operator++() {
      if (this->current != nullptr) {
        this->current = this->current->next;
      }
      return *this;
    }

    ////post-fix
    //iterator operator--(int) {
    //  if (this->current == nullptr) {
    //    iterator ret = *this;
    //    this->current = this->list.back;
    //    return ret;
    //  }
    //  iterator ret = *this;
    //  this->current = this->current->prev;
    //  return ret;
    //}

    ////prefix
    //iterator& operator--() {
    //  if (this->current != nullptr) {
    //    this->current = this->current->prev;
    //  }
    //  else {
    //    this->current = this->list.back;
    //  }
    //  return *this;
    //}


    iterator& operator=(const iterator& rhs) {
      this->current = rhs.current;
      return *this;
    }

  };


  LinkedList()
    : nodeCount(0)
    , front(nullptr)
    , back(nullptr)
  {}

  LinkedList(const LinkedList& rhs)
  {
    if (&rhs != this) {
      nodeCount = 0;
      front = nullptr;
      back = nullptr;

      copy_nodes(rhs);
    }

  }

  LinkedList& operator=(const LinkedList& rhs) {
    if (&rhs != this) {
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
  bool operator==(const LinkedList& rhs) {

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
    return { front };
  }

  iterator end() {
    return { nullptr };
  }

  const_iterator begin() const {
    return  { front };
  }

  const_iterator end() const {
    return { nullptr };
  }

  void push_front(const T& value) {
    Node * toAdd = new Node(value);
    toAdd->next = front;
    front = toAdd;
    ++nodeCount;
    if (1 == nodeCount) {
      back = front;
    }
  }

  void push_back(const T& value) {
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
  }

  iterator insert(iterator position, const T& value) {
    Node * toAdd = new Node(value);
    position.current->prev->next = toAdd;
    toAdd->prev = position.current->prev;
    position.current->prev = toAdd;
    toAdd->next = position.current;
    ++nodeCount;
    return { toAdd };
  }

  iterator erase(iterator position) {
    Node * toRemove = position.current;
    if (toRemove == nullptr) {
      return end();
    }
    if (toRemove->prev == nullptr) {
      pop_front();
      return begin();
    }
    else if (toRemove->next == nullptr) {
      pop_back();
      return end();
    }

    toRemove->prev->next = toRemove->next;
    iterator nextPosition = { toRemove->next };
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


