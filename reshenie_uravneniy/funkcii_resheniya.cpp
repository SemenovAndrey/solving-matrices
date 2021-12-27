#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h"
using namespace std;

// ������� ������� ������
void Gauss(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// ��������� �������
	infile << "----------------------" << endl << "������� ������� ������" << endl << "----------------------" << endl;
	infile << "������ ������� �������� ��������� �������:" << endl;
	print_matrica_in_txt(ArrayA, ArrayB, rows, columns);
	infile << endl << "��� ����, ����� ������ ������ ������� ������� ������, � ������ ������� ����� �������� � � ������������ ����." << endl;
	infile << "����������� ������� ����������, ���� ��������� ��������� �������:" << endl;
	infile << "1) ��� ��������� ������ ����� ����� ����� ���� ���������;" << endl;
	infile << "2) ������ ��������� ������� ������ ������ ����� ������ ������� ���������� �������� ���������� ������." << endl << endl;

	// ������ ���������� ������� � �����������
	infile << "� �������, ���� ������� A ������� 3�3 (������� 1), ��� ������ ������� �� ����� ����:" << endl;
	infile << "    ( a[1][1]  a[1][2]  a[1][3] )" << endl;
	infile << "A = ( a[2][1]  a[2][2]  a[2][3] )" << endl;
	infile << "    ( a[3][1]  a[3][2]  a[3][3] )" << endl << endl;
	infile << "�������� � ����� � ���������� ���� (������� ������):" << endl;
	infile << "    ( a[1][1]  a[1][2]  a[1][3] )" << endl;
	infile << "A = (    0     a[2][2]  a[2][3] )" << endl;
	infile << "    (    0        0     a[3][3] )" << endl << endl;
	infile << "���������� ��� � ������� ���� � ������� ������������ ��������������:" << endl;
	infile << "1) ����� ���� �������������� �����/��������;" << endl;
	infile << "2) ��������� ������/������� �� �����, �� ������ 0;" << endl;
	infile << "3) �������� ���� �����/��������." << endl << endl;

	if (rows == 1 and columns == 1) {
		infile << "�� ��� ��� ������ ������� ������� 1�1, �� ����� ���������� ���������:" << endl;
		infile << "x = y / a[1][1]";
		infile << "� ����������, ��� � = " << ArrayB[0] / ArrayA[0][0] << "." << endl << endl;

		infile << "�����: x = " << ArrayB[0] / ArrayA[0][0] << "." << endl;
	}

	else {
		// ���������� � ����������� �������
		privedeine_k_treug_vidu(ArrayA, ArrayB, rows, columns);

		// ����� �������
		infile << endl << "�� ���� ����� ���������� ������ ������� � ������������ ����, �������� ��� ��������� �������:" << endl;
		print_matrica_in_txt(ArrayA, ArrayB, rows, columns);
		infile << endl;

		// ����� �������
		infile << "� ����� ����� ���������� ��������� ������� ����������:" << endl;
		print_uravnenie_in_txt(ArrayA, ArrayB, rows, columns);
		infile << endl;

		// ������ ������� �������
		infile << "������ ������� �������� ��� ��� ������: ���������� ���� ���������� ����� ������." << endl;
		infile << "��������, ���� ���� ������� ������� 3�3 � ��� ��������� � ������������ ����, �� ��������� �������� ��������� �������:" << endl;
		infile << "x1 + x2 + x3 = y1" << endl;
		infile << "     x2 + x3 = y2" << endl;
		infile << "          x3 = y3" << endl;
		infile << "�� ����� ��������� ����� �������� ���������� x3:" << endl << "x3 = y3" << endl;
		infile << "����� ���������� ���������� x3 �� ������ ���������, � �����:" << endl;
		infile << "x2 + y3 = y2" << endl << "x2 = y2 - y3" << endl;
		infile << "���������� ���������� �������� � ������ ���������, �������� ��������� ����������:" << endl;
		infile << "x1 + x2 + x3 = y1" << endl;
		infile << "x1 + y2 - y3 + y3 = y1" << endl;
		infile << "x1 = y1 - y2" << endl << endl;

		// ������� ������� ��������� ��������� ������
		int k1 = 0, k2 = 0;
		for (int i = 0; i < columns; ++i) {
			if (ArrayA[i][i - 1] == 0) {
				k1 += 1;
			}
			if (ArrayA[i][i] == 0) {
				k2 += 1;
			}
		}

		// ������� ��� �������, � ������� ��� ��������� ������� ������� �� �����
		if (k1 != columns - 1 or k2 != 0) {
			infile << "������ ������� �� ����� ���, ��� ����������� ������� 1, �������������, x" << rows << " ����������� �� -oo �� +oo." << endl;
			infile << "�, �������������, ������� ����� ����������� ���������� �������." << endl;
		}
		// ������� ����������� �������
		else if (k1 == columns - 1 and k2 == 0) {
			infile << "������� �������:" << endl;
			double* Answers = new double[columns];
			for (int i = 0; i < columns; ++i) {
				Answers[i] = 0;
			}

			decisions_of_system(ArrayA, ArrayB, Answers, rows);
			infile << endl << "���������� ��������� ����������:" << endl;
			print_answers_in_column_for_Gauss(Answers, columns);
			infile << endl;
			print_answers_for_Gauss(Answers, columns);
			infile << endl;

			delete[] Answers;
		}
	}

	infile.close();
}

// ������� ������� �������
void Kramer(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	double opredelitel;
	infile << "-----------------------" << endl << "������� ������� �������" << endl << "-----------------------" << endl;
	infile << "������ ������� �������� ��������� �������:" << endl;
	print_matrica_in_txt(ArrayA, ArrayB, rows, columns);
	// ���������� ������������
	infile << endl << "������ ����� ���������� ����� ������������. ������������ ����� ����� ������ � ��� ������, ���� ������� ����������" << endl;
	infile << "��� ��� �� ���� ����������� ������ ���������� �������, �� ������������ ����� ����� � ����� ������." << endl << endl;
	infile << "�������� ��� ��������� �������:" << endl;

	// ������������ ��� ������� ������� 1�1
	if (rows == 1 and columns == 1) {
		infile << "������ ������� ������� �� 1 ������ � 1 �������, ������������� ������������� �������� ������� �������." << endl;
		opredelitel = Opredelitel(ArrayA, rows, columns);
		infile << "|A| = " << opredelitel << endl;
	}

	// ������������ ��� ������� ������� 2�2
	else if (rows == 2 and columns == 2) {
		infile << "������ ������ ������� 2�2, �������������, ��� ����, ����� ����� ������������, ����� �� ������������ ��������� ������� ��������� ";
		infile << "������� ������������ ��������� �������� ���������. �� ����:" << endl;
		infile << "������� �:" << endl << "( a[1][1]  a[1][2] )" << endl << "( a[2][1]  a[2][2] )" << endl;
		infile << "|A| = a[1][1] * a[2][2] - a[1][2] * a[2][1]" << endl << endl;

		opredelitel = Opredelitel(ArrayA, rows, columns);
		infile << "|A| = " << opredelitel << "." << endl << endl;
	}

	// ������������ ��� ������� ������� ��������, ��� 2�2
	else if (rows > 2 and columns > 2) {
		infile << "������ ������ ������� " << rows << "x" << columns << "." << endl;
		infile << "������������ ����� ������� ����� �������� ������� ���������, ��������, ����� ������." << endl;
		infile << "� �������, ���� ������� � ������� 3�3:" << endl;
		infile << "    ( a[1][1]  a[1][2]  a[1][3] )" << endl;
		infile << "A = ( a[2][1]  a[2][2]  a[2][3] )" << endl;
		infile << "    ( a[3][1]  a[3][2]  a[3][3] )" << endl << endl;

		infile << "�����:" << endl;
		infile << "                             | a[2][2]  a[2][3] |                          | a[2][1]  a[2][3] |                          | a[2][1]  a[2][2] |" << endl;
		infile << "|A| = (-1)^(1+1) * a[1][1] * |                  | + (-1)^(1+2) * a[1][2] * |                  | + (-1)^(1+3) * a[1][3] * |                  |" << endl;
		infile << "                             | a[3][2]  a[3][3] |                          | a[3][1]  a[3][3] |                          | a[3][1]  a[3][2] |" << endl << endl;

		infile << "������� ��������� �������� ������ ������, ������������� ��������������� ������ � �������, ";
		infile << "� ����� ���� ������� ������ ������ ���������� �� ����� ���������� 4 ���������." << endl;
		infile << "� ������� ����� -1 ����� �������������� ������� �������� ������ ������ (a[i][j]: (-1)^(i+j)), ������� ���������� ���� ����� �������������." << endl;
		infile << "��� a[1][1]: (-1)^(1+1)." << endl;
		infile << "���� �� ������� �������� �������, �� �������� �� ����� ��� �� - ������� ����������� �� ������� 2�2." << endl;
		infile << "�� ���� ������������ ����� 0, �� ������� �� ����� �������, ��� ��� � ����������� ��������� ������� ����� ������ �������� �� ������������." << endl;
		opredelitel = Opredelitel(ArrayA, rows, columns);
		infile << "����� �������, |A| = " << opredelitel << endl << endl;
	}

	// �������� ������������ (�� �� ������ ��������� 0, �.� ����� �� �������� ����� ��������)
	if (opredelitel == 0) {
		infile << "������������ ����� 0. �������������, ������� �� ����� �������!" << endl;
		infile << "�����: ��� �������." << endl;
	}

	else {
		// ���������� ������ � � ������ �
		infile << "����� ����, ��� ������ ������������, ���������� ����� ������ ��� ������� �������:" << endl;
		infile << "�� ���� ����� ����� ������������, ������� ��������� ������ ������� ���, ���� ����� ������." << endl;
		infile << "� �������, ���� ����������� ������� (A | B), ��� ������ ������� � 2�2:" << endl;
		infile << "( a[1][1]  a[1][2] | b[1])" << endl;
		infile << "(                  |     )" << endl;
		infile << "( a[2][1]  a[2][2] | b[2])" << endl;
		infile << "��� ��� ���������� �������� ��������� ������� � �� ������� ������� �, �� a[i][j] = b[i]." << endl;
		infile << "�����:" << endl;
		infile << "     | b[1]  a[1][2] |" << endl;
		infile << "\177" << "x = |               |" << endl;
		infile << "     | b[2]  a[2][2] |" << endl << endl;
		infile << "� " << "\177" << "x = b[1] * a[2][2] - a[1][2] * b[2]" << endl << endl;

		// ��������� �������
		double* Answers = new double[columns];
		for (int i = 0; i < columns; ++i) {
			Answers[i] = reshenie_matricy_s_zamenoi_stolbca(ArrayA, ArrayB, rows, columns, i);
		}
		for (int i = 0; i < columns; ++i) {
			reshenie_matricy_s_zamenoi_stolbca_void(ArrayA, ArrayB, rows, columns, i);
		}
		infile << "���������� ��������� ����������:" << endl;
		print_delta(Answers, rows);
		infile << endl;

		infile << "����� ���������� ������������� � ���������� ���������, �� ���������� ��������� �������� �� ������������ �������������� �������." << endl;
		infile << "x = " << "\177" << "x / |A| " << endl << endl;
		infile << "����� ��������� �������� ���������� ���������:" << endl;
		print_answers_in_column_for_Kramer(Answers, columns, opredelitel);
		infile << endl;
		print_answers_for_Kramer(Answers, columns, opredelitel);
		infile << endl;

		infile.close();

		delete[] Answers;
	}
}
