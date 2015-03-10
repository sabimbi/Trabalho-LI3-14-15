#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CatalogoClientes.h"

/* Estrutura Interna*/
struct node
{
    char *codCliente;
    struct node*  left;
    struct node*  right;
    int      height;
};


struct cliente {
Clientes *lista;
};



static int pos;
/* Funçoes AVL */

static void dispose(Clientes t){
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        t=NULL;
        free( t );
    }
}
static Clientes find(char *codCliente,Clientes t ){
    if( t == NULL )
        return NULL;
    if( strcmp(codCliente,t->codCliente)<0)
        return find(codCliente,t->left );
    else if(strcmp(codCliente,t->codCliente)>0)
        return find( codCliente, t->right );
    else
        return t;
}
static Clientes find_min( Clientes t ){
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
static Clientes find_max(Clientes t ){
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
 
    return t;
}
static int height( Clientes n ){
    if( n == NULL )
        return -1;
    else
        return n->height;
}
static int max( int l, int r){
    return l > r ? l: r;
}
static Clientes single_rotate_with_left(Clientes k2 ){
   Clientes k1 = NULL;
 
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
 
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}
static Clientes single_rotate_with_right(Clientes k1 ){
    Clientes k2=NULL;
 
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
 
    return k2;  /* New root */
}
static Clientes double_rotate_with_left( Clientes k3 ){
    k3->left = single_rotate_with_right( k3->left );
    return single_rotate_with_left( k3 );
} 
static Clientes double_rotate_with_right(Clientes k1 ){
    k1->right = single_rotate_with_left( k1->right );
    return single_rotate_with_right( k1 );
} 
static Clientes insert(char *codCliente, Clientes t ){
    if( t == NULL ){
        t = (Clientes)malloc(sizeof(struct node));
        if( t == NULL ){
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else{
            t->codCliente = strdup(codCliente);
            t->height = 0;
            t->left = t->right = NULL;
        }
    }
    else if( strcmp(codCliente,t->codCliente)<0)
    {
        t->left = insert( codCliente, t->left );
        if( (height( t->left ) - height( t->right )) == 2 )
            if( strcmp(codCliente,t->left->codCliente )<0)
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( codCliente > t->codCliente ){
        t->right = insert(codCliente, t->right );
        if( (height( t->right ) - height( t->left )) == 2 )
            if( strcmp(codCliente,t->right->codCliente )>0)
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    /* Else X is in the tree already; we'll do nothing */ 
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}
static char* get(Clientes n){
    return n->codCliente;
}


int containsCliente(CClientes catalogo, char* codCliente){
    int id=codCliente[0]-'A';
    if(find(codCliente, catalogo->lista[id]))return 1;
    return 0;        
}
CClientes init_CatalogoCliente(){
    CClientes new;
int i;
    new=(CClientes) malloc(sizeof(struct cliente));
new->lista=(Clientes *) malloc(26*sizeof(Clientes));
for(i=0;i<26;i++)new->lista[i]=NULL;
    
return new;
}
CClientes insert_CatalogoCliente(CClientes catalogo, char* cod){   
    Clientes p;
    char c=cod[0];
    int id=(c-'A'); ;    
    
    p=catalogo->lista[id];
    p=insert(cod,p);
catalogo->lista[id]=p;
    return catalogo;
}
