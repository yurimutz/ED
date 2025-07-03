// Feito dia 03/07/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef REC_H
#define REC_H

#include "lista.h"
#include "leitor.h"
#include "livro.h"

typedef struct Rec Rec;

Rec *criaRec(Livro *livro, Leitor *leitor);

void liberaRec(Rec *rec);

void imprimeRec(Rec *rec);

int comparaRec(Rec *l, int idLivro, int idLeitor);

#endif