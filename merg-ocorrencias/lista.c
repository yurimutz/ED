#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TipoItem Aluno (tipo opaco)
 Estrutura interna do tipo deve ser definida na implementacao do TAD. Devem ser definidos campos:
 - nome (string)
 - matricula (int) */
//typedef struct aluno TAluno;

struct aluno{

    char *nome;
    int matricula;

};

typedef struct Celula Celula;

struct Celula{

    TAluno *prod;
    Celula *prox;

};

/*Tipo que define a lista (tipo opaco)
 Estrutura interna do tipo deve ser definida na implementacao do TAD.
 Usar lista COM Sentinela */
//typedef struct lista TLista;

struct lista{

    Celula *inicio;
    Celula *fim;

};

/*Inicializa o sentinela de uma lista
 * inputs: nenhum
 * output: Sentinela inicializado (lista vazia)
 * pre-condicao: nenhuma
 * pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL */
TLista* CriaLista(){

    TLista *l = malloc(sizeof(TLista));

    l->inicio = NULL;
    l->fim = NULL;

    return l;

}

/*Inicializa um TipoItem aluno
 * inputs: o nome e a matricula do aluno
 * output: um ponteiro para o tipo TAluno criado
 * pre-condicao: nome e matricula validos
 * pos-condicao: tipo TAluno criado, com os campos nome e matricula COPIADOS */
TAluno* InicializaAluno(char* nome, int matricula){

    TAluno *a = malloc(sizeof(TAluno));

    a->matricula = matricula;
    a->nome = strdup(nome);

    return a;

}

/*Insere um aluno na primeira posicao da lista de alunos
 * inputs: aluno a ser inserido na lista (do tipo TAluno) e a lista
 * output: nenhum
 * pre-condicao: aluno não NULL e lista não NULL (mas, a lista pode estar vazia)
 * pos-condicao: lista contem o aluno inserido na primeira posicao */
void InsereAluno (TLista* lista, TAluno* aluno){

    Celula* novo = malloc(sizeof(Celula));

    novo->prod = aluno;

    novo->prox = lista->inicio;

    lista->inicio = novo;

    if (lista->fim == NULL) {
        lista->fim = novo;
    }

}

/*Retira a primeira ocorrencia de um aluno de matricula mat da lista de alunos
 * inputs: a lista e a matricula do aluno a ser retirado da lista
 * output: o aluno (do tipo TAluno) retirado da lista ou NULL, se o aluno nao se encontrar na lista
 * pre-condicao: lista nao eh NULL (mas pode estar vazia)
 * pos-condicao: lista nao contem a primeira ocorrencia do aluno de matricula mat */
TAluno* Retira (TLista* lista, int mat){

    Celula *p = lista->inicio;
    Celula *ant = NULL;

    TAluno *aux = NULL;

    while(p != NULL && p->prod->matricula != mat){

        ant = p;
        p = p->prox;

    }

    if(p == NULL){

        return NULL;

    }

    if(p == lista->inicio && p == lista->fim){

        lista->inicio = lista->fim = NULL;

        aux = p->prod;
        
        //free(p);

        return aux;

    }

    if(p == lista->fim){

        ant->prox = NULL;
        lista->fim = ant;

        aux = p->prod;

        //free(p);

        return aux;

    }

    if(p == lista->inicio){

        lista->inicio = p->prox;

        aux = p->prod;

        //free(p);

        return aux;

    }

    aux = p->prod;

    ant->prox = p->prox;

    //free(p);

    return aux;

}

/* Retira as repeticoes na lista. Ou seja, deixa apenas uma referencia para cada aluno na lista
 * inputs: a lista
 * output: nenhum
 * pre-condicao: lista nao eh NULL (mas pode estar vazia)
 * pos-condicao: lista nao contem repeticoes de alunos - APENAS UMA OCORRENCIA DE CADA ALUNO */
void RetiraRepetidos (TLista* lista){

    int matAux = 0;
    int cont = 0;

    Celula *aux = lista->inicio;
    Celula *proximo;

    TAluno *lixo;

    while(aux != NULL){

        Celula *indice2 = lista->inicio;

        matAux = aux->prod->matricula;

        cont = 0;

        while(indice2 != NULL){

            proximo = indice2->prox;

            if(indice2->prod->matricula == matAux){

                if(cont == 0){

                    cont++;

                } else { 

                    lixo = Retira(lista, indice2->prod->matricula);

                }

            } 

            indice2 = proximo;

        }

        aux = aux->prox;

    }

}


/* Intercala os alunos das turmas 1 e 2 em uma nova lista. Por exemplo, se a turma 1 tiver (a1->a2->a3) e a turma 2 tiver (b1->b2->b3->b4->b5), a funcao deve retornar uma nova lista formada pelos elementos (a1->b1->a2->b2->a3->b3->b4->b5). Se uma das  listas tiver mais elementos que a outra, os elementos excedentes são transferidos na mesma ordem para a nova lista. As listas originais devem ficar vazias (com sentila prim e ult apontando para NULL).
 * inputs: duas listas não nulas (porém, podem estar vazias)
 * output: uma nova lista com os elementos intercalados
 * pre-condicao: listas turma1 e turma2 nao sao NULL (mas podem estar vazias)
 * pos-condicao: lista retornada contem os elementos intercalados. As listas de entrada vazias (apenas com sentinela). */
TLista* Merge (TLista* turma1, TLista* turma2){

    Celula *indice1 = turma1->inicio;
    Celula *indice2 = turma2->inicio;

    TLista *novaLista = CriaLista();

    while(indice1 != NULL || indice2 != NULL){

        if(indice2 != NULL){

            InsereAluno(novaLista, indice2->prod);

            indice2 = indice2->prox;

        }

        if(indice1 != NULL){

            InsereAluno(novaLista, indice1->prod);

            indice1 = indice1->prox;

        }

    }

    Celula *aux = turma1->inicio;
    Celula *proximo = NULL;

    while(aux != NULL){

        proximo = aux->prox;

        free(aux);

        aux = proximo;

    }

    aux = turma2->inicio;

    while(aux != NULL){

        proximo = aux->prox;

        free(aux);

        aux = proximo;

    }

    turma1->inicio = turma1->fim = NULL;
    turma2->inicio = turma2->fim = NULL;

    return novaLista;

}

/* Libera a memoria alocada para o aluno
 * inputs: o aluno do tipo TAluno*
 * output: nenhum
 * pre-condicao: aluno não NULL
 * pos-condicao: toda a memoria alocada para o aluno foi liberada (inclusive para o nome) */
void LiberaAluno (TAluno* aluno){

    free(aluno->nome);
    free(aluno);

}

/*Imprime os dados de todos os alunos da lista
 * inputs: a lista de alunos
 * output: nenhum
 * pre-condicao: lista nao eh NULL (mas, pode estar vazia)
 * pos-condicao: dados dos alunos impressos na saida padrao */
void Imprime (TLista* lista){

    Celula *aux = lista->inicio;

    while(aux != NULL){

        printf("Matricula: %d\n", aux->prod->matricula);
        printf("Nome: %s\n\n", aux->prod->nome);

        aux = aux->prox;

    }

}

/*Libera toda a memoria alocada para a lista (lembre-se de tambem liberar a memoria para o aluno)
 * inputs: a lista encadeada de alunos
 * output: nenhum
 * pre-condicao: lista nao eh NULL (mas pode estar vazia)
 * pos-condicao: toda memoria alocada eh liberada (use valgrind!) */
void LiberaLista (TLista* lista){

    Celula *aux = lista->inicio;
    Celula *proximo = NULL;

    while(aux != NULL){

        proximo = aux->prox;

        if(aux->prod != NULL){

            LiberaAluno(aux->prod);

        }

        free(aux);

        aux = proximo;

    }

    free(lista);

}