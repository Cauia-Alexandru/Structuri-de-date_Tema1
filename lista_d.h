#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _lista_
#define _lista_
typedef struct celula
{
    void* info;
    struct celula *urm;
    struct celula *pre;
}TCelula, *TLGD;

typedef struct {
    char *Key;
    char *Value;
}Tquery;


typedef int (*TFElem)(void*);
typedef void (*TF)(void*);
typedef int (*TFCmp)(void*, void*);

int ins_ordonat(TLGD* aL, void* ae, TFCmp f);
void Afisare(TLGD* aL, TF afiEL);
void DistrCel(void *celula);
void DistrCelula(void *ae);

#endif