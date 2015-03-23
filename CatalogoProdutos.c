#include <stdio.h>
#include <stdlib.h>
#include "CatalogoProdutos.h"
#include <string.h>
struct produto{
    char* data;
    struct produto*  left;
    struct produto*  right;
    int      height;
};

struct array{
    produto* t;
};

/*
    remove all nodes of an AVL tree
*/
static int count;
static char *strdup2(char *str){
int len=0,i=0;
char *aux=NULL;
len=strlen(str)+1;
aux=malloc(len*sizeof(char));
for(i=0;str[i]!='\0';i++){
    aux[i]=str[i];
}
aux[i]='\0';

return aux;
}
static produto* find(char *codProduto,produto* t ){
    if( t == NULL )
        return NULL;
    if( strcmp(codProduto,t->data)<0)
        return find(codProduto,t->left );
    else if(strcmp(codProduto,t->data)>0)
        return find( codProduto, t->right );
    else
        return t;
}
static void dispose(produto* t)
{
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        free( t );
    }
}
 
/*
    find a specific produto's key in the tree
*/
/*
produto* find(char* data, produto* t )
{
    if( t == NULL )
        return NULL;
    if( e < t->data )
        return find( e, t->left );
    else if( e > t->data )
        return find( e, t->right );
    else
        return t;
}
*/
 
/*
    find minimum produto's key
*/
static produto* find_min( produto* t )
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
 
/*
    find maximum produto's key
*/
static produto* find_max( produto* t )
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
 
    return t;
}
 
/*
    get the height of a produto
*/
static int height( produto* n )
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}
 
/*
    get maximum value of two integers
*/
static int max( int l, int r)
{
    return l > r ? l: r;
}
 
/*
    perform a rotation between a k2 produto and its left child
 
    note: call single_rotate_with_left only if k2 produto has a left child
*/
 
static produto* single_rotate_with_left( produto* k2 )
{
    produto* k1 = NULL;
 
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
 
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}
 
/*
    perform a rotation between a produto(k1) and its right child
 
    note: call single_rotate_with_right only if
    the k1 produto has a right child
*/
 
static produto* single_rotate_with_right( produto* k1 )
{
    produto* k2;
 
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
 
    return k2;  /* New root */
}
 
/*
 
    perform the left-right double rotation,
 
    note: call double_rotate_with_left only if k3 produto has
    a left child and k3's left child has a right child
*/
 
static produto* double_rotate_with_left( produto* k3 )
{
    /* Rotate between k1 and k2 */
    k3->left = single_rotate_with_right( k3->left );
 
    /* Rotate between K3 and k2 */
    return single_rotate_with_left( k3 );
}
 
/*
    perform the right-left double rotation
 
   notes: call double_rotate_with_right only if k1 has a
   right child and k1's right child has a left child
*/
 
 
 
static produto* double_rotate_with_right( produto* k1 )
{
    /* rotate between K3 and k2 */
    k1->right = single_rotate_with_left( k1->right );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_right( k1 );
}
 
/*
    insert a new produto into the tree
*/
static produto* insert(char* data, produto* t )
{
    int bal=0;
    if( t == NULL )
    {
        /* Create and return a one-produto tree */
        t = (produto*)malloc(sizeof(produto));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else
        {
            t->data = strdup2(data);
            t->height = 0;
            t->left = t->right = NULL;
        }
    }
    else if(strcmp(data, t->data)<0 )
    {
        t->left = insert( data, t->left );
        bal=((height( t->left )) - (height( t->right )));
        if( bal == 2 )
            if( strcmp(data, t->left->data)<0 )
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( strcmp(data, t->data)>0)
    {
        t->right = insert( data, t->right );
        bal=((height( t->left )) - (height( t->right )));
        if( bal == 2 )
            if(strcmp(data, t->right->data)>0)
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    /* Else X is in the tree already; we'll do nothing */
 
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}
 
/*
    remove a produto in the tree
*/
static produto* delete( int e, produto* t )
{
    printf( "Sorry; Delete is unimplemented; %d remains\n", e );
    return t;
}
 
/*
    data data of a produto
*/
/*
static int get(produto* n)
{
    return n->data;
}
*/
 
/*
    Recursively display AVL tree or subtree
*/
/*
static void display_avl(produto* t)
{
    if (t == NULL)
        return;
    printf("%s\n",t->data);
 
    if(t->left != NULL)
        printf("(L:%s)",t->left->data);
    if(t->right != NULL)
        printf("(R:%s)",t->right->data);
    printf("\n");
 
    display_avl(t->left);
    display_avl(t->right);
}
*/

static char** run_inorder(produto* t, char** strArr){
    
    char* r = (char*) malloc (sizeof(char)*7);
    if(t->left){
        strArr=run_inorder(t->left, strArr);
    }   
    strArr[count]=strdup2(t->data);
    count++;
    strArr = (char**) realloc (strArr,sizeof(char*)*(count+1));
    
    if(t->right){
        strArr=run_inorder(t->right, strArr);
    }
    return strArr;
}
int containsProduto(CProdutos catalogo, char* codProduto){
    int id=codProduto[0]-'A';
    if(find(codProduto, catalogo[id].t))return 1;
    return 0;        
}
char** get_productList(CProdutos cat,char** strArr, char letter){
    strArr= (char**) malloc (sizeof(char*));
    count=0;
    strArr=run_inorder(cat[letter-'A'].t, strArr);
    strArr[count]=NULL;
    return strArr;
}
/*
void printprod(CProdutos c){
int i;
for(i=0;i<26;i++){
display_avl(c[i].t);
}
}
*/
CProdutos init_CatalogoProduto(){
    CProdutos new;
    int i;
    new=(CProdutos) malloc(26*sizeof(struct array));
    for(i=0;i<26;i++)new[i].t=NULL;
    return new;
}
CProdutos insert_CatalogoProduto(CProdutos catalogo, char* cod){   
    char c=cod[0];
    int id=(c-'A'); ;        
    catalogo[id].t=insert(cod, catalogo[id].t);
    return catalogo;
}
