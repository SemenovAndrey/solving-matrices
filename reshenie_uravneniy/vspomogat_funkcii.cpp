#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h"
using namespace std;

// определитель для матрицы 1х1
double Opredelitel1(double* Array[])
{
	return Array[0][0];
}

// определитель для матрицы 2х2
double Opredelitel2(double* Array[])
{
	double opredelitel;
	opredelitel = (Array[0][0] * Array[1][1]) - (Array[0][1] * Array[1][0]);
	return opredelitel;
}

// смена столбов для их последующего сложения/вычитания
void udalenie_stroki(double* Array[], int rows, int columns, int row, int column, double* NewArray[])
{
	// переменные по смещению строки и столбца
	int offset_of_rows = 0, offset_of_columns = 0;

	// изменение матрицы, и последующее её сохранение в новый массив
	for (int i = 0; i < rows - 1; ++i) {
		if (i == row) {
			offset_of_rows = 1;
		}

		offset_of_columns = 0;
		for (int j = 0; j < columns - 1; ++j) {
			if (j == column) {
				offset_of_columns = 1;
			}

			NewArray[i][j] = Array[i + offset_of_rows][j + offset_of_columns];
		}
	}
}

// определитель для матрицы n x m, где n > 2 и m > 2
double Opredelitel(double* ArrayA[], int rows, int columns)
{
	if (rows == 1 and columns == 1) {
		return Opredelitel1(ArrayA);
	}
	else if (rows == 2 and columns == 2) {
		return Opredelitel2(ArrayA);
	}
	else if (rows > 2 and columns > 2 and rows == columns) {
		double opredelitel = 0;
		int znak = 1; // + или - при подсчёте определителя

		// создание нового массива без 0 строки и i столбца
		double** NewArray = new double* [rows - 1];
		for (int i = 0; i < rows; ++i) {
			NewArray[i] = new double[columns - 1];
		}

		// изменение матрицы и подсчёт определителя
		for (int i = 0; i < rows; ++i) {
			udalenie_stroki(ArrayA, rows, columns, 0, i, NewArray);
			opredelitel += znak * ArrayA[0][i] * Opredelitel(NewArray, rows - 1, columns - 1);
			znak = -znak;
		}

		return opredelitel;

		// удаление созданного массива
		for (int i = 0; i < rows; ++i) {
			delete[] NewArray[i];
		}
		delete[] NewArray;
	}
}

// (double для сохранения результатов) изменение матрицы для дельт и нахождение определителя 
double reshenie_matricy_s_zamenoi_stolbca(double* ArrayA[], double ArrayB[], int rows, int columns, int index)
{
	// создание массива, который будет использоваться только внутри этой функции и который сохраняет изменённую матрицу
	double** NewArray = new double* [rows];
	for (int i = 0; i < rows; ++i) {
		NewArray[i] = new double[columns];
	}

	// замена столбца
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (index == j) {
				NewArray[i][j] = ArrayB[i];
			}
			else {
				NewArray[i][j] = ArrayA[i][j];
			}
		}
	}

	// нахождение Δх
	return Opredelitel(NewArray, rows, columns);

	// удаление созданного массива
	for (int i = 0; i < columns; ++i) {
		delete[] NewArray[i];
	}
	delete[] NewArray;
}

// (void для вывода промежуточных ответов)изменение матрицы для дельт и нахождение определителя
void reshenie_matricy_s_zamenoi_stolbca_void(double* ArrayA[], double ArrayB[], int rows, int columns, int index)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// создание массива, который будет использоваться только внутри этой функции и который сохраняет изменённую матрицу
	double** NewArray = new double* [rows];
	for (int i = 0; i < rows; ++i) {
		NewArray[i] = new double[columns];
	}

	// замена столбца
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (index == j) {
				NewArray[i][j] = ArrayB[i];
			}
			else {
				NewArray[i][j] = ArrayA[i][j];
			}
		}
	}

	// вывод изменённой матрицы
	if ((index + 1) % 10 == 3) {
		infile << "Заменив " << index + 1 << "-ий столбец, нужно найти определитель следующей матрицы : " << endl;
	}
	else if ((index + 1) % 10 == 2) {
		infile << "Заменив " << index + 1 << "-ой столбец, нужно найти определитель следующей матрицы : " << endl;
	}
	else {
		infile << "Заменив " << index + 1 << "-ый столбец, нужно найти определитель следующей матрицы : " << endl;
	}
	print_not_all_matrica(NewArray, rows, columns);

	// нахождение Δх
	infile << "И " << "\177" << "x" << index + 1 << " = " << Opredelitel(NewArray, rows, columns) << endl << endl;

	infile.close();

	// удаление созданного массива
	for (int i = 0; i < columns; ++i) {
		delete[] NewArray[i];
	}
	delete[] NewArray;
}

// функция приведения матрицы к треугольному виду
void privedeine_k_treug_vidu(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// создание матрицы, которая в себя будет включать и матрицу А, и матрицу В
	double** NewMatrix = new double* [rows];
	for (int i = 0; i < rows; ++i) {
		NewMatrix[i] = new double[columns + 1];
	}

	// присваивание значений для новой матрицы
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns + 1; ++j) {
			if (j != columns) {
				NewMatrix[i][j] = ArrayA[i][j];
			}
			else {
				NewMatrix[i][columns] = ArrayB[i];
			}
		}
	}

	// преобразования для приведения к треугольному виду
	for (int i = 1; i < rows; ++i) {
		for (int j = i; j < columns; ++j) {
			for (int k = columns; k >= 0; --k) {
				if (NewMatrix[i - 1][i - 1] != 0) {
					NewMatrix[j][k] -= NewMatrix[j][i - 1] / NewMatrix[i - 1][i - 1] * NewMatrix[i - 1][k];
				}
			}
		}
		// промежуточный вывод матрицы
		if ((i + 1) % 10 != 3 and (i + 1) % 10 != 2 and (i + 1) != 2) {
			infile << "Проделав преобразования с " << i + 1 << "-ым столбцом, получаем следующую матрицу:" << endl;
			print_new_matrica(NewMatrix, rows, columns + 1);
		}
		else if (i == 2) {
			infile << "Проделав преобразования со " << i + 1 << "-ым столбцом, получаем следующую матрицу:" << endl;
			print_new_matrica(NewMatrix, rows, columns + 1);
		}
		else if ((i + 1) % 10 == 2) {
			infile << "Проделав преобразования с " << i + 1 << "-ым столбцом, получаем следующую матрицу:" << endl;
			print_new_matrica(NewMatrix, rows, columns + 1);
		}
		else if ((i + 1) % 10 == 3) {
			infile << "Проделав преобразования с " << i + 1 << "-им столбцом, получаем следующую матрицу:" << endl;
			print_new_matrica(NewMatrix, rows, columns + 1);
		}
	}

	// обратное присваивание новых значений первоначальным матрицам
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns + 1; ++j) {
			if (j != columns) {
				ArrayA[i][j] = NewMatrix[i][j];
			}
			else {
				ArrayB[i] = NewMatrix[i][columns];
			}
		}
	}

	infile.close();

	// удаление созданного внутри функции массива
	for (int i = 0; i < rows; ++i) {
		delete[] NewMatrix[i];
	}
	delete[] NewMatrix;
}

// функция решения треугольной матрицы
void decisions_of_system(double* ArrayA[], double ArrayB[], double Answers[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// условия и циклы для подсчёта корней
	if (size >= 2) {
		for (int i = size - 1; i >= 0; --i) {
			infile << "x" << i + 1 << " = (" << ArrayB[i];
			for (int j = size - 1; j >= 0; --j) {
				if (i == j) {
					if (ArrayA[i][j] != 0) {
						Answers[j] = ArrayB[i];
						for (int z = j + 1; z < size; ++z) {
							// вывод подсчётов
							if (ArrayA[i][z] > 0 and Answers[z] < 0) {
								infile << " + " << ArrayA[i][z] << "*" << abs(Answers[z]);
							}
							else if (ArrayA[i][z] < 0 and Answers[z] > 0) {
								infile << " + " << abs(ArrayA[i][z]) << "*" << Answers[z];
							}
							else if (ArrayA[i][z] < 0 and Answers[z] < 0) {
								infile << " - " << abs(ArrayA[i][z]) << "*" << abs(Answers[z]);
							}
							Answers[j] -= ArrayA[i][z] * Answers[z];
						}
						Answers[j] /= ArrayA[i][j];
					}
					else {
						Answers[j] = 0;
					}
				}
			}
			infile << ") / " << ArrayA[i][i];
			infile << endl << "x" << i + 1 << " = " << Answers[i] << endl;
		}
	}

	infile.close();
}
