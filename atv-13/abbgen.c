#include "abbgen.h"

struct arv {
    void *info;
    struct arv* esq;
    struct arv* dir;
};

Arv* abb_criaVazia (){

    return NULL;

}

// Arv* arv_cria (Aluno* c, Arv* e, Arv* d){

//     Arv* p=(Arv*)malloc(sizeof(Arv));
//     p->info = c;
//     p->esq = e;
//     p->dir = d;
//     return p;

// }

void abb_imprime (Arv* a, comparaCliente imprime, FILE *fp){

    if (a != NULL) {

        abb_imprime(a->esq, imprime, fp);
        imprime(a->info, fp);
        abb_imprime(a->dir, imprime, fp);

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

Arv* abb_insere (Arv* a, void *v, comparaCliente compara){

    if (a==NULL) {

        a = (Arv*)malloc(sizeof(Arv));
        a->info = v;
        a->esq = a->dir = NULL;
    }

    // else if (retMat(v) < retMat(a->info)){
    else if (compara(a->info, v)){

        a->esq = abb_insere(a->esq,v, compara);

    }else{ /* v < a->info */

        a->dir = abb_insere(a->dir,v, compara);

    }

    return a;
}

Arv* abb_retira (Arv* r, int v){

    // if (r == NULL){

    //     return NULL;

    // }else if (retMat(r->info) > v){

    //     r->esq = abb_retira(r->esq, v);

    // }else if (retMat(r->info) < v){

    //     r->dir = abb_retira(r->dir, v);

    // }else { /* achou o nó a remover */
    //         /* nó sem filhos */
    //     if (r->esq == NULL && r->dir == NULL) {
    //         free (r);
    //         r = NULL;
    //     }
    //     /* nó só tem filho à direita */
    //     else if (r->esq == NULL) {
    //         Arv* t = r;
    //         r = r->dir;
    //         free (t);
    //     }
    //     /* só tem filho à esquerda */
    //     else if (r->dir == NULL) {
    //         Arv* t = r;
    //         r = r->esq;
    //         free (t);
    //     }
    //     /* nó tem os dois filhos */
    //     else {

    //         Arv* f = r->esq;

    //         while (f->dir != NULL) {

    //             f = f->dir;

    //         }

    //         r->info = f->info; /* troca as informações */
    //         f->info = mudaMat(f->info, v);
    //         r->esq = abb_retira(r->esq,v);

    //         }

    // }

    //return r;

}

// void arv_imprime (Arv* a){

//     if (a != NULL){
//         imprimeAluno(a->info); /* mostra raiz */
//         arv_imprime(a->esq); /* mostra sae */
//         arv_imprime(a->dir); /* mostra sad */
//     }   

// }

Arv* abb_libera (Arv* a, void (*destroy)(void *info)){

    if (a != NULL){

        abb_libera(a->esq, destroy); /* libera sae */
        abb_libera(a->dir, destroy); /* libera sad */
        destroy(a->info); /* libera raiz */
        free(a);

    }

    return NULL;

}