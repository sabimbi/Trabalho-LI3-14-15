#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Compras.h"

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif
#define TABLE_SIZE 10001
#define TABLE_SIZE1 30

typedef struct HashTable1{
    char* codCliente;
    int quantidade;
    int mes[12];
    struct HashTable1* next;
}**Ht1;

typedef struct HashTable{
    char* codProduto;
    Ht1 info;
    struct HashTable* next;
}**Ht;


static Ht set_Prod(Ht table,char* codProduto, char* codCliente, int id, int id1, int quantidade, int mes){
    
    return table;
}

static uint32_t SuperFastHash (const char * data, int len) {
uint32_t hash = len, tmp;
int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

/* Funcões Públicas*/
/*

char** get_produtos_sem_compras(){
    char ** r = (char**) malloc (sizeof(char*));
    struct HashTable* aux;
    int i, j=0;
    for(i=0;i<TABLE_SIZE; i++){
        aux=table[i];    
        while(aux){
            if(table[i]->codProduto && !table[i]->info){
                r=strdup(table[i]->codProduto);
                j++;
                r = (char**) realloc (r, sizeof(char*)*(j+1));
            }
        aux=aux->next;
        }
    }
    return r;
}
int get_total_produtos_sem_compras(){
    int r=0, raux;
    int i, j, e=1;
    struct HashTable* aux;
    for (i=0; i<TABLE_SIZE; i++){
        aux=table[i];
        while(aux && e){
            if (aux->info) r++;
        aux=aux->next;
        }   
    }
    return r;
}
*/
char ** getClientes(Compras compras,char *codProduto){
unsigned id = (unsigned)SuperFastHash(codProduto, strlen(codProduto))%TABLE_SIZE;
int i,j;
struct HashTable*aux1=NULL;
struct HashTable1 *aux2=NULL;
char **clientes=NULL;
clientes=(char ** ) malloc(200000*sizeof(char *));
aux1=compras[id];
while(aux1){
if(strcmp(aux1->codProduto,codProduto)==0){
for(i=j=0;i<TABLE_SIZE1;i++){
	aux2=aux1->info[i];
	while(aux2){
		clientes[j]=strdup(aux2->codCliente);
		j++;
	aux2=aux2->next;
	}
}
break;
}else{
	aux1=aux1->next;

}
}
clientes[j]=NULL;
return clientes;
}

Compras init_Compras(){
    int i;
    Compras table;
    table = (struct HashTable**) malloc (sizeof(struct HashTable*)*TABLE_SIZE);
    for (i=0; i<TABLE_SIZE; i++){
        table[i]=NULL;
    }
    return table;
}
Compras insert_Compras(Compras table, char* codProduto, char* codCliente, int quant, int mes){
    unsigned id = (unsigned)SuperFastHash(codProduto, strlen(codProduto))%TABLE_SIZE;
    unsigned id1 = (unsigned)SuperFastHash(codCliente, strlen(codCliente))%TABLE_SIZE1;
    struct HashTable* aux=NULL;
    struct HashTable1* aux1=NULL;
    int found=0, found1=0, i=0;;
    if (!table[id]){
        table[id] = (struct HashTable*) malloc (sizeof(struct HashTable));
        table[id]->info=(struct HashTable1**) malloc (sizeof(struct HashTable1*)*TABLE_SIZE1);
        for(i=0; i<TABLE_SIZE1; i++){
            table[id]->info[i]=NULL;
        }
        table[id]->codProduto=strdup(codProduto);       
        table[id]->next=NULL;
    }else{
        aux=table[id];
        while(aux){
            if (strcmp(aux->codProduto, codProduto)==0){
                aux->codProduto=strdup(codProduto);
                found=1;
            }
            aux=aux->next;
        }
        if (!found){
            aux=NULL; aux = (struct HashTable*) malloc (sizeof(struct HashTable));
            table[id]->info=(struct HashTable1**) malloc (sizeof(struct HashTable1*)*TABLE_SIZE1);
            for(i=0; i<TABLE_SIZE1; i++){
                table[id]->info[i]=NULL;
            }
            aux->codProduto = strdup(codProduto);
            aux->next=table[id];
            table[id]=aux;
        }
    }
    if (!table[id]->info[id1]){
        table[id]->info[id1] = (struct HashTable1*) malloc (sizeof(struct HashTable1));
        table[id]->info[id1]->codCliente=strdup(codCliente);
        table[id]->info[id1]->mes[mes] = 1;
        table[id]->info[id1]->quantidade = quant;
        table[id]->info[id1]->next=NULL;
    }else{
        aux1=table[id]->info[id1];
        while(aux1){
            if (strcmp(aux1->codCliente, codCliente)==0){
                aux1->codCliente=strdup(codCliente);
                aux1->mes[mes]=1;
                aux1->quantidade+=quant;
                found=1;
            }
            aux1=aux1->next;
        }
        if(!found){
            aux1=NULL; aux1 = (struct HashTable1*) malloc (sizeof(struct HashTable1));
            aux1->codCliente= strdup(codCliente);
            aux1->mes[mes]=1;
            aux1->quantidade=quant;
            aux1->next=table[id]->info[id];
            table[id]->info[id]=aux1;
        }        
    } 
    return table;
}
