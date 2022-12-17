#include <chrono>
#include <iostream>

using namespace std;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

class Array {
  int *a, n;

public:
  // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
  Array(int len = 1, int t = 1, int d = 10) {
    a = new int[len];
    n = len; // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    if (t == 1) {
      for (int i = 0; i < n; i++) {
        a[i] = rand() % d;
      }
      // t = 2 – массив, упорядоченный по неубыванию
    } else if (t == 2) {
      a[0] = rand() % d;
      for (int i = 1; i < n; i++) {
        a[i] = a[i - 1] + rand() % d;
      }
      // t = 3 – массив, упорядоченный по невозрастанию
    } else if (t == 3) {
      a[n - 1] = rand() % d;
      for (int i = n - 2; i >= 0; i--) {
        a[i] = a[i + 1] + rand() % d;
      }
    } else {
      exit(1);
    }
  };
  // конструктор копирования
  Array(Array &);
  // деструктор
  ~Array() {
    if (a)
      delete[] a;
    a = NULL;
  }
  // конструктор 2: по массиву
  Array(int *, int);
  // оператор присваивания
  Array &operator=(const Array &);
  // оператор для получения i-ого элемента
  int &operator[](int);
  // проверка на упорядоченность по неубыванию
  bool Test();
  // равенство элементов массивов (но не порядка)
  bool operator==(Array);

  void Shell_sort();

  void Heapsort();

  void heapify(int, int);

  void Hoar_sort();

  friend istream &operator>>(istream &, Array &);

  friend ostream &operator<<(ostream &, Array &);
};
// конструктор 2: по массиву
Array::Array(int *b, int len) {
  a = new int[len];
  n = len;
  for (int i = 0; i < n; i++) {
    a[i] = b[i];
  }
};
// конструктор копирования
Array::Array(Array &b) {
  a = new int[b.n];
  n = b.n;
  for (int i = 0; i < n; i++) {
    a[i] = b.a[i];
  }
};
// оператор присваивания
Array &Array::operator=(const Array &newArr) {
  if (this == &newArr)
    return *this;
  delete[] a;
  n = newArr.n;
  a = new int[n];
  for (int i = 0; i < n; i++) {
    a[i] = newArr.a[i];
  }
  return *this;
};
// оператор для получения i-ого элемента
int &Array::operator[](int b) {
  if (b < 0 || b >= n)
    exit(-1);
  return a[b];
}
// проверка на упорядоченность по неубыванию
bool Array::Test() {
  for (int i = 1; i < n; i++) {
    if (a[i] < a[i - 1]) {
      return false;
    }
  }
  return true;
}
// равенство элементов массивов (но не порядка)
bool Array::operator==(Array b) {
  if (n != b.n) {
    return false;
  }
  int len = n;
  for (int i = 0; i < n; i++) {
    bool ch = false;
    for (int j = 0; j < len; j++) {
      if (a[i] == b.a[j]) {
        ch = true;
        b[j] = b[len - 1];
        len--;
        break;
      }
    }
    if (ch == false) {
      return false;
    }
  }
  return true;
}

istream &operator>>(istream &in, Array &obj) {
  int len;
  cout << "Lenght: ";
  in >> len;
  // cout << len;
  int *a;
  a = new int[len];
  for (int i = 0; i < len; i++) {
    in >> a[i];
  }
  obj = Array(a, len);
  delete[] a;
  return in;
}

ostream &operator<<(ostream &out, Array &a) {
  out << "\nArray: ";
  for (int i = 0; i < a.n; i++) {
    out << a[i] << " ";
  }
  out << "\n";
  return out;
}

void Array::Shell_sort() {
  for (int step = n / 2; step > 0; step /= 2) { // разбиваем на шаги
    // выполняем сортировку вставки для элементов с шагом step
    for (int b = 0; b < step; b++) { // извлекаем первый элемент подмассива
      for (int i = b + step; i < n;
           i += step) { // проходимся по другим элементам подмассива
        int x = a[i];
        int k;
        for (k = i - step; k >= 0 && a[k] > x;
             k -= step) { //смотрим на предыдушие элементы и сравниваем с нашим
          a[k + step] = a[k];
        }
        a[k + step] = x;
      }
    }
    cout << *this << "\tstep=" << step << "\n";
  }
}

int hoar_recursive(int *a, int l, int r) {
  if (l >= r) {
    return 0;
  }
  int i = l;
  int j = r;
  int x = a[(l + r) / 2]; // вычисляем эталонное значение
  while (i <= j) {
    while (a[i] < x) {
      i++;
    }
    while (a[j] > x) {
      j--;
    }
    if (i <= j) {
      swap(a[i], a[j]);
      i++;
      j--;
    }
  }
  /*cout << "i: " << i << "\tj: " << j << "\tx: " << x << "\n";
  cout << "Array: ";
  for (int k = l; k <= r; k++) {
      cout << a[k] << " ";
  }
  cout << "\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";*/
  hoar_recursive(a, l, j);
  hoar_recursive(a, i, r);
  return 0;
}

void Array::Hoar_sort() { hoar_recursive(a, 0, n - 1); }
// функция просеивания
void Array::heapify(int n, int i) {
  int j = 2 * i + 1;
  int x = a[i];
  bool f = true; // нашли ли мы место для элемента x
  while (j < n && f) {
    if (j + 1 < n && a[j + 1] > a[j])
      j++; // выбираем дочернюю вершину j с максимальным значением
    if (a[j] > x) { // если свойство пирамиды не выполняется
      // то рассматриваем вершину j как корневую
      a[i] = a[j];
      i = j;
      j = 2 * i + 1;
    } else
      f = false;
  }
  a[i] = x;
}

void Array::Heapsort() {
  // генерация кучи
  for (int i = n / 2 - 1; i >= 0; i--)
    this->heapify(n, i);
  cout << *this << endl;
  // сортировка на сгенерированной куче
  for (int i = n - 1; i > 0; i--) {
    swap(a[0], a[i]);
    this->heapify(i, 0);
  }
}

void measuring() {

  Array test_arr(10000000, 1);
  Array shell_arr = test_arr;
  Array heap_arr = test_arr;
  Array hoar_arr = test_arr;

  auto time_start = high_resolution_clock::now();
  shell_arr.Shell_sort();
  auto time_end = high_resolution_clock::now();
  duration<double, std::milli> ms_double = time_end - time_start;
  cout << "Shell_sort(): " << ms_double.count() << " ms\n";
  if (shell_arr.Test()) {
    cout << "Shell_sort(): sorted\n";
  } else {
    cout << "Shell_sort(): not sorted\n";
  }
  time_start = high_resolution_clock::now();
  heap_arr.Heapsort();
  time_end = high_resolution_clock::now();
  ms_double = time_end - time_start;
  cout << "Heap_sort(): " << ms_double.count() << " ms\n";
  if (heap_arr.Test()) {
    cout << "Heap_sort(): sorted\n";
  } else {
    cout << "Heap_sort(): not sorted\n";
  }
  time_start = high_resolution_clock::now();
  hoar_arr.Hoar_sort();
  time_end = high_resolution_clock::now();
  ms_double = time_end - time_start;
  cout << "Hoar_sort(): " << ms_double.count() << " ms\n";
  if (hoar_arr.Test()) {
    cout << "Hoar_sort(): sorted\n";
  } else {
    cout << "Hoar_sort(): not sorted\n";
  }
}

int main() {
  Array t(10, 1);
  cin >> t;
  cout << t << endl;
  t.Shell_sort();
  cout << t << endl;
  // measuring();

  return 0;
}
