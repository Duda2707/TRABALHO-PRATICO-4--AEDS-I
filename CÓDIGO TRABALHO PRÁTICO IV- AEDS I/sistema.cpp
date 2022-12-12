#include "sistema.hpp"

void menu()//exibe o menu do programa
{
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                    Linhas de Ônibus                    #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                1 - Procura Linha de Ônibus             #" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                2 - Manutenção                          #" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                3 - Sair                                #" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
}

void procuraLinhaDeOnibus(forward_list<Linha> *lista_linhas)//procura linhas de onibus
{
    system("cls");
    if (lista_linhas->empty())
    {
        cout << "Não existem linhas cadastradas." << endl;//exibe a mensagem
        cout << "Acesse o menu de 'Manutenção' para adicionar novas linhas." << endl;
        system("pause");
        return;
    }

    unsigned int opcao;
    do
    {
        cout << "##########################################################" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                Procura Linha de Ônibus                 #" << endl;
        cout << "#                                                        #" << endl;
        cout << "##########################################################" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                1 - Pesquisa Por Cidade                 #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                2 - Pesquisa Por Código                 #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                3 - Voltar                              #" << endl;
        cout << "#                                                        #" << endl;
        cout << "##########################################################" << endl;
        cin >> opcao;
        cin.ignore();
        switch (opcao)
        {
        case 1:
            pesquisaPorCidade(lista_linhas);//pesquisa as linhas por nome de origem e destino
            break;

        case 2:
            pesquisaPorCodigo(lista_linhas);//pesquisa linhas por codigo 
            break;
        }
        system("cls");
    } while (opcao != 3);//enquanto a opcao for igual a 3
}

void pesquisaPorCidade(forward_list<Linha> *lista_linhas)//pesquisa por cidade
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                  Pesquisa Por Cidade                   #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Digite o nome da cidade de origem: ";//cidade de saida
    string cidade_origem;
    getline(cin, cidade_origem);//nao da erro ao ler

    cout << "Digite o nome da cidade de destino: ";//cidade de destino
    string cidade_destino;
    getline(cin, cidade_destino);//nao da erro ao ler

    forward_list<Linha> lista_linhas_com_cidade_selecionada;  // Separa as linhas que possuem a cidade de destino

    for (auto &linha : *lista_linhas)
    {
        if (!ListaDuplamenteEncadeadaCircularEstaVazia(&linha.lista_paradas))//se nao estiver vazio
        {
            Apontador aux = linha.lista_paradas.inicio->prox;//comeca do inicio da lista
            do
            {
                aux = aux->prox;//avanca para o proximo
                if (aux->item.nome.compare(cidade_destino) == 0)
                {
                    lista_linhas_com_cidade_selecionada.push_front(linha);//primerio elemento 
                    break;
                }
            } while (aux != linha.lista_paradas.fim);//enquanto nao chegar ao fim
        }
    }

    struct informacoes_importantes
    {
        Linha linha;
        float preco = 0;
        Parada origem;
        Parada destino;
    };

    vector<informacoes_importantes> lista_informacoes;//criou uma vector com a struct a cima

    // Separa as linhas anteriormente separadas que possuem a cidade de origem
    for (auto &linha : lista_linhas_com_cidade_selecionada)
    {
        Apontador aux = linha.lista_paradas.fim;//comeca do fim da lista
        bool cidade_destino_encontrada = false;//comeca como falso
        informacoes_importantes informacoes;//declara
        while (aux != linha.lista_paradas.inicio)//vai do fim para o inicio procurando
        {
            informacoes.linha = linha;
            if (aux->item.nome.compare(cidade_destino) == 0)//se achar o destino
            {
                informacoes.destino = aux->item;//destino recebe o item
                cidade_destino_encontrada = true;//recebe achado
            }
            else if (aux->item.nome.compare(cidade_origem) == 0)//se achar a origem
            {
                if (cidade_destino_encontrada)//se o destino for encontrado 
                {
                    informacoes.origem = aux->item;//origem recebe o item
                    informacoes.preco += aux->item.valor_passagem;//preco
                    lista_informacoes.push_back(informacoes);//ultimo 
                }
                break;
            }
            else if (cidade_destino_encontrada)//se encontou o destino
            {
                informacoes.preco += aux->item.valor_passagem;//faz o valor da passagem
            }
            aux = aux->ant;//vai andando para traz
        }
    }

    if (lista_informacoes.empty())//se tem elementos na lista ou nao
    {
        cout << "Nenhuma linha encontrada." << endl;
        Sleep(2000);//pausa de 2 segundos
    }
    else
    {
        cout << "\n";
        for (auto &informacoes : lista_informacoes)// Separa as linhas com informacoes
        {
            cout << "Linha: " << informacoes.linha.codigo << endl;
            cout << "Origem: " << informacoes.origem.nome << endl;
            cout << "Destino: " << informacoes.destino.nome << endl;
            cout << "Preço da Passagem: R$:" << informacoes.preco << endl;
            cout << "Horário Saída: " << put_time(&informacoes.origem.horario_saida, "%H:%M") << endl;
            cout << "Horário Chegada: " << put_time(&informacoes.destino.horario_chegada, "%H:%M") << endl;
            cout << "\n";
        }
        system("pause");
    }
}

void pesquisaPorCodigo(forward_list<Linha> *lista_linhas)//pesquisa pelo codigo 
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                  Pesquisa Por Código                   #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Digite o código da linha: ";
    string codigo;
    getline(cin, codigo);//para nao dar erro na leitura
    Linha *linha_encontrada = procuraLinhaPorCodigo(lista_linhas, codigo);//varivvel recebe o return da funcao
    if (linha_encontrada == NULL)//se nao foi encontrado
    {
        cout << "Não foi encontrado nenhuma linha com o código passado." << endl;
        Sleep(2000);//pausa de 2 segundos
    }
    else
    {//se nao exibe
        cout << "Código: " << linha_encontrada->codigo << endl;
        cout << "Companhia: " << linha_encontrada->companhia << endl;
        ImprimeListaDuplamenteEncadeadaCircular(&linha_encontrada->lista_paradas);//imprime a lista circular
        system("pause");
    }
}

void manutencaoDoPrograma(forward_list<Linha> *lista_linhas)//para modificar as linhas
{
    if (!validaSenha())//verifica a senha pedida
    {
        cout << "Senha Inválida!" << endl;
        Sleep(2000);//pausa de 2 segundos
        return;
    }
    system("cls");
    unsigned int opcao;
    do//mostra o menu de manutencao
    {
        cout << "##########################################################" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                Manutenção do Programa                  #" << endl;
        cout << "#                                                        #" << endl;
        cout << "##########################################################" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                1 - Incluir Nova Linha                  #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                2 - Incluir Nova Parada                 #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                3 - Alterar Parada                      #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                4 - Eliminar Parada                     #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                5 - Eliminar Linha                      #" << endl;
        cout << "#                                                        #" << endl;
        cout << "#                6 - Voltar                              #" << endl;
        cout << "#                                                        #" << endl;
        cout << "##########################################################" << endl;
        cin >> opcao;
        cin.ignore();//para nao dar erro
        switch (opcao)//as opcoes de manutencao
        {
        case 1:
            incluirNovaLinha(lista_linhas);//inclui uma nova linha
            break;

        case 2:
            incluirParada(lista_linhas);//inclui uma nova parada a uma linha
            break;

        case 3:
            alterarParada(lista_linhas);//altera uma parada
            break;

        case 4:
            eliminarParada(lista_linhas);//remove uma parada
            break;

        case 5:
            eliminarLinha(lista_linhas);//remove uma linha
            break;
        }
        system("cls");
    } while (opcao != 6);//enquanto a opcao nao for 6
}

bool validaSenha()//vai verificar a senha
{
    system("cls");
    string senha;
    cout << "Senha: ";
    getline(cin, senha);
    return senha.compare(SENHA) == 0;//compara se a senha digitada e igual a q se pede
}

void incluirNovaLinha(forward_list<Linha> *lista_linhas)//insere uma nova linha
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                   Incluir Nova Linha                   #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Código da nova linha (-1 para cancelar): ";
    string codigo;
    getline(cin, codigo);//para nao dar erro na leitura
    if (codigo.compare("-1") == 0)//compara 
    {
        return;
    }
    if (procuraLinhaPorCodigo(lista_linhas, codigo) == NULL)//se a linha for fazia
    {
        Linha nova_linha;
        nova_linha.codigo = codigo;//nova linha recebe codigo
        cout << "Nome da companhia: ";
        getline(cin, nova_linha.companhia);//le a compania
        CriaListaDuplamenteEncadeadaCircularVazia(&nova_linha.lista_paradas);//cria a lista de paradas
        cout << "Insira no mínimo 2 paradas (Origem e Destino):" << endl;
        unsigned int numero_paradas = 0;
        unsigned int opcao;
        do
        {//faz 2 vezes para inserir duas paradas
            Parada nova_parada;
            criaParada(&nova_parada);//cria parada
            InsereListaDuplamenteEncadeadaCircularUltimo(&nova_linha.lista_paradas, &nova_parada);//insere a parada
            numero_paradas++;//atualiza o numero de paradas
            if (numero_paradas >= 2)//se for menor ou igual a 2
            {
                do//pergunta
                {
                    cout << "Deseja adicionar outra parada?" << endl;
                    cout << "1-Sim" << endl;
                    cout << "2-Não" << endl;
                    cin >> opcao;
                    cin.ignore();
                    system("cls");
                } while (opcao > 2);//enquanto op for diferente de 2
            }
            system("cls");
        } while (numero_paradas < 2 || opcao == 1);//enquanto for menor q 2 paradas

        cout << "Linha criada com sucesso." << endl;
        lista_linhas->push_front(nova_linha);//inicio
        Sleep(1000);//pausa de 1 segundo
    }
    else
    {//se nao exibe a mensagem
        cout << "Linha já cadastrada, verifique e tente novamente." << endl;
        Sleep(2000);//pausa de 2 segundos
    }
}

Linha *procuraLinhaPorCodigo(forward_list<Linha> *lista_linhas, string codigo)//procura a linha pelo codigo
{
    for (auto &linha : *lista_linhas)// Separa 
    {
        if (linha.codigo.compare(codigo) == 0)//compara os codigos e retorna a linha
        {
            return &linha;
        }
    }
    return NULL;
}

void criaParada(Parada *parada)//cria nova parada
{
    cout << "Nome da Parada: ";
    getline(cin, parada->nome);//le o nome
    cout << "Horario de Chegada (ex: 12:30): ";
    cin >> get_time(&parada->horario_chegada, "%H:%M");
    cout << "Horario de Saída (ex: 13:00): ";
    cin >> get_time(&parada->horario_saida, "%H:%M");
    cout << "Valor da Passagem: R$ ";
    cin >> parada->valor_passagem;
    cin.ignore();// para nao dar erro na leitura
}

void incluirParada(forward_list<Linha> *lista_linhas)//inclui novas paradas
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                   Incluir Nova Parada                  #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Código da nova linha (-1 para cancelar): ";
    string codigo;
    getline(cin, codigo);//le o codigo
    if (codigo.compare("-1") == 0)//compara ele
    {
        return;
    }
    Linha *linha_encontrada = procuraLinhaPorCodigo(lista_linhas, codigo);//recebe o resultado da funcao
    if (linha_encontrada == NULL)//se a linha encontada for igul a nulo
    {
        cout << "Não foi encontrado nenhuma linha com o código passado." << endl;//exibe
        Sleep(2000);//pausa de 2 segundos
    }
    else
    {
        ImprimeListaDuplamenteEncadeadaCircular(&linha_encontrada->lista_paradas);//imprime a lista de paradas
        cout << "Escolha o id da parada a qual deseja inserir após: ";
        unsigned int id;
        cin >> id;
        cin.ignore();
        if (validaId(&linha_encontrada->lista_paradas, id))//valida o id procurado
        {
            Parada nova_parada;
            criaParada(&nova_parada);//cria nova parada
            InsereListaDuplamenteEncadeadaCircularApos(&linha_encontrada->lista_paradas, &nova_parada, id);
        }// insere apos o id procurado
    }
}

void alterarParada(forward_list<Linha> *lista_linhas)//altera a parada
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                     Alterar Parada                     #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Código da nova linha (-1 para cancelar): ";
    string codigo;
    getline(cin, codigo);
    if (codigo.compare("-1") == 0)//procura
    {
        return;
    }
    Linha *linha_encontrada = procuraLinhaPorCodigo(lista_linhas, codigo);//recebe o resultado da funcao
    if (linha_encontrada == NULL)
    {
        cout << "Não foi encontrado nenhuma linha com o código passado." << endl;
        Sleep(2000);//pausa de 2 segundos
    }
    else
    {
        cout << "Escolha o id da parada a qual deseja atualizar: " << endl;
        ImprimeListaDuplamenteEncadeadaCircular(&linha_encontrada->lista_paradas);//exibe a lista de paradas
        unsigned int id;
        cin >> id;
        cin.ignore();//para nao dar erro
        Parada *parada_encontrada = PesquisaParada(&linha_encontrada->lista_paradas, id);//recebe o resultado da funcao
        if (parada_encontrada == NULL)//se a parada for igual a nulo
        {
            cout << "Nenhuma parada com esse id encontrada." << endl;
            Sleep(2000);//pausa de 2 segundos
        }
        else//se nao
        {
            criaParada(parada_encontrada);//cria parada
            cout << "Parada Atualizada com Sucesso!" << endl;
            Sleep(1000);//pausa de 1 segundo
        }
    }
}

void eliminarParada(forward_list<Linha> *lista_linhas)//remove uma parada
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                     Elimina Parada                     #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Código da nova linha (-1 para cancelar): ";
    string codigo;
    getline(cin, codigo);
    if (codigo.compare("-1") == 0)//compara
    {
        return;
    }
    Linha *linha_encontrada = procuraLinhaPorCodigo(lista_linhas, codigo);//recebe o resultado da funcao
    if (linha_encontrada == NULL)//se a linha for igual a nulo
    {
        cout << "Não foi encontrado nenhuma linha com o código passado." << endl;
        Sleep(2000);//pausa de 2 segundos
    }
    else
    {
        if (TamanhoListaDuplamenteEncadeadaCircular(&linha_encontrada->lista_paradas) == 2)
        {//se o tamanho da lista for igual a 2
            cout << "Não é possível ter uma linha com menos de duas (2) paradas." << endl;
            Sleep(2000);//pausa de 2 segundos
        }
        else
        {
            cout << "Escolha o id da parada a qual deseja excluir: " << endl;
            ImprimeListaDuplamenteEncadeadaCircular(&linha_encontrada->lista_paradas);
            //imprime a lista de paradas para escolha
            unsigned int id;
            cin >> id;
            cin.ignore();//para nao dar erro na leitura
            Parada *parada_encontrada = PesquisaParada(&linha_encontrada->lista_paradas, id);
            //recebe o resultado da funcao pesquisa
            if (parada_encontrada == NULL)//se a parada for igual a nulo
            {
                cout << "Nenhuma parada com esse id encontrada." << endl;
                Sleep(2000);//pausa de 2 segundos
            }
            else//se nao
            {
                RemoveParada(&linha_encontrada->lista_paradas, *parada_encontrada);//remove a parada
                cout << "Parada Removida com Sucesso!" << endl;
                Sleep(1000);//pausa de 1 segundo
            }
        }
    }
}

void eliminarLinha(forward_list<Linha> *lista_linhas)//remove uma linha
{
    system("cls");
    cout << "##########################################################" << endl;
    cout << "#                                                        #" << endl;
    cout << "#                     Elimina Linha                      #" << endl;
    cout << "#                                                        #" << endl;
    cout << "##########################################################" << endl;
    cout << "Código da nova linha (-1 para cancelar): ";
    string codigo;
    getline(cin, codigo);
    if (codigo.compare("-1") == 0)//compara o codigo
    {
        return;
    }
    Linha *linha_encontrada = procuraLinhaPorCodigo(lista_linhas, codigo);//recebe o resultado da funcao
    if (linha_encontrada == NULL)//se a linha for igual a nulo
    {
        cout << "Não foi encontrado nenhuma linha com o código passado." << endl;
        Sleep(2000);//pausa de 2 segundos
    }
    else
    {// se nao 
        lista_linhas->remove(*linha_encontrada);//remove a linha_encontrada
        cout << "Linha Removida com Sucesso!" << endl;
        Sleep(1000);//pausa de 1 segundo
    }
}