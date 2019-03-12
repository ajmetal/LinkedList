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
  for (auto & i : container) {
    ss << string(i) << ", ";
  }
  ss.seekp(-2, ss.cur);
  cout << ss.str() << endl;
}

int main()
{

  //list<string> stl_list;
  LinkedList<string> string_list;


  for (int i = 'A'; i < 'Z' + 1; ++i) {
    string_list.push_back(move(string(1, i)));
  }
  print_container(string_list);

  string_list.insert(string_list.begin(), "front");
  string_list.insert(string_list.end(), "back");

  string_list.erase(string_list.begin());
  string_list.erase(--string_list.end());

  print_container(string_list);

  auto x_position = find(string_list.begin(), string_list.end(), "X");
  auto beforeX = string_list.insert(x_position, "before X");
  print_container(string_list);
  string_list.erase(beforeX);
  print_container(string_list);

  LinkedList<string> copy_list = string_list;

  assert(copy_list == string_list && "copied list was not the same");

  copy_list.push_back("different");

  assert(copy_list != string_list && "lists weren't different");

  copy_list.erase(find(copy_list.begin(), copy_list.end(), "Z"), copy_list.end());
  copy_list.push_back("7");

  assert(copy_list.back() == "7" && "back() returned the wrong value");

  copy_list.back() = "9";

  assert(copy_list.back() == "9" && "value wasn't changed from outside list");

  copy_list.push_front("7");

  assert(copy_list.front() == "7" && "back() returned the wrong value");

  copy_list.front() = "9";

  assert(copy_list.front() == "9" && "value wasn't changed from outside list");

  assert(copy_list != string_list && "lists weren't different");

}
