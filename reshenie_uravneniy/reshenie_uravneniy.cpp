// ������� ��������� � ������� ���������� ������ ������� ������ � ������� �������
// 907 �����

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h";
using namespace std;

int main()
{
	// ����� ������� ���� � �������
	setlocale(LC_ALL, "Rus");

	// ����� � �������� ���� .txt (ios::app - ��������� ���� � ������ ����������)
	ofstream infile;
	infile.open("solving equations.txt");

	cout << "������� ��������� � ������� ���������� ������ ������� ������ � ������� �������" << endl << endl;

	// �������� �������� �������
	int rows, columns;
	cout << "������� ���������� ��������� (����� �������) � ���������� ���������� (�������� �������)." << endl;
	cout << "������� ���������� ���������: ";
	cin >> rows;
	cout << "������� ���������� ����������: ";
	cin >> columns;
	if (rows <= 0 or columns <= 0 or rows != columns) {
		while (true) {
			cout << "������! ";
			if (rows <= 0 or columns <= 0) {
				cout << "������� �����, ������� ����!" << endl;
				cout << "������� ���������� ���������: ";
				cin >> rows;
				cout << "������� ���������� ����������: ";
				cin >> columns;
			}
			else if (rows != columns) {
				cout << "���������� ��������� �� ����� ���������� ����������! ������� ����� ������!" << endl;
				cout << "������� ���������� ���������: ";
				cin >> rows;
				cout << "������� ���������� ����������: ";
				cin >> columns;
			}
			if (rows > 0 and columns > 0 and rows == columns) {
				break;
			}
		}
	}

	// �������� ������� A � B (���������� � ������)
	double** MatricaA = new double* [rows];
	for (int i = 0; i < rows; ++i) {
		MatricaA[i] = new double[columns];
	}
	double* MatricaB = new double[rows];

	// �������� �������� �������
	cout << endl << "������� ������������ ��� ���������� (������� ����� � ��������� �� 2 ������ ����� �������)" << endl;
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

	// ����� ���������
	cout << "�������� ����� �������� ��������� ���������:" << endl;
	print_uravnenie(MatricaA, MatricaB, rows, columns);
	cout << endl;

	// ����� �������
	cout << "������ ��������� ������������ ������ � ������� ���������� ������� ������� ������ ��� ������� �������." << endl;
	cout << "������� ������� ��������� �������� ��������� �������:" << endl;
	print_matrica(MatricaA, MatricaB, rows, columns);
	cout << endl;

	// ����� ������, ������� ����� ������ �������
	int metod; // ���������� metod ��������� �������� ���� 1, ���� 2
	cout << "�������� ����� ������� ����� ������ ��������� (1 - ����� ������, 2 - ����� �������): ";
	cin >> metod;

	// ������� ��������� �������
	while (metod != 1 or metod != 2) {
		if (metod == 1) {
			cout << "�� ������� ������� ������� ������." << endl;
			Gauss(MatricaA, MatricaB, rows, columns);
			break;
		}
		else if (metod == 2) {
			cout << "�� ������� ������� ������� �������." << endl;
			Kramer(MatricaA, MatricaB, rows, columns);
			break;
		}
		else {
			cout << "������. ������� ���� 1, ���� 2: ";
			cin >> metod;
		}
	}

	infile.close();

	// �������� ��������
	for (int i = 0; i < rows; ++i) {
		delete[] MatricaA[i];
	}
	delete[] MatricaA;
	delete[] MatricaB;
	return 0;
}
