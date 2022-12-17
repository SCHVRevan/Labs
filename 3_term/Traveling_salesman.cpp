#include <iostream>
using namespace std;

class route {
    // r – массив, представляющий маршрут; n – количество городов
    int *r, n;
    public:
        // создает начальную перестановку по возрастанию
        route(int num = 0);
        // конструктор копирования
        route(const route&);
        // операция присваивания
        route& operator = (const route&);
        // деструктор
        ~route() {
            if(r) delete []r;
            r = NULL;
        }
        // вычисляет стоимость маршрута по матрице стоимости
        int route_price(int**);
        // вычисляет следующий маршрут, используя алгоритм Дейкстры
        bool next_route();
        // вывод маршрута
        friend ostream& operator << (ostream &st, const route &x) {
            for (int i = 0; i < x.n; i++) {
                st << x.r[i] << " ";
            }
            return st;
        }
};

route::route(int num) {
    n = num;
    r = new int[num];
    //заполняем массив числами от 1 до n
    for (int i = 0; i < num; i++) {
        r[i] = i + 1;
    }
}

//копируем длину маршрута
route::route(const route &arr) {
    n = arr.n;
    r = new int[arr.n];
    for (int i = 0; i < arr.n; i++) {
        r[i] = arr.r[i];
    }
}

// перегзузка операции присваивания
route& route::operator = (const route &x) {
    if (this == &x) {   // this - указатель на текущий объект данного класса
        return *this;   // с помощью this можно возвращать текущий объект класса
    }
    delete(r);
    n = x.n;            // присваеваем длину маршрута
    r = new int [x.n];
    for(int i = 0; i < x.n; i++) {
        r[i] = x.r[i];
    }
    return *this;
}

// подсчёт матрицы стоимости
int route::route_price(int** arr) {
    int sum = 0;
    for (int i = 0; i < n-1; i++) {
        sum += arr[r[i]-1][r[i+1]-1];   // заносим стоимость пути между рассматриваемым и следующим городом
    }
    sum += arr[r[n-1]-1][r[0]-1];       // путь из последнего в первый (замыкаем цикл)
    return sum;
}

bool route::next_route() {
    int i, j;
    bool flag = false;
    //поиск i
    for (i = n-2; i >= 0; i--) {
        if (r[i] < r[i+1]) {
            flag = true;
            break;
        }
    }

    if(flag) {
        //поиск j
        for(j = n-1; j > i; j--) {
            if (r[i] < r[j]) {
                break;
            }
        }

        int tmp;
        tmp = r[i];
        r[i] = r[j];
        r[j] = tmp;

        //инвертирование хвоста
        if(i < n-2) {
            int left = i+1;
            int right = n-1;
            while(left < right) {
                tmp = r[left];
                r[left] = r[right];
                r[right] = tmp;
                left++;
                right--;
            }
        }
        if(r[0] != 1) {
            flag = false;
        }
        return flag;
    }
    else {
        return flag;
    }
}

// решение задачи коммивояжера
route solution(int num) {
    int** matrix = new int* [num];
    for (int i = 0; i < num; i++) {
        matrix[i] = new int [num];
    }
    // заполняем матрицу
    for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++) {
            cin >> matrix[i][j];
        }
    }
    route r(num), final_r = r;          // начальный путь по возрастанию нумерации городов и определение конечного пути соответственно
    int sum = r.route_price(matrix);    // стоимость начального пути
    cout << r << "with price " << sum << "  Initial route" << endl;  // вывод начального пути и его стоимость
    while (r.next_route()) {
        int new_sum = r.route_price(matrix);    // стоимость следующего пути
        cout << r << "with price " << new_sum << endl;  // вывод следующего пути и его стоимость
        if (sum > new_sum && new_sum > 0) {     // если путь дешевле, выбираем его
            sum = new_sum;
            final_r = r;
        }
    }
    return final_r;                             // возвращаем лучший путь
}

int main() {
    int n;
    cout << "Number of cities = ";
    cin >> n;
    cout << n << "\n" << solution(n) << "               Final route";
   
    return 0;
}
