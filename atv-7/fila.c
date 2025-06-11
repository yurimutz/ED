#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef struct Fila Fila;

struct Lista{

    // float info;
    Amostra *amostra;
    Lista *prox;

};

struct Fila{

    Lista* ini;
    Lista* fim;

};

Fila* criaFila(){

    Fila* f = (Fila*)malloc(sizeof(Fila));

    f->ini = f->fim = NULL;

    return f;

}

void insereFila (Fila* f, Amostra *amostra){

    Lista* n = (Lista*) malloc(sizeof(Lista));

    n->amostra = amostra; /* armazena informação */

    n->prox = NULL; /* novo nó passa a ser o último */

    if(retornaIdade(amostra) < 60){

        if (f->fim != NULL){ /* verifica se lista não estava vazia */

            f->fim->prox = n;

        }else{ /* fila estava vazia */

            f->ini = n; 

        }

        f->fim = n;

    } else {

        if (f->fim == NULL){ /* verifica se lista estava vazia */

            f->fim = f->ini = n;

        }else{ /* fila nao estava vazia */

            n->prox = f->ini;
            f->ini = n; 

        }

    }

}

Amostra *retiraFila (Fila* f){

    Lista* t;
    Amostra *v;

    if (f==NULL || filaVazia(f)) { 

        printf("Fila vazia.\n");

        return NULL;

    } /* aborta programa */

    t = f->ini;

    v = t->amostra;

    f->ini = t->prox;

    if (f->ini == NULL){ /* verifica se fila ficou vazia */

        f->fim = NULL;
    }

    free(t);

    return v;


}

void liberaFila (Fila* f){

    Lista* q = f->ini;

    while (q!=NULL) {

        Lista* t = q->prox;

        liberaAmostra(q->amostra);

        free(q);

        q = t;

    }
    
    free(f);

}

void imprimeFila(Fila *f){

    Lista *aux = f->ini;

    while(aux != NULL){

        printf("\t");
        imprimeAmostra(aux->amostra);

        aux = aux->prox;

    }

}

int filaVazia(Fila *f){

    return f->ini == NULL;

}