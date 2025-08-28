#ifndef LOJA_H
#define LOJA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "BoloSimples.h"
#include "BoloRecheado.h"
using namespace std;

class Loja {
    vector<shared_ptr<Bolo>> bolos;

    int pesquisar(string sabor) {
        vector<int> indices;
        for (int i=0; i<(int)bolos.size(); i++) {
            if (bolos[i]->getSabor() == sabor) {
                cout << i << " -> " << bolos[i]->toString() << endl;
                indices.push_back(i);
            }
        }
        if (indices.empty()) return -1;
        if (indices.size() == 1) return indices[0];
        cout << "Digite o índice desejado: ";
        int idx; cin >> idx;
        return idx;
    }

public:
    void inserir();
    void listarTodos();
    void exibirUm();
    void alterar();
    void remover();
    void relatorio();
    void salvar();
    void carregar();
    void menu();
};


inline void Loja::inserir() {
    int tipo;
    cout << "1 - Bolo Simples\n2 - Bolo Recheado\nEscolha: ";
    cin >> tipo;
    cin.ignore();

    string sabor; float preco; int qtd, dia, mes, ano;
    cout << "Sabor: "; getline(cin, sabor);
    cout << "Preço: "; cin >> preco;
    cout << "Quantidade: "; cin >> qtd;
    cout << "Data de fabricação (d m a): "; cin >> dia >> mes >> ano;

    if (tipo == 1) {
        bolos.push_back(make_shared<BoloSimples>(sabor,preco,qtd,Data(dia,mes,ano)));
    } else {
        string recheio;
        cout << "Recheio: "; cin.ignore(); getline(cin, recheio);
        bolos.push_back(make_shared<BoloRecheado>(sabor,preco,qtd,Data(dia,mes,ano),recheio));
    }
}

inline void Loja::listarTodos() {
    for (auto &b : bolos) cout << b->toString() << endl;
}

inline void Loja::exibirUm() {
    cin.ignore();
    string sabor;
    cout << "Sabor para pesquisar: "; getline(cin, sabor);
    int idx = pesquisar(sabor);
    if (idx != -1) cout << bolos[idx]->toString() << endl;
}

inline void Loja::alterar() {
    cin.ignore();
    string sabor;
    cout << "Sabor para alterar: "; getline(cin, sabor);
    int idx = pesquisar(sabor);
    if (idx != -1) {
        float preco; int qtd;
        cout << "Novo preço: "; cin >> preco;
        cout << "Nova quantidade: "; cin >> qtd;
        bolos[idx]->setPreco(preco);
        bolos[idx]->setQuantidade(qtd);
    }
}

inline void Loja::remover() {
    cin.ignore();
    string sabor;
    cout << "Sabor para remover: "; getline(cin, sabor);
    int idx = pesquisar(sabor);
    if (idx != -1) bolos.erase(bolos.begin()+idx);
}

inline void Loja::relatorio() {
    double total=0;
    for (auto &b : bolos) total += b->getPreco()*b->getQuantidade();
    cout << "Bolos cadastrados: " << bolos.size() << endl;
    cout << "Valor total em estoque: R$ " << total << endl;
}

inline void Loja::salvar() {
    ofstream arq("bolos.txt");
    for (auto &b : bolos) arq << b->serialize() << endl;
}

inline void Loja::carregar() {
    ifstream arq("bolos.txt");
    string linha;
    while (getline(arq, linha)) {
        stringstream ss(linha);
        string tipo, sabor, precoS, qtdS, dS, mS, aS, extra;
        getline(ss,tipo,';');
        getline(ss,sabor,';');
        getline(ss,precoS,';');
        getline(ss,qtdS,';');
        getline(ss,dS,';');
        getline(ss,mS,';');
        getline(ss,aS,';');
        getline(ss,extra,';');

        float preco=stod(precoS); int qtd=stoi(qtdS);
        int d=stoi(dS), m=stoi(mS), a=stoi(aS);

        if (tipo=="BoloSimples")
            bolos.push_back(make_shared<BoloSimples>(sabor,preco,qtd,Data(d,m,a)));
        else if (tipo=="BoloRecheado")
            bolos.push_back(make_shared<BoloRecheado>(sabor,preco,qtd,Data(d,m,a),extra));
    }
}

inline void Loja::menu() {
    carregar();
    int op;
    do {
        cout << "\n1-Inserir\n2-Listar\n3-Exibir um\n4-Alterar\n5-Remover\n6-Relatório\n7-Sair\nOpção: ";
        cin >> op;
        switch(op) {
            case 1: inserir(); break;
            case 2: listarTodos(); break;
            case 3: exibirUm(); break;
            case 4: alterar(); break;
            case 5: remover(); break;
            case 6: relatorio(); break;
            case 7: salvar(); break;
        }
    } while (op != 7);
}

#endif

