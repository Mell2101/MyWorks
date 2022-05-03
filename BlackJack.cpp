#include <iostream>
#include <string>

class DivisionZero {
private:
    std::string m_message;
public:
    DivisionZero(std::string message = "") :m_message(message) {}
    const std::string& getMessage() const {
        return m_message;
    }
};

namespace my {
    template<typename T>
    double div(T numerator, T denominator) {
        if (denominator == 0) {
            throw DivisionZero("Denominator cannot be zero");
            return numerator / denominator;
        }
    }
}

void exception() {
    try {
        double result = my::div(5, 0);
        std::cout << result << std::endl;
    }
    catch (const DivisionZero& e) {
        std::cerr << e.getMessage() << std::endl;
    }
}
//===============================================================

class Ex {
public: 
    double m_X;
    Ex(double x) : m_X(x) {}
};

class Bar {
private:
    double m_Y;
public:
    Bar(double y = 0.0) : m_Y(y) {}
    void set(double a) {
        if ((m_Y + a) > 100) {
            throw Ex(a * m_Y);
        }
        else {
            m_Y = a;
        }
    }
};

void exception_1() {
    Bar a;
    int b;

    try {
        while (true){
            std::cin >> b;
            if (b == 0) break;
            a.set(b);
        }
    }
    catch (const Ex& e) {
        std::cout << e.m_X << std::endl;
    }
}
//=========================================================

class OffTheField {
private:
    int cur_pos_X;
    int cur_pos_Y;
    int new_pos_X;
    int new_pos_Y;
    std::string m_message;
public:

    OffTheField(int c_X, int c_Y, int n_X, int n_Y) :
        cur_pos_X(c_X), cur_pos_Y(c_Y), new_pos_X(n_X), new_pos_Y(n_Y), m_message("") {
    
        if (new_pos_X > 10 || cur_pos_X < 1) {
            m_message += "Coordinate X error! The robot goes out of the field! \n";

            m_message += '[' + std::to_string(cur_pos_X) + ';' + std::to_string(cur_pos_Y) + "] => [" +
                std::to_string(new_pos_X) + ';' + std::to_string(new_pos_X) + "]\n";
        }

        if (new_pos_Y > 10 || new_pos_Y < 1) {
            m_message += "Coordinate Y error! The robot goes out of the field! \n";

            m_message += '[' + std::to_string(cur_pos_X) + ';' + std::to_string(cur_pos_Y) + "] => [" +
                std::to_string(new_pos_X) + ';' + std::to_string(new_pos_X) + "]\n";
        }
    }

    
    const std::string& getInfo() const{
    
        return m_message;
    }
};


class IllegalCammand {
private:
    int cur_pos_X;
    int cur_pos_Y;
    int new_pos_X;
    int new_pos_Y;
    std::string m_message;
public:
    IllegalCammand(int c_x, int c_y, int n_x, int n_y) :
        cur_pos_X(c_x), cur_pos_Y(c_y), new_pos_X(n_x), new_pos_Y(n_y), m_message("") {
        
        if (abs(cur_pos_X - new_pos_X) > 1) {
            m_message += "Error! Step X is too big \n";

            m_message += '[' + std::to_string(cur_pos_X) + ';' + std::to_string(cur_pos_Y) + "] => [" +
                std::to_string(new_pos_X) + ';' + std::to_string(new_pos_Y) + "] \n";
        }

        if (abs(cur_pos_Y - new_pos_Y) > 1) {
            m_message += "Error! Step Y is too big \n";

            m_message += '[' + std::to_string(cur_pos_X) + ';' + std::to_string(cur_pos_Y) + "] => [" +
                std::to_string(new_pos_X) + ';' + std::to_string(new_pos_Y) + "] \n";
        }

        if (cur_pos_X == new_pos_X && cur_pos_Y == new_pos_Y) {
            m_message += "Error! Cannot go to the same place! \n";

            m_message += '[' + std::to_string(cur_pos_X) + ';' + std::to_string(cur_pos_Y) + "] => [" +
                std::to_string(new_pos_X) + ';' + std::to_string(new_pos_Y) + "] \n";

        }

    }

    const std::string& getIngo() const {
        return m_message;
    }
};


class Robot {
private:
    int pos_X;
    int pos_Y;
public:
    Robot(int X = 5, int Y = 5) : pos_X(X), pos_Y(Y) {
        std::cout << "Start position Robot [ " << pos_X << ';' << pos_Y << ']' << std::endl;
    }

    void move(int x, int y);
};

void Robot::move(int x, int y) {
    if (abs(pos_X - x) > 1 || abs(pos_Y - y) > 1 || (pos_X == x && pos_Y == y))
        throw IllegalCammand(pos_X, pos_Y, x, y);
    if (x > 10 || x < 1 || y > 10 || y < 1)
        throw OffTheField(pos_X, pos_Y, x, y);

    std::cout << "Robot does step! [" << pos_X << ';' << pos_Y << "] => [" << x << ';' << y << ']' << std::endl;

    pos_X = x;
    pos_Y = y;
}

void exception_2() {
    int x = 0, y = 0;
    
    Robot robot;

    while (true)
    {
        std::cin >> x >> y;

        if (x == 0 && y == 0) break;

        try{
            robot.move(x, y);

        }
        catch (const IllegalCammand& e){
            
            std::cerr << e.getIngo() << std::endl;
        }
        catch (const OffTheField& e) {
            std::cerr << e.getInfo() << std::endl;
        }

    }
}

int main()
{
    exception();
    exception_1();
    exception_2();
    
    return 0;
}

