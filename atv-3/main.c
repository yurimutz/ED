//
//  main.c
//  TADMatriz
//
//  Created by Yuri Tressmann Mutz on 14/05/25.
//  Copyright © 2020 Yuri Tressmann Mutz. All rights reserved.
//

#include "matriz.h"

int main(){

    int nlinhas=0, ncolunas=0;

    printf("Escreva o tamanho da matriz:\n");
    scanf("%d %d", &nlinhas, &ncolunas);
    scanf("%*c");

    Matriz *mat = inicializaMatriz (nlinhas, ncolunas);

    printf("Escreva os %d elementos:\n", nlinhas *ncolunas);
    for(int i=0; i<recuperaNLinhas (mat); i++){

        for(int j=0; j<recuperaNColunas (mat); j++){

            int elem=0;
            scanf("%d", &elem);
            scanf("%*c");

            modificaElemento (mat, i, j, elem);

        }

    }

    printf("Escreva os indices da posicao que sera recuperada:\n");
    int linha=0, coluna=0;
    scanf("%d %d", &linha, &coluna);
    scanf("%*c");

    printf("Elemento recuperado: %d\n\n", recuperaElemento(mat, linha, coluna));

    Matriz *tr = transposta(mat);

    Matriz *mult = multiplicacao (mat, tr);

    imprimeMatriz(mat);

    imprimeMatriz(tr);

    imprimeMatriz(mult);

    int indice2=0;

    printf("Escreva a linha da matrix a ser multiplicada:\n");
    scanf("%d", &indice2);
    scanf("%*c");

    imprimeLinha (mult, indice2);

    destroiMatriz(mat);

    destroiMatriz(tr);

    destroiMatriz(mult);


    return 0;

}