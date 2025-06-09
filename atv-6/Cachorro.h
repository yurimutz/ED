#ifndef cachorro_h
#define cachorro_h

#define BRAVO 1
#define MANSO 0

typedef struct Cachorro Cachorro;

Cachorro *inicCachorro(char *nome, int agressividade);

void liberaCachorro(Cachorro *c);

int retAgressCachorro(Cachorro *c);

void imprimeCachorro(Cachorro *c);

char *retNomeCachorro(Cachorro *c);

void atribuiNivelAgressividadeCachorro(Cachorro *c, int agressividade);

#endif