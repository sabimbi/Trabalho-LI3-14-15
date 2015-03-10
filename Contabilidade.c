#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include<math.h>
#include "Contabilidade.h"
#define TABLE_SIZE 50001

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

/* Estrutura interna */
 struct info {
    int quantidade;
    float facturacao;
};

struct conta{
    Info info;
};
struct HashTable {
    char* codProduto;
    Conta*arr;
    int height;
    struct HashTable* left, *right;
};

struct contabilidade {
    Field *produtos;
};


/* Variavel global da estutura */

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

    return hash % TABLE_SIZE;
}

/*Funções Públicas*/



static int height(Field n) {
    if (n == NULL)
        return -1;
    else
        return n->height;
}

static int max(int l, int r) {
    return l > r ? l : r;
}

static Field single_rotate_with_left(Field k2) {
    Field k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    return k1; /* new root */
}

static Field single_rotate_with_right(Field k1) {
    Field k2 = NULL;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;

    return k2; /* New root */
}

static Field double_rotate_with_left(Field k3) {
    k3->left = single_rotate_with_right(k3->left);
    return single_rotate_with_left(k3);
}

static Field double_rotate_with_right(Field k1) {
    k1->right = single_rotate_with_left(k1->right);
    return single_rotate_with_right(k1);
}

static Field insert(Field t, char* codProduto, int mes, char prom, int qnt, float fac) {

    int prom1 = 0, i = 0;
    if (prom == 'P') prom1 = 1;
    if (t == NULL) {
        t = (Field) malloc(sizeof (struct HashTable));
        if (t == NULL) {
            fprintf(stderr, "Out of memory!!! (insert)\n");
            exit(1);
        } else {
t->height = 0;
            t->codProduto = strdup(codProduto);
            t->left = NULL;
            t->right = NULL;
            t->arr = (Conta *) malloc(sizeof (Conta)*13);
            
                    for(i=0; i<13; i++){
                        t->arr[i].info=(Info) malloc(2*sizeof(struct info));
             t->arr[i].info[0].quantidade = 0;
                t->arr[i].info[0].quantidade = 0;
                t->arr[i].info[1].facturacao = 0.0;
                t->arr[i].info[1].facturacao = 0.0;
                    }

            
            


            t->height = max(height(t->left), height(t->right)) + 1;
            
        }
    }else if (strcmp(codProduto, t->codProduto) < 0) {
            t->left = insert(t->left, codProduto, mes, prom, qnt, fac);
            if (abs(height(t->right) - height(t->left)) > 1)
                if (strcmp(codProduto, t->left->codProduto) < 0)
                    t = single_rotate_with_left(t);
                else
                    t = double_rotate_with_left(t);
        } else if (strcmp(codProduto, t->codProduto) > 0) {
            t->right = insert(t->right, codProduto, mes, prom, qnt, fac);
            if (abs(height(t->right) - height(t->left)) > 1)
                if (strcmp(codProduto, t->right->codProduto) > 0)
                    t = single_rotate_with_right(t);
                else
                    t = double_rotate_with_right(t);
        } else {
            
                t->arr[mes].info[prom1].facturacao += fac;
                t->arr[mes].info[prom1].quantidade += qnt;
                
            
        }
        /* Else X is in the tree already; we'll do nothing */
        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }
static int get_products_tree(Field f){
    int i,r;
    if(f!=NULL){
        for(i=0,r=1;i<13 && r;i++){
            if((f->arr[i].info[0].quantidade)==0){
                if((f->arr[i].info[1].quantidade)==0){
                    
                }else{
                    r=0;
                }
            }else{
                r=0;
            }
            
        }
        if(r==1){
            return 1+get_products_tree(f->left)+get_products_tree(f->right);
        }else{
           return get_products_tree(f->left)+get_products_tree(f->right); 
        }
    }else{
        return 0;
    }

}
Field get_produto(Contabilidade table,char *codProduto){
    unsigned id = SuperFastHash(codProduto, strlen(codProduto));
    Field f=table->produtos[id];
    while(f!=NULL){
        if(strcmp(f->codProduto,codProduto)==0){

            

            return f;
        }else{
            if(strcmp(f->codProduto,codProduto)<0){
                f=f->left;
        }else{
                f=f->right;
        }
        }
    }
    return NULL;
    
}
int get_products_not_bought(Contabilidade table){
    int i=0,res=0;
    Field f=NULL;
    for(i=0;i<TABLE_SIZE;i++){
        f=table->produtos[i];
        res+=get_products_tree(f);
    }
    return res;
}
    Contabilidade insert_Contabilidade(Contabilidade table, char* codProduto, int mes, char prom, int qnt, float fac) {
        unsigned id = SuperFastHash(codProduto, strlen(codProduto));


        struct HashTable *f = NULL;
        f = table->produtos[id];
        f = insert(f, codProduto, mes, prom, qnt, fac);
        table->produtos[id] = f;
        
        return table;
        
    }

    Contabilidade init_Contabilidade() {

        int i;
        Contabilidade table;
        table = (Contabilidade) malloc(sizeof (struct contabilidade));
        table->produtos = (Field *) malloc(TABLE_SIZE * sizeof (struct HashTable *));
        for (i = 0; i < TABLE_SIZE; i++) {
            table->produtos[i] = NULL;
        }
        return table;
    }


