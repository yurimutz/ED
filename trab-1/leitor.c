// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include "leitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Leitor{

    int id;
    char *nome;
    int nAfinidades;
    char **afinidades;
    Lista *lidos;
    Lista *desejados;
    Lista *recomendacoes;
    
};

Leitor *criaLeitor(int id, char *nome, int nAfinidades, FILE *fp){

    Leitor *l = malloc(sizeof(Leitor));

    l->id = id;
    l->nome = nome;
    l->nAfinidades = nAfinidades;

    l->afinidades = malloc(nAfinidades * sizeof(char*));
    for(int i=0; i<nAfinidades; i++){

        l->afinidades[i] = leLinha(fp);

    }

    l->lidos = criaLista();
    l->desejados = criaLista();
    l->recomendacoes= criaLista();

    return l;

}

Leitor *leLeitor(FILE *fp){

    // int id=0;
    // scanf("%d;", &id);

    // char *nome = leLinha(fp);

    // int nAfinidades=0;
    // scanf("%d;", &nAfinidades);

    // Leitor *l = criaLeitor(id, nome, nAfinidades);

    // return l;

    int id=0;
    fscanf(fp, "%d;", &id);

    char *nome = leLinha(fp);

    int nAfinidades=0;
    fscanf(fp, "%d;", &nAfinidades);

    Leitor *l = criaLeitor(id, nome, nAfinidades, fp);

    return l;

}

char *leLinha(FILE *fp){

    char temp[50];
    char lixo;

    fscanf(fp, "%[^;\n]", temp);
    fscanf(fp, "%c", &lixo);

    char *str = strdup(temp);

    return str;

}

void liberaLeitor(Leitor *l){

    free(l->nome);
    
    for(int i=0; i<l->nAfinidades; i++){

        free(l->afinidades[i]);

    }

    free(l->afinidades);

    liberaLista(l->lidos);
    liberaLista(l->desejados);
    liberaLista(l->recomendacoes);

    free(l);

}

void imprimeLeitor(Leitor *l){

    printf("%d\n", l->id);
    printf("%s\n", l->nome);
    printf("%d\n", l->nAfinidades);

    for(int i=0; i<l->nAfinidades; i++){

        printf("%s\n", l->afinidades[i]);

    }

}

int retId(Leitor *l){

    return l->id;

}

Lista *retListaLidosLeitor(Leitor *l){

    return l->lidos;

}