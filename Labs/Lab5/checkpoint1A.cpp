#include <iostream>
#include <string>
#include <vector>


template <class T>
void print(std::vector<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (unsigned int i = 0; i < data.size(); i++) {
    std::cout << " " << data[i];
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::vector<T> &data) {
  // FILL IN THIS FUNCTION
	unsigned int i = data.size();
	unsigned int j = 0;
	for(i--; j < data.size() / 2 && i != j; i--, j++){
		T temp;
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}

int main() {
  std::vector<int> data;
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

  std::vector<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

	std::vector<int> test1;
	test1.push_back(2);

	print(test1, "before");
	reverse(test1);
	print(test1, "after");

	std::vector<int> test2;
	test2.push_back(2);
	test2.push_back(3);
	print(test2, "before");
	reverse(test2);
	print(test2, "after");

	std::vector<int> test3;
	print(test3, "before");
	reverse(test3);
	print(test3, "after");
}
