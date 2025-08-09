#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct palavra {

    char *string;
    int freq;
    Palavra *prox;
    
};

struct hash {

    int n;
    int dim;
    Palavra **v;

};

Palavra *criaPalavra(char *str){

    Palavra *p = malloc(sizeof(Palavra));

    p->string = strdup(str);
    p->freq = 0;
    p->prox = NULL;

    return p;

}

void liberaPalavra(Palavra *a){

    free(a->string);
    free(a);

}

Hash* hsh_cria (void){ 
    
    Hash* tab = (Hash*) malloc(sizeof (Hash ));

    tab ->n = 0;
    tab -> dim = 7; 
    tab ->v = (Palavra**)malloc(tab -> dim*sizeof (Palavra *));

    for (int i=0; i<tab -> dim; ++i){

        tab ->v[i] = NULL;

    }

    return tab;

}

static int hash (Hash* tab , char *str){

    int total = 0;

    for(int i=0; str[i] != '\0'; i++){

        total += str[i];

    }

    return (total% tab -> dim );

}

Palavra* hsh_insere (Hash* tab , Palavra* a){ 

    int flagInsere=0;

    if (tab ->n > 0.75* tab -> dim){

        redimensiona(tab);

    }

    int h = hash(tab , a->string);

    if(tab->v[h] != NULL){

        if(strcmp(tab->v[h]->string, a->string) == 0){

            tab->v[h]->freq++;
            liberaPalavra(a);

        } else {

            Palavra *aux = tab->v[h]->prox;

            while(aux != NULL){

                if(strcmp(aux->string, a->string) == 0){

                    aux->freq++;
                    flagInsere++;
                    liberaPalavra(a);
                    break;

                }             

                aux = aux->prox;

            }

            if(flagInsere == 0){

                a->freq++;
                a->prox = NULL;

                Palavra *ultimo = tab->v[h];

                while(ultimo->prox != NULL) {

                    ultimo = ultimo->prox;
                }

                ultimo->prox = a; 
                tab->n++;

            }

        }

    } else {

        tab ->v[h] = a;
        tab->v[h]->freq++;
        tab ->n++;  

    }

    return a;

}

static void redimensiona (Hash* tab){ 

    int max_ant = tab -> dim;
    Palavra** ant = tab ->v;
    tab ->n = 0;
    tab -> dim *= 1.947; 
    tab ->v = (Palavra**) malloc(tab -> dim*sizeof (Palavra *));

    for (int i=0; i<tab -> dim; ++i){

        tab ->v[i] = NULL;

    }

    for (int i=0; i< max_ant; ++i) {

        Palavra* atual = ant[i];

        while (atual != NULL) {
            
            Palavra* prox = atual->prox; 
            atual->prox = NULL;
            hsh_insere(tab, atual);
            atual = prox;

        }

    }

    free(ant);
}

void printaHashMap(Hash* tab){

    Palavra *prox = NULL;

    for(int i=0; i < tab->dim; i++){

        if(tab->v[i] != NULL){

            printf("Palavra: %s, Frequencia: %d\n", tab->v[i]->string, tab->v[i]->freq);

            prox = tab->v[i]->prox;

            while(prox != NULL){

                printf("Palavra: %s, Frequencia: %d\n", prox->string, prox->freq);

                prox = prox->prox;

            }

        }

    }

    printf("Numero de palavras: %d\n", tab->n);

}

Palavra **criaVetorOrdenado(Hash* tab){

    Palavra **vet = malloc(tab->n  * sizeof(Palavra*));

    int indice = 0;

    Palavra *prox = NULL;

    for(int i=0; i < tab->dim; i++){

         if(tab->v[i] != NULL){

            vet[indice] = tab->v[i];
            indice++; 

            prox = tab->v[i]->prox;

            while(prox != NULL){

                vet[indice] = prox;
                indice++;

                prox = prox->prox;

            }

        }

    }

    qsort(vet, tab->n, sizeof(Palavra*), comparaFreq);
    
    return vet;

}

int comparaFreq(const void *p1, const void *p2) {

    const Palavra *aux1 = *(const Palavra **)p1; 
    const Palavra *aux2 = *(const Palavra **)p2;

    return aux1->freq - aux2->freq; 
}

void printaInformacoes(Palavra **vet, Hash *tab){

    FILE *fp = fopen("saida.txt", "w");

    for(int i=0; i < tab->n; i++){

        fprintf(fp, "%s %d\n", vet[i]->string, vet[i]->freq);

    }

    fprintf(fp, "------------------------\n");

    fprintf(fp, "%d palavras distintas encontradas\n", tab->n);

    fprintf(fp, "%d palavras no total\n", retFrequenciasSomadas(vet, tab->n));

    Palavra *p = retPalavraMaiorFreq(vet, tab->n);

    fprintf(fp, "%s é a palavra de maior frequência (%d)\n", p->string, p->freq);

    fclose(fp);

}

int retFrequenciasSomadas(Palavra **vet, int tam){

    int total = 0;

    for(int i=0; i < tam; i++){

        total += vet[i]->freq;

    }

    return total;

}

Palavra *retPalavraMaiorFreq(Palavra **vet, int tam){

    Palavra *p = NULL;
    int maior=0;

    for(int i=0; i < tam; i++){

        if(vet[i]->freq > maior){

            maior = vet[i]->freq;
            p = vet[i];

        }

    }

    return p;

}

void liberaHash(Hash *tab){

    free(tab->v);

    free(tab);

}

void liberaVet(Palavra **vet, Hash *tab){

    for(int i=0; i < tab->n; i++){

        liberaPalavra(vet[i]);

    }

    free(vet);

}
