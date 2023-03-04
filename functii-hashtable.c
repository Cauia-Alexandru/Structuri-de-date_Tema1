#include "hashtable.h"
#include "lista_d.h"
#include <stdbool.h>

TH *init_hash(size_t M, TFHash fh)
{
    TH *h = (TH *)calloc(sizeof(TH), 1);
    if (!h)
    {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLGD *)calloc(M, sizeof(TLGD));
    if (!h->v)
    {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;

    return h;
}

void AfiTH(TH *ah, TF afiEl)
{
    TLGD p, el;
    int i;
    for (i = 0; i < ah->M; i++)
    {
        p = ah->v[i];
        if (p)
        {
            printf("LISTA %d:\n", i);
            afiEl(p->info);                          //afisez primul element
            for (el = p->urm; el != p; el = el->urm) //incep loop-ul de la al 2lea
                afiEl(el->info);
            printf("\n");
        }
    }
}

void DistrTH(TH **ah, TF fe)
{
    TLGD *p, el, aux;

    //parcurgere cu pointeri
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++)
    {
        if (*p != NULL)
        {
            //daca exista elemente corespunzatoare acestui hash
            //eliberam info din celula si apoi eliberam celula
            for (el = (*p)->urm; el != *p;)
            {
                aux = el;
                el = el->urm;
                el->pre = aux->pre; //refacerea legaturilor
                aux->pre = el;

                fe(aux->info);
                free(aux);
            }
            fe(el->info);
            free(el);
            *p = NULL;
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

int InsTH(TH *ah, void *ae, TFCmp f, int M)
{
    int cod = ah->fh(ae, M); //generez codul hash
    TLGD head, aux;
    head = ah->v[cod];

    if (head == NULL)
    {
        ins_ordonat(ah->v + cod, ae, f); //inserez daca lista e vida
        return 0;
    }

    aux = head->urm;

    if (f(head->info, ae) == 0)
    {
        DistrCel(ae);
        return -1;
    }

    for (; aux != head; aux = aux->urm) //verific element cu element daca e egal cu ae
    {
        if (f(aux->info, ae) == 0)
        {
            DistrCel(ae); //daca da, return
            return -1;
        }
    }
    ins_ordonat(ah->v + cod, ae, f); //altfel inserez
    return 0;
}

int Remove_key(TH *ah, void *ae, TFCmp f, int M)
{

    int cod = ah->fh(ae, M);
    TLGD head, aux;
    head = ah->v[cod];

    if (head == NULL)
        return -1;

    if (head->urm == head && f(head->info, ae) == 0) //daca capul e singur si trebuie eliminat
    {

        DistrCel(head);
        ah->v[cod] = NULL;
        return 1;
    }

    if (head->urm != head && f(head->info, ae) == 0) //capul nu e singur
    {
        head->urm->pre = head->pre;
        head->pre->urm = head->urm; //refacerea legaturilor
        ah->v[cod] = head->urm;
        DistrCel(head); //distrugerea celulei
        return 1;
    }

    aux = head->urm;
    for (; aux != head; aux = aux->urm) 
    {

        if (f(aux->info, ae) == 0 && aux->urm != head)
        {
            aux->pre->urm = aux->urm; //eliminare de la mijloc
            aux->urm->pre = aux->pre;
            DistrCel(aux);
            return 1;
        }
        else if (f(aux->info, ae) == 0 && aux->urm == head)
        {
            aux->pre->urm = aux->urm;
            aux->urm->pre = aux->pre; //eliminare de la sfarsit
            DistrCel(aux);
            return 1;
        }
    }

    return -1;
}

int get(TH *ah, void *ae, TFCmp f, int M, FILE *fwrite)
{
    int cod = ah->fh(ae, M);
    TLGD head, aux;
    head = ah->v[cod];
    if (head == NULL)
    {
        fprintf(fwrite, "NULL\n");
        DistrCel(ae);
        return -1;
    }

    if (f(head->info, ae) == 0)
    {

        fprintf(fwrite, "%s\n", ((Tquery *)(head->info))->Value); //afisez in fisier Value al capului
        DistrCel(ae);
        return 1;
    }

    aux = head->urm;
    for (; aux != head; aux = aux->urm) //verific restul listei
    {
        if (f(aux->info, ae) == 0)
        {

            fprintf(fwrite, "%s\n", ((Tquery *)(aux->info))->Value); //afisez
            DistrCel(ae);
            return 1;
        }
    }

    fprintf(fwrite, "NULL\n");
    DistrCel(ae);
    return -1;
}

bool find(TH *ah, void *ae, TFCmp f, int M)
{
    int cod = ah->fh(ae, M);
    TLGD head, aux;
    head = ah->v[cod];

    if (head == NULL)
    {
        DistrCel(ae);
        return false;
    }

    if (f(head->info, ae) == 0)
    {
        DistrCel(ae);
        return true;
    }

    aux = head->urm;
    for (; aux != head; aux = aux->urm)
    {
        if (f(aux->info, ae) == 0)
        {
            DistrCel(ae);
            return true;
        }
    }
    DistrCel(ae);
    return false;
}

void print(TH *ah, int M, FILE *fwrite)
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (ah->v[i] == NULL)
            continue;

        int cod = ah->fh(ah->v[i]->info, M);
        TLGD aux = ah->v[i];

        fprintf(fwrite, "%d: %s", cod, ((Tquery *)aux->info)->Value);
        for (aux = aux->urm; aux != ah->v[i]; aux = aux->urm)
        {

            fprintf(fwrite, "%s", ((Tquery *)aux->info)->Value);
        }
    }
}

void print_bucket(TH *ah, int cod1, int M, FILE *fwrite)
{
    int i;
    if (cod1 >= M)
        return;
    for (i = 0; i < M; i++)
    {
        if (ah->v[i] == NULL)
        {
            continue;
        }
        int cod0 = ah->fh(ah->v[i]->info, M);
        if (cod0 == cod1)
        {

            TLGD aux = ah->v[i];

            fprintf(fwrite, "%s ", ((Tquery *)aux->info)->Value);

            for (aux = aux->urm; aux != ah->v[i]; aux = aux->urm)
            {

                fprintf(fwrite, "%s ", ((Tquery *)aux->info)->Value);
            }

            fprintf(fwrite, "\n");
            return;
        }
    }
    fprintf(fwrite, "VIDA\n");
}
