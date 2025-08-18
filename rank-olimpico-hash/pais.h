#ifndef PAIS_H
#define PAIS_H

#include <stdio.h>

typedef struct pais Pais;

Pais *criaPais(char *nome, int ouro, int prata, int bronze, int total);

Pais *lePais(FILE *fp);

Pais *liberaPais(Pais *p);

char *retNomePais(Pais *p);

void atualizaFreq(Pais *recebe, Pais* conteudo);

int comparaNome(Pais *p1, Pais *p2);

Pais *retPaisProx(Pais *p);

Pais *procuraUltimoFila(Pais *p);

void atualizaProx(Pais *recebe, Pais *conteudo);

void atualizaProxComNULL(Pais *p);

void imprimePais(Pais *p, FILE *fp);

int comparaMedalhas(const void *p1, const void *p2);

void imprimeVetor(Pais **vet, int tam);

void liberaVet(Pais **vet, int tam);

#endif