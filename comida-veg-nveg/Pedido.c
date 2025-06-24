#include "Pedido.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef struct pedido Pedido;

struct pedido{

    int numero;
    Lista *calorico;
    Lista *nCalorico;

};

/* Cria um pedido, ainda vazio, com duas listas de alimentos, vazias
* inputs: numero do pedido.
* output: pedido alocado e vazia, com listas de alimentos ainda vazias
* pre-condicao: nao tem
* pos-condicao: pedido alocado e vazio, com listas de alimentos criadas e vazias
 */
Pedido* inicPedido (int numero){

    Pedido *p = malloc(sizeof(Pedido));

    p->calorico = criaLista();
    p->nCalorico = criaLista();

    p->numero = numero;

    return p;

}

/* Insere uma comida vegana em uma das listas de alimentos, dependendo do seu nível de caloria
* inputs: referência para a um pedido e a referência para o alimento
* output: nenhum
* pre-condicao: pedido alocado e alimento alocado
* pos-condicao: pedido contém o alimento em uma de suas listas, dependendo do nível de calorias do alimento  */
void insereComidaVegana (Pedido* pedido, ComidaVegana* food){

    if(retornaCaloriasComidaVegana (food) > 500){

        insereLista(pedido->calorico, food, VEGANA);

    } else {

        insereLista(pedido->nCalorico, food, VEGANA);

    }

}


/* Insere uma comida não vegana em uma das listas de alimentos, dependendo do seu nível de caloria
* inputs: referência para a um pedido e a referência para o alimento
* output: nenhum
* pre-condicao: pedido alocado e alimento alocado
* pos-condicao: pedido contém o alimento em uma de suas listas, dependendo do nível de calorias do alimento  */
void insereComidaNaoVegana (Pedido* pedido, ComidaNaoVegana* food){

    if(retornaCaloriasComidaNaoVegana (food) > 500){

        insereLista(pedido->calorico, food, nVEGANA);

    } else {

        insereLista(pedido->nCalorico, food, nVEGANA);

    }

}

//retorna o numero do pedido
int retornaNumeroPedido(Pedido* pedido){

    return pedido->numero;

}

/* Essa função atualiza a situação de uma comida nao vegana no pedido. Caso o alimento esteja na lista errada, ele é devidamente MOVIDO para a lista correta.
* inputs: referência para o pedido e a referência para o alimento
* output: nenhum
* pre-condicao: pedido alocado e alimento alocado
* pos-condicao: alimento deve estar na lista correta, de acordo com seu nível de calorias */
void atualizaSituacaoComidaNaoVegana(Pedido* pedido, ComidaNaoVegana* food){

    if(retornaCaloriasComidaNaoVegana(food) > 500 && buscaLista(pedido->nCalorico, retornaNomeComidaNaoVegana(food))){

        insereCelula(pedido->calorico, retiraLista(pedido->nCalorico, retornaNomeComidaNaoVegana(food)));

    } else if(retornaCaloriasComidaNaoVegana(food) <= 500 && buscaLista(pedido->calorico, retornaNomeComidaNaoVegana(food))){

        insereCelula(pedido->nCalorico, retiraLista(pedido->calorico, retornaNomeComidaNaoVegana(food)));

    }

}

/* Essa função atualiza a situação de uma comida vegana no pedido. Caso o alimento esteja na lista errada, ele é devidamente MOVIDO para a lista correta.
* inputs: referência para o pedido e a referência para o alimento
* output: nenhum
* pre-condicao: pedido alocado e alimento alocado
* pos-condicao: alimento deve estar na lista correta, de acordo com seu nível de calorias */
void atualizaSituacaoComidaVegana(Pedido* pedido, ComidaVegana* food){

    if(retornaCaloriasComidaVegana(food) > 500 && buscaLista(pedido->nCalorico, retornaNomeComidaVegana(food))){

        insereCelula(pedido->calorico, retiraLista(pedido->nCalorico, retornaNomeComidaVegana(food)));

    } else if(retornaCaloriasComidaVegana(food) <= 500 && buscaLista(pedido->calorico, retornaNomeComidaVegana(food))){

        insereCelula(pedido->nCalorico, retiraLista(pedido->calorico, retornaNomeComidaVegana(food)));

    }

}


//Imprime os dados do pedido, seguindo o formato a seguir
/*Imprimindo Detalhes do Pedido número: 123
  Valor total do Pedido: 135.90

 Lista de Itens de Baixa Caloria: 1
 Nome comida nao vegana: Picanha, valor: 90.50, calorias: 300

 Lista de Itens de Alta Caloria: 2
 Nome comida vegana: Empadao, calorias: 600
 Nome comida nao vegana: Sorvete de Creme, valor: 15.40, calorias: 600
*/
void imprimePedido (Pedido* pedido){

    printf("Numero do pedido: %d\n", pedido->numero);

    printf("\nPedidos nao caloricos:");

    imprimeLista(pedido->nCalorico);

    printf("\nPedidos caloricos:");

    imprimeLista(pedido->calorico);

    printf("\n");

}

//comida vegana tem o valor fixo de 30 reais
float calculaValorPedido (Pedido* pedido){



}

/* Libera toda a memória alocada
* inputs: referencia para o pedido
* output: não tem
* pre-condicao: pedido alocado
* pos-condicao: Toda a memória liberada, a não ser alimentos, que são responsabilidade do cliente. */
void liberaPedido (Pedido* pedido){

    Lista *aux = pedido->calorico;

    liberaLista(aux);

    aux = pedido->nCalorico;

    liberaLista(aux);

    free(pedido);

}