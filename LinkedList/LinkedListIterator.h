//
//class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
//  friend class LinkedList;
//
//public:
//
//  explicit const_iterator(LinkedList& list, Node * start)
//    : list(list)
//    , current(start)
//  {}
//
//  T operator*() const {
//    assert(current != nullptr && "An attempt was made to dereference the end of a list.");
//    return current->value;
//  }
//
//  T operator->() const {
//    assert(current != nullptr && "An attempt was made to dereference the end of a list.");
//    return current->value;
//  }
//
//  const_iterator& operator=(const iterator& rhs) {
//    current = rhs.current;
//    list = rhs.list;
//    return *this;
//  }
//
//  //post-fix
//  const_iterator operator++(int) {
//    if (current == nullptr) {
//      return *this;
//    }
//    const_iterator ret = *this;
//    current = current->next;
//    return ret;
//  }
//
//  //prefix
//  const_iterator& operator++() {
//    if (current != nullptr) {
//      current = current->next;
//    }
//    return *this;
//  }
//
//  //post-fix
//  const_iterator operator--(int) {
//    if (current == nullptr) {
//      const_iterator ret = *this;
//      current = list.back;
//      return ret;
//    }
//    const_iterator ret = *this;
//    current = current->prev;
//    return ret;
//  }
//
//  //prefix
//  const_iterator& operator--() {
//    if (current != nullptr) {
//      current = current->prev;
//    }
//    else {
//      current = list.back;
//    }
//    return *this;
//  }
//
//  bool operator!=(const const_iterator & rhs) const {
//    return (current != rhs.current);
//  }
//
//  bool operator==(const const_iterator & rhs) const {
//    return (current == rhs.current);
//  }
//
//  ~const_iterator() {
//    current = nullptr;
//  }
//
//private:
//
//  LinkedList& list;
//  Node * current;
//
//}; #pragma once
