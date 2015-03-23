#include<stdio.h>
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
#define TABLE_SIZE 150001
#define TABLE_SIZE1 1000

struct HashTable1 {
    char* codCliente;
    int mes[13];
    
    int np[2];
    struct HashTable1* next;
};

struct HashTable {
    char* codProduto;
    Ht1 info;
    int mes[13];
    struct HashTable* next;
};

static char *strdup2(char *str) {
    int len = 0, i = 0;
    char *aux = NULL;
    len = strlen(str) + 1;
    aux = malloc(len * sizeof (char));
    for (i = 0; str[i] != '\0'; i++) {
        aux[i] = str[i];
    }
    aux[i] = '\0';

    return aux;
}

/*Funçoes Clientes*/
static uint32_t SuperFastHash(const char * data, int len) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (; len > 0; len--) {
        hash += get16bits(data);
        tmp = (get16bits(data + 2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        data += 2 * sizeof (uint16_t);
        hash += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits(data);
            hash ^= hash << 16;
            hash ^= ((signed char) data[sizeof (uint16_t)]) << 18;
            hash += hash >> 11;
            break;
        case 2: hash += get16bits(data);
            hash ^= hash << 11;
            hash += hash >> 17;
            break;
        case 1: hash += (signed char) *data;
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

/*Funçoes Publicas*/

char** get_frequent_buyers(Compras table, char** clientList) {
    char** r = (char**) malloc(sizeof (char*));
    unsigned id = 0;
    int clic, i, j, k, e = 1, rcount = 0, op;
    int comp[13];
    struct HashTable* prod = NULL;
    struct HashTable1* cli = NULL;
    for (clic = 0; clientList[clic]; clic++) {
        id = (unsigned) SuperFastHash(clientList[clic], strlen(clientList[clic])) % TABLE_SIZE1;
        for (i = 1; i < 13; i++)comp[i] = 0;
        for (i = 0; i < TABLE_SIZE; i++) {
            prod = table[i];
            if (prod != NULL) {
                while (prod) {
                    cli = prod->info[id];
                    e=1;
                    while (cli != NULL && e) {
                        if (strcmp(cli->codCliente, clientList[clic]) == 0) {
                            for (j = 1; j < 13; j++) {
                                comp[j] += cli->mes[j];
                            }

                            e = 0;
                        }
                        cli = cli->next;
                    }
                    prod = prod->next;
                }
            }

        }
        for(i=e=1;i<13&& e ;i++){
            if(comp[i]==0)e=0;
        }
         if(e==1){
        for (k = op = 0; k < rcount && op; k++) {
            if (strcmp(r[k], clientList[clic]) == 0) op = 1;
        }
        if (op == 0) {
            
            r[rcount] = strdup2(clientList[clic]);

            rcount++;
            r = (char**) realloc(r, sizeof (char*)*(rcount + 1));
        }
    } 


}

r[rcount] = NULL;
return r;
}

void get_product_buyers(Compras table, char* codProduto, char*** codN, int* totalN, char*** codP, int* totalP) {
    char** cN = (char**) malloc(sizeof (char*));
    char** cP = (char**) malloc(sizeof (char*));
    unsigned id = (unsigned) SuperFastHash(codProduto, strlen(codProduto)) % TABLE_SIZE;
    int i, ntN = 0, ntP = 0, cNcount = 0, cPcount = 0;
    struct HashTable* prod = NULL;
    
    struct HashTable1* aux = NULL;
    prod = table[id];
    while (prod) {
        if (strcmp(prod->codProduto, codProduto) == 0) {
            break;
        } else {
            prod = prod->next;
        }
    }
    for (i = 0; i < TABLE_SIZE1; i++) {
        if (prod != NULL) {
            aux = prod->info[i];
            if (aux != NULL) {

                while (aux) {
                    if (aux->np[0] == 1) {
                        cN[cNcount] = strdup2(aux->codCliente);

                        cNcount++;
                        cN = (char**) realloc(cN, sizeof (char*)*(cNcount));
                        ntN += aux->np[0];
                    }
                    if (aux->np[1] == 1) {
                        cP[cPcount] = strdup2(aux->codCliente);

                        cPcount++;
                        cP = (char**) realloc(cP, sizeof (char*)*(cPcount));
                        ntP += aux->np[1];
                    }

                    aux = aux->next;
                }
            }
        }
    }
    cN[cNcount] = NULL;
    cP[cPcount] = NULL;
    *codN = cN;
    *totalN = ntN;
    *codP = cP;
    *totalP = ntP;
}

Compras init_Compras() {
    int i;
    Compras table;
    table = (struct HashTable**) malloc(sizeof (struct HashTable*)*TABLE_SIZE);
    for (i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
    return table;
}

static Ht1 insert_ht(Ht1 table, char* codCliente, int quant, int mes, int np) {
    unsigned id = (unsigned) SuperFastHash(codCliente, strlen(codCliente)) % TABLE_SIZE1;
    struct HashTable1* aux = NULL;
    int found = 0, i;
    if (!table[id]) {
        i = 0;
        aux = (struct HashTable1*) malloc(sizeof (struct HashTable1));
        aux->codCliente = strdup2(codCliente);
        while (i < 13) {
            aux->mes[i] = 0;
            i++;
        }
        aux->mes[mes] += quant;
        aux->np[0] = 0;
        aux->np[1] = 0;
        aux->np[np] = 1;
        aux->next = NULL;
        table[id] = aux;
        return table;
    } else {
        aux = table[id];
        while (aux) {
            if (strcmp(aux->codCliente, codCliente) == 0) {

                aux->mes[mes] += quant;
                aux->np[np] = 1;
                found = 1;
            }
            aux = aux->next;
        }
        if (!found) {
            i = 0;
            aux = NULL;
            aux = (struct HashTable1*) malloc(sizeof (struct HashTable1));
            aux->codCliente = strdup2(codCliente);

            while (i < 13) {
                aux->mes[i] = 0;
                i++;
            }
            aux->mes[mes] += quant;
            aux->np[0] = 0;
            aux->np[1] = 0;
            aux->np[np] = 1;
            aux->next = table[id];

            table[id] = aux;

        }
    }
    return table;
}

Compras insert_Compras(Compras table, char* codProduto, char* codCliente, int quant, int mes, char np) {
    unsigned id = (unsigned) SuperFastHash(codProduto, strlen(codProduto)) % TABLE_SIZE;
    struct HashTable* aux = NULL;
    int found = 0, i = 0, npa = 0;
    if (np == 'P') npa = 1;
    if (!table[id]) {
        table[id] = (struct HashTable*) malloc(sizeof (struct HashTable));
        table[id]->info = (struct HashTable1**) malloc(sizeof (struct HashTable1*)*TABLE_SIZE1);
        table[id]->codProduto = strdup2(codProduto);

        for (i = 0; i < TABLE_SIZE1; i++) {
            table[id]->info[i] = NULL;
        }
        table[id]->info = insert_ht(table[id]->info, codCliente, quant, mes, npa);
        for (i = 0; i < 13; i++) {
            table[id]->mes[i] = 0;
        }
        table[id]->mes[mes]++;
        table[id]->next = NULL;

        return table;
    } else {

        aux = table[id];

        while (aux) {
            if (strcmp(aux->codProduto, codProduto) == 0) {

                aux->info = insert_ht(aux->info, codCliente, quant, mes, npa);
                aux->mes[mes]++;
                found = 1;
                break;
            }
            aux = aux->next;
        }
        if (!found) {
            aux = NULL;
            aux = (struct HashTable*) malloc(sizeof (struct HashTable));
            aux->info = (struct HashTable1**) malloc(sizeof (struct HashTable1*)*TABLE_SIZE1);
            for (i = 0; i < TABLE_SIZE1; i++) {
                aux->info[i] = NULL;
            }
            for (i = 0; i < 13; i++) {
                aux->mes[i] = 0;
            }
            aux->mes[mes]++;
            aux->info = insert_ht(aux->info, codCliente, quant, mes, npa);
            aux->codProduto = strdup2(codProduto);
            aux->next = table[id];
            table[id] = aux;
        }
    }
    return table;
}

