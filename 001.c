#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

typedef struct noPaises{
    char nome[50];
    char descricao[200];
    struct noPaises *pProxP;
}NoPaises;

typedef struct noLetra{
    char letra;
    int quant;

    NoPaises *pNomePaises;
    
    struct noLetra *pProxL;
    struct noLetra *pAntL;
}NoLetra;

NoLetra *pInicioL = NULL, *pAuxL, *pAntAux;
NoPaises *pAuxP;

char resp, letraTemp, nomePesq[50], nomePais[50], descricao[200]; int op;

// *****************  FUNÇÕES  *****************

void inserir(){

    letraTemp = toupper(nomePais[0]);
    pAuxL = pInicioL;
    pAntAux = NULL;

    if(pInicioL == NULL){
        NoLetra *novaL = (NoLetra*) malloc(sizeof(NoLetra));
        novaL->letra = letraTemp;
        novaL->quant = 1;
        novaL->pProxL = NULL;
        novaL->pAntL = NULL;    
            
            
        NoPaises *novoP = (NoPaises*) malloc(sizeof(NoPaises));
        strcpy(novoP->nome, nomePais);
        strcpy(novoP->descricao, descricao);
        novoP->pProxP = NULL;

        novaL->pNomePaises = novoP;
        pInicioL = novaL;
        return;
    }//inicio do pragrma, quando esta tudo vazio

    while(pAuxL != NULL){
        if(pAuxL->letra == letraTemp){
            // A letra já existe! Vamos adicionar o país no final da lista de países dela.
            NoPaises *novoP = (NoPaises*) malloc(sizeof(NoPaises));

            strcpy(novoP->nome, nomePais);
            strcpy(novoP->descricao, descricao);
            novoP->pProxP = NULL;

            pAuxP = pAuxL->pNomePaises;
            
            while(pAuxP->pProxP != NULL){
                pAuxP = pAuxP->pProxP;
            }

            pAuxP->pProxP = novoP;
            pAuxL->quant++;

            return;
        }

        pAntAux = pAuxL;
        pAuxL = pAuxL->pProxL; 
    }
    // Se saiu do while, a letra não existe. Vamos criar uma nova no final da lista de letras.
    NoLetra *novaL = (NoLetra*) malloc(sizeof(NoLetra));
    novaL->letra = letraTemp;
    novaL->quant = 1; // Inicializa a quantidade
    novaL->pProxL = NULL;
    novaL->pAntL = pAntAux;

    NoPaises *novoP = (NoPaises*) malloc(sizeof(NoPaises));
    strcpy(novoP->nome, nomePais); 
    strcpy(novoP->descricao, descricao);
    novoP->pProxP = NULL;   

    novaL->pNomePaises = novoP;
    pAntAux->pProxL = novaL;
}

void pesquisar(){
    letraTemp = toupper(nomePesq[0]);
    pAuxL = pInicioL;

    while(pAuxL != NULL){
        
        if(pAuxL->letra == letraTemp){
            pAuxP = pAuxL->pNomePaises;

            while(pAuxP != NULL){
                
                if(stricmp(pAuxP->nome, nomePesq) == 0){
                    gotoxy(8, 7);
                    printf("[ PAIS ENCONTRADO ]\n");

                    gotoxy(8, 8);
                    printf("> Nome: %s\n", pAuxP->nome);

                    gotoxy(8, 9);
                    printf("> Descricao: %s\n", pAuxP->descricao);

                    gotoxy(8, 11);
                    system("pause");
                    return;
                }

                pAuxP = pAuxP->pProxP;
            }

            gotoxy(8, 7);
            printf("[ PAIS NAO ENCONTRADO DENTRO DA LISTA '%C' ]", letraTemp);

            gotoxy(8, 9);
            system("pause");
            return;
        }

        pAuxL = pAuxL->pProxL;
    }

    gotoxy(8, 7);
    printf("[ NENHUM PAIS COM LETRA '%C' NAO CADASTRADA NO SISTEMA ]", letraTemp);

    gotoxy(8, 9);
    system("pause");
}

void editar(){

    letraTemp = toupper(nomePesq[0]);
    pAuxL = pInicioL;

    while(pAuxL != NULL){
        
        if(pAuxL->letra == letraTemp){
            pAuxP = pAuxL->pNomePaises;

            while(pAuxP != NULL){
                
                if(stricmp(pAuxP->nome, nomePesq) == 0){
                    gotoxy(8, 7);
                    printf("[ PAIS ENCONTRADO ]\n");

                    gotoxy(8, 8);
                    printf("> Nome: %s\n", pAuxP->nome);

                    gotoxy(8, 9);
                    printf("> Descricao: %s\n", pAuxP->descricao);

                    gotoxy(8, 11);
                    system("pause");
                    return;
                }

                pAuxP = pAuxP->pProxP;
            }

            gotoxy(8, 7);
            printf("[ PAIS NAO ENCONTRADO DENTRO DA LISTA '%C' ]", letraTemp);

            gotoxy(8, 9);
            system("pause");
            return;
        }

        pAuxL = pAuxL->pProxL;
    }

    gotoxy(8, 7);
    printf("[ NENHUM PAIS COM LETRA '%C' NAO CADASTRADA NO SISTEMA ]", letraTemp);

    gotoxy(8, 9);
    system("pause");




}

// *****************  TELAS  *****************   

void telaInserir(){

    system("cls");

    gotoxy(8,1);
    printf("****************************** ADICIONAR PAIS ******************************");
    
    gotoxy(8,2);
    printf("*                                                                          *");
    
    gotoxy(8,3);
    printf("* > NOME:                                                                  *");

    gotoxy(8,4);
    printf("* > DESCRICAO:                                                             *");


    gotoxy(8,5);
    printf("*                                                                          *");

    gotoxy(8,6);
    printf("****************************************************************************");

    gotoxy(19,3);
    scanf(" %[^\n]", nomePais);
    while(getchar() != '\n');

    gotoxy(23,4);
    scanf(" %[^\n]", descricao);
    while(getchar() != '\n');
}

void telaPesquisar(){

    system("cls");

    if(pInicioL == NULL){
        gotoxy(15,18);
        printf("ATENCAO: nenhum pais foi cadastrado ");
        
        gotoxy(8,20);
        system("pause");
        return;
    }

    gotoxy(8,1);
    printf("******************************** PESQUISAR ********************************");
    
    gotoxy(8,2);
    printf("*                                                                         *");
    
    gotoxy(8,3);
    printf("* Nome do pais:                                                           *");

    gotoxy(8,4);
    printf("*                                                                         *");

    gotoxy(8,5);
    printf("***************************************************************************");

    gotoxy(24, 3);
    scanf(" %[^\n]", nomePesq);
    while(getchar() != '\n');

}

void telaEditar(){

    system("cls");

    if(pInicioL == NULL){
        gotoxy(15,18);
        printf("ATENCAO: nenhum pais foi cadastrado ");
        
        gotoxy(8,20);
        system("pause");
        return;
    }

    gotoxy(8,1);
    printf("********************************* EDITAR **********************************");
    
    gotoxy(8,2);
    printf("*                                                                         *");
    
    gotoxy(8,3);
    printf("* Nome do pais:                                                           *");

    gotoxy(8,4);
    printf("*                                                                         *");

    gotoxy(8,5);
    printf("***************************************************************************");

    gotoxy(24, 3);
    scanf(" %[^\n]", nomePesq);
    while(getchar() != '\n');
}

void menu(){

    do{

        system("cls");
        
        gotoxy(8,1);
        printf("*********** MENU ************");

        gotoxy(8,2);
        printf("*  EXIBIR..............[1]  *");

        gotoxy(8,3);
        printf("*  INSERIR.............[2]  *");

        gotoxy(8,4);
        printf("*  EDITAR..............[3]  *");

        gotoxy(8,5);
        printf("*  REMOVER.............[4]  *");

        gotoxy(8,6);
        printf("*  PESQUISAR...........[5]  *");

        gotoxy(8,7);
        printf("*  ENSERIR EM ORDEM....[6]  *");

        gotoxy(8,8);
        printf("*  Sair................[7]  *");

        gotoxy(8,9);
        printf("*****************************");

        gotoxy(8,11);
        printf("> Informe a opcao: ");

        gotoxy(27,11);
        scanf("%d", &op);
        while(getchar() != '\n');
        printf("\n");
        
        switch(op){
            case 0:
                break;
            case 1:
                //exibir();
                break;
            case 2:
                telaInserir();
                inserir();
                break;
            case 3:
                telaEditar();
                editar();
                break;
            case 4:
                //remover();
                break;
            case 5:
                telaPesquisar();
                pesquisar();
                break;
                
            case 7:
                gotoxy(8, 15);
                printf("Encerrando programa...");

                gotoxy(8, 16);
                system("pause");
                break;
            default:
                gotoxy(8, 15);
                printf("ATENCAO: Opcao Invalida! ");

                gotoxy(8, 16);
                system("pause");
        }

    } while (op != 7);
}

int main(){

    menu();

    return 0;
}


