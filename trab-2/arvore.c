#include "arvore.h"

struct arv {
    unsigned int frequencia;
    unsigned char carac;
    struct arv* esq;
    struct arv* dir;
};

Arv* arv_cria (unsigned int frequencia, unsigned char carac){

    Arv* p=(Arv*)malloc(sizeof(Arv));
    p->carac = carac;
    p->frequencia = frequencia;
    p->esq = NULL;
    p->dir = NULL;
    return p;

}

Arv* arvCriaNaoVazia(Arv *esq, Arv *dir){

    Arv *arv = malloc(sizeof(Arv));
    arv->frequencia = 0;
    if (esq != NULL) {
        arv->frequencia += esq->frequencia;
    }
    if (dir != NULL) {
        arv->frequencia += dir->frequencia;
    }
    arv->carac = '&';
    arv->esq = esq;
    arv->dir = dir;

    return arv;

}

Arv* abb_libera (Arv* a){

    if (a != NULL){

        abb_libera(a->esq); /* libera sae */
        abb_libera(a->dir); /* libera sad */
        free(a); /* libera raiz */

    }

    return NULL;

}

unsigned int retFrequencia(Arv *a){

    return a->frequencia;

}

unsigned char retCarac(Arv *a){

    return a->carac;

}

unsigned int altura(Arv* a){

    if(a == NULL){

        return -1;

    }

    unsigned int altEsq = altura(a->esq);
    unsigned int altDir = altura(a->dir);

    if (altEsq > altDir){

        return altEsq + 1;

    } else {

        return altDir + 1;

    }

}

void preencheDicionario(unsigned char **dic, Arv *a, unsigned char *conteudo, unsigned int altura){

    // Precisei fazer dinamico pois tava dando erro quando criei essas strings estaticas
    unsigned char *esqAux = malloc(altura * sizeof(unsigned char));
    unsigned char *dirAux = malloc(altura * sizeof(unsigned char));

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

    free(esqAux);
    free(dirAux);

}

unsigned char *decodificaFinal2(Arv *a, bitmap *bm, unsigned int tamUtil, char *dir){

    Arv *aux = a;

    unsigned int tamDecodificado = 0;

    unsigned char *decodificado = malloc((bitmapGetLength(bm)+1) * sizeof(unsigned char));

    for(unsigned int i=0; i < tamUtil; i++){

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
    
    FILE *teste = fopen(dir, "wb");
    fwrite(decodificado, sizeof(unsigned char), tamDecodificado, teste);
    fclose(teste);
    
    //se precisar da string eu tiro isso;
    free(decodificado);

    return decodificado;

}

Arv *recriaArvore(bitmap *bm, unsigned int *tamAtual, unsigned int tamUtil){

    if (*tamAtual >= tamUtil) {
        return NULL;
    }

    if(bitmapGetBit(bm, *tamAtual) == 0){

        (*tamAtual)++;

        Arv* esq = recriaArvore(bm, tamAtual, tamUtil);
        Arv* dir = recriaArvore(bm, tamAtual, tamUtil);

        return arvCriaNaoVazia(esq, dir);

    } else {

        (*tamAtual)++;

        unsigned char carac = lerByteInteiro(bm, *tamAtual);

        (*tamAtual) = *(tamAtual) + 8;
        //printf("%c ", carac);
        return arv_cria(0, carac);

    }

}

unsigned int calculaTamanhoArvore(Arv* a) {
   
    if (a == NULL) {
        return 0;
    }

    if (a->esq == NULL && a->dir == NULL) {
        // Um nó folha é representado por: 1 bit (para o '1') + 8 bits (para o caractere).
        // Total de 9 bits.
        return 1 + 8;
    }

    unsigned int tamanhoEsq = calculaTamanhoArvore(a->esq);
    unsigned int tamanhoDir = calculaTamanhoArvore(a->dir);

    return 1 + tamanhoEsq + tamanhoDir;
}

void criaStringArvore_Manual(Arv* a, unsigned char* buffer, unsigned int* indice) {
    if (a == NULL) {
        return;
    }

    // Se é um nó folha
    if (a->esq == NULL && a->dir == NULL) {
        buffer[*indice] = '1';
        (*indice)++;
        buffer[*indice] = a->carac; // Adiciona o byte do caractere diretamente
        (*indice)++;
    } 
    
    // Se é um nó interno
    else {
        buffer[*indice] = '0';
        (*indice)++;
        criaStringArvore_Manual(a->esq, buffer, indice);
        criaStringArvore_Manual(a->dir, buffer, indice);
    }
}
