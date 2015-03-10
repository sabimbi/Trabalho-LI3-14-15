#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CatalogoProdutos.h"

/* Estrutura Interna*/
struct node
{
    char *codProduto;
    struct node*  left;
    struct node*  right;
    int      height;
};


struct produto {
Produtos *lista;
};



static int pos;
/* Funçoes AVL */
char *strdup (char *s) {
    char *d = malloc (strlen (s) + 1);   
    if (d == NULL) return NULL;          
    strcpy (d,s);                       
    return d;                            
}
static void dispose(Produtos t){
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        t=NULL;
        free( t );
    }
}
static Produtos find(char *codProduto,Produtos t ){
    if( t == NULL )
        return NULL;
    if( strcmp(codProduto,t->codProduto)<0)
        return find(codProduto,t->left );
    else if(strcmp(codProduto,t->codProduto)>0)
        return find( codProduto, t->right );
    else
        return t;
}
static Produtos find_min( Produtos t ){
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
static Produtos find_max(Produtos t ){
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
 
    return t;
}
static int height( Produtos n ){
    if( n == NULL )
        return -1;
    else
        return n->height;
}
static int max( int l, int r){
    return l > r ? l: r;
}
static Produtos single_rotate_with_left(Produtos k2 ){
   Produtos k1 = NULL;
 
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
 
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}
static struct node* single_rotate_with_right(Produtos k1 ){
    Produtos k2=NULL;
 
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
 
    return k2;  /* New root */
}
static Produtos double_rotate_with_left( Produtos k3 ){
    k3->left = single_rotate_with_right( k3->left );
    return single_rotate_with_left( k3 );
} 
static Produtos double_rotate_with_right(Produtos k1 ){
    k1->right = single_rotate_with_left( k1->right );
    return single_rotate_with_right( k1 );
} 
static Produtos insert(char *codProduto, Produtos t ){
    if( t == NULL ){
        t = (Produtos)malloc(sizeof(struct node));
        if( t == NULL ){
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else{
            t->codProduto = strdup(codProduto);
            t->height = 0;
            t->left = t->right = NULL;
        }
    }
    else if( strcmp(codProduto,t->codProduto)<0)
    {
        t->left = insert( codProduto, t->left );
        if( (height( t->left ) - height( t->right )) == 2 )
            if( strcmp(codProduto,t->left->codProduto )<0)
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( codProduto > t->codProduto ){
        t->right = insert(codProduto, t->right );
        if( (height( t->right ) - height( t->left )) == 2 )
            if( strcmp(codProduto,t->right->codProduto )>0)
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    /* Else X is in the tree already; we'll do nothing */ 
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}
static char* get(Produtos n){
    return n->codProduto;
}


int containsProduto(CProdutos catalogo, char* codProduto){
    int id=codProduto[0]-'A';
    if(find(codProduto, catalogo->lista[id]))return 1;
    return 0;        
}
CProdutos init_CatalogoProduto(){
    CProdutos new;
int i;
    new=(CProdutos) malloc(sizeof(struct produto));
new->lista=(Produtos *) malloc(26*sizeof(Produtos));
for(i=0;i<26;i++)new->lista[i]=NULL;
  
return new;
}
CProdutos insert_CatalogoProduto(CProdutos catalogo, char* cod){   
    Produtos p;
    char c=cod[0];
    int id=(c-'A'); ;    
    
    p=catalogo->lista[id];
    p=insert(cod,p);
catalogo->lista[id]=p;
    return catalogo;
}
