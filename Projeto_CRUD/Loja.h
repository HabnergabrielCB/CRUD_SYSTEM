#ifndef LOJA_H
#define LOJA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "BoloSimples.h"
#include "BoloRecheado.h"
#include "KitFesta.h"
using namespace std;

class Loja {
    vector<shared_ptr<ProdutoLoja>> produtos;

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
        cout << "Digite o indice desejado: ";
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

// implementacoes
inline void Loja::inserir() {
    int tipo;
    cout << "1 - Bolo Simples\n2 - Bolo Recheado\n3 - Kit Festa\nEscolha: ";
    cin >> tipo;
    cin.ignore();

    string nome; float preco; int qtd, dia, mes, ano;
    cout << "Nome do Cliente: "; getline(cin, nome);
    cout << "Preco: "; cin >> preco;
    cout << "Quantidade: "; cin >> qtd;
    cout << "Data de entrega (d m a): "; cin >> dia >> mes >> ano;

    if (tipo == 1) {
        produtos.push_back(make_shared<BoloSimples>(nome,preco,qtd,Data(dia,mes,ano)));
    } 
    else if (tipo == 2) {
        string recheio;
        cout << "Recheio: "; cin.ignore(); getline(cin, recheio);
        produtos.push_back(make_shared<BoloRecheado>(nome,preco,qtd,Data(dia,mes,ano),recheio));
    }
    else if (tipo == 3) {
        int docinhos, salgados;
        cout << "Qtd Docinhos: "; cin >> docinhos;
        cout << "Qtd Salgados: "; cin >> salgados;
        produtos.push_back(make_shared<KitFesta>(nome,preco,qtd,Data(dia,mes,ano),docinhos,salgados));
    }
}

inline void Loja::listarTodos() {
    for (auto &p : produtos) cout << p->toString() << endl;
}

inline void Loja::exibirUm() {
    cin.ignore();
    string nome;
    cout << "Nome para pesquisar: "; getline(cin, nome);
    int idx = pesquisar(nome);
    if (idx != -1) cout << produtos[idx]->toString() << endl;
}

inline void Loja::alterar() {
    cin.ignore();
    string nome;
    cout << "Nome para alterar: "; getline(cin, nome);
    int idx = pesquisar(nome);
    if (idx != -1) {
        float preco; int qtd;
        cout << "Novo preco: "; cin >> preco;
        cout << "Nova quantidade: "; cin >> qtd;
        produtos[idx]->setPreco(preco);
        produtos[idx]->setQuantidade(qtd);
    }
}

inline void Loja::remover() {
    cin.ignore();
    string nome;
    cout << "Nome para remover: "; getline(cin, nome);
    int idx = pesquisar(nome);
    if (idx != -1) produtos.erase(produtos.begin()+idx);
}

inline void Loja::relatorio() {
    double total=0;
    for (auto &p : produtos) total += p->getPreco()*p->getQuantidade();
    cout << "Produtos cadastrados: " << produtos.size() << endl;
    cout << "Valor total em estoque: R$ " << fixed << setprecision(2) << total << endl;
}

inline void Loja::salvar() {
    ofstream arq("produtos.txt");
    for (auto &p : produtos) arq << p->serialize() << endl;
}

inline void Loja::carregar() {
    ifstream arq("produtos.txt");
    string linha;
    while (getline(arq, linha)) {
        stringstream ss(linha);
        string tipo, nome, precoS, qtdS, dS, mS, aS, extra1, extra2;
        getline(ss,tipo,';');
        getline(ss,nome,';');
        getline(ss,precoS,';');
        getline(ss,qtdS,';');
        getline(ss,dS,';');
        getline(ss,mS,';');
        getline(ss,aS,';');

        float preco=stod(precoS); int qtd=stoi(qtdS);
        int d=stoi(dS), m=stoi(mS), a=stoi(aS);

        if (tipo=="BoloSimples")
            produtos.push_back(make_shared<BoloSimples>(nome,preco,qtd,Data(d,m,a)));
        else if (tipo=="BoloRecheado") {
            getline(ss,extra1,';');
            produtos.push_back(make_shared<BoloRecheado>(nome,preco,qtd,Data(d,m,a),extra1));
        }
        else if (tipo=="KitFesta") {
            getline(ss,extra1,';');
            getline(ss,extra2,';');
            produtos.push_back(make_shared<KitFesta>(nome,preco,qtd,Data(d,m,a),stoi(extra1),stoi(extra2)));
        }
    }
}

inline void Loja::menu() {
    carregar();
    int op;
    do {
        cout << "\n1-Inserir\n2-Listar\n3-Pesquisar\n4-Alterar\n5-Remover\n6-Relatorio\n7-Sair\nOpcao: ";
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

