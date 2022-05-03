#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

std::mutex m;

void pcout(int num) {

    
    std::lock_guard lock1(m);
    std::cout << "Start thread " << num << std::endl;
    std::cout << "Finish thread " << num << std::endl;
    
}
void exersize_1() {
    std::thread th1(pcout, 1);
    std::thread th2(pcout, 2);
    std::thread th3(pcout, 3);
    th1.join();
    th2.join();
    th3.join();
}
//======================================
class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};
bool isPrime(size_t num) {
    size_t limit = num / 2;
    if (num > 2) {
        for (size_t i = 2; i <= limit; ++i) {
            if (num % i == 0) {
                return false;
            }
        }
    }

    return true;
}
void exersize_2() {
    int maxValue = 25000;
    int countThreads = 10;
    std::vector<int> answers;
    std::mutex m;

    Timer time("With threads");
   
    for (int i = 0; i < maxValue;) {
        std::vector<std::thread> v;

        for (int j = i + countThreads; i <= j; ++i) {
            v.push_back(std::thread([=, &m, &answers]() {
                if (isPrime(i)) {
                    std::lock_guard lock (m);
                    answers.push_back(i);
                }
            }));
        }
        
        for (auto& t : v) {
            t.join();
        }
    }
   
   

    time.print();

    answers.clear();
    answers.shrink_to_fit();
    
    time.start("Without threads");

    for (size_t i = 0; i < maxValue; ++i) {
        if (isPrime(i)) {
            answers.push_back(i);
        }
    }
   
    time.print();
}
//======================================
void generateThings(std::vector<int> &v) {
    std::random_device rand;
    std::mt19937 mersenne(rand());
    std::uniform_int_distribution<int> urd(0, 1000);

    std::lock_guard lock(m);

    std::generate(v.begin(), v.end(), [&]() {
        return urd(mersenne);
    });

}

void popThings(std::vector<int> &v) {
    std::lock_guard lock(m);

    std::cout << *std::max_element(v.begin(), v.end()) << std::endl;

}

void exersize_3() {
    std::vector<int> v(100);
    int count = 100;

    while (count--) {
        std::thread owner([&]() {
            generateThings(v);
            });
        std::thread thief([&]() {
            popThings(v);
            });

        owner.join();
        thief.join();
    }
}


int main()
{
    exersize_1();
    std::cout << "-------------------------" << std::endl;
    exersize_2();
    std::cout << "-------------------------" << std::endl;
    exersize_3();

    return 0;
}

