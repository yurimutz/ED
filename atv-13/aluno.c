#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

struct Aluno{

    char *nome;
    int mat;
    int cr;

};

Aluno *CriaAluno(int mat, char *nome, int cr){

    Aluno *aluno = malloc(sizeof(Aluno));

    aluno->mat = mat;

    aluno->nome = strdup(nome);

    aluno->cr = cr;

    return aluno;

}

void DestroiAluno(void *aluno){

    Aluno *aux = (Aluno*)aluno;

    free(aux->nome);
    free(aux);

}

Aluno *LeAluno(FILE *fp){

    int mat=0;

    fscanf(fp, "%d ", &mat);

    char nome[50];

    fscanf(fp, "%[^ ]", nome);
    fscanf(fp, "%*[ ]");

    int cr=0;
    fscanf(fp, "%d", &cr);
    fscanf(fp, "%*c");


    Aluno *aluno = CriaAluno(mat, nome, cr);

    return aluno;

}

int retMat(Aluno *aluno){

    return aluno->mat;

}

int imprimeAluno(void *aluno, void *fp){

    Aluno *aux = (Aluno*)aluno;

    FILE *arq = (FILE*)fp;

    fprintf(arq, "%d %s %d\n", aux->mat, aux->nome, aux->cr);

    return 1;

}

char *retNome(Aluno *aluno){

    return aluno->nome;

}

Aluno* mudaMat(Aluno *aluno, int matNovo){

    aluno->mat = matNovo;

}

int comparaNome(void *a, void *nome){

    Aluno *aux = (Aluno*)a;

    Aluno *aux2 = (Aluno*)nome;

    if(strcmp(aux->nome, aux2->nome) > 0){

        return 1;

    }

    return 0;

}

int comparaMat(void *a, void *mat){

    Aluno *aux = (Aluno*)a;

    Aluno *aux2 = (Aluno*)mat;

    return aux->mat > aux2->mat;

}