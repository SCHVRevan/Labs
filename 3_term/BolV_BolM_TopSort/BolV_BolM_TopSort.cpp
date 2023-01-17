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
	
	friend ostream& operator << (ostream &, const BoolV &);
	friend istream& operator >> (istream &, BoolV &);

	int weight();	//вес вектора
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

// Удаляется массив
BoolV::~BoolV() {
	if (v) {
		delete[]v;
	}
	v = NULL;
}

// Устанавливает указанный бит в 1
void BoolV::Set1(int k) {
    if ((k < nbit) && (k >= 0)) {
        v[k] = 1;
    }
	else {
		cout << "\nThe entered value is outside the vector's range.\n";
	}
}

// Устанавливает указанный бит в 0
void BoolV::Set0(int k) {
    if ((k < nbit) && (k >= 0)) {
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
    if ((k < nbit) && (k >= 0)) {
        if (v[k] == 0) {
			return 0;
		}
        else {
			return 1;
		}
    }
	else {
        cout << "\nThe entered value is outside the vector's range.\n";
        return -1;
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

// ИЛИ
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

// И
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
    BoolV copy = vec;
    for (int i = 0; i < copy.nbit; i++) {
        if (copy[i]  == 0) {
            out << 0;
        } else {
            out << 1;
        }
    }
    return out;
}

int BoolV::weight() {
	BoolV op = *this;
	int power = 0;
	for (int i = 0; i < op.nbit; i++) {
		if (op.v[i] == 1) {
			power++;
		}
	}
	return power;
}


/*
// Создание булевой матрицы из булевых векторов
BoolM::BoolM(int k, int l) {
    m = k;
    bm = new BoolV[m];
    n = l;
    BoolV v(n);
    for (int i = 0; i < m; i++) {
        bm[i] = v;
    }
}

// Конструктор копирования (размерности и строки)
BoolM::BoolM(const BoolM &M) {
    n = M.n;
    bm = new BoolV[m = M.m];
    for (int i = 0; i < m; i++) {
        bm[i] = M.bm[i];
    }
}

// Возвращает строку
BoolV &BoolM::operator[](int k) {
    return this->bm[k];
}

// Приравнивание
BoolM BoolM::operator =( const BoolM &M) {
    if (this != &M) {
        n = M.n;	// колличество столбцов
        delete[]bm;
        bm = new BoolV[m = M.m];
		// Пробегаем по строкам и записываем новые строки
        for (int i = 0; i < m; i++) {
            bm[i] = M.bm[i];
        }
    }
    return *this;
}

ostream &operator<<(ostream &out, BoolM &M) {
    for (int i = 0; i < M.m; i++) out << M.bm[i] << '\n';
    return out;
}*/




/*
// Топологическая сортировка на булевой матрице
void topsort(BoolM &M, int m, int *a); // a – результат сортировки
ifstream file("graf.txt");

text.close();
*/



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
	int k;
	cin >> k;
	cout << "Bit №" << k << " from the last vector (" << AND_test << ") = " << AND_test[k] << "\n";
	cout << "Weight of the last vector: " << AND_test.weight() << "\n";
	
	return 0;
}