#ifndef HASH_H
#define HASH_H

#define N 127
#define NTAB 127

typedef struct hash Hash;

typedef struct palavra Palavra;

Palavra *criaPalavra(char *str);

void liberaPalavra(Palavra *a);

Hash* hsh_cria (void);

static int hash (Hash* tab , char *str);

Palavra* hsh_insere (Hash* tab , Palavra* a);

static void redimensiona (Hash* tab);

void printaHashMap(Hash* tab);

Palavra **criaVetorOrdenado(Hash* tab);

int comparaFreq(const void *p1, const void *p2);

void printaInformacoes(Palavra **vet, Hash *tab);

int retFrequenciasSomadas(Palavra **vet, int tam);

Palavra *retPalavraMaiorFreq(Palavra **vet, int tam);

void liberaHash(Hash *tab);

void liberaVet(Palavra **vet, Hash *tab);

#endif