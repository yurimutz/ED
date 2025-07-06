#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef struct Arv Arv;

struct Arv {
    Aluno *prod;
    Arv *esq;
    Arv *dir;
};

//Cria uma árvore vazia
Arv* arv_criavazia (void){

    return NULL;

}

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arv* arv_cria (Aluno* c, Arv* e, Arv* d){

    Arv* p=(Arv*)malloc(sizeof(Arv));
    p->prod = c;
    p->esq = e;
    p->dir = d;
    return p;

}

//libera o espaço de memória ocupado pela árvore a
Arv* arv_libera (Arv* a){

    if (!arv_vazia(a)){

        arv_libera(a->esq); /* libera sae */
        arv_libera(a->dir); /* libera sad */
        free(a); /* libera raiz */

    }

    return NULL;

}

//retorna true se a árvore estiver vazia e false caso contrário
int arv_vazia (Arv* a){

    return a == NULL;

}

//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arv* a, int mat){

    if (arv_vazia(a))
    return 0; /* árvore vazia: não encontrou */
    else
    return retMat(a->prod)==mat || arv_pertence(a->esq,mat) || arv_pertence(a->dir,mat);
}

//imprime as informações dos nós da árvore
void arv_imprime (Arv* a){

    if (!arv_vazia(a)){
        imprimeAluno(a->prod); /* mostra raiz */
        arv_imprime(a->esq); /* mostra sae */
        arv_imprime(a->dir); /* mostra sad */
    }   

}

//retorna a mãe/pai de um dado no que contém o aluno com a matrícula mat
Arv* arv_pai (Arv* a, int mat){

    if(a == NULL){

        return a;

    }

    if((!arv_vazia(a->dir) && retMat(a->dir->prod) == mat) || (!arv_vazia(a->esq) && retMat(a->esq->prod) == mat)){

        return a;

    } else {

        Arv* p = arv_pai(a->esq, mat);
        Arv* e = arv_pai(a->dir, mat);

        if (p != NULL){

            return p;

        }
           
        if (e != NULL){

            return e;

        }

    }

    return NULL;

}

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arv* a){

    if(a == NULL){

        return 0;

    }

    int cont = 0;

    if(arv_vazia (a->dir) && arv_vazia (a->esq)){

        cont++;

    }

    return cont + folhas (a->esq) + folhas (a->dir);

}

//retorna o numero de ocorrencias de um dado aluno na árvore
int ocorrencias (Arv* a, int mat){

    if(a == NULL){

        return 0;

    }

    int cont = 0;

    if(retMat(a->prod) == mat){

        cont++;

    }

    return cont + ocorrencias (a->esq, mat) + ocorrencias (a->dir, mat);

}

//retorna a altura da árvore a
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

void imprime2(Arv *a){

    imprimeAluno(a->prod);

}