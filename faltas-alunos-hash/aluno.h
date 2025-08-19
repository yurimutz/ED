#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>

typedef struct aluno Aluno;

Aluno *criaALuno(char *nome, int faltas, int pres);

Aluno *leAluno(FILE *fp);

Aluno *leAluno2(FILE *fp);

void liberaAluno(Aluno *a);

void imprimeAluno(Aluno *a);

char *retNomeAluno(Aluno *a);

int comparaNome(Aluno *a, Aluno *b);

void atualizoFrequencia(Aluno *a, Aluno *b);

Aluno *retProxAluno(Aluno *a);

Aluno *retUltimoAluno(Aluno *a);

void atualizaProxAluno(Aluno *a, Aluno *b);

void atualizaProxComNULL(Aluno *a);

int compara(const void *a1, const void *a2);

void imprimeVet(Aluno **vet, int tam);

void liberaVet(Aluno **vet, int tam);

#endif