#ifndef BOLORECHEADO_H
#define BOLORECHEADO_H
#include "Bolo.h"

class BoloRecheado : public Bolo {
    string recheio;
public:
    BoloRecheado(string s="", float p=0.0, int q=0, Data d=Data(), string r="")
        : Bolo(s,p,q,d), recheio(r) {}

    string getTipo() const override { return "BoloRecheado"; }

    string toString() const override {
        return Bolo::toString() + " | Recheio: " + recheio;
    }

    string serialize() const override {
        return Bolo::serialize() + ";" + recheio;
    }
};

#endif
