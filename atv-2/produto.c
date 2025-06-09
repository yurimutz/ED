#include "produto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Produto{

    char *nome;
    float valor;

};

Produto *criaProduto(char *nome, float valor){

    Produto *prod = malloc(sizeof(Produto));
    prod->valor = valor;

    prod->nome = malloc(50 * sizeof(char));
    strcpy(prod->nome, nome);

    return prod;

}

void liberaProduto(Produto *p){

    free(p->nome);
    free(p);

}

Produto *leProduto(){

    char nome[50];
    printf("Digite o nome do produto:\n");
    scanf(" %[^\n]", nome);
    scanf("%*c");

    float valor=0;
    printf("Digite o valor do produto:\n");
    scanf("%f", &valor);
    scanf("%*c");

    Produto *prod = criaProduto(nome, valor);

    return prod;

}

float valorProduto(Produto *p){
    return p->valor;
}

void printaProduto(Produto *p){

    printf(" %s, valor unitario: %0.2f, ", p->nome, p->valor);

}