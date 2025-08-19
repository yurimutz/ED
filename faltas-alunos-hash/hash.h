#ifndef HASH_H
#define HASH_H

#include "aluno.h"

typedef struct hash Hash;

Hash* hsh_cria (void);

static int hash (Hash* tab , char *str);

Aluno* hsh_insere (Hash* tab , Aluno* a);

static void redimensiona (Hash* tab);

void liberaHash(Hash *tab);

Aluno **criarVetordenado(Hash *tab);

int retN(Hash *tab);

void printaHashMap(Hash* tab);

#endif