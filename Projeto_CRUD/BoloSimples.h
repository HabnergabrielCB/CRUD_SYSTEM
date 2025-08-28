#ifndef BOLOSIMPLES_H
#define BOLOSIMPLES_H
#include "Bolo.h"

class BoloSimples : public Bolo {
public:
    BoloSimples(string s="", float p=0.0, int q=0, Data d=Data())
        : Bolo(s,p,q,d) {}

    string getTipo() const override { return "BoloSimples"; }
};

#endif
