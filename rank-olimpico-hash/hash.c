#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct hash{

    int n;
    int dim;
    Pais **paises;

};

Hash* hsh_cria (void){

    Hash *h = malloc(sizeof(Hash));

    h->n = 0;
    h->dim = 7;

    h->paises = (Pais**)malloc(h->dim * sizeof(Pais*));

    for(int i=0; i < h->dim; i++){

        h->paises[i] = NULL;

    }

    return h;

}

static int hash (Hash* tab , char *str){

    int total = 0;

    for(int i=0; str[i] != '\0'; i++){

        total += str[i];

    }

    return (total % tab->dim);

}

Pais* hsh_insere (Hash* tab , Pais* a){

    int flagInsere = 0;

    if(tab->n > (0.75 * tab->dim)){

        redimensiona(tab);

    }

    int h = hash(tab, retNomePais(a));

    if(tab->paises[h] != NULL){

        if(comparaNome(tab->paises[h], a)){

            atualizaFreq(tab->paises[h], a);
            liberaPais(a);

        } else {

            Pais *aux = retPaisProx(tab->paises[h]);

            while(aux != NULL){

                if(comparaNome(aux, a)){

                    flagInsere++;
                    atualizaFreq(aux, a);
                    liberaPais(a);

                }

                if(flagInsere != 0){

                    break;

                }

                aux = retPaisProx(aux);

            }

            if(flagInsere == 0){

                tab->n++;
            
                Pais *ultimoFila = procuraUltimoFila(tab->paises[h]);

                //atualizaFreq(ultimoFila, a);
                atualizaProx(ultimoFila, a);

            }

        }

    } else {

        tab->paises[h] = a;
        //atualizaFreq(tab->paises[h], a);
        tab->n++;

    }

    return a;

}

static void redimensiona (Hash* tab){

    int maxAnt = tab->dim;
    Pais **paisesAnt = tab->paises;
    tab->n = 0;
    tab->dim *= 1.947;
    tab->paises = (Pais**)malloc(tab->dim * sizeof(Pais*));

    for(int i=0; i < tab->dim; i++){

        tab->paises[i] = NULL;

    }

    for(int i=0; i < maxAnt; i++){

        Pais *atual = paisesAnt[i];

        while(atual != NULL){

            Pais *prox = retPaisProx(atual);
            atualizaProxComNULL(atual);
            hsh_insere(tab, atual);
            atual = prox;

        }

    }

    free(paisesAnt);

}

void printaHashMap(Hash* tab){

    Pais *prox = NULL;

    for(int i=0; i < tab->dim; i++){

        if(tab->paises[i] != NULL){

            //imprimePais(tab->paises[i]);

            prox = retPaisProx(tab->paises[i]);

            while(prox != NULL){

                //imprimePais(prox);

                prox = retPaisProx(prox);

            }

        }

    }

}


void liberaHash(Hash *tab){

    free(tab->paises);

    free(tab);

}

Pais **criaVetorOrdenado(Hash *tab){

    Pais **vet = malloc(tab->n * sizeof(Pais*));
    int indiceVet=0;

    Pais *prox = NULL;

    for(int i=0; i < tab->dim; i++){

        if(tab->paises[i] != NULL){

            vet[indiceVet] = tab->paises[i];
            indiceVet++;

            prox = retPaisProx(tab->paises[i]);

            while(prox != NULL){

                vet[indiceVet] = prox;
                indiceVet++;

                prox = retPaisProx(prox);

            }

        }

    }

    qsort(vet, tab->n, sizeof(Pais*), comparaMedalhas);

    return vet;

}

int retTamTab(Hash *tab){

    return tab->n;

}
