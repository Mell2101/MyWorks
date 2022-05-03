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
	std::string punctuationMarks{ ".?!" };                               // разделительные знаки пунктуации
	std::string temp;                                                     // найденное предложение из введенных данных

	for (const char& c : s)                                               // посимвольно перебираем поток данных
	{
		temp.push_back(c);                                                // добавляем каждый символ в потенциальное найденное предложение

		if (punctuationMarks.find(c) != std::string::npos)                // если найден разделительный знак пунктуации - заканчиваем поиск
		{
			s.erase(0, temp.size());                                      // удаляем найденное предложение из потока данных
			if (temp[0] == ' ') { temp.erase(0, 1); }                     // обрезаем пробел в начале предложения, если он есть
			return temp;                                                  // возвращаем найденное предложение
		}
	}

	return {};                                                            // иначе возвращаем пустой объект
}

void exercise_2() {
	std::unordered_set<std::string, std::hash<std::string>> sentences;
	std::string currentString, tempString;                                // текущая считанная строка и новый формируемый поток данных

	while (std::getline(std::cin, currentString))
	{
		if (!currentString.empty())                                       // пропускаем пустую строку, если она есть
		{
			tempString += currentString + ' ';                            // суммируем в новом потоке все введённые предложения, если предыдущее не закончено
																		  // добавляем разделитель, если предложение было перенесено на новую строку
			while (true)
			{
				std::string sentence(std::move(getSentence(tempString))); // ищем предложение из сформированного потока данных
				if (sentence.empty())
				{
					break;                                                // прекращаем поиск, если нет ни одного найденного предложения
				}
				sentences.insert(std::move(sentence));                    // иначе сохраняем найденное предложение и продолжаем поиск другого
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