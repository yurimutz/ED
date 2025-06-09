#include "item.h"
#include "produto.h"
#include <stdlib.h>
#include <stdio.h>

struct Item{

    Produto *prod;
    int qtd;

};

Item *criaItem(Produto *prod, int qtd){

    Item *i = malloc(sizeof(Item));
    i->prod = prod;
    i->qtd = qtd;

    return i;

}

void liberaItem(Item *i){

    liberaProduto(i->prod);
    free(i);

}

Item *leItem(){

    Produto *prod = leProduto();

    int qtdAux=0;
    printf("Digite a quantidade do item no estoque:\n");
    scanf("%d", &qtdAux);
    scanf("%*c");

    Item *Item = criaItem(prod, qtdAux);

    return Item;

}

float valorItem(Item *i){
    return valorProduto(i->prod) * (float)i->qtd;
}

void printaItem(Item *i){

    printf("\t\tItem:");
    printaProduto(i->prod);
    printf("quantidade: %d\n", i->qtd);

}

