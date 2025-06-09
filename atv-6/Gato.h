#ifndef gato_h
#define gato_h

#define BRAVO 1
#define MANSO 0

typedef struct Gato Gato;

Gato *inicGato(char *nome, int agressividade);

void liberaGato(Gato *c);

int retAgressGato(Gato *c);

void imprimeGato(Gato *c);

char *retNomeGato(Gato *c);

void atribuiNivelAgressividadeGato(Gato *c, int agressividade);

#endif