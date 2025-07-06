#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

// typedef struct Aluno tAluno;

struct Aluno{

    char *nome;
    int mat;

};

Aluno *CriaAluno(int mat, char *nome){

    Aluno *aluno = malloc(sizeof(Aluno));

    aluno->mat = mat;

    aluno->nome = strdup(nome);

    return aluno;

}

void DestroiAluno(Aluno *aluno){

    free(aluno->nome);
    free(aluno);

}

Aluno *LeAluno(){

    char nome[50];

    scanf("%[^\n]", nome);
    scanf("%*[\n]");

    int mat=0;
    scanf("%d", &mat);
    scanf("%*c");

    Aluno *aluno = CriaAluno(mat, nome);

    return aluno;

}

int retMat(Aluno *aluno){

    return aluno->mat;

}

void imprimeAluno(Aluno *aluno){

    printf("Aluno de nome %s e matricula %d\n", aluno->nome, aluno->mat);

}

char *retNome(Aluno *aluno){

    return aluno->nome;

}

