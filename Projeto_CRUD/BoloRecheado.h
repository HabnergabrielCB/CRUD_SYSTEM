#ifndef BOLORECHEADO_H
#define BOLORECHEADO_H
#include "ProdutoLoja.h"
#include <string>
#include <iostream>

using namespace std;


class BoloRecheado : public ProdutoLoja {
    string recheio;
public:
    BoloRecheado(string s="", float p=0.0, int q=0, Data d=Data(), string r="")
        : ProdutoLoja(s,p,q,d), recheio(r) {}

    string getTipo() const override { return "BoloRecheado"; }

    string toString() const override {
        return ProdutoLoja::toString() + " | Recheio: " + recheio;
    }

    string serialize() const override {
        return ProdutoLoja::serialize() + ";" + recheio;
    }
};

#endif

