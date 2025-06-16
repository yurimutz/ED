// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include "lista.h"

typedef struct Leitor Leitor;

Leitor *criaLeitor(int id, char *nome, int nAfinidades, FILE *fp);

Leitor *leLeitor(FILE *fp);

char *leLinha(FILE *fp);

void liberaLeitor(Leitor *l);

void imprimeLeitor(Leitor *l);

int retId(Leitor *l);

Lista *retListaLidosLeitor(Leitor *l);

Lista *retListaDesejadosLeitor(Leitor *l);

Lista *retListaRecomendadosLeitor(Leitor *l);

Lista *retListaLeitoresComAfinidadeLeitor(Leitor *l);

char *retLeitorNome(Leitor *l);

int verficaAfinidade(Leitor *l1, Leitor *l2);

int verificaListaLeitoresComAfinidade(Leitor *l1, Leitor *l2);

#endif