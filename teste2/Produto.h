#ifndef PRODUTO_H
#define PRODUTO_H
#include <string>
#include "Data.h"
using namespace std;

class Produto {
protected:
    string nome;
    float preco;
    int quantidade;
    Data dataCadastro;
public:
    Produto(string n="", float p=0.0, int q=0, Data d=Data())
        : nome(n), preco(p), quantidade(q), dataCadastro(d) {}

    virtual ~Produto() {}
    virtual string getTipo() const = 0;

    string getNome() const { return nome; }
    void setNome(string n) { nome = n; }

    float getPreco() const { return preco; }
    void setPreco(float p) { preco = p; }

    int getQuantidade() const { return quantidade; }
    void setQuantidade(int q) { quantidade = q; }

    virtual string toString() const {
        return "[" + getTipo() + "] " + nome + " | R$ " + to_string(preco) +
               " | Qtd: " + to_string(quantidade) +
               " | Data: " + dataCadastro.toString();
    }

    virtual string serialize() const {
        return getTipo() + ";" + nome + ";" + to_string(preco) + ";" + 
               to_string(quantidade) + ";" + 
               to_string(dataCadastro.dia) + ";" + 
               to_string(dataCadastro.mes) + ";" + 
               to_string(dataCadastro.ano);
    }
};

#endif
