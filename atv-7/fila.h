//
//  Created by Yuri Tressmann Mutz on 14/07/22.
//

#ifndef FILA_H
#define FILA_H

#include "amostra.h"
#include "posto.h"

typedef struct Fila Fila;

typedef struct Lista Lista;

Fila* criaFila();

void insereFila (Fila* f, Amostra *amostra);

Amostra *retiraFila (Fila* f);

void liberaFila (Fila* f);

void imprimeFila(Fila *f);

int filaVazia(Fila *f);

#endif
