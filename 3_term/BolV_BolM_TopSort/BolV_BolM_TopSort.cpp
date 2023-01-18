#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Класс булев вектор
class BoolV {
	unsigned int *v;
	int nbit, m; // nbit – количество бит вектора, m – количество элементов массива v
public:
	BoolV(int nn = 1); // формируется булев вектор из nn бит; все биты со значениями 0
	BoolV(const char*); // формируется булев вектор по строке из нулей и единиц
	BoolV(const BoolV &);
	~BoolV();
	
	void Set1(int);	// устанавливает указанный бит в 1
	void Set0(int); // устанавливает указанный бит в 0
	int operator[](int);
	BoolV operator = (const BoolV &);
	bool operator == (const BoolV &); // равенство векторов
	BoolV operator | (const BoolV &);
	BoolV operator & (const BoolV &);
	BoolV operator ~ ();
	int weight();	// вес вектора
	
	friend ostream& operator << (ostream &, const BoolV &);
	friend istream& operator >> (istream &, BoolV &);
};

// Класс булева матрица
class BoolM {
	BoolV *bm;
	int m, n; // m – количество строк, n – количество столбцов
public:
	BoolM(int k = 1, int l = 1); // формируется нулевая булева матрица размера kl
	BoolM(const BoolM &);
	
	BoolV & operator[] (int);
	BoolM operator = (const BoolM &);
	int Matrix();
	friend ostream & operator << (ostream &, BoolM &);
};

// Формируется булев вектор из nn бит; все биты со значениями 0
BoolV::BoolV(int nn) {
    	nbit = nn;
    	v = new unsigned int[nbit];
	for (int i = 0; i < nbit; i++) {
		v[i] = 0;
	}
}

// Формируется булев вектор по строке из нулей и единиц
BoolV::BoolV(const char *str) {
    	nbit = strlen(str);
    	if (nbit <= 32) {
        	v = new unsigned int[nbit];
        	for (int i = 0; i < nbit; i++) {
            		if (str[i] == '1') {
				v[i] = 1;
			}
			else {
				v[i] = 0;
			}
        	}
    	}
	else {
		cout << "\nOut of range for unsigned int.\n";
	}
}

// Конструктор копирования
BoolV::BoolV(const BoolV &other_V) {
    	nbit = other_V.nbit;
    	v = new unsigned int[nbit];
	for (int i = 0; i < nbit; i++) {
		v[i] = other_V.v[i];
	}
}

// Деструктор
BoolV::~BoolV() {
	if (v) {
		delete[]v;
	}
	v = NULL;
}

// Устанавливает указанный бит в 1
void BoolV::Set1(int k) {
    	if ((k >= 0) && (k < nbit)) {
    	    v[k] = 1;
    	}
	else {
		cout << "\nThe entered value is outside the vector's range.\n";
	}
}

// Устанавливает указанный бит в 0
void BoolV::Set0(int k) {
    	if ((k >= 0) && (k < nbit)) {
     		v[k] = 0;
    	}
	else {
		cout << "\nThe entered value is outside the vector's range.\n";
	}
}

// Равенство векторов
bool BoolV::operator == (const BoolV &other_V) {
    	if (nbit != other_V.nbit) {
       		return false;
    	}
	for (int i = 0; i < nbit; i++) {
		if (v[i] != other_V.v[i]) {
			return false;
		}
	}
    	return true;
}

// Возвращает указанный бит из вектора
int BoolV::operator [] (int k) {
    	int BoolV::operator [] (int k) {
    	if ((k < 0) && (k >= nbit)) {
		cout << "The entered value is outside the vector's range.\nReturn the one with the index 0: ";
        	return v[0];
    	}
	else {
        	return v[k];
    	}
}

// Перегрузка присвоения
BoolV BoolV::operator = (const BoolV &other_V) {
    	if (this != &other_V) {
		delete[] v;
		nbit = other_V.nbit;
    		v = new unsigned int[nbit];
		for (int i = 0; i < nbit; i++) {
			v[i] = other_V.v[i];
		}
    	}
    	return *this;
}

// OR
BoolV BoolV::operator | (const BoolV &other_V) {
    	BoolV first_op = *this;
	BoolV tmp;
	if (first_op.nbit >= other_V.nbit) {
		tmp = first_op;
	}
	else {
		tmp = other_V;
	}
	for (int i = max(first_op.nbit, other_V.nbit) - 1; i >= (max(first_op.nbit, other_V.nbit)-min(first_op.nbit, other_V.nbit)); i--) {
		if (first_op.nbit >= other_V.nbit) {
			if (!(first_op.v[i] == 0 && other_V.v[i-(first_op.nbit - other_V.nbit)] == 0)) {
				tmp.v[i] = 1;
			}
			else {
				tmp.v[i] = 0;
			}
		}
		else {
			if (!(other_V.v[i] == 0 && first_op.v[i-(other_V.nbit - first_op.nbit)] == 0)) {
				tmp.v[i] = 1;
			}
			else {
				tmp.v[i] = 0;
			}
		}
	}
	first_op = tmp;
	return first_op;
}

// AND
BoolV BoolV::operator & (const BoolV &other_V) {
    	BoolV first_op = *this;
	BoolV tmp;
	if (first_op.nbit >= other_V.nbit) {
		tmp = first_op;
	}
	else {
		tmp = other_V;
	}
	for (int i = max(first_op.nbit, other_V.nbit) - 1; i >= (max(first_op.nbit, other_V.nbit)-min(first_op.nbit, other_V.nbit)); i--) {
		if (first_op.nbit >= other_V.nbit) {
			if (!(first_op.v[i] == 1 && other_V.v[i-(first_op.nbit - other_V.nbit)] == 1)) {
				tmp.v[i] = 0;
			}
			else {
				tmp.v[i] = 1;
			}
		}
		else {
			if (!(other_V.v[i] == 1 && first_op.v[i-(other_V.nbit - first_op.nbit)] == 1)) {
				tmp.v[i] = 0;
			}
			else {
				tmp.v[i] = 1;
			}
		}
	}
	first_op = tmp;
	return first_op;
}

// Инвертирование вектора
BoolV BoolV::operator ~ () {
    	BoolV op = *this;
	for (int i = 0; i < op.nbit; i++) {
    		if (op.v[i] == 1) {
			op.v[i] = 0;
		}
		else {
			op.v[i] = 1;
		}
	}
    	return op;
}

istream &operator >> (istream &in, BoolV &vec) {
	char *buff = new char[33];
	in.getline(buff, 33);
	vec = BoolV(buff);
	delete[] buff;
	return in;
}

ostream &operator << (ostream &out, const BoolV &vec) {
    	for (int i = 0; i < vec.nbit; i++) {
        	if (vec.v[i]  == 0) {
        	    	out << 0;
        	} else {
            		out << 1;
        	}
    	}
	return out;
}

// Вес вектора
int BoolV::weight() {
	int power = 0;
	for (int i = 0; i < nbit; i++) {
		if (v[i] == 1) {
			power++;
		}
	}
	return power;
}

// Создание булевой матрицы из булевых векторов
// Конструктор использующего класса отвечает за генерацию член-данных используемого класса
BoolM::BoolM(int k, int l) {
    	m = k;
	n = l;
    	bm = new BoolV[m];
    	BoolV v(n);	// Список инициализации
    	for (int i = 0; i < m; i++) {
        	bm[i] = v;
    	}
}

// Конструктор копирования (размерности и строки)
BoolM::BoolM(const BoolM &M) {
	m = M.m;
	n = M.n;
    	bm = new BoolV[m];
    	for (int i = 0; i < m; i++) {
        	bm[i] = M.bm[i];
    	}
}

// Вывод строки по её индексу
BoolV &BoolM::operator [] (int k) {
    	if (k < 0 || k>=m) {
		cout << "The line number is incorrect.\nReturn the one with the index 0: ";
		return bm[0];
	}
	return bm[k];
}

// Перегрузка присвоения
BoolM BoolM::operator = (const BoolM &M) {
    	if (this != &M) {
        	delete[]bm;
		m = M.m;
		n = M.n;
        	bm = new BoolV[m];
        	for (int i = 0; i < m; i++) {
            		bm[i] = M.bm[i];
        	}
    	}
    	return *this;
}

ostream &operator << (ostream &out, BoolM &M) {
    	for (int i = 0; i < M.m; i++) {
		out << M.bm[i] << '\n';
	}
    	return out;
}

// Построение матрицы из файла
int BoolM::Matrix() {
    	ifstream file("graph.txt");
    	if (file.is_open()) {
        	int f_vertex, s_vertex, num_vert;
        	file >> num_vert;
        	BoolM BM(num_vert, num_vert);
        	while (!file.eof()) {
            		file >> f_vertex;
            		file >> s_vertex;
            		BM[f_vertex - 1].Set1(s_vertex - 1);
        	}
        	file.close();
        	*this = BM;
        	return num_vert;
    	}
	cout << "\nThe file does not exist or access to it is denied. Please, try again.\n";
    	return 0;
}

// Топологическая сортировка на булевой матрице
void topsort(BoolM &M, int m, int *a) { // a – результат сортировки
    	BoolV v0(m), v1(m), v2(m), zero_V(m);
    	int k = 0;
    	while (v0.weight() != m) {
        	v1 = zero_V;
        	for (int i = 0; i < m; i++) {
         		v1 = v1 | M[i];
        	}
        	v2 = (~v1) & (~v0);
        
        	if (v2 == zero_V) {
            		cout << "\nThere is a cycle in the graph: topological sorting is not applicable.\n";
			return ;
        	}
        	for (int i = 0; i < m; i++) {
            		if (v2[i] == 1) {
                	a[k++] = i + 1;
                	M[i] = zero_V;
            	}
        }
        v0 = v0 | v2;
    }
}

int main() {
	BoolV first_vec(32);
    	BoolV second_vec = first_vec;
    	if (first_vec == second_vec) {
        	cout << first_vec << "\n" << second_vec << "\nVectors are equal.\n\n";
    	}
   	second_vec.Set1(17);
    	if (!(first_vec == second_vec)) {
        	cout << first_vec << "\n" << second_vec << "\nVectors aren't equal.\n\n";
    	}
	cout << "Enter vector to invert it: ";
    	BoolV some_vec;
	cin >> some_vec;
    	some_vec = ~some_vec;
    	cout << "Vector has been inverted: " << some_vec << "\n\n";
	cout << "Enter two random vectors:\n";
    	cin >> first_vec >> second_vec;
	BoolV OR_test, AND_test; 
    	OR_test = first_vec | second_vec;
    	AND_test = first_vec & second_vec;
    	cout << " OR: " << OR_test << "\nAND: " << AND_test << "\n\n";
    	cout << "Enter the index of the bit you want to check: ";
	int k, m;
	cin >> k;
	cout << AND_test[k] << "\n";
	cout << "Weight of the last vector: " << AND_test.weight() << "\n\n";

	BoolM zero_matrix(3, 8);
    	BoolM matrix_from_file;
    	m = matrix_from_file.Matrix();

	cout << "Some default matrix:\n" << zero_matrix << "\n";
    	cout << "Matrix from file: " << "\n" << matrix_from_file << "\n";
    	cout << "Enter index of string from matrix wich you want to see: ";
	cin >> k;
	cout << matrix_from_file[k] << "\n\n";
    
    	zero_matrix = matrix_from_file;
    	cout << "Check of overloaded assignment operator:\n" << zero_matrix << "\n";
    	int *ans = new int[m];
    	topsort(matrix_from_file, m, ans);
    	cout << ("Answer: ");
    	for (int i = 0; i < m; i++) {
        	cout << ans[i];
    	}
	cout << "\n";
	
	return 0;
}
