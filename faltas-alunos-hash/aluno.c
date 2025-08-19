#include "aluno.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct aluno{

    char *nome;
    int faltas;
    int pres;
    Aluno *prox;

};

Aluno *criaALuno(char *nome, int faltas, int pres){

    Aluno *aluno = malloc(sizeof(Aluno));

    aluno->nome = nome;
    aluno->faltas = faltas;
    aluno->pres = pres;
    aluno->prox = NULL;

    return aluno;

}

Aluno *leAluno(FILE *fp){

    char nome[50];
    fscanf(fp, "%[^ ]", nome);
    fscanf(fp, "%*[ ]");

    char *nomeDin = strdup(nome);

    int faltas=0, pres=0;
    char lixo1, lixo2;
    fscanf(fp, "%d%c %d%c", &pres, &lixo1, &faltas, &lixo2);
    fscanf(fp, "%*c");

    Aluno *aluno = criaALuno(nomeDin, faltas, pres);

    return aluno;
}

void liberaAluno(Aluno *a){

    free(a->nome);
    free(a);

}

void imprimeAluno(Aluno *a){

    printf("Nome:%s p:%d f:%d\n", a->nome, a->pres, a->faltas);

}

char *retNomeAluno(Aluno *a){

    return a->nome;

}

int comparaNome(Aluno *a, Aluno *b){

    if(strcmp(a->nome, b->nome) == 0){

        return 1;

    }

    return 0;

}

void atualizoFrequencia(Aluno *a, Aluno *b){

    a->faltas += b->faltas;
    a->pres += b->pres;

}

Aluno *retProxAluno(Aluno *a){

    return a->prox;

}

Aluno *retUltimoAluno(Aluno *a){

    Aluno *aux = a;

    while(aux->prox != NULL){

        aux = aux->prox;

    }

    return aux;

}

void atualizaProxAluno(Aluno *a, Aluno *b){

    b->prox = NULL;
    a->prox = b;

}

void atualizaProxComNULL(Aluno *a){

    a->prox = NULL;

}