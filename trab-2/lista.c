#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "bitmap.h"

struct Celula{

    Arv *arv;
    Celula *prox;

};

struct Lista{

    int tam;
    Celula *inicio;
    Celula *fim;

};

Lista *criaLista(){

    Lista *l = malloc(sizeof(Lista));

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;

}

void *liberaLista(Lista *l){

    Celula *inicio = l->inicio;
    Celula *prox;

    while(inicio != NULL){

        prox = inicio->prox;  
        abb_libera(l->inicio->arv);  
        free(inicio);
        inicio = prox;

    }

    free(l);

}

void imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    // while(aux != NULL){

    //     printf("Char: %c, Frequencia: %d\n",  retCarac(aux->arv), retFrequencia(aux->arv));

    //     aux = aux->prox;

    // }

    abb_imprime (l->inicio->arv);

}

Celula *retiraLista(Lista *lista, char *nome){

    // Celula *ant = NULL;
    // Celula *p = lista->inicio;

    // while(p != NULL && (strcmp(retNomeGato(p->prod), nome) != 0 && strcmp(retNomeCachorro(p->prod), nome) != 0)){

    //     ant = p;
    //     p = p->prox;

    // }

    // if(p == NULL){

    //     return NULL;

    // } 

    // if(p == lista->inicio && p == lista->fim){

    //     lista->inicio = lista->fim = NULL;

    //     return(p);

    // }

    // if(p == lista->fim){

    //     lista->fim = ant;
        
    //     ant->prox = NULL;

    //     return(p);

    // }

    // if(p == lista->inicio){

    //     lista->inicio = p->prox;

    // } else {

    //     ant->prox = p->prox;

    // }

    // return(p);

}

Celula *retiraPrimeiro(Lista *l){

    if(l->inicio == NULL){

        return NULL;

    }

    Celula *aux = l->inicio;

    l->inicio = l->inicio->prox;

    if(l->inicio == NULL){

        l->fim = NULL;

    }

    return aux;

}

void insereListaOrdenado(Lista *l, Arv *a){

    Celula *novo = malloc(sizeof(Celula));
    novo->arv = a;
    novo->prox = NULL;

    if(l->fim == NULL){

        l->inicio = l->fim = novo;
        l->fim->prox = NULL;
        l->tam++;

    } else if(retFrequencia(l->inicio->arv) > retFrequencia(a)){

            novo->prox = l->inicio->prox;
            l->inicio->prox = novo;
            l->tam++;

    } else {

        Celula *aux = l->inicio;

        while (aux->prox != NULL && retFrequencia(aux->prox->arv) <= retFrequencia(a)){

            aux = aux->prox;

        }

        novo->prox = aux->prox;

        aux->prox = novo;

        if (novo->prox == NULL) {

            l->fim = novo;  // Atualiza fim se for inserido no final

        }
        
        l->tam++;

    }

}

void *insereCelula(Lista *l, Celula *cel){

    if(l->fim == NULL){

        l->inicio = l->fim = cel;

    } else {

        l->fim->prox = cel;
        l->fim = l->fim->prox;

    }

    l->fim->prox = NULL;

}

void insereCelulasHuff(Lista *l, Celula *esq, Celula *dir){

    Arv *arv = arvCriaNaoVazia(esq->arv, dir->arv);

    insereListaOrdenado(l, arv);

    free(esq);
    free(dir);

}

void criaArvoreHuff(Lista *l){

    while(l->inicio != NULL && l->inicio->prox != NULL){

        Celula *esquerda = retiraPrimeiro(l);
        Celula *direita = retiraPrimeiro(l);

        insereCelulasHuff(l, esquerda, direita);

    }

}

unsigned int retAlturaCelula(Lista *l){

    if(l->inicio != NULL){

        return altura(l->inicio->arv);

    }

    return 0;

}

unsigned char **criaDicionario(Lista *a, unsigned int altura){

    unsigned char **dic = malloc(256 * sizeof(char*));

    for(int i=0; i < 256; i++){

        dic[i] = calloc((altura+1), sizeof(unsigned char));

    }

    preencheDicionario(dic, a->inicio->arv, "", altura);

    return dic;

}

void stringArvore(Lista *l){

    // unsigned int tamBitMap=0;

    // //preciso fazer uma funcao pra ver o tamanho de nos da arvore e usar como tamanho;
    // unsigned char * str = calloc(calculaTamanhoArvore(l->inicio->arv), sizeof(unsigned char));

    // criaStringArvore(l->inicio->arv, str);


    // //printf("%s\n", str);

    // for(unsigned int i=0; i < strlen(str); i++){

    //     if(/*str[i] == '1' ||*/ str[i] == '0'){

    //         tamBitMap++;

    //     } else {

    //         tamBitMap = tamBitMap + 8; 

    //     }

    // }


    // unsigned int tamMax = tamBitMap;
    // while(tamMax % 8 != 0){

    //     tamMax++;

    // }

    // bitmap *bm = bitmapInit(tamMax);

    // unsigned int indice = strlen(str);
    // for(unsigned int i=0; i < indice; i++){

    //     if( str[i] == '0'){

    //         bitmapAppendLeastSignificantBit(bm, str[i]);

    //     } else {

    //         bitmapAppendLeastSignificantBit(bm, str[i]);
    //         i++;
    //         for(int j=7; j >= 0; j--){

    //             unsigned char charTemp = (str[i] >> j) & 1;
    //             bitmapAppendLeastSignificantBit(bm, charTemp);

    //         } 

    //     }

    // }

    // FILE *fp = fopen("saida.txt", "wb");

    // fwrite(&tamBitMap, sizeof(unsigned int), 1, fp);
    // fwrite(&tamMax, sizeof(unsigned int), 1, fp);
    // fwrite(bitmapGetContents(bm), sizeof(unsigned char), tamMax/8, fp);

    // bitmapLibera(bm);
    // fclose(fp);
    // free(str);

    // // FILE *fp2 = fopen("saida.txt", "rb");

    // // int tamTotal=0, tamUtil=0;

    // // fread(&tamUtil, sizeof(int), 1, fp2);
    // // fread(&tamTotal, sizeof(int), 1, fp2);

    // // printf("%d %d ", tamBitMap, tamMax);
    // // printf("%d %d", tamUtil, tamTotal);
    if (l == NULL || l->inicio == NULL) return;

    unsigned int tamanhoMaximoBuffer = calculaTamanhoArvore(l->inicio->arv);
    unsigned char *str = calloc(tamanhoMaximoBuffer + 1, sizeof(unsigned char));

    unsigned int indice_final = 0;
    // Função auxiliar que criamos na etapa anterior (está em arvore.c)
    criaStringArvore_Manual(l->inicio->arv, str, &indice_final);

    unsigned int tamBitMap = 0;
    unsigned int i_calc = 0;
    while(i_calc < indice_final) {
        if (str[i_calc] == '0') {
            tamBitMap++;
            i_calc++;
        } else if (str[i_calc] == '1') {
            tamBitMap += 9; // 1 bit para o '1' + 8 bits para o caractere
            i_calc += 2; // Pula o '1' e o caractere
        }
    }

    unsigned int tamMax = tamBitMap;
    while(tamMax % 8 != 0){
        tamMax++;
    }

    bitmap *bm = bitmapInit(tamMax);

    // --- LAÇO CORRIGIDO USANDO 'while' ---
    unsigned int i = 0;
    while (i < indice_final) {
        if (str[i] == '0') {
            bitmapAppendLeastSignificantBit(bm, 0);
            i++; // Avança 1 posição
        } else if (str[i] == '1') {
            bitmapAppendLeastSignificantBit(bm, 1);
            i++; // Avança para o byte do caractere
            
            // Adiciona os 8 bits do caractere
            for (int j = 7; j >= 0; j--) {
                unsigned char bit = (str[i] >> j) & 1;
                bitmapAppendLeastSignificantBit(bm, bit);
            }
            i++; // Avança para depois do caractere
        }
    }
    // ------------------------------------

    FILE *fp = fopen("saida.txt", "wb");
    if (fp == NULL) {
        perror("Erro ao abrir saida.txt");
        free(str);
        bitmapLibera(bm);
        return;
    }

    fwrite(&tamBitMap, sizeof(unsigned int), 1, fp);
    fwrite(&tamMax, sizeof(unsigned int), 1, fp);
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), tamMax/8, fp);

    bitmapLibera(bm);
    fclose(fp);
    free(str);
}

Lista *criaListaOrdenada(Lista *l, unsigned int *vetFreq){

    for(int i=0; i<256; i++){

        if(vetFreq[i] > 0){

            Arv *arvAux = arv_cria(vetFreq[i], i);

            insereListaOrdenado(l, arvAux);

        }

    }

    return l;

}

unsigned char *decodificaArquivo(Lista *l, unsigned char *txt, FILE *fp){

    if(l->inicio != NULL){

        return decodificaFinal(l->inicio->arv, txt, fp);

    }

    return NULL;

}