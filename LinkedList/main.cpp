#include "LinkedList.h"
#include <string>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
   
   vector<string> words;
   for (int i = 'A'; i < 'Z' + 1; ++i) {
      words.push_back(string(1, i));
   }

   LinkedList<string> string_list;

   try {
      cout << string_list.pop_back() << endl;
   }
   catch (const std::out_of_range& e) {
      cout << "caught exception: " << e.what() << endl;
   }

   for (auto& it : words) {
      string_list.push_front(it);
   }

   cout << string_list.toString() << endl;
   cout << string_list.pop_front() << endl;
   cout << string_list.toString() << endl;

   int a = 1;
}