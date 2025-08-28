#ifndef SISTEMA_H
#define SISTEMA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Livro.h"
#include "Revista.h"
using namespace std;

class Sistema {
    vector<shared_ptr<Produto>> produtos;

    int pesquisar(string nome) {
        vector<int> indices;
        for (int i=0; i<(int)produtos.size(); i++) {
            if (produtos[i]->getNome() == nome) {
                cout << i << " -> " << produtos[i]->toString() << endl;
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

// Implementações inline (poderia ir pra .cpp também)
inline void Sistema::inserir() {
    int tipo;
    cout << "1 - Livro\n2 - Revista\nEscolha: ";
    cin >> tipo;
    cin.ignore();

    string nome; float preco; int qtd, dia, mes, ano;
    cout << "Nome: "; getline(cin, nome);
    cout << "Preço: "; cin >> preco;
    cout << "Quantidade: "; cin >> qtd;
    cout << "Data (d m a): "; cin >> dia >> mes >> ano;

    if (tipo == 1) {
        string autor;
        cout << "Autor: "; cin.ignore(); getline(cin, autor);
        produtos.push_back(make_shared<Livro>(nome,preco,qtd,Data(dia,mes,ano),autor));
    } else {
        int edicao;
        cout << "Edição: "; cin >> edicao;
        produtos.push_back(make_shared<Revista>(nome,preco,qtd,Data(dia,mes,ano),edicao));
    }
}

inline void Sistema::listarTodos() {
    for (auto &p : produtos) cout << p->toString() << endl;
}

inline void Sistema::exibirUm() {
    cin.ignore();
    string nome;
    cout << "Nome para pesquisar: "; getline(cin, nome);
    int idx = pesquisar(nome);
    if (idx != -1) cout << produtos[idx]->toString() << endl;
}

inline void Sistema::alterar() {
    cin.ignore();
    string nome;
    cout << "Nome para alterar: "; getline(cin, nome);
    int idx = pesquisar(nome);
    if (idx != -1) {
        float preco; int qtd;
        cout << "Novo preço: "; cin >> preco;
        cout << "Nova quantidade: "; cin >> qtd;
        produtos[idx]->setPreco(preco);
        produtos[idx]->setQuantidade(qtd);
    }
}

inline void Sistema::remover() {
    cin.ignore();
    string nome;
    cout << "Nome para remover: "; getline(cin, nome);
    int idx = pesquisar(nome);
    if (idx != -1) produtos.erase(produtos.begin()+idx);
}

inline void Sistema::relatorio() {
    double total=0;
    for (auto &p : produtos) total += p->getPreco()*p->getQuantidade();
    cout << "Itens cadastrados: " << produtos.size() << endl;
    cout << "Valor total em estoque: R$ " << total << endl;
}

inline void Sistema::salvar() {
    ofstream arq("dados.txt");
    for (auto &p : produtos) arq << p->serialize() << endl;
}

inline void Sistema::carregar() {
    ifstream arq("dados.txt");
    string linha;
    while (getline(arq, linha)) {
        stringstream ss(linha);
        string tipo, nome, precoS, qtdS, dS, mS, aS, extra;
        getline(ss,tipo,';');
        getline(ss,nome,';');
        getline(ss,precoS,';');
        getline(ss,qtdS,';');
        getline(ss,dS,';');
        getline(ss,mS,';');
        getline(ss,aS,';');
        getline(ss,extra,';');

        float preco=stod(precoS); int qtd=stoi(qtdS);
        int d=stoi(dS), m=stoi(mS), a=stoi(aS);
        if (tipo=="Livro")
            produtos.push_back(make_shared<Livro>(nome,preco,qtd,Data(d,m,a),extra));
        else if (tipo=="Revista")
            produtos.push_back(make_shared<Revista>(nome,preco,qtd,Data(d,m,a),stoi(extra)));
    }
}

inline void Sistema::menu() {
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
