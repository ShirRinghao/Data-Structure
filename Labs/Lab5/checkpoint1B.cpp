#include <iostream>
#include <string>
#include <vector>
#include <list>

template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
	typename std::list<T>::iterator i = data.begin();
  for (; i != data.end(); i++) {
    std::cout << " " << *i;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
  // FILL IN THIS FUNCTION
	unsigned int curr = 0;
	typename std::list<T>::iterator i = data.begin();
	typename std::list<T>::iterator j = data.end();
	for(j--; curr< data.size()/2 && i != j; curr++, i++, j--){
		T temp = *i;
		*i = *j;
		*j = temp;
	}
}


int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

	std::list<int> test1;
	test1.push_back(2);

	print(test1, "before");
	reverse(test1);
	print(test1, "after");

	std::list<int> test2;
	test2.push_back(2);
	test2.push_back(3);

	print(test2, "before");
	reverse(test2);
	print(test2, "after");

	std::list<int> test3;

	print(test3, "before");
	reverse(test3);
	print(test3, "after");
}
