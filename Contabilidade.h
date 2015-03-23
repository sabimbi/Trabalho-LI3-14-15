#ifndef CONTABILIDADE_H
#define	CONTABILIDADE_H

/*Matriz Anos-Tipo de Venda*/
typedef struct Array **Info;
/*Array de Apontadores*/
typedef struct HashTable **Contabilidade, *Field;


Contabilidade init_Contabilidade();
Contabilidade insert_Contabilidade(Contabilidade table, char* codProduto, int mes, char prom, int qnt, float fac);
void get_NP_byMonth(Contabilidade cont, char* codProduto, int mes, int* totN, float* facN, int* totP, float*facP);
char **get_codProducts_with_noBuyers(Contabilidade table);
void get_total_byMonths(Contabilidade table, int mes1, int mes2,int* totC, float* totF);

#endif	/* CONTABILIDADE_H */

