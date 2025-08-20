#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_exp.h"

//typedef struct arv Arv;

#define OPERADOR 1 
#define OPERANDO 2

struct arv{

    char conteudoChar;
    int conteudoInt;
    int tipo;
    Arv *esq;
    Arv *dir;

};

/*Cria uma arvore vazia, ou seja, retorna NULL
* inputs: nenhum
* output: NULL
*/
Arv* CriaVazia(void){

    return NULL;

}

/*cria um n� raiz de operador dados o operador e as duas sub-�rvores, a da esquerda e a da direita
* inputs: o operador, as sub-arvores da esquerda e da direita
* output: o endere�o do n� raiz criado
*/
Arv* CriaOperador(char c, Arv* esq, Arv* dir){

    Arv *a = malloc(sizeof(Arv));
    a->esq = esq;
    a->dir = dir;
    a->conteudoChar = c;
    a->tipo = OPERADOR;

    return a;

}

/*cria um n� operando dado o valor do no (como o operando � um n� folha, as sub-arvores da esquerda e da direita s�o nulas
* inputs: o operando
* output: o endere�o do n� raiz criado
*/
Arv* CriaOperando(int valor){

    Arv *a = malloc(sizeof(Arv));
    a->tipo = OPERANDO;
    a->dir = NULL;
    a->esq = NULL;
    a->conteudoInt = valor;

    return a;

}

/*Imprime a �rvore em nota��o InOrder (esq, raiz, direita)
* inputs: o endere�o da raiz da �rvore
* output: nenhum
*/
void Imprime(Arv* arv){

    Arv *aux = arv;

    if(aux != NULL){

        Imprime(aux->esq);

        if(arv->tipo == OPERANDO){

            printf("%c\n", (arv->conteudoChar));

        } else {

            printf("%d\n",  (arv->conteudoInt));

        }

        Imprime(aux->dir);

    }

}

/* Libera mem�ria alocada pela estrutura da �rvore
as sub-�rvores devem ser liberadas antes de se liberar o n� raiz
* inputs: o endere�o da raiz da �rvore
* output: uma �rvore vazia, representada por NULL
*/
Arv* Libera (Arv* arv){

    if (arv != NULL){

        Libera(arv->esq); /* libera sae */
        Libera(arv->dir); /* libera sad */
        free(arv); /* libera raiz */

    }

    return NULL;

}


/* Retorna o valor correspondente � avalia��o da express�o representada na �rvore
* inputs: o endere�o da raiz da �rvore
* output: o valor da express�o
*/
float Avalia(Arv* arv){

    if(arv->tipo == OPERADOR){

        if(arv->conteudoChar == '+'){

            return Avalia(arv->esq) + Avalia(arv->dir);

        } else if(arv->conteudoChar == '-'){

            return Avalia(arv->esq) - Avalia(arv->dir);

        } else if(arv->conteudoChar == '*'){

            return Avalia(arv->esq) * Avalia(arv->dir);

        } else {

            return Avalia(arv->esq) / Avalia(arv->dir);

        }

    } else {

        return arv->conteudoInt;

    }

}


/* Retorna o n�mero de folhas da �rvore
* inputs: o endere�o da raiz da �rvore
* output: o n�mero de folhas
*/
int Folhas(Arv* arv){

    if(arv->dir == NULL && arv->esq == NULL){

        return 1;

    } else {

        return Folhas(arv->esq) + Folhas(arv->dir);


    }

}

/* Retorna a altura da �rvore
* inputs: o endere�o da raiz da �rvore
* output: a altura da �rvore
*/
int Altura(Arv* arv){

    if(arv == NULL){

        return -1;

    }

    int altEsq = Altura(arv->esq);
    int altDir = Altura(arv->dir);

    if(altEsq > altDir){

        return altEsq + 1;

    } else {

        return altDir + 1;

    }

}