#ifndef BOLORECHEADO_H
#define BOLORECHEADO_H
#include "Produto.h"
#include <string>
#include <iostream>

using namespace std;


class BoloRecheado : public Produto {
    string recheio;
public:
    BoloRecheado(string s="", float p=0.0, int q=0, Data d=Data(), string r="")
        : Produto(s,p,q,d), recheio(r) {}

    string getTipo() const override { return "BoloRecheado"; }

    string toString() const override {
        return Produto::toString() + " | Recheio: " + recheio;
    }

    string serialize() const override {
        return Produto::serialize() + ";" + recheio;
    }
};

#endif
