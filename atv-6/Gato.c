#include "Gato.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Gato{

    char *nome;
    int agressividade;

};

Gato *inicGato(char *nome, int agressividade){

    Gato *c = malloc(sizeof(Gato));

    c->nome = strdup(nome);

    c->agressividade = agressividade;

    return c;

}

void liberaGato(Gato *c){

    free(c->nome);
    
    free(c);

}

int retAgressGato(Gato *c){

    return c->agressividade;

}

void imprimeGato(Gato *c){

    printf(" Nome do gato: %s\n", c->nome);

}

char *retNomeGato(Gato *c){

    return c->nome;

}

void atribuiNivelAgressividadeGato(Gato *c, int agressividade){

    c->agressividade = agressividade;

}
