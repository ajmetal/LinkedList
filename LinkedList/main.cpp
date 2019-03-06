#include "LinkedList.h"
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{

  vector<string> words;
  for (int i = 'A'; i < 'Z' + 1; ++i) {
    words.push_back(string(1, i));
  }

  LinkedList<string> string_list;

  auto head = string_list.begin();
  auto foo = string_list.push_front("foo");
  string_list.erase(foo);
  auto tail = string_list.end();

  if (head == tail) {
    cout << "begin() and end() iterators are equal when list is empty." << endl;
  }

  for (auto& it : words) {
    string_list.push_back(it);
  }

  for (LinkedList<string>::iterator it = string_list.begin(); it != string_list.end(); ++it) {
    cout << *it << endl;
  }

  //ostream_iterator<string> out_it(cout, ", ");
  //copy(string_list.begin(), string_list.end(), out_it);

  cout << string_list.toString() << endl;
  auto r_position = std::find(string_list.begin(), string_list.end(), "R");   
  auto s_position = string_list.erase(string_list.begin(), r_position);
  cout << *s_position << endl;
  cout << string_list.toString() << endl;
}