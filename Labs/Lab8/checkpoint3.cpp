// A simple "caller ID" program
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int, string> &phonebook, int number, string const &name) {
  phonebook.insert(make_pair(number, name));
}

// given a phone number, determine who is calling
void identify(const map<int, string> &phonebook, int number) {
  if (phonebook.find(number) == phonebook.end())
    cout << "unknown caller!" << endl;
  else {
    cout << phonebook.find(number)->second << " is calling!" << endl;
  }
}

int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
}
