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
    char tipo;
    char aux[50];
    char lixo;

    fscanf(fp, "%[^\n]", aux);
    fscanf(fp, "%*[\n]");
    //printf("%s\n", aux);

    sscanf(aux, "%s %c", nome, &tipo);

    //printf("%s %c\n", nome, tipo);

    char *nomeDin = strdup(nome);

    Aluno *aluno;

    if(tipo == 'P'){
    
        aluno = criaALuno(nomeDin, 0, 1);

    } else {

        aluno = criaALuno(nomeDin, 1, 0);

    }

    //imprimeAluno(aluno);

    return aluno;
}

Aluno *leAluno2(FILE *fp){

    char nome[50];
    fscanf(fp, "%[^\n]", nome);
    fscanf(fp, "%*[\n]");

    char *nomeDin = strdup(nome);

    //int faltas=0, pres=0;
    //char lixo1, lixo2;
    //fscanf(fp, "%d%c %d%c", &pres, &lixo1, &faltas, &lixo2);
    //fscanf(fp, "%*c");

    Aluno *aluno = criaALuno(nomeDin, 0, 0);

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

int compara(const void *a1, const void *a2){

    const Aluno **aux1 = (Aluno**)a1;
    const Aluno **aux2 = (Aluno**)a2;

    const Aluno *ret1 = *aux1;
    const Aluno *ret2 = *aux2;

    return strcmp(ret1->nome, ret2->nome);

}

void imprimeVet(Aluno **vet, int tam){

    FILE *fp = fopen("saida.txt", "w");

    for(int i=0; i < tam; i++){

        fprintf(fp, "%s %dP %dF\n", vet[i]->nome, vet[i]->pres, vet[i]->faltas);

    }

    fclose(fp);

}

void liberaVet(Aluno **vet, int tam){

    for(int i=0; i<tam; i++){

        liberaAluno(vet[i]);

    }

    free(vet);

}