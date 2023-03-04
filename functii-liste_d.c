
#include "lista_d.h"
#include <stdio.h>

int ins_ordonat(TLGD *aL, void *ae, TFCmp f)
{

    TLGD current = malloc(sizeof(TCelula));
    if (!current)
        return 0;

    current->info = ae;  //elementul care trebuie inserat
    current->urm = NULL; //ii setez legaturile spre el
    current->pre = NULL;

    TLGD aux = *aL; //initializarea capului listei
    if (*aL == NULL)
    {

        *aL = current;
       
        current->urm = current; //devine capul listei daca lista e vida
        current->pre = current;
        return 1;
    }
    else if (f(aux->info, current->info) > 0)
    {

        current->urm = aux;
        current->pre = aux->pre; //inserarea la inceput
        aux->pre->urm = current;
        aux->pre = current;
        *aL = current; //mut capul
        return 1;
    }
    else
    {
        do
        {
            aux = aux->urm;
            if (f(aux->info, current->info) > 0)
            {
                current->urm = aux;
                current->pre = aux->pre;
                aux->pre->urm = current; //inserarea la mijloc
                aux->pre = current;
                return 1;
            }
            
        }while(aux!=*aL); //daca ajunge sa fie egal cu capul, intra pe ultimul caz
        current->urm = aux;
        current->pre = aux->pre;
        aux->pre->urm = current;
        aux->pre = current; //inserarea la sfarsit
        return 1;
        
    }
    return -1;
}

void Afisare(TLGD *aL, TF afiEL)
{
    if (!*aL)
    {
        printf("Lista vida\n");
        return;
    }

    printf("[\n");
    TLGD head;
    head = *aL;
    afiEL(head->info);

    for (head = head->urm; head->urm != *aL; head = head->urm)
    {
        afiEL((*aL)->info);
    }
    printf("]\n");
}

void DistrCelula(void *ae)
{
    Tquery *p = (Tquery *)ae;
    free(p->Key);
    free(p->Value);
    free(p);
}

void DistrCel(void *celula)
{
    TLGD p = (TLGD)celula;

    Tquery *tq = (Tquery *)p->info;
    // free(tq->Key);
    // free(tq->Value);
    free(tq);

    free(p);
}




