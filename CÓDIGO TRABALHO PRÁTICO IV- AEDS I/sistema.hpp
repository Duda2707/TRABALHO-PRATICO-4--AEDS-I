#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <forward_list> //Biblioteca do c++ de Lista Encadeada Simples
#include <string>
#include <windows.h>
#include <vector>
#include "ListaDuplamenteEncadeadaCircular.cpp"

using namespace std;

#define OPCAO_SAIDA 3
#define SENHA "admin"

typedef struct Linha
{
    string codigo;
    string companhia;
    ListaDuplamenteEncadeadaCircular lista_paradas;

    bool operator==(const Linha &rhs) { return codigo.compare(rhs.codigo) == 0; } // Sobrecarga no operador de verificação de igualdade. Compara os códigos das linhas. Necessário para apagar o item usando o método remove da forward_list
};

void menu();

void procuraLinhaDeOnibus(forward_list<Linha> *lista_linhas);
void pesquisaPorCidade(forward_list<Linha> *lista_linhas);
void pesquisaPorCodigo(forward_list<Linha> *lista_linhas);

void manutencaoDoPrograma(forward_list<Linha> *lista_linhas);
bool validaSenha();
void incluirNovaLinha(forward_list<Linha> *lista_linhas);
Linha *procuraLinhaPorCodigo(forward_list<Linha> *lista_linhas, string codigo);
void criaParada(Parada *parada);
void incluirParada(forward_list<Linha> *lista_linhas);
void alterarParada(forward_list<Linha> *lista_linhas);
void eliminarParada(forward_list<Linha> *lista_linhas);
void eliminarLinha(forward_list<Linha> *lista_linhas);

#endif