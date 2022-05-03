#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Timer.h"


auto swap1( auto *T1, auto *T2){
	auto B = *T1;
	
	*T1 = *T2;
	*T2 = B;

	return *T1, *T2;
}

void pointer() {

	int var1 = 5;
	int var2 = 6;

	std::string word1 = "Hello";
	std::string word2 = "World";

	int* ptr1 = &var1;
	int* ptr2 = &var2;

	auto* ptr3 = &word1;
	auto* ptr4 = &word2;

	std::cout << var1 << ' ' << var2 << std::endl;
	std::cout << word1 << ' ' << word2 << std::endl;

	swap1(ptr1, ptr2);
	swap1(ptr3, ptr4);

	std::cout << var1 << ' ' << var2 << std::endl;
	std::cout << word1 << ' ' << word2 << std::endl;
}
//=================================================
void SortPointer(std::vector<int*> &v) {
	

	
	std::sort(v.begin(), v.end(), 
		[](const auto& v1, const auto& v2) {
		return *v1 < *v2;
		});

}


void sortVector() {
	std::vector<int*> point;
	int arr[10];
	for (int i = 0; i < 10; i++) {

		arr[i] = rand() % 10;
		point.push_back(&arr[i]);
		std::cout << *point[i] << std::endl;
	}

	SortPointer(point);

	std::cout << "=========================" << std::endl;

	for (int i = 0; i < 9; i++) {

		std::cout << *point[i] << std::endl;
	}
}
//=================================================

namespace book {
	const std::string_view vowels{ " AEIOUaeiou" };

	void method_1(const std::string_view& s) {

		Timer timer("Couting vowels [method 1]");
		size_t count = std::count_if(s.begin(), s.end(), [&](const auto& c) {
			return vowels.find(c) != std::string::npos;
			});
		std::cout << count << std::endl;
		timer.print();
	}

	void method_2(const std::string_view& s) {

		Timer timer("Couting vowels [method 2]");
		size_t count = std::count_if(s.begin(), s.end(), [&](const auto& c) {
			for (size_t i = 0; i < vowels.size(); ++i) {
				if (vowels[i] == c)
					return true;
			}
			return false;
			});
		std::cout << count << std::endl;
		timer.print();
	}

	void method_3(const std::string_view& s) {

		size_t count = 0;
		Timer timer("Couting vowels [method 3]");
		for (size_t i = 0; i < s.size(); ++i) {
			if (vowels.find(s[i] != std::string::npos)) ++count;

		}

		std::cout << count << std::endl;
		timer.print();
	}

	void method_4(const std::string_view& s) {

		size_t count = 0;
		Timer timer("Couting vowels [method 4]");
		for (size_t i = 0; i < s.size(); ++i) {
			for (size_t j = 0; j < vowels.size(); ++j) {
				if (vowels[j] == s[i]) ++count;
			}
		}

		std::cout << count << std::endl;
		timer.print();
	}
}

int main()
{
	std::ifstream file("D:\\War and Peace.txt");
	file.seekg(0, std::ios::end);

	size_t size = file.tellg();
	file.seekg(0);
	std::string s(size, ' ');
	file.read(&s[0], size);

	book::method_1(s);
	book::method_2(s);
	book::method_3(s);
	book::method_4(s);

	std::cout << "=========================" << std::endl;
	
	sortVector();

	std::cout << "=========================" << std::endl;
	
	pointer();

	return 0;
		
}

