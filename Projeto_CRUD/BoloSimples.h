#ifndef BOLOSIMPLES_H
#define BOLOSIMPLES_H
#include "ProdutoLoja.h"

class BoloSimples : public Produto {
    public:
    BoloSimples(string s="", float p=0.0, int q=0, Data d=Data())
        : Produto(s,p,q,d) {}

    string getTipo() const override { return "BoloSimples"; }
};


#endif
