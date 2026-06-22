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
    struct noLetra *pAntL, *pAntAuxP;
}NoLetra;

NoLetra *pInicioL = NULL, *pAuxL, *pAntAux;
NoPaises *pAuxP, *pAntAuxP, *paisEncontrado;

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

NoPaises* pesquisar(char nomeBuscado[]){
    letraTemp = toupper(nomeBuscado[0]);
    pAuxL = pInicioL;

    while(pAuxL != NULL){
        
        if(pAuxL->letra == letraTemp){
            pAuxP = pAuxL->pNomePaises;

            while(pAuxP != NULL){
                
                if(stricmp(pAuxP->nome, nomeBuscado) == 0){
                    
                    return pAuxP;
                }

                pAuxP = pAuxP->pProxP;
            }
            
            return NULL;
        }

        pAuxL = pAuxL->pProxL;
    }

    return NULL;
}

int remover(){

    letraTemp = toupper(nomePesq[0]);
    pAuxL = pInicioL;

    while(pAuxL != NULL){
        if(pAuxL->letra == letraTemp){
            pAuxP = pAuxL->pNomePaises;
            pAntAuxP = NULL;

            while(pAuxP != NULL){

                if(stricmp(pAuxP->nome, nomePesq) == 0){

                    if(pAntAuxP == NULL){
                        // Cenário A: É o primeiro país da lista desta letra
                        pAuxL->pNomePaises = pAuxP->pProxP;
                    }else{
                        // Cenário B: O país está no meio ou no fim da lista
                        pAntAuxP->pProxP = pAuxP->pProxP;
                    }

                    free(pAuxP); // Devolve a memória do país para o PC!
                    pAuxL->quant--;

                    if(pAuxL->quant == 0){

                        if(pAuxL->pAntL == NULL){

                            pInicioL = pAuxL->pProxL;
                            if(pInicioL != NULL){
                                pInicioL->pAntL = NULL;
                            }
                        }else{

                            pAuxL->pAntL->pProxL = pAuxL->pProxL;
                            if(pAuxL->pProxL != NULL){
                                pAuxL->pProxL->pAntL = pAuxL->pAntL;
                            }
                        }
                        
                        free(pAuxL);
                    }

                    return 1; //sucesso na remocão;
                }

                pAntAuxP = pAuxP;
                pAuxP = pAuxP->pProxP;
            }

            return 2; //pais não encontrado 
        }

        pAuxL = pAuxL->pProxL;
    }

    return 0; //letra não existe
}

void editar(){

    if (toupper(nomePais[0]) == toupper(paisEncontrado->nome[0])) {
        // Cenário Simples: A letra é a mesma. Só atualiza o texto!
        strcpy(paisEncontrado->nome, nomePais); 
        strcpy(paisEncontrado->descricao, descricao);
        
    } else {
        // Cenário Complexo: A letra inicial mudou! (Ex: Brasil -> Noruega)
        remover(); // Apaga o antigo (que está na global nomePesq)
        inserir(); // Cria o novo (que está nas globais nomePais e descricao)
    }

}


// ******************* TELAS *******************

int telaInserir(){

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

    gotoxy(18,3);
    scanf(" %[^\n]", nomePais);
    while(getchar() != '\n');

    gotoxy(23,4);
    scanf(" %[^\n]", descricao);
    while(getchar() != '\n');

    paisEncontrado = pesquisar(nomePais);

    if(paisEncontrado != NULL){

        gotoxy(8,8);
        printf("[AVISO] Pais '%s' já cadastrado no sistema [AVISO]", nomePais);
        gotoxy(8,9);
        system("pause");
        return 0;
    }

    return 1;
}

int telaPesquisar(){

    system("cls");

    if(pInicioL == NULL){
        gotoxy(15,18);
        printf("[AVISO] nenhum pais foi cadastrado [AVISO]");
        
        gotoxy(8,20);
        system("pause");
        return 0;
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

    paisEncontrado = pesquisar(nomePesq);

    if(paisEncontrado != NULL){
        
        gotoxy(8, 7);
        printf("***************************** PAIS ENCONTRADO *****************************");
        gotoxy(8,8);
        printf("*                                                                         *");

        gotoxy(8, 9);
        printf("* > Nome:                                                                 *");
        
        gotoxy(18, 9);
        printf("%s", paisEncontrado->nome); 

        gotoxy(8, 10);
        printf("* > Descricao:                                                            *");
        
        gotoxy(23, 10);
        printf("%s", paisEncontrado->descricao); 

        gotoxy(8,11);
        printf("*                                                                         *");

        gotoxy(8, 12);
        printf("***************************************************************************");

    }else{
        gotoxy(8, 7);
        printf("[AVISO] PAIS '%s' NAO ENCONTRADO NO SISTEMA [AVISO]", nomePesq);
    }

    gotoxy(8, 14);
    system("pause");

    return 1;
}

int telaEditar(){

    system("cls");

    if(pInicioL == NULL){
        gotoxy(15,18);
        printf("[AVISO]: nenhum pais foi cadastrado[AVISO]");
        
        gotoxy(8,20);
        system("pause");
        return 0;
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

    paisEncontrado = pesquisar(nomePesq);

    if(paisEncontrado == NULL){
        gotoxy(8, 7);
        printf("[AVISO] PAIS '%s' NAO ENCONTRADO NO SISTEMA [AVISO]", nomePesq);
        gotoxy(8, 9);
        system("pause");
        return 0; // Aborta e volta pro menu
    }

    // 3. Se achou, mostra como está hoje
    gotoxy(8, 7);
    printf("***************************** DADOS ATUAIS ********************************");

    gotoxy(8,8);
    printf("*                                                                         *");

    gotoxy(8, 9);
    printf("* > Nome Atual:                                                           *"); 

    gotoxy(24,9);
    printf("%s", paisEncontrado->nome);

    gotoxy(8, 10);
    printf("* > Descricao Atual:                                                      *");
    
    gotoxy(29,10);
    printf("%s", paisEncontrado->descricao);
    
    gotoxy(8,11);
    printf("*                                                                         *");

    gotoxy(8, 12);
    printf("***************************************************************************");

    // 4. Desenha o formulário para os novos dados
    gotoxy(8, 14);
    printf("***************************** NOVOS DADOS *********************************");
    
    gotoxy(8,15);
    printf("*                                                                         *");

    gotoxy(8, 16);
    printf("* > Novo nome:                                                            *");

    gotoxy(8, 17);
    printf("* > Nova descricao:                                                       *");

    gotoxy(8,18);
    printf("*                                                                         *");

    gotoxy(8, 19);
    printf("***************************************************************************");
    
    gotoxy(23, 16);
    scanf(" %[^\n]", nomePais); 
    while(getchar() != '\n');

    gotoxy(28, 17);
    scanf(" %[^\n]", descricao); 
    while(getchar() != '\n');

    return 1;
}

int telaRemover(){

    system("cls");

    if(pInicioL == NULL){
        gotoxy(15,18);
        printf("[AVISO] nenhum pais foi cadastrado [AVISO]");
        
        gotoxy(8,20);
        system("pause");
        return 0;
    }

    gotoxy(8,1);
    printf("********************************* REMOVER *********************************");
    
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

    paisEncontrado = pesquisar(nomePesq);

    if(paisEncontrado != NULL){
        
        gotoxy(8, 7);
        printf("***************************** PAIS ENCONTRADO *****************************");

        gotoxy(8,8);
        printf("*                                                                         *");

        gotoxy(8, 9);
        printf("* > Nome:                                                                 *");
        
        gotoxy(18, 9);
        printf("%s", paisEncontrado->nome); 

        gotoxy(8, 10);
        printf("* > Descricao:                                                            *");
        
        gotoxy(23, 10);
        printf("%s", paisEncontrado->descricao); 

        gotoxy(8,11);
        printf("*                                                                         *");

        gotoxy(8, 12);
        printf("***************************************************************************");

        gotoxy(8,14);
        printf("Remover pais? Sim[S] Nao[outra tecla]");

        gotoxy(8,15);
        printf("> ");

        gotoxy(10, 15);
        scanf("%c", &resp);
        while(getchar() != '\n');

        if(resp == 's' || resp == 'S'){

            return 1;
        }

        gotoxy(8, 17);
        printf("[AVISO] REMOCAO CANCELADA PELO USUARIO [AVISO]");
        gotoxy(8, 18);
        system("pause");
        return 0;

    }else{
        
        gotoxy(8, 7);
        printf("[AVISO] PAIS NAO ENCONTRADO NO SISTEMA [AVISO]");
        gotoxy(8, 9);
        system("pause");
        return 0;
    }

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
        
            case 1:
                //exibir();
                break;
            case 2:
                if(telaInserir() == 1){
                    inserir();
            
                    gotoxy(8, 8);
                    printf("[AVISO] PAIS ADICIONADO COM SUCESSO [AVISO]");
                    gotoxy(8, 9);
                    system("pause");
                }
                break;
            case 3:
                if(telaEditar() == 1){
                editar();
                }
                break;
            case 4:
                if(telaRemover() == 1){
                    
                    remover();
                    
                    gotoxy(8, 17);
                    printf("[AVISO] PAIS REMOVIDO DO SISTEMA [AVISO]");
                    gotoxy(8, 18);
                    system("pause");
                }
                break;
            case 5:
                telaPesquisar();
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


