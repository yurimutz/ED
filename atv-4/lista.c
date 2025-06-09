#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "produto.h"

typedef struct Celula Celula;

struct Celula{

    Produto *prod;
    Celula *prox;

};

struct Lista{

    Celula *inicio;
    Celula *fim;

};

Lista *criaLista(){

    Lista *l = malloc(sizeof(Lista));

    l->inicio = NULL;
    l->fim = NULL;

    return l;

}

void *liberaLista(Lista *l){

    Celula *inicio = l->inicio;
    Celula *prox;

    while(inicio != NULL){

        prox = inicio->prox;
        liberaProduto(inicio->prod);
        free(inicio);
        inicio = prox;

    }

    free(l);

}

void *imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    while(aux != NULL){

        printaProduto(aux->prod);
        printf("\n");

        aux = aux->prox;

    }

}

int retiraLista(Lista *lista, int codigo){

    Celula *ant = NULL;
    Celula *p = lista->inicio;

    while(p != NULL && retornaCodigo(p->prod) != codigo){

        ant = p;
        p = p->prox;

    }

    if(p == NULL){

        return 1;

    } 

    if(p == lista->inicio && p == lista->fim){

        lista->inicio = lista->fim = NULL;

        free(p);

        return 1;

    }

    if(p == lista->fim){

        lista->fim = ant;
        
        ant->prox = NULL;

        free(p);

        return 1;

    }

    if(p == lista->inicio){

        lista->inicio = p->prox;

    } else {

        ant->prox = p->prox;

    }

    free(p);

    return 1;

}

void *insereLista(Lista *l, Produto *p){

    //Produto *p = leProduto();

    Celula *novo = malloc(sizeof(Celula));

    if(l->fim == NULL){

        l->inicio = l->fim = novo;

    } else {

        l->fim->prox = novo;
        l->fim = l->fim->prox;

    }

    l->fim->prod = p;
    l->fim->prox = NULL;

}
