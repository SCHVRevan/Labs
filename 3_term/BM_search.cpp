#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class String {
    char *str;
    int len;
    public:
        String(int l = 0) {
            str = new char[l + 1];
            len = 0;
            strcpy(str, "\0");
        }
        
        String(const char *a) {
            str = new char[strlen(a) + 1];
            strcpy(str, a);
            len = strlen(a);
        }
        
        String(String &a) {
            str = new char[a.len + 1];
            len = a.len;
            strcpy(str, a.str);
        }
        
        ~String() {
            if (str) {
                delete[]str;
            }
            str = NULL;
        }
        
        int Len() {
            return len;
        }
        
        String &operator = (const String &x) {
            if (this != &x) {
                delete[] str;
                str = new char[x.len + 1];
                strcpy(str, x.str);
                len = x.len;
            }
            return *this;
        }
        
        char &operator [] (int x) {
            if (x < 0 || x >= len) {
                exit(1);
            }
            return str[x];
        }
        
        bool operator == (String &x) {
            if (strcmp(str, x.str)) {
                return false;
            }
            return true;
        }
        
        bool operator != (String &x) {
            if (strcmp(str, x.str)) {
                return true;
            }
            return false;
        }
        
        String operator + (const String &x) {
            String y(len + x.len + 1);
            y.len = len + x.len;
            strcpy(y.str, str);
            strcat(y.str, x.str);
            return y;
        }
        
        String &operator += (const String &x) {
            char *t = new char[len + 1];
            strcpy(t, str);
            delete[] str;
            len = len + x.len;
            str = new char[len + 1];
            strcpy(str, t);
            strcat(str, x.str);
            delete[] t;
            return *this;
        }
        
        friend istream &operator >> (istream &in, String &x) {
            char tmp[100];
            in >> tmp;
            String q(tmp);
            x = q;
            return in;
        }
        
        friend ostream &operator << (ostream &out, String &x) {
            cout << x.str;
            return out;
        }
        
        int BMH_search(String &);               // БМ поиск
};

int String::BMH_search(String &x) {             // БМ поиск
            int m = x.len;                      // длинна образца
            int n = len;                        // длина текста
            int t[256];                         // выделение памяти под таблицу символов
            fill_n(t, 256, m);                  // заполнение элементов таблицы символов длинной образца
            for (int i = m - 1; i >= 0; i--) {  // заменяем значения встречающихся в образце элементов
                t[(int)x.str[i]] = m - i - 1;
            }
            int i = m - 1, j = m - 1;
            while (i < n && j >= 0) {
                int k = i;
                j = m - 1;
                while (j >= 0) {
                    if (str[k] != x.str[j]) {
                        i += t[str[i]];
                        break;
                    }
                    j--;
                    k--;
                }
            }
            if (j >= 0) {
                return -1;
            }
            else return i - m + 1;
        }

int main() {
    String a, b, c, d, f;
    cin >> a >> b >> d >> f;
    cout << "String d = " << d << "\nString f = " << f;
    
    c = d + f;
    cout << "\n\nc = d + f = " << c;
    c += d;
    cout << "\nc += d = " << c;
    if (c == f) {
        cout << "\nc equal to f\n";
    }
    if (c != f) {
        cout << "\nc aren't equal to f\n";
    }

    cout << "\nString a = " << a << "\nString b = " << b << "\nFirst_occurrence = " << a.BMH_search(b);
    cout << "\n\nLen(" << a << ") = " << a.Len();

    return 0;
}