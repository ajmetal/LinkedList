#pragma once

#include <string>
#include <sstream>
#include <exception>

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

   LinkedList() 
      : nodeCount(0)
      , front(nullptr)
      , back(nullptr)
   {}

   int size() const {
      return nodeCount;
   }

   bool empty() const {
      return 0 == nodeCount;
   }

   //TODO: return iterator to newly created value
   void push_front(const T& value) {
      Node * toAdd = new Node(value);
      toAdd->next = front;
      front = toAdd;
      ++nodeCount;
      if (1 == nodeCount) {
         back = front;
      }
   }

   //TODO: return iterator to newly created value
   void push_back(const T& value) {
      Node * toAdd = new Node(value);
      toAdd->prev = back; 
      if (nullptr != back) {
         back->next = toAdd;
      }
      back = toAdd;
      if (0 == nodeCount) {
         front = back;
      }
      ++nodeCount;
   }

   T pop_front() {
      if (0 == nodeCount) {
         throw std::out_of_range (
            "An attempt was made to pop_front from an empty list."
         );
      }
      Node * ret = front;
      front = front->next;
      T copy = ret->value;
      delete ret;
      --nodeCount;
      return copy;
   }

   T pop_back() {
      if (0 == nodeCount) {
         throw std::out_of_range (
            "An attempt was made to pop_back from an empty list."
         );
      }
      Node * ret = back;
      back = back->prev;
      T copy = ret->value;
      delete ret;
      --nodeCount;
      return copy;
   }

   std::string toString() const {
      std::stringstream ss;
      ss << "[";
      Node * current = front;
      while (nullptr != current) {
         ss << " " << current->value << ",";
         current = current->next;
      }
      ss.seekp(-1, std::ios_base::end);
      ss << " ]";
      return ss.str();
   }

private:

   Node * front;
   Node * back;
   int nodeCount;
};


