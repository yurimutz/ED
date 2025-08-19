#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash{

    int dim;
    int n;
    Aluno **alunos;

};

Hash* hsh_cria (void){

    Hash *h = malloc(sizeof(Hash));

    h->n = 0;
    h->dim = 7;

    h->alunos = malloc(h->dim * sizeof(Aluno*));

    for(int i=0; i < h->dim; i++){

        h->alunos[i] = NULL;

    }

    return h;

}

static int hash (Hash* tab , char *str){

    int total=0;

    for(int i=0; str[i] != '\0'; i++){

        total += str[i];

    }

    return total % tab->dim;

}

Aluno* hsh_insere (Hash* tab , Aluno* a){

    int flagInsere=0;

    if(tab->n > (0.75 * tab->dim)){

        redimensiona(tab);

    }

    int h = hash(tab, retNomeAluno(a));

    if(tab->alunos[h] != NULL){

        if(comparaNome(tab->alunos[h], a)){

            atualizoFrequencia(tab->alunos[h], a);
            liberaAluno(a);

        } else {

            Aluno *prox = retProxAluno(tab->alunos[h]);

            while(prox != NULL){

                if(comparaNome(prox, a)){

                    atualizoFrequencia(tab->alunos[h], a);
                    liberaAluno(a);
                    flagInsere++;

                }

                if(flagInsere != 0){

                    break;

                }

                prox = retProxAluno(prox);

            }

            if(flagInsere == 0){

                Aluno *ultimo = retUltimoAluno(tab->alunos[h]);
                atualizaProxAluno(ultimo, a);

                tab->n++;

            }

        }


    } else {

        tab->alunos[h] = a;
        tab->n++;

    }

    return a;

}

static void redimensiona (Hash* tab){

    int tamMaxAnt = tab->dim;
    Aluno **ant = tab->alunos;
    tab->n = 0;
    tab->dim *= 1.947; 
    tab->alunos = malloc(tab->dim * sizeof(Aluno*));

    for(int i=0; i < tab->dim; i++){

        tab->alunos[i] = NULL;

    }

    for(int i=0; i < tamMaxAnt; i++){

        Aluno *atual = ant[i];

        while(atual != NULL){

            Aluno *prox = retProxAluno(atual);
            atualizaProxComNULL(atual);
            hsh_insere(tab, atual);
            atual = prox;

        }

    }

    free(ant);

}

void liberaHash(Hash *tab){

    free(tab->alunos);
    free(tab);

}

Aluno **criarVetordenado(Hash *tab){

    int indice=0;

    Aluno **vet = malloc(tab->n * sizeof(Aluno*));

    for(int i=0; i < tab->dim; i++){

        if(tab->alunos[i] != NULL){

            vet[indice] = tab->alunos[i];
            indice++;

            Aluno *prox = retProxAluno(tab->alunos[i]);

            while(prox != NULL){

                vet[indice] = prox;
                indice++;

                prox = retProxAluno(prox);

            }

        }

    }

    qsort(vet, tab->n, sizeof(Aluno*), compara);

    return vet;

}

int retN(Hash *tab){

    return tab->n;

}

void printaHashMap(Hash* tab){

    Aluno *prox = NULL;

    for(int i=0; i < tab->dim; i++){

        if(tab->alunos[i] != NULL){

            imprimeAluno(tab->alunos[i]);

            prox = retProxAluno(tab->alunos[i]);

            while(prox != NULL){

                imprimeAluno(prox);

                prox = retProxAluno(prox);

            }

        }

    }

}