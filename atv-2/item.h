#ifndef ITEM
#define ITEM

typedef struct Item Item;

Item *criaItem();

void liberaItem(Item *i);

Item *leItem();

float valorItem(Item *i);

void printaItem(Item *i);

#endif