// Решение уравнение с помощью квадратных матриц методом Гаусса и методом Крамера
// 907 строк

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h";
using namespace std;

int main()
{
	// вывод русских букв в консоль
	setlocale(LC_ALL, "Rus");

	// вывод в отельный файл .txt (ios::app - открывает файл в режиме добавления)
	ofstream infile;
	infile.open("solving equations.txt");

	cout << "РЕШЕНИЕ УРАВНЕНИЙ С ПОМОЩЬЮ КВАДРАТНЫХ МАТРИЦ МЕТОДОМ ГАУССА И МЕТОДОМ КРАМЕРА" << endl << endl;

	// создание размеров матрицы
	int rows, columns;
	cout << "Введите количество уравнений (строк матрицы) и количество переменных (столбцов матрицы)." << endl;
	cout << "Введите количество уравнений: ";
	cin >> rows;
	cout << "Введите количество переменных: ";
	cin >> columns;
	if (rows <= 0 or columns <= 0 or rows != columns) {
		while (true) {
			cout << "Ошибка! ";
			if (rows <= 0 or columns <= 0) {
				cout << "Введите числа, большие нуля!" << endl;
				cout << "Введите количество уравнений: ";
				cin >> rows;
				cout << "Введите количество переменных: ";
				cin >> columns;
			}
			else if (rows != columns) {
				cout << "Количество уравнений не равно количеству переменных! Введите числа заново!" << endl;
				cout << "Введите количество уравнений: ";
				cin >> rows;
				cout << "Введите количество переменных: ";
				cin >> columns;
			}
			if (rows > 0 and columns > 0 and rows == columns) {
				break;
			}
		}
	}

	// создание матрицы A и B (переменные и ответы)
	double** MatricaA = new double* [rows];
	for (int i = 0; i < rows; ++i) {
		MatricaA[i] = new double[columns];
	}
	double* MatricaB = new double[rows];

	// указание значений матрицы
	cout << endl << "Укажите коэффициенты при переменных (вводите числа с точностью до 2 знаков после запятой)" << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns + 1; ++j) {
			if (j != columns) {
				cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
				cin >> MatricaA[i][j];
			}
			else {
				cout << "B[" << i + 1 << "] = ";
				cin >> MatricaB[i];
			}
		}
	}
	cout << endl;

	// вывод уравнения
	cout << "Заданные числа образуют следующее уравнение:" << endl;
	print_uravnenie(MatricaA, MatricaB, rows, columns);
	cout << endl;

	// вывод матрицы
	cout << "Данное уравнение предлагается решить с помощью квадратной матрицы методом Гаусса или методом Крамера." << endl;
	cout << "Матрица данного уравнения выглядит следующим образом:" << endl;
	print_matrica(MatricaA, MatricaB, rows, columns);
	cout << endl;

	// выбор метода, которым будет решена матрица
	int metod; // переменная metod принимает значение либо 1, либо 2
	cout << "Выберите каким методом будет решено уравнение (1 - метод Гаусса, 2 - метод Крамера): ";
	cin >> metod;

	// решение выбранным методом
	while (metod != 1 or metod != 2) {
		if (metod == 1) {
			cout << "Вы выбрали решение методом Гаусса." << endl;
			Gauss(MatricaA, MatricaB, rows, columns);
			break;
		}
		else if (metod == 2) {
			cout << "Вы выбрали решение методом Крамера." << endl;
			Kramer(MatricaA, MatricaB, rows, columns);
			break;
		}
		else {
			cout << "Ошибка. Введите либо 1, либо 2: ";
			cin >> metod;
		}
	}

	infile.close();

	// удаление массивов
	for (int i = 0; i < rows; ++i) {
		delete[] MatricaA[i];
	}
	delete[] MatricaA;
	delete[] MatricaB;
	return 0;
}
