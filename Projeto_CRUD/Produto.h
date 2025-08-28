#ifndef PRODUTO_H
#define PRODUTO_H
#include <string>
#include <sstream>
#include <iomanip>
#include "Data.h"
using namespace std;

class Produto {
protected:
    string nome;
    float preco;
    int quantidade;
    Data dataFabricacao;
public:
    Produto(string n="", float p=0.0, int q=0, Data d=Data())
        : nome(n), preco(p), quantidade(q), dataFabricacao(d) {}

    virtual ~Produto() {}
    virtual string getTipo() const = 0;

    string getNome() const { return nome; }
    void setNome(string n) { nome = n; }

    float getPreco() const { return preco; }
    void setPreco(float p) { preco = p; }

    int getQuantidade() const { return quantidade; }
    void setQuantidade(int q) { quantidade = q; }

    virtual string toString() const {
        ostringstream oss;
        oss << fixed << setprecision(2) << preco;

        return "[" + getTipo() + "] " + nome + 
               " | R$ " + oss.str() +
               " | Qtd: " + to_string(quantidade) +
               " | Fabricação: " + dataFabricacao.toString();
    }

    virtual string serialize() const {
        return getTipo() + ";" + nome + ";" + to_string(preco) + ";" + 
               to_string(quantidade) + ";" + 
               to_string(dataFabricacao.dia) + ";" + 
               to_string(dataFabricacao.mes) + ";" + 
               to_string(dataFabricacao.ano);
    }
};

#endif
