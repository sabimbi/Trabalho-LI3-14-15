#ifndef CATALOGOPRODUTOS_H
#define	CATALOGOPRODUTOS_H
typedef struct produto produto;
typedef struct array* CProdutos;

CProdutos init_CatalogoProduto();
CProdutos insert_CatalogoProduto(CProdutos catalogo, char* cod);
char** get_productList(CProdutos cat,char** strArr, char letter);
int containsProduto(CProdutos catalogo, char* codProduto);
void printprod(CProdutos c);
#endif	/* CATALOGOPRODUTOS_H */

