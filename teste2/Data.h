#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;

class Data {
public:
    int dia, mes, ano;
    Data(int d=1, int m=1, int a=2000) : dia(d), mes(m), ano(a) {}
    string toString() const {
        return to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);
    }
};

#endif
