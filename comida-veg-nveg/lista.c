#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Celula{

    void *prod;
    int tipo;
    Celula *prox;

};

struct Lista{

    Celula *inicio;
    Celula *fim;

};

Lista *criaLista(){

    Lista *l = malloc(sizeof(Lista));

    l->fim = NULL;
    l->inicio = NULL;

    return l;

}

void liberaLista(Lista *l){

    Celula *aux = l->inicio;
    Celula *prox;

    while(aux != NULL){

        prox = aux->prox;

        if(aux->tipo == VEGANA){

            //liberaComidaVegana(aux->prod);

        } else {

            //liberaComidaNaoVegana(aux->prod);

        }

        free(aux);

        aux = prox;

    }

    free(l);

}

void insereLista(Lista *l, void *prod, int tipo){
    
    Celula *novo = malloc(sizeof(Celula));

    novo->prox = NULL;
    novo->prod = prod;
    novo->tipo = tipo;

    if(l->fim == NULL){

        l->fim = l->inicio = novo;

    } else {

        l->fim->prox = novo;
        l->fim = novo;

    }


}

void insereCelula(Lista *l, Celula *cel){

    Celula *novo = malloc(sizeof(Celula));

    novo->prox = NULL;
    novo->prod = cel->prod;
    novo->tipo = cel->tipo;

    if(l->fim == NULL){

        l->fim = l->inicio = novo;

    } else {

        l->fim->prox = novo;
        l->fim = novo;

    }

    free(cel);

}

Celula *retiraLista(Lista *l, char *nome){

    Celula *p = l->inicio;
    Celula *ant = NULL;

    while(p != NULL && (strcmp(retornaNomeComidaVegana(p->prod), nome) != 0) && strcmp(retornaNomeComidaVegana(p->prod), nome) !=0){

        ant = p;
        p = p->prox;

    }

    if(p == NULL){

        return NULL;

    }

    if(p == l->inicio && p == l->fim){

        l->fim = l->inicio = NULL;

        return p;

    }

    if(p == l->fim){

        ant->prox = NULL;
        l->fim = ant;
        return p; 

    }

    if(p == l->inicio){

        l->inicio = p->prox;

        return p;

    }

    ant->prox = p->prox;

    return p;

}

int buscaLista(Lista *l, char *nome){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(strcmp(retornaNomeComidaNaoVegana(aux->prod), nome) == 0 || strcmp(retornaNomeComidaVegana(aux->prod), nome) == 0){

            return 1;

        }

    }

    return 0;

}

void imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(aux->tipo == VEGANA){

            imprimeComidaVegana (aux->prod);

        } else {

            imprimeComidaNaoVegana (aux->prod);

        }

        aux = aux->prox;

    }

}