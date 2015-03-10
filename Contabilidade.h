#ifndef CONTABILIDADE_H
#define	CONTABILIDADE_H

/*Matriz Anos-Tipo de Venda*/

/*Array de Apontadores*/
typedef struct HashTable *Field;
typedef struct contabilidade *Contabilidade;
typedef struct conta Conta;
typedef struct info *Info;
Contabilidade init_Contabilidade();
int get_products_not_bought(Contabilidade table);
Field get_produto(Contabilidade table,char *codProduto);
Contabilidade insert_Contabilidade(Contabilidade table, char* codProduto, int mes, char prom, int qnt, float fac);


#endif	/* CONTABILIDADE_H */

