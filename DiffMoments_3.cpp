#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <iomanip>

void arithmetic(std::vector<double> &v) {

	double sum = 0;

	for (int i = 0; i < v.size(); ++i) {
		sum = v[i] + sum;
	}
	
	double arith = sum / v.size();
	v.push_back(arith);
}
void exercize_1() {
	std::vector<double> value;

	for (int i = 0; i < 1000; ++i) {
		value.push_back(rand() % 1000 + 1.5);
	}

	arithmetic(value);

	std::cout << "Average:" << value[1000] << std::endl;

}
//=============================================================
class Matrix {
	
	const size_t matrixSize;
	const size_t matrixCapacity;
	double* array;
	double matrixDeterminant{ 0.0 };

	Matrix getModifiedMatrix(Matrix& arr, const size_t item);
	double calculateDeterminant(Matrix& arr);
public:
	Matrix(const int size);
	void fillRandom();
	void print() const;
	size_t size() const;
	double determinant() const;

	class Iterator {
		double* current;
	public:
		Iterator(double* pointer);
		double& operator[](size_t i);
		Iterator& operator ++();
		bool operator!= (const Iterator& iterator);
		double& operator*();
	};

	Iterator operator[](size_t i);
	Iterator begin();
	Iterator end();

	~Matrix();

};

Matrix::Matrix(const int size) : matrixSize(size), matrixCapacity(size* size) {
	array = new double[matrixCapacity];
}

Matrix::Iterator::Iterator(double* pointer) : current(pointer) {};

double& Matrix::Iterator::operator[](size_t i) {
	return *(current + i);
}

Matrix::Iterator Matrix::operator[](size_t i) {
	return Iterator(array + i * matrixSize);
}

Matrix Matrix::getModifiedMatrix(Matrix& arr, const size_t item) {
	Matrix newArray(arr.size() - 1);
	size_t currentRow = 0;

	for (size_t i = 0; i < arr.size(); ++i) {
		if (item == i) {
			currentRow = i;
			continue;
		}

		for (size_t j = 0; j < newArray.size(); ++j) {
			newArray[currentRow][j] = arr[i][j + 1];
		}

		++currentRow;
	}
	return newArray;
}

double Matrix::calculateDeterminant(Matrix &arr) {
	double determinant = 0;

	if (arr.size() == 1) {

		determinant = arr[0][0];
	}
	else if(arr.size() == 2) {

		determinant = arr[0][0] * arr[1][1] + arr[1][0] * arr[0][1];

	}
	else {
		int sing = 1;

		for (size_t i = 0; i < arr.size(); ++i) {
			Matrix newArray = getModifiedMatrix(arr, i);
			determinant += sing * arr[i][0] * calculateDeterminant(newArray);
			sing = -sing;
		}
	}
	return determinant;
}

void Matrix::fillRandom() {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_real_distribution<double> urd(-10.0, 10.0);

	for (size_t i = 0; i < matrixCapacity; ++i) {
		*(array + i) = round(urd(mersenne) * 10) / 10;
	}

	matrixDeterminant = calculateDeterminant((*this));
}

void Matrix::print() const {
	std::cout << '[';
	for (size_t i = 0; i < matrixCapacity;) {
		std::cout << ' ' << *(array + i++);

		if (!(i % matrixSize)) {
			std::cout << " ]" << std::endl;

			if (i < matrixCapacity) {
				std::cout << '[';
			}
		}
		else
		{
			std::cout << ',';
		}

	}
}

Matrix::Iterator& Matrix::Iterator::operator++() {
	++current;
	return *this;
}

bool Matrix::Iterator::operator!=(const Iterator& iterator) {
	return current != iterator.current;
}

double &Matrix::Iterator::operator*() {
	return *current;
}

Matrix::Iterator Matrix::begin() {
	return Iterator(array);
}

Matrix::Iterator Matrix::end() {
	return Iterator(array + matrixCapacity);
}

size_t Matrix::size() const {
	return matrixSize;
}

double Matrix::determinant() const {
	return matrixDeterminant;
}

Matrix::~Matrix() {
	array = nullptr;
	delete[] array;
}


void exercixe_2() {
	for (size_t i = 1; i < 8; ++i) {
		std::cout << " Matrix " << i << 'x' << i << ':' << std::endl;
		Matrix m(i);
		m.fillRandom();
		m.print();
		std::cout << "Determinant matrix: " << std::setprecision(10) << m.determinant() << "\n\n";
	}
}

void exercixe_3() {
	Matrix m(4);
	m.fillRandom();

	for (const double& i : m) {
		std::cout << ' ' << i;
	}
	std::cout << std::endl;
}


int main()
{
	exercize_1();
	std::cout << "=============================" << std::endl;
	exercixe_2();
	std::cout << "=============================" << std::endl;
	exercixe_3();

	return 0;
}

