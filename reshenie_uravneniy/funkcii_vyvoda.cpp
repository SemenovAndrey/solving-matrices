#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h"
using namespace std;

// вывод расширенной матрицы в консоль
void print_matrica(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	// i - номер строки
	for (int i = 0; i < rows; ++i) {
		cout << setw(2) << left << "( ";
		// j - номер столбца
		for (int j = 0; j < columns + 1; ++j) {
			// вывод  матрицы А
			if (j != columns) {
				cout << setw(7) << left << ArrayA[i][j];
			}
			//вывод матрицы В
			else {
				cout << setw(6) << left << setw(0) << "| " << setw(6) << left << ArrayB[i];
			}
		}
		cout << " )" << endl;
	}
}

// для определения дельт
// вывод обычной матрицы А
void print_not_all_matrica(double* Array[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// i - номер строки
	for (int i = 0; i < rows; ++i) {
		infile << setw(2) << left << "( ";
		// j - номер столбца
		for (int j = 0; j < columns; ++j) {
			infile << setw(7) << left << Array[i][j];
		}
		infile << " )" << endl;
	}

	infile.close();
}

// вывод расширенной матрицы в файл .txt
void print_matrica_in_txt(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// i - номер строки
	for (int i = 0; i < rows; ++i) {
		infile << setw(2) << left << "( ";
		// j - номер столбца
		for (int j = 0; j < columns + 1; ++j) {
			// вывод матрицы А
			if (j != columns) {
				infile << setw(7) << left << ArrayA[i][j];
			}
			// вывод матрицы В
			else {
				infile << setw(6) << left << setw(0) << "| " << setw(6) << left << ArrayB[i];
			}
		}
		infile << " )" << endl;
	}

	infile.close();
}

// в функции приведения матрицы к треугольному виду
// вывод массива, который является расширенной матрицей
void print_new_matrica(double* Array[], int rows, int columns)
{
	// вывод расширенной матрицы

	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// i - номер строки
	for (int i = 0; i < rows; ++i) {
		infile << setw(2) << left << "( ";
		// j - номер столбца
		for (int j = 0; j < columns; ++j) {
			// вывод матрицы А внутри расширенной
			if (j != columns - 1) {
				infile << setw(7) << left << Array[i][j];
			}
			// вывод матрицы В внутри расширенной
			else {
				infile << setw(6) << left << setw(0) << "| " << setw(6) << left << Array[i][j];
			}
		}
		infile << " )" << endl;
	}

	infile.close();
}

// вывод уравнения в файл .txt
void print_uravnenie_in_txt(double* Array[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < rows; ++i) {
		// i - номер строчки
		for (int j = 0; j < columns + 1; ++j) {
			// j - номер столбца
			if (j != columns) {
				// вывод элемента столбца, если он равен нулю
				if (Array[i][j] == 0) {
					for (int i = 0; i < 11; ++i) {
						infile << " ";
					}
				}
				// вывод столбцов
				else {
					// вывод первого столбца
					if (j == 0) {
						if (Array[i][j] > 0) {
							infile << setw(0) << " " << setw(6) << right << Array[i][j] << setw(0) << "*x" << j + 1 << " ";
						}
						else if (Array[i][j] < 0) {
							infile << "-" << setw(6) << right << abs(Array[i][j]) << setw(0) << "*x" << j + 1 << " ";
						}
					}
					// вывод не первого столбца
					else if (j != 0) {
						if (Array[i][j] > 0) {
							infile << setw(0) << "+" << setw(6) << right << Array[i][j] << setw(0) << "*x" << j + 1 << " ";
						}
						else if (Array[i][j] < 0) {
							infile << setw(0) << "-" << setw(6) << right << abs(Array[i][j]) << setw(0) << "*x" << j + 1 << " ";
						}
					}
				}
			}
			// вывод того, чему равна матрица
			else {
				infile << setw(0) << "= " << ArrayB[i] << endl;
			}
		}
	}

	infile.close();
}

// вывод уравнения в консоль
void print_uravnenie(double* Array[], double ArrayB[], int rows, int columns)
{
	for (int i = 0; i < rows; ++i) {
		// i - номер строчки
		for (int j = 0; j < columns + 1; ++j) {
			// j - номер столбца
			if (j != columns) {
				// вывод элемента столбца, если он равен нулю
				if (Array[i][j] == 0) {
					for (int i = 0; i < 11; ++i) {
						cout << " ";
					}
				}
				// вывод столбцов
				else {
					// вывод первого столбца
					if (j == 0) {
						if (Array[i][j] > 0) {
							cout << setw(0) << " " << setw(6) << right << Array[i][j] << setw(0) << "*x" << j + 1 << " ";
						}
						else if (Array[i][j] < 0) {
							cout << "-" << setw(6) << right << abs(Array[i][j]) << setw(0) << "*x" << j + 1 << " ";
						}
					}
					// вывод не первого столбца
					else if (j != 0) {
						if (Array[i][j] > 0) {
							cout << setw(0) << "+" << setw(6) << right << Array[i][j] << setw(0) << "*x" << j + 1 << " ";
						}
						else if (Array[i][j] < 0) {
							cout << setw(0) << "-" << setw(6) << right << abs(Array[i][j]) << setw(0) << "*x" << j + 1 << " ";
						}
					}
				}
			}
			// вывод того, чему равна матрица
			else {
				cout << setw(0) << "= " << ArrayB[i] << endl;
			}
		}
	}
}

// вывод дельт
void print_delta(double Array[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < size; ++i) {
		infile << "\177" << "x" << i + 1 << " = " << Array[i] << endl;
	}

	infile.close();
}

// вывод ответов в столбик для метода Крамера
void print_answers_in_column_for_Kramer(double Array[], int size, double opredelitel)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < size; ++i) {
		infile << "x" << i + 1 << " = " << Array[i] << " / " << opredelitel << " = " << Array[i] / opredelitel << endl;
	}

	infile.close();
}

// вывод ответов для метода Крамера
void print_answers_for_Kramer(double Array[], int size, double opredelitel)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	infile << "Ответ: ";
	for (int i = 0; i < size; ++i) {
		if (i != size - 1) {
			infile << "x" << i + 1 << " = " << Array[i] / opredelitel << "; ";
		}
		else {
			infile << "x" << i + 1 << " = " << Array[i] / opredelitel << ".";
		}
	}

	infile.close();
}

// вывод ответов в стобик для метода Гаусса
void print_answers_in_column_for_Gauss(double Array[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < size; ++i) {
		infile << "x" << i + 1 << " = " << Array[i] << endl;
	}

	infile.close();
}

// вывод ответов для метода Гаусса
void print_answers_for_Gauss(double Array[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	infile << "Ответ: ";
	for (int i = 0; i < size; ++i) {
		if (i != size - 1) {
			infile << "x" << i + 1 << " = " << Array[i] << "; ";
		}
		else {
			infile << "x" << i + 1 << " = " << Array[i] << ".";
		}
	}

	infile.close();
}
