#include "pedido.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct pedido TPedido;

typedef struct Celula Celula;

struct Celula{

    TProduto *prod;
    Celula *prox;

};

struct pedido{

    char *dono;
    Celula *fim;
    Celula *inicio;

};

TPedido* InicPedido (char* dono){

    TPedido *pedido = malloc(sizeof(TPedido));

    pedido->fim = NULL;
    pedido->inicio = NULL;

    pedido->dono = strdup(dono);

    return pedido;

}

/*----------------------------------------------------------------------
 * Inclui um produto no pedido de um cliente (ou seja, a sentinela!). Inserir ao FINAL!
 * Lembrando que um produto nao pode ser inserido mais de uma vez no pedido! Neste caso, exiba a mensagem "Produto já existe no pedido\n"
 * inputs: o pedido e o produto a ser inserido
 * output: nada
 * pre-condicao: pedido e produto foram devidamente inicializados
 * pos-condicao: produto inserido no pedido OU lista inalterada (caso o produto ja esteja na lista)
 *----------------------------------------------------------------------*/
void IncluiProdutoPedido (TPedido* pedido, TProduto* prod){

    Celula *aux = pedido->inicio;

    int cont = 0;

    while(aux != NULL){

        if(strcmp(RetornaNome (prod), RetornaNome (aux->prod)) == 0){

            cont++;

        }

        aux = aux->prox;

    }

    if(cont == 0){

        Celula *novo = malloc(sizeof(Celula));

        novo->prod = prod;
        novo->prox = NULL;

        if(pedido->fim == NULL){

            pedido->fim = pedido->inicio = novo;

        } else {

            pedido->fim->prox = novo;
            pedido->fim = novo;

        }

    } else {

        printf("Produto já existe no pedido\n");

    }

}

/*----------------------------------------------------------------------
 * Imprime todos os dados de um pedido (o dono seguido de todos os produtos e ingredientes)
 * Caso o pedido seja novo e nao tenha ainda produtos, exibir a mensagem "Nao ha produtos neste pedido!\n"
 * inputs: o pedido
 * output: nada
 * pre-condicao: pedido devidamente inicializado
 * pos-condicao: funcao nao alterad os dados do pedido
 *----------------------------------------------------------------------*/
void ImprimePedido (TPedido* pedido){

    Celula *aux = pedido->inicio;

    if(pedido->fim == NULL){

        printf("Nao ha produtos neste pedido!\n");

    } else {

        printf("\nDono do pedido: %s\n", pedido->dono);

        while(aux != NULL){

            ImprimeIngredientes(aux->prod);

            aux = aux->prox;

        }

    }

}

/*----------------------------------------------------------------------
 * Retira a unica ocorrência do produto (caso ele exista na lista).
 * Importante!!! Esta funcao nao libera o produto! Apenas o retira do pedido!
 * inputs: o pedido e, o produto a ser retirado
 * output: nada
 * pre-condicao: pedido e produto devidamente inicializados
 * pos-condicao: pedido nao contem o produto
 *----------------------------------------------------------------------*/
void RetiraProdutoPedido (TPedido* pedido, char* prod){

    Celula *ant = NULL;
    Celula *p = pedido->inicio;

    while(p != NULL && (strcmp(RetornaNome(p->prod), prod) != 0)){
        ant = p;
        p = p->prox;

    }

    if(p == NULL){


    } else if(p == pedido->inicio && p == pedido->fim){

        pedido->inicio = pedido->fim = NULL;

    } else if(p == pedido->fim){

        pedido->fim = ant;    
        ant->prox = NULL;     

    } else if(p == pedido->inicio){

        pedido->inicio = p->prox;

    } else {

        ant->prox = p->prox;

    }

    free(p);

}

//A função envia pedido verifica se há restrição calórica ou restrição alimentar
//Se estiver tudo ok, retira o pedido da lista (libera o pedido, porém não libera o produto) e retorna 1
//Se não estiver ok, a lista permanece a mesma e a função retorna zero

/*----------------------------------------------------------------------
 * Primeiramente, verifica se há restrição calórica ou restrição alimentar, de acordo com os parametros
 **** Para a restricao calorica, deve-se somar as calorias de todos o produtos do pedido! Caso o numero de calorias do pedido ultrapasse a restricao, exiba a mensagem : "Pedido não Enviado! Pedido tem mais calorias do que a restricao, tente retirar algum produto!"
 ****** Para a restricao alimentar, deve-se verificar se algum produto contem como ingrediente a restricao especificada. Caso algum produto contenha o ingrediente indicado, exiba a mensagem: nPedido não Enviado! Restricao alimentar no produto: %s\n
* Se estiver tudo certo (ou seja respeitando-se as restricoes), destroi o pedido da pessoa, porém não libera os produtos) e retorna 1
 * inputs: o pedido e as restricoes calorica e alimentar
 * output: 0 (problema em algumas das restricoes). 1 (pedido enviado)
 * pre-condicao: pedido devidamente inicializado e strings validas
 * pos-condicao: se houver problema com as restricoes, o pedido deve ficar inalterado. se estiver tudo ok com as restricoes, deve destruir o pedido, porem os produtos nao devem ser liberados (pois podem estar em outros pedidos, de outras pessoas).
 *----------------------------------------------------------------------*/
int EnviaPedido (TPedido* pedido, int restricao_calorica, char* restricao_alimentar){

    Celula *aux = pedido->inicio;

    int calorias = 0;

    while(aux != NULL){

        if(VerificaIngrediente (aux->prod, restricao_alimentar)){

            printf("Pedido não Enviado! Restricao alimentar no produto: %s\n", RetornaNome(aux->prod));
            
            return 0;

        }

        calorias += Calorias(aux->prod);

        aux = aux->prox;

    }

    if(calorias > restricao_calorica){

        printf("Pedido não Enviado! Pedido tem mais calorias do que a restricao, tente retirar algum produto!\n");

        return 0;

    } else {

        aux = pedido->inicio;
        Celula *prox = NULL;

        while(aux != NULL){

            prox = aux->prox;

            free(aux);

            aux = prox;

        }

        free(pedido->dono);
        free(pedido);

        return 1;

    }

}