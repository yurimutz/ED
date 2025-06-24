// Feito dia 28/05/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "produto.h"

struct Lista{

    Lista *ant;
    Lista *prox;
    Produto *produto;

};

Lista *criaLista(){

    return NULL;

}

void *liberaLista(Lista *l){

    Lista *aux = l;
    Lista *retirar;

    while(aux != NULL){

        retirar = aux;
        aux = aux->prox;

        liberaProduto(retirar->produto);
        free(retirar);

    }

}

void *imprimeLista(Lista *l){

    Lista *aux = l;

    while(aux != NULL){

        printaProduto(aux->produto);
        printf("\n");

        aux = aux->prox;

    }
    
}

Lista *busca(Lista *l, int codigo){

    Lista *aux = l;

    for(aux; aux != NULL; aux = aux->prox){

        if(retornaCodigo(aux->produto) == codigo){

            return aux;

        }

    }

    return NULL;

}

Lista * retiraLista(Lista *lista, int codigo){

    Lista *aux = busca(lista, codigo);

    if(aux == NULL){

        return lista;

    }

    if(lista == aux){

        lista = aux->prox;

    } else {

        aux->ant->prox = aux->prox;

    }

    if(aux->prox != NULL){

        aux->prox->ant = aux->ant;

    }


    liberaProduto(aux->produto);
    free(aux);

    return lista;

}

Lista *insereLista(Lista *l, Produto *p){

    Lista *novo = malloc(sizeof(Lista));

    novo->produto = p;
    novo->prox = l;
    novo->ant = NULL;

    if(l != NULL){

        l->ant = novo;

    }

    return novo;

}

