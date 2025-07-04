// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "leitor.h"
#include "livro.h"
#include "recomendacao.h"

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

        } else if(inicio->tipo == LEITOR){

            liberaLeitor(inicio->prod);

        } else {

            liberaRec(inicio->prod);

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

void imprimeLista(Lista *l, FILE *fp){

    Celula *aux = l->inicio;

    int cont = 0;

    while(aux != NULL){

        if(aux->tipo == LIVRO){

            if(cont == 0){

                fprintf(fp, "%s", retLivroTitulo(aux->prod));

            } else {

                fprintf(fp, ", %s", retLivroTitulo(aux->prod));

            }

        } else {

            if(cont == 0){

                fprintf(fp, "%s", retLeitorNome(aux->prod));

            } else {

                fprintf(fp, ", %s", retLeitorNome(aux->prod));

            }

        }
        
        cont++;

        aux = aux->prox;

    }


}

void imprimeBookED(Lista *l, FILE *fp){

    fprintf(fp, "Imprime toda a BookED\n\n");

    Celula *aux = l->inicio;

    while(aux != NULL){

        imprimeLeitor(aux->prod, fp);
        fprintf(fp, "\n");

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

int retIdLivroLista(Celula *l){

    return retIdLivro(l->prod);

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

Lista *retListaRecProd(Celula *cel){

    return retRecProd(cel->prod);

}

char *retLivroTituloLista(Celula *cel){

    return retLivroTitulo(cel->prod);

}

char *retLeitorNomeLista(Celula *cel){

    return retLeitorNome(cel->prod);

}

void *verificaLivrosEmComum(Celula *l1, Celula *l2, FILE *fp){

    Lista *afinidade1 = retListaLidos(l1);
    Lista *afinidade2 = retListaLidos(l2);

    Celula *lista1 = afinidade1->inicio;

    int cont = 0;

    fprintf(fp, "Livros em comum entre %s e %s: ", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

    while(lista1 != NULL){

        Celula *lista2 = afinidade2->inicio;

        while(lista2 != NULL){

            if(strcmp(retLivroTitulo(lista1->prod), retLivroTitulo(lista2->prod)) == 0){

                if(cont != 0){

                    fprintf(fp, ", ");

                }

                cont++;

                fprintf(fp, "%s", retLivroTitulo(lista1->prod));

            }

            lista2 = lista2->prox;

        }

        lista1 = lista1->prox;

    }

    if(cont == 0){

        fprintf(fp, "Nenhum livro em comum\n");

    } else {

        fprintf(fp, "\n");

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

int verificaAfinidadeLista(Celula *l1, Celula *l2, FILE *fp){

    if(verficaAfinidade(l1->prod, l2->prod)){

        fprintf(fp, "Existe afinidade entre %s e %s\n", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

        return 1;

    }

    Lista *visitados = criaLista();

    if(buscaProfundidade(l1->prod, l2->prod, visitados)){

        fprintf(fp, "Existe afinidade entre %s e %s\n", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

        liberaExterno(visitados);

        return 1;

    }

    fprintf(fp, "Não existe afinidade entre %s e %s\n", retLeitorNome(l1->prod), retLeitorNome(l2->prod));

    liberaExterno(visitados);

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

int comparaIdsLista(Celula *l1, Celula *l2){

    if(l1->tipo == LEITOR){

        return comparaIdLeitor(l1->prod, l2->prod);

    } else {

        return comparaIdLivro(l1->prod, l2->prod);

    }

    return 0;

}

Celula *retPrimeiraCelula(Lista *l1){

    return l1->inicio;

}

Celula *retProximaCelula(Celula *l1){

    return l1->prox;

}

int retIdLista(Celula *l1){

    if(l1->tipo == LEITOR){

        return retId(l1->prod);

    } else {

        return retIdLivro(l1->prod);

    }

}

void *retProdLista(Celula *l1){

    return l1->prod;

}

int existeRec(Lista *rec, int idLivro, int idLeitor){

    Celula *aux = rec->inicio;

    while(aux != NULL){

        if(comparaRec(aux->prod, idLivro, idLeitor)){

            return 1;

        }

        aux = aux->prox;

    }

    return 0;

}