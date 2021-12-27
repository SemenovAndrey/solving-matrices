#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h"
using namespace std;

// ����� ����������� ������� � �������
void print_matrica(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	// i - ����� ������
	for (int i = 0; i < rows; ++i) {
		cout << setw(2) << left << "( ";
		// j - ����� �������
		for (int j = 0; j < columns + 1; ++j) {
			// �����  ������� �
			if (j != columns) {
				cout << setw(7) << left << ArrayA[i][j];
			}
			//����� ������� �
			else {
				cout << setw(6) << left << setw(0) << "| " << setw(6) << left << ArrayB[i];
			}
		}
		cout << " )" << endl;
	}
}

// ��� ����������� �����
// ����� ������� ������� �
void print_not_all_matrica(double* Array[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// i - ����� ������
	for (int i = 0; i < rows; ++i) {
		infile << setw(2) << left << "( ";
		// j - ����� �������
		for (int j = 0; j < columns; ++j) {
			infile << setw(7) << left << Array[i][j];
		}
		infile << " )" << endl;
	}

	infile.close();
}

// ����� ����������� ������� � ���� .txt
void print_matrica_in_txt(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// i - ����� ������
	for (int i = 0; i < rows; ++i) {
		infile << setw(2) << left << "( ";
		// j - ����� �������
		for (int j = 0; j < columns + 1; ++j) {
			// ����� ������� �
			if (j != columns) {
				infile << setw(7) << left << ArrayA[i][j];
			}
			// ����� ������� �
			else {
				infile << setw(6) << left << setw(0) << "| " << setw(6) << left << ArrayB[i];
			}
		}
		infile << " )" << endl;
	}

	infile.close();
}

// � ������� ���������� ������� � ������������ ����
// ����� �������, ������� �������� ����������� ��������
void print_new_matrica(double* Array[], int rows, int columns)
{
	// ����� ����������� �������

	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// i - ����� ������
	for (int i = 0; i < rows; ++i) {
		infile << setw(2) << left << "( ";
		// j - ����� �������
		for (int j = 0; j < columns; ++j) {
			// ����� ������� � ������ �����������
			if (j != columns - 1) {
				infile << setw(7) << left << Array[i][j];
			}
			// ����� ������� � ������ �����������
			else {
				infile << setw(6) << left << setw(0) << "| " << setw(6) << left << Array[i][j];
			}
		}
		infile << " )" << endl;
	}

	infile.close();
}

// ����� ��������� � ���� .txt
void print_uravnenie_in_txt(double* Array[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < rows; ++i) {
		// i - ����� �������
		for (int j = 0; j < columns + 1; ++j) {
			// j - ����� �������
			if (j != columns) {
				// ����� �������� �������, ���� �� ����� ����
				if (Array[i][j] == 0) {
					for (int i = 0; i < 11; ++i) {
						infile << " ";
					}
				}
				// ����� ��������
				else {
					// ����� ������� �������
					if (j == 0) {
						if (Array[i][j] > 0) {
							infile << setw(0) << " " << setw(6) << right << Array[i][j] << setw(0) << "*x" << j + 1 << " ";
						}
						else if (Array[i][j] < 0) {
							infile << "-" << setw(6) << right << abs(Array[i][j]) << setw(0) << "*x" << j + 1 << " ";
						}
					}
					// ����� �� ������� �������
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
			// ����� ����, ���� ����� �������
			else {
				infile << setw(0) << "= " << ArrayB[i] << endl;
			}
		}
	}

	infile.close();
}

// ����� ��������� � �������
void print_uravnenie(double* Array[], double ArrayB[], int rows, int columns)
{
	for (int i = 0; i < rows; ++i) {
		// i - ����� �������
		for (int j = 0; j < columns + 1; ++j) {
			// j - ����� �������
			if (j != columns) {
				// ����� �������� �������, ���� �� ����� ����
				if (Array[i][j] == 0) {
					for (int i = 0; i < 11; ++i) {
						cout << " ";
					}
				}
				// ����� ��������
				else {
					// ����� ������� �������
					if (j == 0) {
						if (Array[i][j] > 0) {
							cout << setw(0) << " " << setw(6) << right << Array[i][j] << setw(0) << "*x" << j + 1 << " ";
						}
						else if (Array[i][j] < 0) {
							cout << "-" << setw(6) << right << abs(Array[i][j]) << setw(0) << "*x" << j + 1 << " ";
						}
					}
					// ����� �� ������� �������
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
			// ����� ����, ���� ����� �������
			else {
				cout << setw(0) << "= " << ArrayB[i] << endl;
			}
		}
	}
}

// ����� �����
void print_delta(double Array[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < size; ++i) {
		infile << "\177" << "x" << i + 1 << " = " << Array[i] << endl;
	}

	infile.close();
}

// ����� ������� � ������� ��� ������ �������
void print_answers_in_column_for_Kramer(double Array[], int size, double opredelitel)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < size; ++i) {
		infile << "x" << i + 1 << " = " << Array[i] << " / " << opredelitel << " = " << Array[i] / opredelitel << endl;
	}

	infile.close();
}

// ����� ������� ��� ������ �������
void print_answers_for_Kramer(double Array[], int size, double opredelitel)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	infile << "�����: ";
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

// ����� ������� � ������ ��� ������ ������
void print_answers_in_column_for_Gauss(double Array[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	for (int i = 0; i < size; ++i) {
		infile << "x" << i + 1 << " = " << Array[i] << endl;
	}

	infile.close();
}

// ����� ������� ��� ������ ������
void print_answers_for_Gauss(double Array[], int size)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	infile << "�����: ";
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
