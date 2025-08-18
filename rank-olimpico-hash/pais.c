#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pais.h"

struct pais{

    int ouro;
    int prata;
    int bronze;
    int total;
    char *nome;
    int freq;
    Pais *prox;

};

Pais *criaPais(char *nome, int ouro, int prata, int bronze, int total){

    Pais *p = malloc(sizeof(Pais));

    p->nome = nome;

    p->ouro = ouro;
    p->prata = prata;
    p->bronze = bronze;
    p->total = total;
    p->freq = 0;

    p->prox = NULL;

    return p;

}

Pais *lePais(FILE *fp){

    char nome[50];
    fscanf(fp, "%[^ ]", nome);
    fscanf(fp, "%*[ ]");

    char *nomeDinam = strdup(nome);

    int ouro=0, prata=0, bronze=0, total=0;
    fscanf(fp, "%d %d %d %d", &ouro, &prata, &bronze, &total);
    fscanf(fp, "%*c");

    Pais *p = criaPais(nomeDinam, ouro, prata, bronze, total);

    return p;

}

Pais *liberaPais(Pais *p){

    free(p->nome);
    free(p);

}

char *retNomePais(Pais *p){

    return p->nome;

}

void atualizaFreq(Pais *recebe, Pais* conteudo){

    recebe->freq++;
    recebe->bronze += conteudo->bronze;
    recebe->prata += conteudo->prata;
    recebe->ouro += conteudo->ouro;

    recebe->total += conteudo->bronze + conteudo->prata + conteudo->ouro; 

}

int comparaNome(Pais *p1, Pais *p2){

    if(strcmp(p1->nome, p2->nome) == 0){

        return 1;

    }

    return 0;

}

Pais *retPaisProx(Pais *p){

    return p->prox;

}

Pais *procuraUltimoFila(Pais *p){

    Pais *aux = p;

    while(aux->prox != NULL){

        aux = aux->prox;

    }

    return aux;

}

void atualizaProx(Pais *recebe, Pais *conteudo){

    recebe->prox = conteudo;

}

void atualizaProxComNULL(Pais *p){

    p->prox = NULL;

}

void imprimePais(Pais *p, FILE *fp){

    fprintf(fp, "%s %d %d %d %d\n", p->nome, p->ouro, p->prata, p->bronze, p->total);

}

int comparaMedalhas(const void *p1, const void *p2){

    const Pais **point = (const Pais**)p1;
    const Pais **point2 = (const Pais**)p2;

    const Pais *aux1 = *point;
    const Pais *aux2 = *point2;

    if(aux1->ouro != aux2->ouro){

        return aux2->ouro - aux1->ouro;

    } else {
        
        if(aux1->prata != aux2->prata){

            return aux2->prata - aux1->prata;

        } else {

            if(aux1->bronze != aux2->bronze){

                return aux2->bronze - aux1->bronze;

            }

        }
    
    }

    return strcmp(aux1->nome, aux2->nome);

}

void imprimeVetor(Pais **vet, int tam){

    FILE *fp = fopen("saida.txt", "w");

    for(int i=0; i < tam; i++){

        imprimePais(vet[i], fp);

    }

    fclose(fp);

}

void liberaVet(Pais **vet, int tam){

    for(int i=0; i < tam; i++){

        liberaPais(vet[i]);

    }

    free(vet);

}