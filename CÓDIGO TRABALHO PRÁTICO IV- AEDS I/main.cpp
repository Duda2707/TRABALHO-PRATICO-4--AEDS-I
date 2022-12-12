#include "sistema.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    UINT UTF8 = 65001;
    SetConsoleOutputCP(UTF8);

    forward_list<Linha> lista_linhas;//declara

    unsigned int opcao;
    do
    {
        system("cls");
        menu();//mostra o menu do programa
        cin >> opcao;//le a opcao escolhida
        cin.ignore();//para nao dar erro na leitura

        switch (opcao)
        {
        case 1:
            procuraLinhaDeOnibus(&lista_linhas);//procura as linhas de onibus
            break;

        case 2:
            manutencaoDoPrograma(&lista_linhas);//abre a funcao que pede a senha para alteracao do programa
            break;
        }

    } while (opcao != OPCAO_SAIDA);//enquanto nao for a opcao de sair 

    return 0;
}
