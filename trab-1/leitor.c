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
    Lista *leitoresComAfinidade;
    
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
    l->leitoresComAfinidade = criaLista();

    return l;

}

Leitor *leLeitor(FILE *fp){

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

    liberaExterno(l->lidos);
    liberaExterno(l->desejados);
    liberaExterno(l->recomendacoes);
    liberaExterno(l->leitoresComAfinidade);

    free(l);

}

void imprimeLeitor(Leitor *l, FILE *fp){

    fprintf(fp, "Leitor: %s\n", l->nome);

    fprintf(fp, "Lidos: ");
    imprimeLista(l->lidos, fp);
    fprintf(fp, "\n");

    fprintf(fp, "Desejados: ");
    imprimeLista(l->desejados, fp);
    fprintf(fp, "\n");

    fprintf(fp, "Recomendacoes: ");
    imprimeLista(l->recomendacoes, fp);
    fprintf(fp, "\n");

    fprintf(fp, "Afinidades: ");
    imprimeLista(l->leitoresComAfinidade, fp);
    fprintf(fp, "\n");

}

int retId(Leitor *l){

    return l->id;

}

Lista *retListaLidosLeitor(Leitor *l){

    return l->lidos;

}

Lista *retListaDesejadosLeitor(Leitor *l){

    return l->desejados;

}

Lista *retListaRecomendadosLeitor(Leitor *l){

    return l->recomendacoes;

}

Lista *retListaLeitoresComAfinidadeLeitor(Leitor *l){

    return l->leitoresComAfinidade;

}

char *retLeitorNome(Leitor *l){

    return l->nome;

}

int verficaAfinidade(Leitor *l1, Leitor *l2){

    if(strcmp(l1->nome, l2->nome) != 0){

        for(int i=0; i<l1->nAfinidades; i++){

            for(int j=0; j<l2->nAfinidades; j++){

                if(strcmp(l1->afinidades[i], l2->afinidades[j]) == 0){

                    return 1;

                }

            }

        }

    }

    return 0;

}

int verificaListaLeitoresComAfinidade(Leitor *l1, Leitor *l2){

    if(strcmp(l1->nome, l2->nome) != 0){

        if(encotraLeitorComum(l1->leitoresComAfinidade, l2->leitoresComAfinidade)){

            return 1;

        }

    }

    return 0;

}

int comparaIdLeitor(Leitor *l1, Leitor *l2){

    return l1->id == l2->id;

}