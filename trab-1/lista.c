#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct Celula{

    void *prod;
    int tipo;
    Celula *prox;
    Celula *ant;

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

    // while(inicio != NULL){

    //     prox = inicio->prox;    
    //     free(inicio);
    //     inicio = prox;

    // }

    while(inicio != NULL){

        prox = inicio->prox;  
        
        if(inicio->tipo == LIVRO){

            liberaLivro(inicio);

        } else {

            liberaLeitor(inicio);

        }
        
        inicio = prox;

    }


    free(l);

}

void *imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(aux->tipo == LIVRO){

            imprimeLivro(aux->prod);

        } else {

            imprimeLeitor(aux->prod);

        }
        
        aux = aux->prox;

    }

}

Celula *retiraLista(Lista *lista, char *nome){

    //Celula *ant = NULL;
    Celula *p = lista->inicio;

    while(p != NULL && (strcmp(retNomeGato(p->prod), nome) != 0 && strcmp(retNomeCachorro(p->prod), nome) != 0)){

        //ant = p;
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

        //lista->fim = ant;
        lista->fim = p->ant;
        
        //ant->prox = NULL;
        p->ant->prox = NULL;

        return(p);

    }

    if(p == lista->inicio){

        lista->inicio = p->prox;

    } else {

        //ant->prox = p->prox;
        p->ant->prox = p->prox;

    }

    return(p);

}

void *insereLista(Lista *l, void *p, int tipo){

    Celula *novo = malloc(sizeof(Celula));

    if(l->fim == NULL){

        l->inicio = l->fim = novo; 

    } else {

        l->fim->prox = novo;
        novo->ant = l->fim;
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
        cel->ant = l->fim;
        l->fim = l->fim->prox;

    }

    l->fim->prox = NULL;

}

