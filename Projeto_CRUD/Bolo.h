#ifndef BOLO_H
#define BOLO_H
#include <string>
#include <sstream>
#include <iomanip>
#include "Data.h"
using namespace std;

class Bolo {
protected:
    string sabor;
    float preco;
    int quantidade;
    Data dataFabricacao;
public:
    Bolo(string s="", float p=0.0, int q=0, Data d=Data())
        : sabor(s), preco(p), quantidade(q), dataFabricacao(d) {}

    virtual ~Bolo() {}
    virtual string getTipo() const = 0;

    string getSabor() const { return sabor; }
    void setSabor(string s) { sabor = s; }

    float getPreco() const { return preco; }
    void setPreco(float p) { preco = p; }

    int getQuantidade() const { return quantidade; }
    void setQuantidade(int q) { quantidade = q; }

    virtual string toString() const {
        ostringstream oss;
        oss << fixed << setprecision(2) << preco;

        return "[" + getTipo() + "] " + sabor + 
               " | R$ " + oss.str() +
               " | Qtd: " + to_string(quantidade) +
               " | Fabricação: " + dataFabricacao.toString();
    }

    virtual string serialize() const {
        return getTipo() + ";" + sabor + ";" + to_string(preco) + ";" + 
               to_string(quantidade) + ";" + 
               to_string(dataFabricacao.dia) + ";" + 
               to_string(dataFabricacao.mes) + ";" + 
               to_string(dataFabricacao.ano);
    }
};

#endif
