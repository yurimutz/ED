// Feito dia 03/07/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include "recomendacao.h"
#include <stdio.h>
#include <stdlib.h>

struct Rec{

    Livro *livro;
    Leitor *leitorRec;

};

Rec *criaRec(Livro *livro, Leitor *leitor){

    Rec *rec = malloc(sizeof(Rec));

    rec->livro = livro;
    rec->leitorRec = leitor;

    return rec;

}

void liberaRec(Rec *rec){

    free(rec);

}

void imprimeRec(Rec *rec){

    imprimeLivro(rec->livro);

    imprimeLeitor2(rec->leitorRec);

}

int comparaRec(Rec *l, int idLivro, int idLeitor){

    if(retIdLivro(l->livro) == idLivro && retId(l->leitorRec) == idLeitor){

        return 1;

    }

    return 0;

}