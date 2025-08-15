#include "arvore.h"

struct arv {
    int frequencia;
    char carac;
    struct arv* esq;
    struct arv* dir;
};

Arv* abb_criaVazia (){

    return NULL;

}

Arv* arv_cria (int frequencia, char carac){

    Arv* p=(Arv*)malloc(sizeof(Arv));
    p->carac = carac;
    p->frequencia = frequencia;
    p->esq = NULL;
    p->dir = NULL;
    return p;

}

Arv* arvCriaNaoVazia(Arv *esq, Arv *dir){

    Arv *arv = malloc(sizeof(Arv));
    arv->frequencia = esq->frequencia + dir->frequencia;
    arv->carac = '&';
    arv->esq = esq;
    arv->dir = dir;

    return arv;

}

void abb_imprime (Arv* a){

    if (a != NULL) {

        printf("Carac:%c Freq: %d\n", a->carac, a->frequencia);
        abb_imprime(a->esq);
        abb_imprime(a->dir);

    }

}

Arv* abb_libera (Arv* a){

    if (a != NULL){

        abb_libera(a->esq); /* libera sae */
        abb_libera(a->dir); /* libera sad */
        free(a); /* libera raiz */

    }

    return NULL;

}

int retFrequencia(Arv *a){

    return a->frequencia;

}

char retCarac(Arv *a){

    return a->carac;

}

int altura(Arv* a){

    if(a == NULL){

        return -1;

    }

    int altEsq = altura(a->esq);
    int altDir = altura(a->dir);

    if (altEsq > altDir){

        return altEsq + 1;

    } else {

        return altDir + 1;

    }

}

void preencheDicionario(unsigned char **dic, Arv *a, char *conteudo, int altura){

    unsigned char esqAux[altura], dirAux[altura];

    if(a->esq == NULL && a->dir == NULL){

        strcpy(dic[a->carac], conteudo);

    } else {

        strcpy(esqAux, conteudo);
        strcpy(dirAux, conteudo);

        strcat(esqAux, "0");
        strcat(dirAux, "1");

        /*a string conteudo vira as esqAux e dirAux por que elas que sao
          as strings que sao atualizadas a cada iteracao*/
        preencheDicionario(dic, a->esq, esqAux, altura);
        preencheDicionario(dic, a->dir, dirAux, altura);

    }

}

void criaStringArvore(Arv* a, char* conteudo){

    Arv *aux = a;

    char strAux[2];
    char strAux2[3];
    strAux[1] = '\0';
    strAux2[2] = '\0';

    if(a->dir == NULL && a->esq == NULL){

        strAux2[1] = a->carac;
        strAux2[0] = '1';
        strcat(conteudo, strAux2);

    } else {

        strAux[0] = '0';
        strcat(conteudo, strAux);

        criaStringArvore(a->esq, conteudo);
        criaStringArvore(a->dir, conteudo);        

    }

}

char *decodificaFinal(Arv *a, char *txtCodificado, FILE *fp){

    Arv *aux = a;

    int tamDecodificado = 0;

    char *decodificado = malloc(strlen(txtCodificado) * sizeof(char));

    for(int i=0; txtCodificado[i] != '\0'; i++){

        if(txtCodificado[i] == '0' ){

            aux = aux->esq;

        } else if(txtCodificado[i] == '1' ){

            aux = aux->dir;

        }

        if(aux->dir == NULL && aux->esq == NULL){

            decodificado[tamDecodificado] = aux->carac;
            tamDecodificado++;

            aux = a;

        }

    }

    decodificado[tamDecodificado] = '\0';

    return decodificado;

}

char *decodificaFinal2(Arv *a, bitmap *bm, int tamUtil){

    Arv *aux = a;

    int tamDecodificado = 0;

    char *decodificado = malloc((tamUtil+1) * sizeof(char));

    for(int i=0; i < tamUtil; i++){

        if(bitmapGetBit(bm, i) == 0 ){

            aux = aux->esq;

        } else if(bitmapGetBit(bm, i) == 1 ){

            aux = aux->dir;

        }

        if(aux->dir == NULL && aux->esq == NULL){

            decodificado[tamDecodificado] = aux->carac;
            tamDecodificado++;

            aux = a;

        }

    }

    decodificado[tamDecodificado] = '\0';

    printf("%s", decodificado);

    return decodificado;


}

Arv *recriaArvore(bitmap *bm, int *tamAtual){

    if(bitmapGetBit(bm, *tamAtual) == 0){

        (*tamAtual)++;

        Arv* esq = recriaArvore(bm, tamAtual);
        Arv* dir = recriaArvore(bm, tamAtual);

        return arvCriaNaoVazia(esq, dir);

    } else {

        (*tamAtual)++;

        unsigned char carac = lerByteInteiro(bm, *tamAtual);

        (*tamAtual) = *(tamAtual) + 8;

        return arv_cria(0, carac);

    }

}