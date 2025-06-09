#include "Cachorro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cachorro{

    char *nome;
    int agressividade;

};

Cachorro *inicCachorro(char *nome, int agressividade){

    Cachorro *c = malloc(sizeof(Cachorro));

    c->nome = strdup(nome);

    c->agressividade = agressividade;

    return c;

}

void liberaCachorro(Cachorro *c){

    free(c->nome);
    
    free(c);

}

int retAgressCachorro(Cachorro *c){

    return c->agressividade;

}

void imprimeCachorro(Cachorro *c){

    printf(" Nome do cachorro: %s\n", c->nome);

}

char *retNomeCachorro(Cachorro *c){

    return c->nome;

}

void atribuiNivelAgressividadeCachorro(Cachorro *c, int agressividade){

    c->agressividade = agressividade;

}
