#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
#include <random>

/*
Имеется отсортированный массив целых чисел. Необходимо разработать функцию 
insert_sorted, которая принимает вектор и новое число и 
вставляет новое число в определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером,
содержащим любой тип значения.
*/


void insert_sorted_1(std::vector<int> &v, int val) {

    std::vector<int>::iterator low;
    low = std::lower_bound(v.begin(), v.end(), val);
    int pos = low - v.begin();
    std::cout << "lower_bound at position:" << pos << std::endl;

    v.insert( v.begin() + pos, val);

    for_each(v.begin(), v.end(),
        [](int i) { std::cout << i << std::endl;});
}

template<template<typename, typename> class TContainer, typename TItem, typename TIterator>
void insert_sorted_2(TContainer<TItem, TIterator>& c, const TItem& i)
{
    
    typename TContainer<TItem, TIterator>::iterator it = find_if(c.begin(), c.end(), [&](const TItem& current)
        {
            return current >= i;
        });
    
    c.insert(it, i);

    for_each(c.begin(), c.end(),
        [](auto i) { std::cout << i << std::endl;});
}

void exercise_1() {
    int var1 = 12;
    std::string var2 = "9";

    std::vector<int> vec(15);
    std::deque<std::string> st;
    st = { "1", "5", "8", "2" };
    

    std::generate(vec.begin(), vec.end(),
        []() { return rand() % 100; });
   

    std::sort(vec.begin(), vec.end());
    std::sort(st.begin(), st.end());

    for_each(vec.begin(), vec.end(),
        [](int i) { std::cout << i << std::endl;});

    std::cout << "======================= insert_sorted_1:" << std::endl;
    insert_sorted_1(vec, 65);

    std::cout << "=======================  insert_sort_2:" << std::endl;
    insert_sorted_2(vec,41);

    std::cout << "=======================  insert_sort_2:" << std::endl;
    insert_sorted_2(st,var2);

   
}
//=======================================================================================

/*
Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала. 
На основе этого массива чисел создайте другой вектор целых чисел b, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел. 
Выведите получившиеся массивы чисел. Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле:
где:
N - количество элементов в векторе,
a - элемент вектора с дробными числами, b - элемент вектора с целыми числами
Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы.
*/

template<template<typename, typename> class TContainer, typename TItem, typename TIterator, typename T>
void generator(TContainer<TItem, TIterator>& c, const T& rangeStart, const T& rangeEnd){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<double> urd(rangeStart, rangeEnd);
    std::generate(c.begin(), c.end(), [&]() 
        {return urd(mersenne);}
    );
    
}

void exercise_2() {
    std::vector<double> v(100);

    double error = 0;
  
    generator(v, -1000.0, 1000.0);
    for_each(v.begin(), v.end(), [](auto i) {std::cout << i << ' ';});   // 1-ый вектор - печать исходного вектора

    std::cout << std::endl << "-----------------------------" << std::endl;

    copy(v.begin(), v.end(), std::ostream_iterator<int> { std::cout, " " });     // 2-ой вектор - печать целочисленного вектора

    std::cout << std::endl << "-----------------------------" << std::endl;

    for_each(v.begin(), v.end(), [&](const double& i)
        {
            error += pow(i - static_cast<int>(i), 2);
        });

    std::cout <<std:: endl << error << std::endl;
}



int main()
{
    exercise_1();
    std::cout << "==========================" << std::endl;
    exercise_2();

    return 0;
}

