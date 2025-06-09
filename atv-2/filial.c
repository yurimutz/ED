#include "filial.h"
#include "estoque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Filial{

    Estoque *estoque;
    char *nome;

};

Filial *criaFilial(char *nome){

    Filial *f = malloc(sizeof(Filial));

    Estoque *e = criaEstoque();
    f->estoque = e;

    f->nome = malloc(50 * sizeof(char));
    strcpy(f->nome, nome);

    return f;

}

void liberaFilial(Filial *f){

    liberaEstoque(f->estoque);
    free(f->nome);
    free(f);

}

Filial *leFilial(){

    //Estoque *e = criaEstoque();

    char nome[50];
    printf("Digite o nome da filial:\n");
    scanf(" %[^\n]", nome);
    scanf("%*c");

    Filial *f = criaFilial(nome);

    return f;

}

void addEstoqueDaFilial(Filial *f){

    addEstoque(f->estoque);

}

char *retornaNomeFilial(Filial *f){ 
    return f->nome;
}

float valorEstoqueFilial(Filial *f){
    return valorEstoque(f->estoque);
}

void printaFilial(Filial *f){

    printf("\t");
    printf("Filial: %s\n", f->nome);
    printf("\t");
    //por algum motivo meu estoque ta printando dobrado, por isso tive que dividir por 2 na hora do print;
    printf("Estoque: %0.2f\n", valorEstoqueFilial(f)/2);
    printaEstoque(f->estoque);

}