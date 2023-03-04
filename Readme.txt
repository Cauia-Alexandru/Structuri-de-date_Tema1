Cauia Alexandru 314CB
					Tema 1_SD
functii-hashtable.c-----------------------------------------------------------------
TH *init_hash(size_t M, TFHash fh):
--aloc spatiu pentru tabela h, apoi verificare.
--aloc spatiu pentru vectorii din h (h->v), de sizeof TLGD, care e marimea unui nod de lista 
dublu inlantuita, apoi verificare.

AfiTH(TH *ah, TF afiEL)
Cu primul for parcurg tabela. Pe p in fac capul fiecarei liste. Apoi afisez capul, pentru 
ca sa sar peste el. Si incep urmatorul for care incepe de la al 2lea elem pana la primul.
Am sarit peste primul, pentru ca e lista circulara si se va opri doar la primul elem.


int InsTH(TH *ah, void *ae, TFCmp f, int M)
verifica daca este ceva in lista, daca nu inserez.
verific mai intai capul daca e egal cu ae, si inserez. Apoi sar peste el si intr-un for verific
restul elementelor daca coincid, daca nu, inserez.


int Remove_key(TH *ah, void *ae, TFCmp f, int M)
Generez codul hash, apoi verific daca capul e nul, ca sa vad daca am de unde sterge.
Verific daca capul e singur si e egal cu ae care e dat ca parametru si il distrug.
Apoi daca trebuie sa elimin capul si mai sunt elemente dupa el; din mijloc; de la urma.

int get(TH *ah, void *ae, TFCmp f, int M, FILE* fwrite)
Verific capul aparte, ca sa pot sari peste el si verific daca Value coincide, si o afisez, daca nu -
NULL.

Functia "find" si "print" dupa acelasi principiu.

void print_bucket(TH *ah, int cod1, int M, FILE* fwrite)
Daca codul generat de functia hash ma opresc.
Cu primul for parcurg toata tabela si ma uit daca e goala lista cu codul respectiv si continui
pana la sfarsit.
Generez codul hash si il compar cu cel primit ca parametru, daca e bun printez capul, apoi
toata lista.

functii-liste_d.c--------------------------------------
int ins_ordonat(TLGD *aL, void *ae, TFCmp f)
Setez legaturile pentru elementul care trebuie inserat.
Aux e capul listei.
Daca lista e vida, curent devine capul listei, si setez legaturile catre el.
Apoi verific daca trebuie de inserat inaintea capului si stez legaturile, apoi mut capul 
la curent.
Altfel fac un loop, in care sar peste cap, apoi verific fiecare element daca e mai mare ca 
current, daca da, il pun inaintea lui aux(inserarea la mijloc). Verific pana cand aux e diferit de cap.
In acest caz ultimul element nu va fi verificat. Ca sa-l verific si pe el fac si ultimul caz(inserarea la urma).

tema1.c----------------------------------------------------------------------------
Functia hash->suma caracterelor din key modulo M(cate liste sunt).
Functia de comparare key-> verifica care e mai mare
Afisare query imi poate afisare info de tip Tquery.

Void citesteTabela
Deschid fisierele. In char* functie stochez primul cuvand citit care reprezinta functia
apoi verific cu strcmp care e primul cuvant stocat si fac ce trbuie pentru fiecare caz in parte.
Ca sa nu am \n la urma verific si il inlocuiesc cu \0
apoi urmeaza alocari de memorie si scrierea in fisier, apeluri de functii corespunzatoare.









 