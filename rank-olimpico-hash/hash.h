#ifndef HASH_H
#define HASH_H

#include "pais.h"

typedef struct hash Hash;

Hash* hsh_cria (void);

static int hash (Hash* tab , char *str);

Pais* hsh_insere (Hash* tab , Pais* a);

static void redimensiona (Hash* tab);

void printaHashMap(Hash* tab);

int retFrequenciasSomadas(Pais **vet, int tam);

void liberaHash(Hash *tab);

Pais **criaVetorOrdenado(Hash *tab);

int retTamTab(Hash *tab);

#endif