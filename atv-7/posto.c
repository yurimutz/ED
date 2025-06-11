#include "posto.h"
#include <string.h>
#include <stdlib.h>
#include "fila.h"

struct posto{

    char *nome;
    Fila *naoProc;
    Fila *posit;
    Fila *neg;

};

/* Cria um posto de saúde, ainda vazio, com as 3 filas, vazias
* inputs: nome do posto de saúde.
* output: posto alocado e vazio, com filas de amostras ainda vazias
* pre-condicao: nao tem
* pos-condicao: posto alocado e vazio, com filas de amostras alocadas e vazias
 */
Posto* inicPosto(char* nome){

    Posto *p = malloc(sizeof(Posto));

    p->nome = strdup(nome);

    p->naoProc = criaFila();
    p->neg = criaFila();
    p->posit = criaFila();

    return p;

}

/* Imprime os dados do Posto no seguinte formato:
 
 Dados do Posto: <nome do posto>
 Amostras não processadas
 <fila de amostras não processadas - do início ao fim>
 
 Amostras com resultados positivos
 <fila de amostras positivas - do início ao fim>
 
 Amostra com resultados negativos
 <fila de amostras negativas - do início ao fim>
 
* inputs: referencia para o posto
* output: nenhum
* pre-condicao: posto alocado
* pos-condicao: dados do posto não são alterados
 */
void imprimePosto(Posto* posto){

    printf("Dados do posto: %s\n", posto->nome);

    printf("Amostras não processadas\n");
    imprimeFila(posto->naoProc);

    printf("Amostras com resultados positivos\n");
    imprimeFila(posto->posit);

    printf("Amostra com resultados negativos\n");
    imprimeFila(posto->neg);
    printf("\n");


}

/* Simula a realização de uma coleta de material para teste
 * A função deve criar uma amostra e fazer as devidas atribuições à amostra
 * Deve-se inserir a amostra na fila de "não processados"
 * ATENÇÃO: se a pessoa for idosa (idade>=60), ela deve ir para o início da fila de não processados
* inputs: referência para o posto de saúde, o nome do dono da coleta e a idade da pessa
* output: nenhum
* pre-condicao: posto válido, nome da pessoa válido
* pos-condicao: Amostra alocada e inserida na fila de amostras não processadas
 */
void realizaColeta(Posto* posto, char* pessoa, int idade){

    Amostra *a = inicAmostra(pessoa, idade);

    insereFila (posto->naoProc, a);

}


/* Essa função simula o processamento (testagem) das amostras e atualiza os resultados nas amostras. Deve-se usar a constante LIMITE_CARGA_VIRAL para definir positivo e negativo.
* inputs: referência do posto de saúde.
* output: nenhum
* pre-condicao: posto válido
* pos-condicao: amostras foram devidamente processadas; fila de amostras não processadas deve ficar vazia; fila de amostras positivas deve conter as amostras que testaram positivo (idosos na frente); fila de amostras negativas deve conter as amostras que testaram negativo (idosos na frente).
 */
void processaLoteAmostras(Posto* posto){

    while(!filaVazia(posto->naoProc)){

        Amostra *a = retiraFila (posto->naoProc);

        if(retornaCargaViral(a) > LIMITE_CARGA_VIRAL){

            registraResultado(a, POSITIVO);

            insereFila (posto->posit, a);

        } else {

            registraResultado(a, NEGATIVO);

            insereFila (posto->neg, a);

        }

    }

}

/* Libera toda a memória alocada para o posto de saúde
* inputs: referência do posto de saúde.
* output: nenhum
* pre-condicao: posto válido
* pos-condicao: Memória para a string nome liberada; memória para as 3 filas liberada, memoria do posto liberada
 */
void liberaPosto(Posto* posto){

    free(posto->nome);

    liberaFila (posto->naoProc);
    liberaFila (posto->neg);
    liberaFila (posto->posit);

    free(posto);

}
