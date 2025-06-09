#include "estoque.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

struct Estoque{

    float valor;
    Item **itens;
    int qtdAtual;
    int qtdMax;

};

Estoque *criaEstoque(){

    Estoque *e = malloc(sizeof(Estoque));
    e->itens = malloc(10 * sizeof(Item*));
    e->qtdAtual = 0;
    e->qtdMax = 10;
    e->valor = 0;

    return e;

}

void liberaEstoque(Estoque *e){

    for(int i=0; i<e->qtdAtual; i++){
        liberaItem(e->itens[i]);
    }

    free(e->itens);
    free(e);

}

void addEstoque(Estoque *e){

    Item *i = leItem();
    
    if(e->qtdAtual == e->qtdMax){

        e->qtdMax = 2 * e->qtdMax;
        e->itens = realloc(e->itens, e->qtdMax * sizeof(Item*));

    }

    e->itens[e->qtdAtual] = i;
    e->qtdAtual++;

}

float valorEstoque(Estoque *e){

    for(int i=0; i<e->qtdAtual; i++){
        e->valor += valorItem(e->itens[i]);
    }

    return e->valor;
}

void printaEstoque(Estoque *e){

    for(int i=0; i<e->qtdAtual; i++){   
        printaItem(e->itens[i]);
    }

}