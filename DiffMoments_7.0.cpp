#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include"protobuf/Exercize_2.pb.h"





void exercize_2() {
    exercise_2::FullName fn;
    fn.set_name("Timofey");
    fn.set_surname("Kagochkin");
    fn.set_patronymic("0");

    exercise_2::Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(2);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    exercise_2::StudentsGroup sg;
    *sg.add_students() = s;

    std::ofstream out("student.bin", std::ios_base::binary);
    sg.SerializeToOstream(&out);
    out.close();

    exercise_2::StudentsGroup new_sg;
    std::ifstream in("student.bin", std::ios_base::binary);
    if (new_sg.ParseFromIstream(&in))
    {
        std::cout << new_sg.students(0).name().surname() << std::endl;
        std::cout << new_sg.students(0).avg_score() << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
    in.close();
}

namespace SG {
    class IRepository {
    public:
        virtual void Open() = 0;
        virtual void Save() = 0;
        virtual ~IRepository() {};
    };

    class IMethod {
    public:
        virtual double GetAverageScore(const exercise_2::FullName& name) = 0;
        virtual std::string GetAllInfo(const exercise_2::FullName& name) = 0;
        virtual std::string GetAllInfo() = 0;
        virtual ~IMethod() {};
    };

    class StudentsGroup : public IRepository, public IMethod {
        std::vector<exercise_2::Student> student;
    public:
        void addStudent(const exercise_2::Student& s) {
            student.push_back(s);
        }

        double GetAverageScore(const exercise_2::FullName& name) {
            auto it = std::find_if(student.begin(), student.end(), [&](const exercise_2::Student& s) {
                return tie(s.name().name(), s.name().surname(), s.name().patronymic()) ==
                    tie(name.name(), name.surname(), name.patronymic());
                });
            if (it == student.end()) return {};

            return it->avg_score();
        }

        std::string GetAllInfo(const exercise_2::FullName& name) {
            auto it = std::find_if(student.begin(), student.end(), [&](const exercise_2::Student& s) {
                return tie(s.name().name(), s.name().surname(), s.name().patronymic()) ==
                    tie(name.name(), name.surname(), name.patronymic());
                });

            if (it == student.end()) return{};

            std::string temp = "Name: " + it->name().name() + ' ' + it->name().surname() 
                + it->name().patronymic() + '\n';
            temp += "Estimates: ";
            for (int i = 0; i < it->grades().size(); ++i) {
                temp += std::to_string(it->grades(i)) + "; ";
            }
            temp += '\n';
            temp += "Grade point average: " + std::to_string(it->avg_score()) + "\n\n";

            return temp;
        }

        std::string GetAllInfo() {
            std::string temp;
            std::for_each(student.begin(), student.end(), [&](const exercise_2::Student& s) {
                temp += GetAllInfo(s.name());
                });

            return temp;
        }

        void Save() {
            std::ofstream out("data.bin", std::ios_base::binary);
            auto size = student.size();
            out.write(reinterpret_cast<char*>(&size), sizeof(size));
            std::for_each(student.begin(), student.end(), [&](const exercise_2::Student& s) {
                s.SerializePartialToOstream(&out);
                });
            out.close();
        }

        void Open() {
            std::ifstream in("data.bin", std::ios_base::binary);
            int size = 0;
            in.read(reinterpret_cast<char*>(&size), sizeof(size));
            while (size--)
            {
                exercise_2::Student s;
                s.ParseFromIstream(&in);
                student.push_back(std::move(s));
            }
            in.close();
        }
        virtual ~StudentsGroup() {};
    };
}

void exercize_3() {
    exercise_2::FullName fn;
    fn.set_name("Timofey");
    fn.set_surname("Kagochkin");
    fn.set_patronymic("Alexandrovich");

    exercise_2::Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(2);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(3);
    s.add_grades(5);
    s.add_grades(2);
    s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / 
        s.grades().size());

    SG::StudentsGroup sg;
    sg.addStudent(s);
    sg.Save();

    SG::StudentsGroup new_sg;
    new_sg.Open();
    std::cout << new_sg.GetAllInfo(fn) << std::endl;
}

int main()
{
    exercize_2();
    std::cout << "================================" << std::endl;
    exercize_3();

    
    return 0;
}

