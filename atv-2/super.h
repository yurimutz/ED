#ifndef SUPER    
#define SUPER

typedef struct Super Super;

Super *criaSuper();

void liberaSuper(Super *s);

void addFilial(Super *s);

void addItemNaFilial(Super *s, char *nome);

float valorEstoqueSuper(Super *s);

void printaSuper(Super *s);

#endif