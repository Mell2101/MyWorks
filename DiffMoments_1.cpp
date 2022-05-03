#include <iostream>
#include <tuple>
#include <optional>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

struct Person
{
	std::string name;  
	std::string surname;
	std::optional<std::string> patronymic;
};

std::optional<std::string> checkPatr(std::string& s) {

	if (s == "") return std::nullopt;
	return s;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {

	out << p.surname << ' ' << p.name << ' ';

	if (p.patronymic.has_value()) {
		out << p.patronymic.value();
	}
	else {
		out << std::setw(5);
	}

	return out;
}

bool operator<(const Person& pr1, const Person& pr2) {

	return std::tie(pr1.surname, pr1.name, pr1.patronymic)< 
		std::tie(pr2.surname, pr2.name, pr2.patronymic);
}

bool operator==(const Person& pr1, const Person& pr2) {

	return std::tie(pr1.surname, pr1.name, pr1.patronymic) ==
		std::tie(pr2.surname, pr2.name, pr2.patronymic);
}
//===================================================================

struct PhoneNumber
{
	int CountryCod = 0;
	int sityCod = 0;
	std::string number;
	std::optional<int> additionalNumber;

};

std::optional<int> checkNumber(std::string& s) {

	if (s == "")
		return std::nullopt;

	return stoi(s);
}

std::ostream& operator<<(std::ostream& out, const PhoneNumber& n) {
	
	out  << std::setw(12) << '+' << n.CountryCod << '(' << n.sityCod << ')' << n.number;

	if (n.additionalNumber.has_value()) {
		out << ' ' << n.additionalNumber.value() << std::endl;
	}
	else {
		out << std::endl;
	}

	return out ;
}

bool operator<(const PhoneNumber& num1, const PhoneNumber& num2) {
	return std::tie(num1.CountryCod, num1.sityCod, num1.number, num1.additionalNumber) <
		std::tie(num2.CountryCod, num2.sityCod, num2.number, num2.additionalNumber);
}

bool operator==(const PhoneNumber& num1, const PhoneNumber& num2) {
	return std::tie(num1.CountryCod, num1.sityCod, num1.number, num1.additionalNumber) ==
		std::tie(num2.CountryCod, num2.sityCod, num2.number, num2.additionalNumber);
}

//===================================================================
class PhoneBook {
	std::vector<std::pair<Person, PhoneNumber>> PersonAndNumber;
public:
	
	PhoneBook(std::ifstream& file);
	
	friend std::ostream& operator<<(std::ostream& out, const PhoneBook& pb);

	void SortByName() {
		std::sort( PersonAndNumber.begin(), PersonAndNumber.end(),
			[](const std::pair<Person, PhoneNumber>& PaP1, const std::pair<Person, PhoneNumber>& PaP2)
			{ return PaP1.first < PaP2.first; });
	}
	void SortByPhone() {
		std::sort(PersonAndNumber.begin(), PersonAndNumber.end(),
			[](const std::pair<Person, PhoneNumber> Pap1, const std::pair<Person, PhoneNumber> Pap2)
			{ return Pap1.second < Pap2.second; });
	}

	std::pair<std::string, std::vector<PhoneNumber>> GetPhoneNumbers(const std::string& f_name) {
		std::vector<PhoneNumber> numbers;
		int count = 0;

		std::for_each(PersonAndNumber.begin(), PersonAndNumber.end(), [&](const auto& entry) {
			if (entry.first.name == f_name) {
				numbers.push_back(entry.second);
				++count;
			}
			});
		switch (count) {
			case 0:
				return{ "not found", numbers };
			case 1:
				return{ "", numbers };
			default:
				return{ "found more than one", numbers };
		}
	}

	void ChangePhoneNumber(const Person& p, const PhoneNumber& pn) {
		auto entry = std::find_if(PersonAndNumber.begin(), PersonAndNumber.end(), [&](const auto& entry) {
			return entry.first == p;
			});

		if (entry != PersonAndNumber.end()) entry->second = pn;

	}
};

std::ostream& operator<<(std::ostream& out, const PhoneBook& pb) {
	for (const auto& [first, second] : pb.PersonAndNumber)
		out << first << ' ' << second;

	return out;
}

PhoneBook::PhoneBook(std::ifstream& file) {
	if (!file) {
		std::cout << "I can`t open the file((" << std::endl;
		exit(-1);
	}

	for (std::string line; std::getline(file, line);) {

		std::stringstream str(line);
		std::vector<std::string> data;

		for (std::string s; std::getline(str, s, ' ');) {
			data.push_back(s);
		}

		std::pair<Person, PhoneNumber> entry;

		for (size_t i = 0; i < data.size(); ++i) {
			switch (i)
			{
			case 0:
				entry.first.surname = data[i];
				break;
			case 1:
				entry.first.name = data[i];
				break;
			case 2:
				entry.first.patronymic = checkPatr(data[i]);
				break;
			case 3:
				entry.second.CountryCod = std::stoi(data[i]);
				break;
			case 4:
				entry.second.sityCod = std::stoi(data[i]);
				break;
			case 5:
				entry.second.number = data[i];
			case 6:
				entry.second.additionalNumber = checkNumber(data[i]);
				break;
			}
		}
		PersonAndNumber.push_back(entry);
	}

}




int main()
{
	std::ifstream file("D:\\PhoneBook1.txt"); // путь к файлу PhoneBook.txt PhoneBook book(file);
	PhoneBook book(file);
	std::cout << book;
	std::cout << "------SortByPhone-------" << std::endl;
	book.SortByPhone();
	std::cout << book;
	std::cout << "------SortByName--------" << std::endl;
	book.SortByName();
	std::cout << book;
	std::cout << "-----GetPhoneNumber-----" << std::endl;
	// лямбда функция, которая принимает фамилию и выводит номер телефона
	//человека, либо строку с ошибкой
		auto print_phone_number = [&book](const std::string& surname) {
			std::cout << surname<< "\t";
			auto answer = book.GetPhoneNumbers(surname);
			if (get<0>(answer).empty())
			{
				for (size_t i = 0; i < get<1>(answer).size(); ++i) {
					std::cout << get<1>(answer)[i];
				}
			}
			else
				std::cout << get<0>(answer);
				std::cout << std::endl;
		};
	// вызовы лямбды
	print_phone_number("Ivanov");
	print_phone_number("Petrov");
	std::cout << "----ChangePhoneNumber----" << std::endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
		PhoneNumber{ 7, 123, "15344458", std::nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
		PhoneNumber{ 16, 465, "9155448", 13 });
	std::cout << book;
	
	return 0;
	
}

