#pragma once

#include <cassert>

template<class T>
class LinkedList {

  class Node {
  public:

    T value;
    Node * next;
    Node * prev;

    Node(const T& value = T{}, Node * prev = nullptr, Node * next = nullptr)
      : value(value)
      , prev(prev)
      , next(next)
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
      assert(current->next != nullptr && "Cannot increment an end iterator");
      current = current->next;
      return *this;
    }

    //post-fix
    const_iterator operator++(int) {
      const_iterator ret = *this;
      ++(*this);
      return ret;
    }

    //prefix
    const_iterator& operator--() {
      assert(current->prev != nullptr && "Cannot decrement a begin iterator");
      current = current->prev;
      return *this;
    }

    //post-fix
    const_iterator operator--(int) {
      const_iterator ret = *this;
      --(*this);
      return ret;
    }

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

    //prefix
    iterator& operator++() {
      assert(this->current->next != nullptr && "Cannot increment an end iterator");
      this->current = this->current->next;
      return *this;
    }

    //post-fix
    iterator operator++(int) {
      iterator ret = *this;
      ++(*this);
      return ret;
    }

    //prefix
    iterator& operator--() {
      assert(this->current->prev != nullptr && "Cannot decrement a begin iterator");
      this->current = this->current->prev;
      return *this;
    }

    //post-fix
    iterator operator--(int) {
      iterator ret = *this;
      --(*this);
      return ret;
    }

    iterator& operator=(const iterator& rhs) {
      this->current = rhs.current;
      return *this;
    }

  };


  LinkedList()
  {
    initialize();
  }

  LinkedList(const LinkedList& rhs)
  {
    if (&rhs != this) {

      initialize();
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
    return { front->next };
  }

  iterator end() {
    return { back };
  }

  const_iterator begin() const {
    return  { front->next };
  }

  const_iterator end() const {
    return { back };
  }

  void push_front(const T& value) {
    insert(begin(), value);
  }

  void push_back(const T& value) {
    insert(end(), value);
  }

  iterator insert(iterator position, const T& value) {
    if (nodeCount == 0) {
      Node * toAdd = new Node(value, front, back);
      back->prev = front->next = toAdd;
      ++nodeCount;
      return { toAdd };
    }

    Node * current = position.current;
    Node * toAdd = new Node(value, current->prev, current);
    current->prev = current->prev->next = toAdd;
    ++nodeCount;
    return { toAdd };
  }

  iterator erase(iterator position) {
    assert(position.current != back && "An attempt was made to erase the end of a list");
    
    Node * toRemove = position.current;
    toRemove->prev->next = toRemove->next;
    toRemove->next->prev = toRemove->prev;
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
    initialize();
  }

  T pop_front() {
    auto first = begin();
    T value = *first;
    erase(first);
    return value;
  }

  T pop_back() {
    auto last = --end();
    T value = *last;
    erase(last);
    return value;
  }

  ~LinkedList()
  {
    erase(begin(), end());
  }

private:

  void copy_nodes(const LinkedList& rhs) {

    if (rhs.nodeCount == 0) {
      return;
    }

    for (auto i = rhs.begin(); i != rhs.end(); ++i) {
      push_back(*i);
    }
  }

  void initialize() {
    nodeCount = 0;
    front = new Node();
    back = new Node();
    front->next = back;
    back->prev = front;
  }

  Node * front;
  Node * back;
  int nodeCount;

};


