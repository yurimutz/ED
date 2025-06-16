// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "leitor.h"
#include "livro.h"

struct Celula{

    void *prod;
    int tipo;
    Celula *prox;

};

struct Lista{

    Celula *inicio;
    Celula *fim;

};

Lista *criaLista(){

    Lista *l = malloc(sizeof(Lista));

    l->inicio = NULL;
    l->fim = NULL;

    return l;

}

void liberaLista(Lista *l){

    Celula *inicio = l->inicio;
    Celula *prox;

    while(inicio != NULL){

        prox = inicio->prox;  
        
        if(inicio->tipo == LIVRO){

            liberaLivro(inicio->prod);

        } else {

            liberaLeitor(inicio->prod);

        }
        
        free(inicio);

        inicio = prox;

    }


    free(l);

}

void liberaExterno(Lista *l){

    Celula *inicio = l->inicio;
    Celula *prox;

    while(inicio != NULL){

        prox = inicio->prox;  
        
        free(inicio);

        inicio = prox;

    }

    free(l);

}

void imprimeLista(Lista *l){

    Celula *aux = l->inicio;

    int cont = 0;

    while(aux != NULL){

        if(aux->tipo == LIVRO){

            if(cont == 0){

                printf("%s", retLivroTitulo(aux->prod));

            } else {

                printf(" , %s", retLivroTitulo(aux->prod));

            }

        } else {

            if(cont == 0){

                printf("%s", retLeitorNome(aux->prod));

            } else {

                printf(" , %s", retLeitorNome(aux->prod));

            }

        }
        
        cont++;

        aux = aux->prox;

    }


}

void imprimeBookED(Lista *l){

    printf("Imprime toda a BookED\n\n");

    Celula *aux = l->inicio;

    while(aux != NULL){

        imprimeLeitor(aux->prod);

        aux = aux->prox;

    }

}

Celula *retiraLista(Lista *lista, char *nome){

    Celula *ant = NULL;
    Celula *p = lista->inicio;

    while(p != NULL && (strcmp(retLivroTitulo(p->prod), nome) != 0)){
        ant = p;
        p = p->prox;

    }

    if(p == NULL){

        return NULL;

    } 

    if(p == lista->inicio && p == lista->fim){

        lista->inicio = lista->fim = NULL;

        return(p);

    }

    if(p == lista->fim){

        lista->fim = ant;    
        ant->prox = NULL;     

        return(p);

    }

    if(p == lista->inicio){

        lista->inicio = p->prox;

    } else {

        ant->prox = p->prox;

    }

    return(p);

}

void *insereLista(Lista *l, void *p, int tipo){

    Celula *novo = malloc(sizeof(Celula));

    if(l->fim == NULL){

        l->inicio = l->fim = novo; 

    } else {

        l->fim->prox = novo;
        l->fim = l->fim->prox;

    }

    l->fim->prod = p;
    l->fim->tipo = tipo;
    l->fim->prox = NULL;
    

}

void *insereCelula(Lista *l, Celula *cel){

    if(l != NULL && cel != NULL){

    //     if(l->fim == NULL){

    //         l->inicio = l->fim = cel;

    //     } else {

    //         l->fim->prox = cel;
    //         l->fim = l->fim->prox;

    //     }

    //     l->fim->prox = NULL;

        Celula *novo = malloc(sizeof(Celula));

        if(l->fim == NULL){

            l->inicio = l->fim = novo; 

        } else {

            l->fim->prox = novo;
            l->fim = l->fim->prox;

        }

        l->fim->prod = cel->prod;
        l->fim->tipo = cel->tipo;
        l->fim->prox = NULL;
        
    }

}

Celula *busca(Lista *l, int id){

    Celula *aux = l->inicio;

    while(aux != NULL){

        if(aux->tipo == LIVRO){

            if(retIdLivro(aux->prod) == id){
                return aux;

            }

        } else {

            if(retId(aux->prod) == id){
                return aux;

            }

        }

        aux = aux->prox;

    }
    
    return NULL;

}

Lista *retListaLidos(Celula *cel){

    Lista *aux = retListaLidosLeitor(cel->prod);

    return aux;

}

Lista *retListaDesejados(Celula *cel){

    Lista *aux = retListaDesejadosLeitor(cel->prod);

    return aux;

}

Lista *retListaRecomendados(Celula *cel){

    Lista *aux = retListaRecomendadosLeitor(cel->prod);

    return aux;

}

Lista *retListaLeitoresComAfinidade(Celula *cel){

    Lista *aux = retListaLeitoresComAfinidadeLeitor(cel->prod);

    return aux;

}

char *retLivroTituloLista(Celula *cel){

    return retLivroTitulo(cel->prod);

}

char *retLeitorNomeLista(Celula *cel){

    return retLeitorNome(cel->prod);

}

void *verificaLivrosEmComum(Celula *l1, Celula *l2){

    Lista *afinidade1 = retListaLidos(l1);
    Lista *afinidade2 = retListaLidos(l2);

    Celula *lista1 = afinidade1->inicio;

    int cont = 0;

    printf("Livros em comum entre %s e %s: ", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

    while(lista1 != NULL){

        Celula *lista2 = afinidade2->inicio;

        while(lista2 != NULL){

            if(strcmp(retLivroTitulo(lista1->prod), retLivroTitulo(lista2->prod)) == 0){

                cont++;

                printf("%s", retLivroTitulo(lista1->prod));

            }

            lista2 = lista2->prox;

        }

        lista1 = lista1->prox;

    }

    if(cont == 0){

        printf("Nenhum livro em comum\n");

    } else {

        printf("\n");

    }

}

void adicionaAfinidades(Lista *l){

    Celula *aux = l->inicio;

    while(aux != NULL){

        Celula *aux2 = l->inicio;

        while(aux2 != NULL){

            if(verficaAfinidade(aux->prod, aux2->prod)){

                Lista *afinidade1 = retListaLeitoresComAfinidadeLeitor(aux->prod);

                insereCelula(afinidade1, aux2);

            }

            aux2 = aux2->prox;

        }

        aux = aux->prox;

    }

}

int verificaAfinidadeLista(Celula *l1, Celula *l2){

    if(verficaAfinidade(l1->prod, l2->prod)){

        printf("Existe afinidade entre %s e %s\n", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

        return 1;

    }

    if(verificaListaLeitoresComAfinidade(l1->prod, l2->prod)){

        printf("Existe afinidade entre %s e %s\n", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

        return 1;

    }

    return 0;

}

int encotraLeitorComum(Lista *l1, Lista *l2){

    Celula *aux = l1->inicio;

    while(aux != NULL){

        Celula *aux2 = l2->inicio;

        while(aux2 != NULL){

            if(retId(aux->prod) == retId(aux2->prod)){

                return 1;

            }

            aux2 = aux2->prox;

        }

        aux = aux->prox;

    }

    return 0;

}