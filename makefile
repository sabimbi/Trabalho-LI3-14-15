GESTHIPER:CatalogoProdutos.o CatalogoClientes.o Compras.o  Contabilidade.o  main.o
	gcc CatalogoProdutos.o CatalogoClientes.o Compras.o  Contabilidade.o  main.o  -g -O2 -ansi -pedantic -Wall -o GESTHIPER

CatalogoProdutos.o: CatalogoProdutos.c CatalogoProdutos.h
	gcc -g -O2 -ansi -pedantic -Wall -c CatalogoProdutos.c -o CatalogoProdutos.o

CatalogoClientes.o: CatalogoClientes.c CatalogoClientes.h
	gcc -g -O2 -ansi -pedantic -Wall -c CatalogoClientes.c -o CatalogoClientes.o

Compras.o: Compras.c Compras.h
	gcc -g -O2 -ansi -pedantic -Wall -c Compras.c -o Compras.o

Contabilidade.o: Contabilidade.c Contabilidade.h
	gcc -g -O2 -ansi -pedantic -Wall -c Contabilidade.c -o Contabilidade.o

main.o: main.c Contabilidade.h Compras.h CatalogoProdutos.h CatalogoClientes.h
	gcc -g -O2 -ansi -pedantic -Wall -c main.c -o main.o

clean:
	-rm -f *.o
	-rm -f linhas
	-rm -f GESTHIPER
