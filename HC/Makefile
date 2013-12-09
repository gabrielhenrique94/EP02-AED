testaRB.exe: testa_rubro_negra.o arvore_rubro_negra.o
	gcc -g -o testaRB.exe testa_rubro_negra.o arvore_rubro_negra.o

testa_rubro_negra.o: arvore_rubro_negra.h testa_rubro_negra.c
	gcc -g -c testa_rubro_negra.c

arvore_rubro_negra.o: arvore_rubro_negra.h arvore_rubro_negra.c
	gcc -g -c arvore_rubro_negra.c

clean:
	rm -f *.o testaRB.exe

