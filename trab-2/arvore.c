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

Arv* abb_busca (Arv* r, int v){

    // if (r == NULL) {
        
    //     return NULL;

    // }else if (retMat(r->info) > v){ 
        
    //     return abb_busca (r->esq, v);

    // }else if (retMat(r->info) < v){
        
    //     return abb_busca (r->dir, v);

    // }else{
        
    //     return r;
    // }

}

Arv* abb_insere (Arv* a, Arv *info){

    // if (a==NULL) {

    //     a = (Arv*)malloc(sizeof(Arv));
    //     //mexer
    //     a->info = v;
    //     a->esq = a->dir = NULL;
    // }

    // else if (retMat(v) < retMat(a->info)){

    //     a->esq = abb_insere(a->esq,v);

    // }else{ /* v < a->info */

    //     a->dir = abb_insere(a->dir,v);

    // }

    // return a;
}

// Arv* abb_retira (Arv* r, int v){

//     if (r == NULL){

//         return NULL;

//     }else if (retMat(r->info) > v){

//         r->esq = abb_retira(r->esq, v);

//     }else if (retMat(r->info) < v){

//         r->dir = abb_retira(r->dir, v);

//     }else { /* achou o nó a remover */
//             /* nó sem filhos */
//         if (r->esq == NULL && r->dir == NULL) {
//             free (r);
//             r = NULL;
//         }
//         /* nó só tem filho à direita */
//         else if (r->esq == NULL) {
//             Arv* t = r;
//             r = r->dir;
//             free (t);
//         }
//         /* só tem filho à esquerda */
//         else if (r->dir == NULL) {
//             Arv* t = r;
//             r = r->esq;
//             free (t);
//         }
//         /* nó tem os dois filhos */
//         else {

//             Arv* f = r->esq;

//             while (f->dir != NULL) {

//                 f = f->dir;

//             }

//             r->info = f->info; /* troca as informações */
//             f->info = mudaMat(f->info, v);
//             r->esq = abb_retira(r->esq,v);

//             }

//     }

//     return r;

// }

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

void preencheDicionario(char **dic, Arv *a, char *conteudo, int altura){

    char esqAux[altura], dirAux[altura];

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