#ifndef CATALOGOCLIENTES_H
#define	CATALOGOCLIENTES_H
typedef struct node* Clientes;
typedef struct cliente * CClientes ;

CClientes init_CatalogoCliente();
CClientes insert_CatalogoCliente(CClientes catalogo, char* cod);
int containsCliente(CClientes catalogo, char* codCliente);


#endif	/* CATALOGOCLIENTES_H */

