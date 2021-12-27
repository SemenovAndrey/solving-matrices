#ifndef FUNKCII
#define FUNKCII

void print_matrica(double* ArrayA[], double ArrayB[], int rows, int columns);
void print_matrica_in_txt(double* ArrayA[], double ArrayB[], int rows, int columns);
void print_uravnenie(double* ArrayA[], double ArrayB[], int rows, int columns);
void print_uravnenie_in_txt(double* ArrayA[], double ArrayB[], int rows, int columns);
void print_delta(double Array[], int size);
void print_answers_in_column_for_Kramer(double Array[], int size, double opredelitel);
void print_answers_in_column_for_Gauss(double Array[], int size);
void print_answers_for_Kramer(double Array[], int size, double opredelitel);
void print_answers_for_Gauss(double Array[], int size);

void Kramer(double* ArrayA[], double ArrayB[], int rows, int columns);
void Gauss(double* ArrayA[], double ArrayB[], int rows, int columns);

void udalenie_stroki(double* Array[], int rows, int columns);
double Opredelitel(double* ArrayA[], int rows, int columns);
double Opredelitel1(double* Array[]);
double Opredelitel2(double* Array[]);

double reshenie_matricy_s_zamenoi_stolbca(double* ArrayA[], double ArrayB[], int rows, int columns, int index);
void reshenie_matricy_s_zamenoi_stolbca_void(double* ArrayA[], double ArrayB[], int rows, int columns, int index);
void privedeine_k_treug_vidu(double* Array[], double ArrayB[], int rows, int columns);
void decisions_of_system(double* ArrayA[], double ArrayB[], double Answers[], int size);

void print_new_matrica(double* Array[], int rows, int columns);
void print_not_all_matrica(double* Array[], int rows, int columns);

#endif
