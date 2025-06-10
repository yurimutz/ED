// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "leitor.h"
#include "livro.h"

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

    // while(inicio != NULL){

    //     prox = inicio->prox;    
    //     free(inicio);
    //     inicio = prox;

    // }

    while(inicio != NULL){

        prox = inicio->prox;  
        
        if(inicio->tipo == LIVRO){

            liberaLivro(inicio->prod);

        } else {

            liberaLeitor(inicio->prod);

        }
        
        free(inicio);

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

    Celula *ant = NULL;
    Celula *p = lista->inicio;

    // while(p != NULL && (strcmp(retNomeGato(p->prod), nome) != 0 && strcmp(retNomeCachorro(p->prod), nome) != 0)){
    while(p != NULL){
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

    if(l != NULL && cel != NULL){

    //     if(l->fim == NULL){

    //         l->inicio = l->fim = cel;

    //     } else {

    //         l->fim->prox = cel;
    //         l->fim = l->fim->prox;

    //     }

    //     l->fim->prox = NULL;

        Celula *novo = malloc(sizeof(Celula));

        if(l->fim == NULL){

            l->inicio = l->fim = novo; 

        } else {

            l->fim->prox = novo;
            l->fim = l->fim->prox;

        }

        l->fim->prod = cel->prod;
        l->fim->tipo = cel->tipo;
        l->fim->prox = NULL;
        
    }

    

}

Celula *busca(Lista *l, int id){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(aux->tipo == LIVRO){

            if(retIdLivro(aux->prod) == id){
                return aux;

            }

        } else {

            if(retId(aux->prod) == id){
                return aux;

            }

        }

        aux = aux->prox;

    }
    
    return NULL;

}

Lista *retListaLidos(Celula *cel){

    Lista *aux = retListaLidosLeitor(cel->prod);

    return aux;

}

