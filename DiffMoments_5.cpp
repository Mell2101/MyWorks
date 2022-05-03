#include<iostream>
#include<set>
#include<iterator>
#include<unordered_set>
#include<list>
#include<deque>
#include<string>
#include <queue>

template< typename It >
void printWords(It beg, It end) {
	std::unordered_set<std::string> countWords(beg, end);
	std::copy(countWords.begin(), countWords.end(), std::ostream_iterator<std::string>(std::cout, "; "));
}

void exercise_1() {
	std::vector<std::string> v{ "1", "2", "3", "4", "2", "1", "3", "4", "10", "11", "9" };
	std::cout << "Vector: ";
	printWords(v.begin(), v.end());

	std::list<std::string> l(v.begin(), v.end());
	std::cout << std::endl << "List: ";
	printWords(l.begin(), l.end());

	std::deque<std::string> d(v.begin(), v.end());
	std::cout << std::endl << "Deque: ";
	printWords(d.begin(), d.end());
}

//======================================================

std::string getSentence(std::string& s)
{
	std::string punctuationMarks{ ".?!" };                               // �������������� ����� ����������
	std::string temp;                                                     // ��������� ����������� �� ��������� ������

	for (const char& c : s)                                               // ����������� ���������� ����� ������
	{
		temp.push_back(c);                                                // ��������� ������ ������ � ������������� ��������� �����������

		if (punctuationMarks.find(c) != std::string::npos)                // ���� ������ �������������� ���� ���������� - ����������� �����
		{
			s.erase(0, temp.size());                                      // ������� ��������� ����������� �� ������ ������
			if (temp[0] == ' ') { temp.erase(0, 1); }                     // �������� ������ � ������ �����������, ���� �� ����
			return temp;                                                  // ���������� ��������� �����������
		}
	}

	return {};                                                            // ����� ���������� ������ ������
}

void exercise_2() {
	std::unordered_set<std::string, std::hash<std::string>> sentences;
	std::string currentString, tempString;                                // ������� ��������� ������ � ����� ����������� ����� ������

	while (std::getline(std::cin, currentString))
	{
		if (!currentString.empty())                                       // ���������� ������ ������, ���� ��� ����
		{
			tempString += currentString + ' ';                            // ��������� � ����� ������ ��� �������� �����������, ���� ���������� �� ���������
																		  // ��������� �����������, ���� ����������� ���� ���������� �� ����� ������
			while (true)
			{
				std::string sentence(std::move(getSentence(tempString))); // ���� ����������� �� ��������������� ������ ������
				if (sentence.empty())
				{
					break;                                                // ���������� �����, ���� ��� �� ������ ���������� �����������
				}
				sentences.insert(std::move(sentence));                    // ����� ��������� ��������� ����������� � ���������� ����� �������
			}
		}
	}

	std::priority_queue<std::pair<size_t, std::string>> q;
	for (const auto& sentence : sentences)
	{
		q.push({ sentence.size(), sentence });
	}
	while (!q.empty())
	{
		std::cout << q.top().first << ": " << q.top().second << '\n';
		q.pop();
	}

}

int main() {

	exercise_1();

	std::cout << std::endl << "----------------------------------" << std::endl;
	
	exercise_2();

	return 0;
}