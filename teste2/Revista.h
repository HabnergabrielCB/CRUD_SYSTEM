#ifndef REVISTA_H
#define REVISTA_H
#include "Produto.h"

class Revista : public Produto {
    int edicao;
public:
    Revista(string n="", float p=0.0, int q=0, Data d=Data(), int e=0)
        : Produto(n,p,q,d), edicao(e) {}

    string getTipo() const override { return "Revista"; }

    string toString() const override {
        return Produto::toString() + " | Edição: " + to_string(edicao);
    }

    string serialize() const override {
        return Produto::serialize() + ";" + to_string(edicao);
    }
};

#endif
