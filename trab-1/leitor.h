#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"

typedef struct Leitor Leitor;

Leitor *criaLeitor();

void liberaLeitor(Leitor *Leitor);

void imprimeLeitor(Leitor *leitor);

#endif