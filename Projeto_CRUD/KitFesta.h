#ifndef KITFESTA_H
#define KITFESTA_H
#include "ProdutoLoja.h"

class KitFesta : public ProdutoLoja {
    int qtdDocinhos;
    int qtdSalgados;
public:
    KitFesta(string n="", float p=0.0, int q=0, Data d=Data(), int docinhos=0, int salgados=0)
        : ProdutoLoja(n,p,q,d), qtdDocinhos(docinhos), qtdSalgados(salgados) {}

    string getTipo() const override { return "KitFesta"; }

    string toString() const override {
        return ProdutoLoja::toString() + 
               " | Docinhos: " + to_string(qtdDocinhos) + 
               " | Salgados: " + to_string(qtdSalgados);
    }

    string serialize() const override {
        return ProdutoLoja::serialize() + ";" + 
               to_string(qtdDocinhos) + ";" + to_string(qtdSalgados);
    }
};

#endif
