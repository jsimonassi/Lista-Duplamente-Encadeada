#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
# define FALSE 0

typedef struct node{
    int info;
    struct node *prox;
    struct node *ant;
}TLDE;

TLDE * init(){
    return NULL;
    }

TLDE * insere(TLDE * inicio, int insere_fim, int num){

    TLDE * novo = (TLDE *) malloc(sizeof(TLDE));
    novo->info = num;

    if(!inicio){
        novo->ant = NULL;
        novo->prox = NULL;
        inicio = novo;
        return inicio;
    }

    if(insere_fim){
        TLDE * aux = inicio;
        while(aux->prox) // O(n)
            aux = aux->prox;
        aux->prox = novo;
        novo->ant = aux;
        novo->prox = NULL;
        return inicio;
    }

    //Insere no inicio

    inicio->ant = novo;
    novo->prox = inicio;
    inicio = novo;
    return inicio;
}


TLDE * busca(TLDE * inicio, int num){
    if(!inicio || inicio->info == num)
        return inicio;
    return busca(inicio->prox, num);
}

void imprime(TLDE * inicio){
    if(inicio){
        printf("<- %d ->", inicio->info);
        imprime(inicio->prox);
        }
    return;
}

TLDE * retira(TLDE * inicio, int num){
    TLDE * aux = busca(inicio, num);
    if(!inicio)
        return inicio;

    if(!aux->prox && aux->ant){
        aux->ant->prox = NULL;
        free(aux);
    }

    else if(!aux->ant && aux->prox){
        inicio = aux->prox;
        aux->prox->ant = NULL;
        free(aux);
    }
    else{
        aux->ant->prox = aux->prox; // Quem está atrás dele, aponta pra quem está na frente dele
        aux->prox->ant = aux->ant; // Quem está na frente dele, aponta para quem está atrás dele
        free(aux);
    }
    return inicio;
}

void libera(TLDE * inicio){
    if(inicio)
        libera(inicio->prox);
    free(inicio);
}

void finish(TLDE * inicio){
    libera(inicio);
    return;
}
// ********************************* Aplicação ************************************************

int main()
{
    int opcao;
    TLDE * inicio = init();

    while(TRUE){

        printf("\n------------------------------\nInsere ------ [1]\n");
        printf("Retira ------ [2]\n");
        printf("Imprime ----- [3]\n");
        printf("Sair -------- [4]\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1){
            printf("\n\n DIgite um inteiro para inserir: ");
            int num;
            scanf("%d", &num);
            printf("Inserir o %d no inicio ou no fim da lista? 1-Inicio / 0-Fim", num);
            int onde_inserir;
            scanf("%d", &onde_inserir);
            if(onde_inserir)
                inicio = insere(inicio, FALSE, num);
            else
                 inicio = insere(inicio, TRUE, num);
            printf("\nInserido!");
            }

        else if(opcao == 2){
            printf("\n\n DIgite um inteiro para retirar da lista: ");
            int num;
            scanf("%d", &num);
            inicio = retira(inicio, num);
            printf("\nRemovido!");
            }

        else if(opcao == 3)
            imprime(inicio);

        else if(opcao == 4){
            finish(inicio);
            exit(0);
            }

        else printf("Digitou errado\n\n");
     }

    return 0;
}
