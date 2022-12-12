#ifndef LISTA_DUPLAMENTE_ENCADEADA_CIRCULAR_H
#define LISTA_DUPLAMENTE_ENCADEADA_CIRCULAR_H

#include <string>
#include <time.h>
#include <iomanip>
#include <windows.h>

using namespace std;

typedef struct Parada
{
    unsigned int id;
    string nome;
    tm horario_chegada;
    tm horario_saida;
    float valor_passagem;
};

typedef struct Celula *Apontador;

typedef struct Celula
{
    Parada item;
    Apontador prox = NULL;
    Apontador ant = NULL;
};

typedef struct ListaDuplamenteEncadeadaCircular
{
    Apontador inicio;
    Apontador fim;
    unsigned int tamanho;
    bool foi_criada;
};

void CriaListaDuplamenteEncadeadaCircularVazia(ListaDuplamenteEncadeadaCircular *lista);
bool ListaDuplamenteEncadeadaCircularEstaVazia(ListaDuplamenteEncadeadaCircular *lista);
void InsereListaDuplamenteEncadeadaCircularPrimeiro(ListaDuplamenteEncadeadaCircular *lista, Parada *parada);
void InsereListaDuplamenteEncadeadaCircularUltimo(ListaDuplamenteEncadeadaCircular *lista, Parada *parada);
void InsereListaDuplamenteEncadeadaCircularApos(ListaDuplamenteEncadeadaCircular *lista, Parada *parada, unsigned int id);
bool validaId(ListaDuplamenteEncadeadaCircular *lista, unsigned int id);
void ImprimeParada(Parada *parada);
Parada *PesquisaParada(ListaDuplamenteEncadeadaCircular *lista_paradas, unsigned int id);
void RemoveParada(ListaDuplamenteEncadeadaCircular *lista, Parada parada);
void AtualizaUltimo(ListaDuplamenteEncadeadaCircular *lista);
int TamanhoListaDuplamenteEncadeadaCircular(ListaDuplamenteEncadeadaCircular *lista);

#endif