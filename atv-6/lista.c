#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

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

    l->inicio = NULL;
    l->fim = NULL;

    return l;

}

void *liberaLista(Lista *l){

    Celula *inicio = l->inicio;
    Celula *prox;

    while(inicio != NULL){

        prox = inicio->prox;    
        free(inicio);
        inicio = prox;

    }

    free(l);

}

void *imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(aux->tipo == CAT){

            imprimeGato(aux->prod);

        } else {

            imprimeCachorro(aux->prod);

        }

        aux = aux->prox;

    }

}

Celula *retiraLista(Lista *lista, char *nome){

    Celula *ant = NULL;
    Celula *p = lista->inicio;

    while(p != NULL && (strcmp(retNomeGato(p->prod), nome) != 0 && strcmp(retNomeCachorro(p->prod), nome) != 0)){

        ant = p;
        p = p->prox;

    }

    if(p == NULL){

        return NULL;

    } 

    if(p == lista->inicio && p == lista->fim){

        lista->inicio = lista->fim = NULL;

        return(p);

    }

    if(p == lista->fim){

        lista->fim = ant;
        
        ant->prox = NULL;

        return(p);

    }

    if(p == lista->inicio){

        lista->inicio = p->prox;

    } else {

        ant->prox = p->prox;

    }

    return(p);

}

void *insereLista(Lista *l, void *p, int tipo){

    Celula *novo = malloc(sizeof(Celula));

    if(l->fim == NULL){

        l->inicio = l->fim = novo;

    } else {

        l->fim->prox = novo;
        l->fim = l->fim->prox;

    }

    l->fim->prod = p;
    l->fim->tipo = tipo;
    l->fim->prox = NULL;

}

void *insereCelula(Lista *l, Celula *cel){

    if(l->fim == NULL){

        l->inicio = l->fim = cel;

    } else {

        l->fim->prox = cel;
        l->fim = l->fim->prox;

    }

    l->fim->prox = NULL;

}

float calculaValor(Lista *l){

    float valor = 0;

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(aux->tipo == CAT){

            valor += 30;

            if(retAgressGato(aux->prod) == 1){

                valor += 5;

            }

        } else {

            valor += 40;

            if(retAgressCachorro(aux->prod) == 1){

                valor += 5;

            }
    
        }

        aux = aux->prox;

    }

    return valor;

}

int procuraElementoGato(Lista *l, Lista *listDest, char *nome){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(strcmp(retNomeGato(aux->prod), nome) == 0){

            aux = retiraLista(l, nome);

            insereCelula(listDest, aux);

            return 1;

        }

        aux = aux->prox;

    }

    return 1;

}

int procuraElementoCachorro(Lista *l, Lista *listDest, char *nome){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(strcmp(retNomeCachorro(aux->prod), nome) == 0){

            aux = retiraLista(l, nome);

            insereCelula(listDest, aux);

            return 1;

        }

        aux = aux->prox;

    }

    return 1;

}