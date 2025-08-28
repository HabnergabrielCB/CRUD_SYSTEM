#ifndef LIVRO_H
#define LIVRO_H
#include "Produto.h"

class Livro : public Produto {
    string autor;
public:
    Livro(string n="", float p=0.0, int q=0, Data d=Data(), string a="")
        : Produto(n,p,q,d), autor(a) {}

    string getTipo() const override { return "Livro"; }

    string toString() const override {
        return Produto::toString() + " | Autor: " + autor;
    }

    string serialize() const override {
        return Produto::serialize() + ";" + autor;
    }
};

#endif
