#ifndef COMPRAS_H
#define	COMPRAS_H

typedef struct HashTable1 **Ht1;
typedef struct HashTable **Compras;
char ** getClientes(Compras compras,char *codProduto);
Compras init_Compras();
Compras insert_Compras(Compras table, char* codProduto, char* codCliente, int quant, int mes, char np);
void get_product_buyers(Compras table, char* codProduto, char*** codN, int* totalN, char*** codP, int* totalP);
char** get_frequent_buyers(Compras table, char** clientList);
#endif	/* COMPRAS_H */




