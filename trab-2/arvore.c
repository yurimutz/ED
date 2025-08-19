#include "arvore.h"

struct arv {
    unsigned int frequencia;
    unsigned char carac;
    struct arv* esq;
    struct arv* dir;
};

Arv* abb_criaVazia (){

    return NULL;

}

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

    //unsigned char esqAux[altura], dirAux[altura];

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

void criaStringArvore(Arv* a, unsigned char* conteudo){

    Arv *aux = a;

    unsigned char strAux[2];
    unsigned char strAux2[3];
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

unsigned char *decodificaFinal(Arv *a, unsigned char *txtCodificado, FILE *fp){

    Arv *aux = a;

    unsigned int tamDecodificado = 0;

    unsigned char *decodificado = malloc(strlen(txtCodificado) * sizeof(unsigned char));

    for(unsigned int i=0; txtCodificado[i] != '\0'; i++){

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
            //printf("%c", aux->carac);
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
    // Caso base: se o nó é nulo, seu tamanho é 0.
    if (a == NULL) {
        return 0;
    }

    // Verifica se é um nó folha (não tem filhos).
    if (a->esq == NULL && a->dir == NULL) {
        // Um nó folha é representado por: 1 bit (para o '1') + 8 bits (para o caractere).
        // Total de 9 bits.
        return 1 + 8;
    }

    // Se não for folha, é um nó interno.
    // Um nó interno é representado por: 1 bit (para o '0') 
    // + o tamanho da sub-árvore esquerda 
    // + o tamanho da sub-árvore direita.
    unsigned int tamanhoEsq = calculaTamanhoArvore(a->esq);
    unsigned int tamanhoDir = calculaTamanhoArvore(a->dir);

    return 1 + tamanhoEsq + tamanhoDir;
}

// Adicione esta nova função em arvore.c
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
