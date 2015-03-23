#ifndef CATALOGOCLIENTES_H
#define	CATALOGOCLIENTES_H

typedef struct cliente cliente;
typedef struct array* CClientes;

CClientes init_CatalogoCliente();
CClientes insert_CatalogoCliente(CClientes catalogo, char* cod);
char** get_clientList(CClientes cat, char letter);
char **get_all_clients(CClientes cat);
int containsCliente(CClientes catalogo, char* codCliente);

#endif	/* CATALOGOCLIENTES_H */

