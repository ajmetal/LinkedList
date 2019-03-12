#include "LinkedList.h"
#include "Stack.h"
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;

template<class Container>
void print_container(const Container container) {
  stringstream ss;
  for (auto i = container.begin(); i != container.end(); ++i) {
    ss << *i << ", ";
  }
  ss.seekp(-2, ss.cur);
  cout << ss.str() << endl;
}

int main()
{

  list<string> stl_list;
  LinkedList<string> my_list;

  //auto b_position = find(my_list.begin(), my_list.end(), "B");
  //auto beforeB = my_list.insert(b_position, "before B");

  stl_list.insert(stl_list.end(), "foo");

  for (int i = 'A'; i < 'Z' + 1; ++i) {
    stl_list.push_back(move(string(1, i)));
    my_list.push_back(move(string(1, i)));
  }

  for (auto & i : my_list) {
    cout << i << ", ";
  }

  cout << endl;
  
  //stl_list.insert(stl_list.end(), "foo");

  LinkedList<string> copycopy = my_list;
  LinkedList<string> movecopy = move(my_list);

  my_list.insert(my_list.begin(), "front");
  my_list.insert(my_list.end(), "back");

  my_list.erase(my_list.begin());
  my_list.erase(--my_list.end());
  print_container(my_list);

  auto x_position = find(my_list.begin(), my_list.end(), "X");
  auto beforeX = my_list.insert(x_position, "before X");
  print_container(my_list);
  my_list.erase(beforeX);
  print_container(my_list);

  LinkedList<string> copy_list = my_list;

  assert(copy_list == my_list && "copied list was not the same");

  my_list.pop_back();
  my_list.pop_front();
  print_container(my_list);
  //auto last = my_list.end()--;

  //while (last != my_list.end()) {
  //  if (*last == "R") break;
  //  --last;
  //}
  //
  ////auto r_position = find(stl_list.begin(), stl_list.end(), "R");

  //auto x_pos = find_if(my_list.begin(), my_list.end(), [](string s) {
  //  return (s == "X");
  //});

  //stl_list.insert(r_position, "7");
  //auto s_position = stl_list.erase(stl_list.begin(), r_position);
  //printList(stl_list);

  //auto my_r = find(my_list.begin(), my_list.end(), "R");
  //my_list.insert(my_r, "7");
  //printList(my_list);
  //auto my_s = my_list.erase(my_list.begin(), my_r);

  //stack<string> stl_stack;
  //Stack<string> my_stack;

  //for (int i = 'A'; i < 'Z' + 1; ++i) {
  //  stl_stack.push(string(1, i));
  //  my_stack.push(string(1, i));
  //}

  //my_stack.top() = "7";

  //int size = my_stack.size();
  //for (int i = 0; i < size; ++i) {
  //  cout << my_stack.pop() << ", ";
  //}

  //cout << endl;

  //for (int i = 0; i < size; ++i) {
  //  cout << stl_stack.top() << ", ";
  //  stl_stack.pop();
  //}

  //cout << endl;



}
