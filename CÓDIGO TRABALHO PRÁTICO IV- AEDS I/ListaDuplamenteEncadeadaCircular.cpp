#include "ListaDuplamenteEncadeadaCircular.hpp"

void CriaListaDuplamenteEncadeadaCircularVazia(ListaDuplamenteEncadeadaCircular *lista)
{
    if (!lista->foi_criada)//se a lista nao foi criada
    {
        lista->inicio = new Celula;//cria uma nova celula
        lista->fim = lista->inicio;//o fim aponta para o inicio
        lista->fim->prox = NULL;//o prox do fim aponta para nulo
        lista->fim->ant = NULL;//o anterior tambem aponta para nulo
        lista->foi_criada = true;//list criada recebe true
        lista->tamanho = 0;//inicia o tamanho como 0 
    }
    else
    {
        cout << "Lista já foi criada" << endl;//se ja foi criada exibe a mensagem
        Sleep(1000);
    }
}

bool ListaDuplamenteEncadeadaCircularEstaVazia(ListaDuplamenteEncadeadaCircular *lista)
{
    return (lista->inicio == lista->fim);//verifica se a lista esta vazia
}

void InsereListaDuplamenteEncadeadaCircularPrimeiro(ListaDuplamenteEncadeadaCircular *lista, Parada *parada)
{
    Apontador nova_celula = new Celula;//cria nova celula em um auxiliar
    nova_celula->item = *parada;//preenche com o item 

    nova_celula->prox = lista->inicio->prox;//nova celula aponta para o primeiro
    nova_celula->ant = lista->fim;//o anterior dela aponta para o fim 
    lista->inicio->prox->ant = nova_celula;//atualiza o ant do primeiro pra a nova celula
    lista->fim->prox = nova_celula;//atualiza o prox do fim 
    lista->inicio->prox = nova_celula;//atualiza o inicio
    lista->tamanho++;//atualiza o tamanho 

    AtualizaUltimo(lista);//atualiza o ponteiro ultimo
}

void InsereListaDuplamenteEncadeadaCircularUltimo(ListaDuplamenteEncadeadaCircular *lista, Parada *parada)
{
    Apontador nova_celula = new Celula;// auxiliar recebe uma nova celula
    nova_celula->item = *parada;//preenche ele com o item
    if (lista->inicio->prox == NULL)//se o inicio apontar para nulo
    {
        nova_celula->item.id = 1;//id recebe 1
        lista->inicio->prox = nova_celula;//inicio recebe o auxiliar
        nova_celula->prox = nova_celula;//o aux prox recebe aux
        nova_celula->ant = nova_celula;//o anterior aponta para aux
        lista->fim = nova_celula;//o fim da lista aponta para nova celula
        lista->tamanho++;//atualiza o tamanho;
        return;
    }

    nova_celula->prox = lista->inicio->prox;//aux recebe lista inicio prox
    nova_celula->ant = lista->fim;//aux ante recebe fim da lista
    lista->inicio->prox->ant = nova_celula;//o prox do aux o anteriro dele aponta para nova celula
    lista->fim->prox = nova_celula;//fim da lista o prox aponta para noova celula
    lista->fim = nova_celula;//fim recebe nova celula
    nova_celula->item.id = nova_celula->ant->item.id + 1;//atualiza o id da celula
    lista->tamanho++;//atualiza o tamanho
}

void InsereListaDuplamenteEncadeadaCircularApos(ListaDuplamenteEncadeadaCircular *lista, Parada *parada, unsigned int id)
{
    if (validaId(lista, id))//chama a funcao valida id
    {
        Apontador aux = lista->inicio->prox;//aux recebe primeiro item da lista
        while (aux->item.id != id)//procura o id inserido
        {
            aux = aux->prox;//avanca para o proximo
        }

        Apontador nova_celula = new Celula;//aux recebe nova celula
        nova_celula->item = *parada;//preenche a celula
        nova_celula->prox = aux->prox;//nova celula recebe aux prox
        nova_celula->ant = aux;//o anterior recebe aux
        aux->prox->ant = nova_celula;//o ante do aux prox recebe o nova celula
        aux->prox = nova_celula;//aux prox recebe nova celula
        lista->tamanho++;//atualiza o tamanho
        AtualizaUltimo(lista);//atualiza o ultimo
        cout << "Parada adicionada com sucesso." << endl;
        Sleep(1000);//parada de 1 segundo
    }
}

bool validaId(ListaDuplamenteEncadeadaCircular *lista, unsigned int id)
{
    if (id > TamanhoListaDuplamenteEncadeadaCircular(lista))//procura o id
    {
        cout << "Id não existente" << endl;//exibe a mensagem
        Sleep(2000);//parada de 2 segundos
        return false;
    }
    return true;
}

void ImprimeListaDuplamenteEncadeadaCircular(ListaDuplamenteEncadeadaCircular *lista)
{
    if (ListaDuplamenteEncadeadaCircularEstaVazia(lista))
    {
        return;
    }
    Apontador aux = lista->inicio;//comeca do inicio da lista
    do
    {
        aux = aux->prox;//avanca pro proximo
        ImprimeParada(&aux->item);//imprime as paradas
    } while (aux != lista->fim);//enquanto a lista nao chegar ao fim
}

void ImprimeParada(Parada *parada)//imprime as informacoes das paradas
{
    cout << "Id:" << parada->id << endl;
    cout << "Cidade: " << parada->nome << endl;
    cout << "Horário Chegada: " << put_time(&parada->horario_chegada, "%H:%M") << endl;//imprime o horario usando put_time
    cout << "Horário Saída: " << put_time(&parada->horario_saida, "%H:%M") << endl;//imprime o horario usando put_time
    cout << "Valor: R$ " << parada->valor_passagem << endl;
    cout << "\n";
}

Parada *PesquisaParada(ListaDuplamenteEncadeadaCircular *lista_paradas, unsigned int id)
{
    Apontador aux = lista_paradas->inicio;//comeca do inicio da lista
    do
    {
        aux = aux->prox;//avanca para o proximo
        if (aux->item.id == id)//compara o id
        {
            return &aux->item;//retorna o item achado
        }
    } while (aux != lista_paradas->fim);//percorre enquanto nao chegar ao fim da lista
    return NULL;
}

void RemoveParada(ListaDuplamenteEncadeadaCircular *lista, Parada parada)
{
    if (!ListaDuplamenteEncadeadaCircularEstaVazia(lista))//verifica se nao esta vazia
    {
        Apontador aux;
        aux = lista->inicio;//comeca do inicio da lista
        do
        {
            aux = aux->prox;//avanca para o proximo
        } while (aux->item.id != parada.id);//enquanto nao achar o id procurado
        if (aux == lista->inicio->prox)//se aux for igual ao inicio da lista
        {
            lista->inicio->prox = aux->prox;//recebe o proximo do aux
        }
        aux->ant->prox = aux->prox;//anterior do aux e o prox dele recebe aux prox
        aux->prox->ant = aux->ant;//anterior do prox do aux recebe aux ant
        delete aux;//deleta o aux
        lista->tamanho--;//atualiza o tamanho
        AtualizaUltimo(lista);//atualiza o ultimo
    }
}

void AtualizaUltimo(ListaDuplamenteEncadeadaCircular *lista)
{
    Apontador aux;
    aux = lista->inicio;//comeca do inicio da lista
    unsigned int id = 0;//inicia o id em 0
    do
    {
        aux = aux->prox;//avanca para o proximo
        aux->item.id = ++id;//aumenta o id
    } while (aux->prox != lista->inicio->prox);//enquanto nao for lista inicio

    lista->fim = aux;//lista fim recebe aux
}

int TamanhoListaDuplamenteEncadeadaCircular(ListaDuplamenteEncadeadaCircular *lista)
{
    return lista->tamanho;//retorna o tamanho da lista
}