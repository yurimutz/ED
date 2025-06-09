#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include <string.h>

struct Produto{

    int codigo;
    char *nome;
    float preco;

};

Produto *criaProduto(int codigo, char *nome, float preco){

    Produto *p = malloc(sizeof(Produto));

    p->codigo = codigo;

    p->nome = nome;

    p->preco = preco;

    return p;

}

Produto *leProduto(){

    int codigo=0;
    char *nome;
    float preco=0;

    printf("Digite o codigo:\n");
    scanf("%d", &codigo);
    scanf("%*c");
    
    printf("Digite o nome:\n");
    nome = leLinha();

    printf("Digite o preco:\n");
    scanf("%f", &preco);
    scanf("%*c");

    Produto *p = criaProduto(codigo, nome, preco);

    return p;

}

char *leLinha(){

    char temp[50];

    scanf(" %49[^\n]", temp);

    char *str = strdup(temp);

    return str;

}

void *liberaProduto(Produto *p){

    free(p->nome);
    free(p);

}

void printaProduto(Produto *p){

    printf("Codigo: %d\n", p->codigo);
    printf("Nome: %s\n", p->nome);
    printf("Preco: %0.2f\n", p->preco);

}

int retornaCodigo(Produto *p){

    return p->codigo;

}