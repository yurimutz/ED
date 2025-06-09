#ifndef ESTOQUE
#define ESTOQUE

typedef struct Estoque Estoque;

Estoque *criaEstoque();

void liberaEstoque(Estoque *e);

void addEstoque(Estoque *e);

float valorEstoque(Estoque *e);

void printaEstoque(Estoque *e);

#endif