#include<iostream>
#include<cmath>
#include<vector>

int main(){
	int size;
	std::cin >> size;
	std::vector<float> nums;
	float sum = 0;
	float average = 0;
	for (int i = 0; i < size; i++){
		float temp_float;
		std::cin >> temp_float;
		nums.push_back(temp_float);
		sum += temp_float;
	}
	average = sum / size;
	std::cout << "The average value is: " << average << std::endl;
	for (int i = 0; i < size; i ++){
		if (nums[i] < average){
			std::cout << nums[i] << std::endl;
		}
	}
	return 0;
}
