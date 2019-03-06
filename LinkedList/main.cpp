#include "LinkedList.h"
#include <string>
#include <iostream>
#include <list>
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

  list<string> stl_list;
  LinkedList<string> my_list;
  for (int i = 'A'; i < 'Z' + 1; ++i) {
    stl_list.push_back(string(1, i));
    my_list.push_back(string(1, i));
  }

  printList(stl_list);

  printList(my_list);

  auto r_position = std::find(stl_list.begin(), stl_list.end(), "R");
  stl_list.insert(r_position, "7");
  auto s_position = stl_list.erase(stl_list.begin(), r_position);
  printList(stl_list);

  auto my_r = std::find(my_list.begin(), my_list.end(), "R");
  my_list.insert(my_r, "7");
  cout << my_list.toString() << endl;
  auto my_s = my_list.erase(my_list.begin(), my_r);

}
