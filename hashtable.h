#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "lista_d.h"
#include <stdbool.h>

#ifndef _hashtable_
#define _hashtable_

typedef void (*TF)(void*);
typedef int (*TFHash)(void*, int);


typedef struct
{
    size_t M;
    TFHash fh;
    TLGD *v;
}TH;


TH* init_hash(size_t M, TFHash fh);
void AfiTH(TH* ah, TF afiEl);
void DistrTH(TH** ah, TF fe);
int InsTH(TH* ah, void* ae, TFCmp f, int M);
int Remove_key(TH* ah, void* ae, TFCmp f, int M);
int get(TH *ah, void *ae, TFCmp f, int M, FILE* fwrite);
bool find(TH* ah, void* ae, TFCmp f, int M);
void print(TH *ah, int M, FILE* fwrite);
void print_bucket(TH *ah, int cod1, int M, FILE* fwrite);

#endif