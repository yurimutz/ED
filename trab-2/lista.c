#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct Celula{

    Arv *arv;
    Celula *prox;

};

struct Lista{

    int tam;
    Celula *inicio;
    Celula *fim;

};

Lista *criaLista(){

    Lista *l = malloc(sizeof(Lista));

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;

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

void imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    // while(aux != NULL){

    //     printf("Char: %c, Frequencia: %d\n",  retCarac(aux->arv), retFrequencia(aux->arv));

    //     aux = aux->prox;

    // }

    abb_imprime (l->inicio->arv);

}

Celula *retiraLista(Lista *lista, char *nome){

    // Celula *ant = NULL;
    // Celula *p = lista->inicio;

    // while(p != NULL && (strcmp(retNomeGato(p->prod), nome) != 0 && strcmp(retNomeCachorro(p->prod), nome) != 0)){

    //     ant = p;
    //     p = p->prox;

    // }

    // if(p == NULL){

    //     return NULL;

    // } 

    // if(p == lista->inicio && p == lista->fim){

    //     lista->inicio = lista->fim = NULL;

    //     return(p);

    // }

    // if(p == lista->fim){

    //     lista->fim = ant;
        
    //     ant->prox = NULL;

    //     return(p);

    // }

    // if(p == lista->inicio){

    //     lista->inicio = p->prox;

    // } else {

    //     ant->prox = p->prox;

    // }

    // return(p);

}

Celula *retiraPrimeiro(Lista *l){

    if(l->inicio == NULL){

        return NULL;

    }

    Celula *aux = l->inicio;

    l->inicio = l->inicio->prox;

    if(l->inicio == NULL){

        l->fim = NULL;

    }

    return aux;

}

void insereListaOrdenado(Lista *l, Arv *a){

    Celula *novo = malloc(sizeof(Celula));
    novo->arv = a;
    novo->prox = NULL;

    if(l->fim == NULL){

        l->inicio = l->fim = novo;
        l->fim->prox = NULL;
        l->tam++;

    } else if(retFrequencia(l->inicio->arv) > retFrequencia(a)){

            novo->prox = l->inicio->prox;
            l->inicio->prox = novo;
            l->tam++;

    } else {

        Celula *aux = l->inicio;

        while (aux->prox != NULL && retFrequencia(aux->prox->arv) <= retFrequencia(a)){

            aux = aux->prox;

        }

        novo->prox = aux->prox;

        aux->prox = novo;

        if (novo->prox == NULL) {

            l->fim = novo;  // Atualiza fim se for inserido no final

        }
        
        l->tam++;

    }

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

void insereCelulasHuff(Lista *l, Celula *esq, Celula *dir){

    Arv *arv = arvCriaNaoVazia(esq->arv, dir->arv);

    insereListaOrdenado(l, arv);

    free(esq);
    free(dir);

}

void criaArvoreHuff(Lista *l){

    while(l->inicio != NULL && l->inicio->prox != NULL){

        Celula *esquerda = retiraPrimeiro(l);
        Celula *direita = retiraPrimeiro(l);

        insereCelulasHuff(l, esquerda, direita);

    }

}

int retAlturaCelula(Lista *l){

    if(l->inicio != NULL){

        return altura(l->inicio->arv);

    }

    return 0;

}

char **criaDicionario(Lista *a, int altura){

    char **dic = malloc(256 * sizeof(char*));

    for(int i=0; i < 256; i++){

        dic[i] = calloc(altura, sizeof(char));

    }

    preencheDicionario(dic, a->inicio->arv, "", altura);

    return dic;

}

Lista *criaListaOrdenada(Lista *l, int *vetFreq){

    for(int i=0; i<256; i++){

        if(vetFreq[i] > 0){

            Arv *arvAux = arv_cria(vetFreq[i], i);

            insereListaOrdenado(l, arvAux);

        }

    }

    return l;

}

char *decodificaArquivo(Lista *l, char *txt, FILE *fp){

    if(l->inicio != NULL){

        return decodificaFinal(l->inicio->arv, txt, fp);

    }

    return NULL;

}