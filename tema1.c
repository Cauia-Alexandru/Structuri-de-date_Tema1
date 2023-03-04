
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include "lista_d.h"
#include "hashtable.h"
#include <string.h>
#include <stdbool.h>


int codHash(void *elem, int M)
{
    int suma;
    Tquery *query_dns = (Tquery *)elem;
    char *cod = query_dns->Key;

    for (suma = 0; *cod != '\0'; cod++)
        suma += *cod;
    return (suma % M);
}


int cmpKey(void *e1, void *e2)
{
    Tquery *info1 = (Tquery *)e1;
    Tquery *info2 = (Tquery *)e2;

    return strcmp(info1->Key, info2->Key); //returneaza > 0 daca info 1 e mai mare
}

void afisareQuery(void *elem)
{
    Tquery *querry = (Tquery *)elem;
    printf("%s, %s ", querry->Key, querry->Value);
}

void citesteTabla(char *numeFisier, char *numeFisierIesire, TH *ah)
{

    FILE *f;
    FILE *fwrite;
    char *line = NULL;
    size_t len = 0;

    f = fopen(numeFisier, "rt");
    fwrite = fopen(numeFisierIesire, "wt");
    if (f == NULL)
        return;

    while (getline(&line, &len, f) != -1)
    {

       
        char *functie = strtok(line, " "); //citesc primul cuvant din fisier, care e denumirea functiei
        if (functie[strlen(functie) - 1] == '\n')
            functie[strlen(functie) - 1] = '\0'; //inclocuiesc \n de la final cu \0
        if (functie[strlen(functie) - 1] == '\r')
            functie[strlen(functie) - 1] = '\0';
        if (strcmp(functie, "put") == 0)
        {
            
            char *site = strtok(NULL, " "); //dupa put mai citesc key si value
            char *IP = strtok(NULL, " ");
            Tquery *info = (Tquery *)malloc(sizeof(Tquery));
            info->Key = (char *)malloc((strlen(site) + 1) * sizeof(char));
            info->Value = (char *)malloc((strlen(IP) + 1) * sizeof(char)); //aloc memorie
            if (IP[strlen(IP) - 1] == '\n')
                IP[strlen(IP) - 1] = '\0';
            if (IP[strlen(IP) - 1] == '\r')
                IP[strlen(IP) - 1] = '\0';
            strcpy(info->Key, site);
            strcpy(info->Value, IP);

            InsTH(ah, (void *)info, cmpKey, ah->M); //inserez in tabela hash

        }
        else if (strcmp(functie, "find") == 0)
        {
            char *site = strtok(NULL, " "); //citesc key
            if (site[strlen(site) - 1] == '\n')
                site[strlen(site) - 1] = '\0';
            if (site[strlen(site) - 1] == '\r')
                site[strlen(site) - 1] = '\0';
            Tquery *info = malloc(sizeof(Tquery)); 
            info->Key = (char *)malloc((strlen(site) + 1) * sizeof(char));
            strcpy(info->Key, site);
            int findResult = find(ah, (void *)info, cmpKey, ah->M); //apelez functia
            if (findResult)
            {
                fprintf(fwrite, "%s", "True\n"); //daca a gasit, true, altfel, false
            }
            else
            {
                fprintf(fwrite, "%s", "False\n");
            }
        }
        else if (strcmp(functie, "print") == 0)
        {

            int i;
            for (i = 0; i < ah->M; i++) 
            {
                if (ah->v[i] == NULL)
                    continue;

                int cod = ah->fh(ah->v[i]->info, ah->M);
                TLGD aux = ah->v[i];
                
                fprintf(fwrite, "%d: %s ", cod, ((Tquery *)aux->info)->Value); // afisez indecele si value al capului
                for (aux = aux->urm; aux != ah->v[i]; aux = aux->urm)
                {
                  
                    fprintf(fwrite, "%s ", ((Tquery *)aux->info)->Value);
                }

                fprintf(fwrite, "\n");
            }
            
        }
        else if (strcmp(functie, "remove") == 0)
        {
            char *site = strtok(NULL, " ");
            if (site[strlen(site) - 1] == '\n')
                site[strlen(site) - 1] = '\0';
            if (site[strlen(site) - 1] == '\r')
                site[strlen(site) - 1] = '\0';
            Tquery *info = malloc(sizeof(Tquery));
            info->Key = (char *)malloc((strlen(site) + 1) * sizeof(char));
            strcpy(info->Key, site);
            Remove_key(ah, (void *)info, cmpKey, ah->M);
        }
        else if (strcmp(functie, "print_bucket") == 0)
        {
            char *cod = strtok(NULL, " "); //citesc intecele
            int cod1 = atoi(cod); //il fac de tip int
            print_bucket(ah, cod1, ah->M, fwrite);
        }
        else if (strcmp(functie, "get") == 0)
        {
            char *site = strtok(NULL, " ");
            if (site[strlen(site) - 1] == '\n')
                site[strlen(site) - 1] = '\0';
            if (site[strlen(site) - 1] == '\r')
                site[strlen(site) - 1] = '\0';
            Tquery *info = malloc(sizeof(Tquery));
            info->Key = (char *)malloc((strlen(site) + 1) * sizeof(char));
            strcpy(info->Key, site);
            get(ah, info, cmpKey, ah->M, fwrite);
        }
    }
    fclose(f);
    fclose(fwrite);
    DistrTH(&ah, DistrCelula);
    free(line);
 
}

int main( int argc, char *argv[] )
{

    TH *h = init_hash( atoi(argv[1]), codHash);
    citesteTabla(argv[2], argv[3], h);

    return 0;
}