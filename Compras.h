#ifndef COMPRAS_H
#define	COMPRAS_H

typedef struct HashTable1 **Ht1;
typedef struct HashTable **Compras;
char ** getClientes(Compras compras,char *codProduto);
Compras init_Compras();
Compras insert_Compras(Compras table, char* codProduto, char* codCliente, int quant, int mes);

#endif	/* COMPRAS_H */

