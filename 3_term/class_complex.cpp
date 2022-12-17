#include <iostream>
#include <cmath>
using namespace std;

class complex {
    double re, im;
    
    public:
        complex(double Re = 0, double Im = 0);
    
        double getRe();
        void setRe(double);
        double getIm();
        void setIm(double);
    
        bool operator == (complex);
        bool operator != (complex);
    
        double mod() {
                return sqrt(re * re + im * im);
            }
    
        complex operator + (const complex &);
        complex operator - (const complex &);
        complex operator * (const complex &);
        complex operator / (const complex &);
    
        friend ostream& operator << (ostream &st, const complex &x) {
            if (x.im > 0) {
                st << x.re << " + i*" << x.im;
            }
            else if (x.im < 0) {
                st << x.re << " - i*" << (-1) * x.im;
            }
            else {
                st << x.re;
            }
            return st;
        }
    
        friend istream& operator >> (istream &st, complex &x) {
            st >> x.re;
            st >> x.im;
            return st;
        }
};

complex::complex(double Re, double Im) {
    re = Re;
    im = Im;
}

double complex::getRe() {
    return re;
}
        
void complex::setRe(double Re) {
    re = Re;
}
    
double complex::getIm() {
    return im;
}
        
void complex::setIm(double Im) {
    im = Im;
}

bool complex::operator == (complex x) {
    if (re == x.re && im == x.im) {
        return true;
    }
    else {
        return false;
    }
}

bool complex::operator != (complex x) {
    if (re != x.re || im != x.im) {
        return true;
    }
    else {
        return false;
    }
}

complex complex::operator + (const complex &x) {
    complex res;
    res.re = re + x.re;
    res.im = im + x.im;
    return res;
}

complex complex::operator - (const complex &x) {
    complex res;
    res.re = re - x.re;
    res.im = im - x.im;
    return res;
}

complex complex::operator * (const complex &x) {
    complex res;
    res.re = re * x.re - im * x.im;
    res.im = re * x.im - re * x.re;
    return res;
}

complex complex::operator / (const complex &x) {
    complex res;
    res.re = (re*x.re + im*x.im) / (pow(x.re, 2) + pow(x.im, 2));
    res.im = (im*x.re - re*x.im) / (pow(x.re, 2) + pow(x.im, 2));
    return res;
}

int main () {
    complex z_1, z_2;
    
    //cout << "op_1: ";
    cin >> z_1;
    //cout << "\nop_2: ";
    cin >> z_2;
    
    cout << "z_1 = " << z_1 << "\n";
    cout << "z_2 = " << z_2 << "\n";
    
    if (z_1 == z_2) {
        cout << "Equal\n";
    }
    if (z_1 != z_2) {
        cout << "Not Equal\n";
    }
    
    z_1.setRe(z_1.getRe() + 15);
    cout << z_1.getRe() << "\n";
    cout << "mod z_1 = " << z_1.mod() << "\n";
    cout << "mod z_2 = " << z_2.mod() << "\n";
    cout << "z_1 + z_2 = " << z_1 + z_2 << "\n";
    cout << "z_1 - z_2 = " << z_1 - z_2 << "\n";
    cout << "z_1 * z_2 = " << z_1 * z_2 << "\n";
    cout << "z_1 / z_2 = " << z_1 / z_2 << "\n";
    
    return 0;
}
