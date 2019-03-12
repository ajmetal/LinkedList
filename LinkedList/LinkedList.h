#pragma once

#include <cassert>
#include <utility>

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

    const_iterator(const LinkedList<T> & list, Node * start = nullptr)
      : list{&list} ,
      current(start)
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

    const LinkedList<T> * list;
    Node * current;

  };//end const iterator

  class iterator : public const_iterator {
    
  public:

    iterator(LinkedList<T> & list, Node * start = nullptr) 
      : const_iterator{ list, start } 
    {
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

  };//end iterator

  //default constructor
  LinkedList()
  {
    initialize();
  }

  //copy constructor
  LinkedList(const LinkedList& rhs)
  {
    if (&rhs != this) {

      initialize();
      for (auto & i : rhs) {
        push_back(i);
      }
    }
  }

  //move constructor
  LinkedList(LinkedList && rhs)
    : nodeCount{ rhs.nodeCount },
    head{ rhs.head },
    tail{ rhs.tail }
  {
    rhs.nodeCount = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
  }

  //copy assignment
  LinkedList& operator=(const LinkedList& rhs) {
    if (&rhs != this) {

      //copy the data we want to a local variable
      LinkedList copy = rhs;
      //swap this list with the copy
      std::swap(*this, copy);

    }//copy destructor is called, cleaning up the data we don't want

    return *this;
  }

  //move assignment
  LinkedList& operator=(LinkedList&& rhs) {
    if (&rhs != this) {
      erase(begin(), end());

      head = std::move(rhs.head);
      tail = std::move(rhs.tail);
      nodeCount = std::move(rhs.nodeCount);
    }
    return *this;
  }

  //destructor
  ~LinkedList()
  {
    erase(begin(), end());
    delete head;
    delete tail;
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

  bool operator!=(const LinkedList& rhs) {
    return !(*this == rhs);
  }

  int size() const {
    return nodeCount;
  }

  bool empty() const {
    return (0 == nodeCount);
  }

  iterator begin() {
    return { *this, head->next };
  }

  iterator end() {
    return { *this, tail };
  }

  const_iterator begin() const {
    return  { *this, head->next };
  }

  const_iterator end() const {
    return { *this, tail };
  }

  //copy semantics insert
  iterator insert(iterator position, const T& value) {
    assert(is_iterator_valid(position) && "Invalid iterator");
    if (nodeCount == 0) {
      Node * toAdd = new Node(value, head, tail);
      tail->prev = head->next = toAdd;
      ++nodeCount;
      return { *this, toAdd };
    }

    Node * current = position.current;
    Node * toAdd = new Node(value, current->prev, current);
    current->prev = current->prev->next = toAdd;
    ++nodeCount;
    return { *this, toAdd };
  }

  //move semantics insert
  iterator insert(iterator position, T&& value) {
    assert(is_iterator_valid(position) && "Invalid iterator");
    if (nodeCount == 0) {
      Node * toAdd = new Node(move(value), head, tail);
      tail->prev = head->next = toAdd;
      ++nodeCount;
      return { *this, toAdd };
    }

    Node * current = position.current;
    Node * toAdd = new Node(move(value), current->prev, current);
    current->prev = current->prev->next = toAdd;
    ++nodeCount;
    return { *this, toAdd };
  }

  void push_front(const T& value) {
    insert(begin(), value);
  }

  void push_back(const T& value) {
    insert(end(), value);
  }

  iterator erase(iterator position) {
    assert(is_iterator_valid(position) && position.current != tail && "Invalid iterator");
    Node * toRemove = position.current;
    toRemove->prev->next = toRemove->next;
    toRemove->next->prev = toRemove->prev;
    iterator nextPosition = { *this, toRemove->next };
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

  T& front() {
    return head->next->value;
  }

  T& back() {
    return tail->prev->value;
  }


private:

  bool is_iterator_valid(const const_iterator& itr) {
    return (itr.list == this && itr.current != nullptr);
  }

  void initialize() {
    nodeCount = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
  }

  Node * head;
  Node * tail;
  int nodeCount;

};


