build:
	gcc -g -o tema1 -Wall -std=c11 functii-hashtable.c functii-liste_d.c tema1.c 

.PHONY: clean
clean:
	rm tema1