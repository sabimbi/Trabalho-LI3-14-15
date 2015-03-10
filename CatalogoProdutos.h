#ifndef CATALOGOPRODUTOS_H
#define	CATALOGOPRODUTOS_H
typedef struct node* Produtos;
typedef struct produto * CProdutos ;

CProdutos init_CatalogoProduto();
CProdutos insert_CatalogoProduto(CProdutos catalogo, char* cod);
int containsProduto(CProdutos catalogo, char* codProduto);
#endif	/* CATALOGOPRODUTOS_H */

