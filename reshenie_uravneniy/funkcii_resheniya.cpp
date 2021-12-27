#include <iostream>
#include <iomanip>
#include <fstream>
#include "funkcii.h"
using namespace std;

// решение методом Гаусса
void Gauss(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	// пояснение решения
	infile << "----------------------" << endl << "Решение методом Гаусса" << endl << "----------------------" << endl;
	infile << "Данная матрица выглядит следующим образом:" << endl;
	print_matrica_in_txt(ArrayA, ArrayB, rows, columns);
	infile << endl << "Для того, чтобы решить данную матрицу методом Гаусса, в первую очередь нужно привести её к треугольному виду." << endl;
	infile << "Треугольной матрица называется, если выполнены следующие условия:" << endl;
	infile << "1) все ненулевые строки стоят после после всех ненулевых;" << endl;
	infile << "2) первый ненулевой элемент каждой строки стоит правее первого ненулевого элемента предыдущей строки." << endl << endl;

	// пример приведения матрицы к треугольной
	infile << "К примеру, дана матрица A размера 3х3 (матрица 1), где каждый элемент не равен нулю:" << endl;
	infile << "    ( a[1][1]  a[1][2]  a[1][3] )" << endl;
	infile << "A = ( a[2][1]  a[2][2]  a[2][3] )" << endl;
	infile << "    ( a[3][1]  a[3][2]  a[3][3] )" << endl << endl;
	infile << "Привести её нужно к следующему виду (частный случай):" << endl;
	infile << "    ( a[1][1]  a[1][2]  a[1][3] )" << endl;
	infile << "A = (    0     a[2][2]  a[2][3] )" << endl;
	infile << "    (    0        0     a[3][3] )" << endl << endl;
	infile << "Приводится она к данному виду с помощью элементарных преобразований:" << endl;
	infile << "1) смена двух соответсвующих строк/столбцов;" << endl;
	infile << "2) умножение строки/столбца на число, не равное 0;" << endl;
	infile << "3) сложение двух строк/столбцов." << endl << endl;

	if (rows == 1 and columns == 1) {
		infile << "Но так как данная матрица размера 1х1, то ответ получатеся следующим:" << endl;
		infile << "x = y / a[1][1]";
		infile << "И получается, что х = " << ArrayB[0] / ArrayA[0][0] << "." << endl << endl;

		infile << "Ответ: x = " << ArrayB[0] / ArrayA[0][0] << "." << endl;
	}

	else {
		// приведение к треугольной матрице
		privedeine_k_treug_vidu(ArrayA, ArrayB, rows, columns);

		// вывод матрицы
		infile << endl << "То есть после приведения данной матрицы к треугольному виду, выглядит она следующим образом:" << endl;
		print_matrica_in_txt(ArrayA, ArrayB, rows, columns);
		infile << endl;

		// вывод системы
		infile << "И после этого получается следующая система уравненией:" << endl;
		print_uravnenie_in_txt(ArrayA, ArrayB, rows, columns);
		infile << endl;

		// пример решения системы
		infile << "Данная система решается уже как обычно: выражается одна переменная через другую." << endl;
		infile << "Например, если дана матрица размера 3х3 и она приведена к треугольному виду, то уравнение выглядит следующим образом:" << endl;
		infile << "x1 + x2 + x3 = y1" << endl;
		infile << "     x2 + x3 = y2" << endl;
		infile << "          x3 = y3" << endl;
		infile << "Из этого уравнения сразу известна переменная x3:" << endl << "x3 = y3" << endl;
		infile << "Далее необходимо подставить x3 во второе уравнение, и тогда:" << endl;
		infile << "x2 + y3 = y2" << endl << "x2 = y2 - y3" << endl;
		infile << "Подставляя полученные значения в первое уравнение, получаем последнюю переменную:" << endl;
		infile << "x1 + x2 + x3 = y1" << endl;
		infile << "x1 + y2 - y3 + y3 = y1" << endl;
		infile << "x1 = y1 - y2" << endl << endl;

		// подсчёт нулевых элементов последней строки
		int k1 = 0, k2 = 0;
		for (int i = 0; i < columns; ++i) {
			if (ArrayA[i][i - 1] == 0) {
				k1 += 1;
			}
			if (ArrayA[i][i] == 0) {
				k2 += 1;
			}
		}

		// решение для матрицы, в которой вся последняя строчка состоит из нулей
		if (k1 != columns - 1 or k2 != 0) {
			infile << "Данная матрица не имеет вид, как треугольная матрица 1, следовательно, x" << rows << " принадлежит от -oo до +oo." << endl;
			infile << "И, соответсвенно, система имеет бесконечное количество решений." << endl;
		}
		// решение треугольной матрицы
		else if (k1 == columns - 1 and k2 == 0) {
			infile << "Решение системы:" << endl;
			double* Answers = new double[columns];
			for (int i = 0; i < columns; ++i) {
				Answers[i] = 0;
			}

			decisions_of_system(ArrayA, ArrayB, Answers, rows);
			infile << endl << "Получаются следующие результаты:" << endl;
			print_answers_in_column_for_Gauss(Answers, columns);
			infile << endl;
			print_answers_for_Gauss(Answers, columns);
			infile << endl;

			delete[] Answers;
		}
	}

	infile.close();
}

// решение методом Крамера
void Kramer(double* ArrayA[], double ArrayB[], int rows, int columns)
{
	ofstream infile;
	infile.open("solving equations.txt", ios::app);

	double opredelitel;
	infile << "-----------------------" << endl << "Решение методом Крамера" << endl << "-----------------------" << endl;
	infile << "Данная матрица выглядит следующим образом:" << endl;
	print_matrica_in_txt(ArrayA, ArrayB, rows, columns);
	// нахождение определителя
	infile << endl << "Первым делом необходимо найти определитель. Определитель можно найти только в том случае, если матрица квадратная" << endl;
	infile << "Так как на вход принимаются только квадратные матрицы, то определитель можно найти в любом случае." << endl << endl;
	infile << "Делается это следующим образом:" << endl;

	// определитель для матрицы размера 1х1
	if (rows == 1 and columns == 1) {
		infile << "Данная матрица состоит из 1 строки и 1 столбца, следовательно определителем является элемент матрицы." << endl;
		opredelitel = Opredelitel(ArrayA, rows, columns);
		infile << "|A| = " << opredelitel << endl;
	}

	// определитель для матрицы размера 2х2
	else if (rows == 2 and columns == 2) {
		infile << "Размер данной матрицы 2х2, следовательно, для того, чтобы найти определитель, нужно из произведения элементов главной диагонали ";
		infile << "вычесть произведение элементов побочной диагонали. То есть:" << endl;
		infile << "Матрица А:" << endl << "( a[1][1]  a[1][2] )" << endl << "( a[2][1]  a[2][2] )" << endl;
		infile << "|A| = a[1][1] * a[2][2] - a[1][2] * a[2][1]" << endl << endl;

		opredelitel = Opredelitel(ArrayA, rows, columns);
		infile << "|A| = " << opredelitel << "." << endl << endl;
	}

	// определитель для матрицы размера большего, чем 2х2
	else if (rows > 2 and columns > 2) {
		infile << "Размер данной матрицы " << rows << "x" << columns << "." << endl;
		infile << "Определитель такой матрицы можно находить разными способами, например, через миноры." << endl;
		infile << "К примеру, дана матрица А размера 3х3:" << endl;
		infile << "    ( a[1][1]  a[1][2]  a[1][3] )" << endl;
		infile << "A = ( a[2][1]  a[2][2]  a[2][3] )" << endl;
		infile << "    ( a[3][1]  a[3][2]  a[3][3] )" << endl << endl;

		infile << "Тогда:" << endl;
		infile << "                             | a[2][2]  a[2][3] |                          | a[2][1]  a[2][3] |                          | a[2][1]  a[2][2] |" << endl;
		infile << "|A| = (-1)^(1+1) * a[1][1] * |                  | + (-1)^(1+2) * a[1][2] * |                  | + (-1)^(1+3) * a[1][3] * |                  |" << endl;
		infile << "                             | a[3][2]  a[3][3] |                          | a[3][1]  a[3][3] |                          | a[3][1]  a[3][2] |" << endl << endl;

		infile << "Берутся поочерёдно элементы первой строки, вычёркиваются соответствующие строка и столбец, ";
		infile << "и затем этот элемент первой строки умножается на минор оставшихся 4 элементов." << endl;
		infile << "В степени числа -1 стоят соответсвующие индексы элемента первой строки (a[i][j]: (-1)^(i+j)), которые определяют знак перед произведением." << endl;
		infile << "Для a[1][1]: (-1)^(1+1)." << endl;
		infile << "Если же матрица большего размера, то делается всё точно так же - матрица уменьшается до размера 2х2." << endl;
		infile << "Но если определитель равен 0, то система не имеет решений, так как в последующих действиях решения нужно делить значения на определитель." << endl;
		opredelitel = Opredelitel(ArrayA, rows, columns);
		infile << "Таким образом, |A| = " << opredelitel << endl << endl;
	}

	// проверка определителя (он не должен равняться 0, т.к тогда не найдутся корни уранений)
	if (opredelitel == 0) {
		infile << "Определитель равен 0. Следовательно, система не имеет решений!" << endl;
		infile << "Ответ: нет решений." << endl;
	}

	else {
		// нахождение дельта х и дельта у
		infile << "После того, как найден определитель, необходимо найти дельту для каждого столбца:" << endl;
		infile << "то есть нужно найти определители, заменив поочерёдно каждый столбец тем, чему равна строка." << endl;
		infile << "К примеру, дана расширенная матрица (A | B), где размер матрицы А 2х2:" << endl;
		infile << "( a[1][1]  a[1][2] | b[1])" << endl;
		infile << "(                  |     )" << endl;
		infile << "( a[2][1]  a[2][2] | b[2])" << endl;
		infile << "Так как необходимо заменить поочерёдно столбцы А на столбец матрицы В, то a[i][j] = b[i]." << endl;
		infile << "Тогда:" << endl;
		infile << "     | b[1]  a[1][2] |" << endl;
		infile << "\177" << "x = |               |" << endl;
		infile << "     | b[2]  a[2][2] |" << endl << endl;
		infile << "И " << "\177" << "x = b[1] * a[2][2] - a[1][2] * b[2]" << endl << endl;

		// получение ответов
		double* Answers = new double[columns];
		for (int i = 0; i < columns; ++i) {
			Answers[i] = reshenie_matricy_s_zamenoi_stolbca(ArrayA, ArrayB, rows, columns, i);
		}
		for (int i = 0; i < columns; ++i) {
			reshenie_matricy_s_zamenoi_stolbca_void(ArrayA, ArrayB, rows, columns, i);
		}
		infile << "Получаются следующие результаты:" << endl;
		print_delta(Answers, rows);
		infile << endl;

		infile << "После нахождения определителей с заменёнными столбцами, их необходимо поочерёдно поделить на определитель первоначальной матрицы." << endl;
		infile << "x = " << "\177" << "x / |A| " << endl << endl;
		infile << "После финальных расчётов получается следующее:" << endl;
		print_answers_in_column_for_Kramer(Answers, columns, opredelitel);
		infile << endl;
		print_answers_for_Kramer(Answers, columns, opredelitel);
		infile << endl;

		infile.close();

		delete[] Answers;
	}
}
