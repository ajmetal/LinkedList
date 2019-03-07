#include "LinkedList.h"
#include "Stack.h"
#include <string>
#include <iostream>
#include <list>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;

void printList(list<string> list) {
  for (auto i = list.begin(); i != list.end(); ++i) {
    cout << *i << ", ";
  }
  cout << endl;
}

void printList(LinkedList<string> list) {
  for (auto i = list.begin(); i != list.end(); ++i) {
    cout << *i << ", ";
  }
  cout << endl;
}

int main()
{

  //list<string> stl_list;
  //LinkedList<string> my_list;
  //for (int i = 'A'; i < 'Z' + 1; ++i) {
  //  stl_list.push_back(string(1, i));
  //  my_list.push_back(string(1, i));
  //}

  //printList(stl_list);

  //printList(my_list);

  //auto r_position = std::find(stl_list.begin(), stl_list.end(), "R");
  //stl_list.insert(r_position, "7");
  //auto s_position = stl_list.erase(stl_list.begin(), r_position);
  //printList(stl_list);

  //auto my_r = std::find(my_list.begin(), my_list.end(), "R");
  //my_list.insert(my_r, "7");
  //printList(my_list);
  //auto my_s = my_list.erase(my_list.begin(), my_r);

  stack<string> stl_stack;
  Stack<string> my_stack;

  for (int i = 'A'; i < 'Z' + 1; ++i) {
    stl_stack.push(string(1, i));
    my_stack.push(string(1, i));
  }

  my_stack.top() = "7";

  int size = my_stack.size();
  for (int i = 0; i < size; ++i) {
    cout << my_stack.pop() << ", ";
  }

  cout << endl;

  for (int i = 0; i < size; ++i) {
    cout << stl_stack.top() << ", ";
    stl_stack.pop();
  }

  cout << endl;



}
