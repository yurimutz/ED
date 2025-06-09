#ifndef FILA    
#define FILA

typedef struct Filial Filial;

Filial *criaFilial(char *nome);

void liberaFilial(Filial *f);

Filial *leFilial();

void addEstoqueDaFilial(Filial *f);

char *retornaNomeFilial(Filial *f);

float valorEstoqueFilial(Filial *f);

void printaFilial(Filial *f);

#endif