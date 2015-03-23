#include <stdio.h>
#include <stdlib.h>
#include "CatalogoClientes.h"
#include <string.h>
struct cliente{
    char* data;
    struct cliente*  left;
    struct cliente*  right;
    int      height;
};

struct array{
    cliente* t;
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
static cliente* find(char *codCliente,cliente* t ){
    if( t == NULL )
        return NULL;
    if( strcmp(codCliente,t->data)<0)
        return find(codCliente,t->left );
    else if(strcmp(codCliente,t->data)>0)
        return find( codCliente, t->right );
    else
        return t;
}
static void dispose(cliente* t)
{
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        free( t );
    }
}
 
/*
    find a specific cliente's key in the tree
*/
/*
cliente* find(char* data, cliente* t )
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
    find minimum cliente's key
*/
static cliente* find_min( cliente* t )
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
 
/*
    find maximum cliente's key
*/
static cliente* find_max( cliente* t )
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
 
    return t;
}
 
/*
    get the height of a cliente
*/
static int height( cliente* n )
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
    perform a rotation between a k2 cliente and its left child
 
    note: call single_rotate_with_left only if k2 cliente has a left child
*/
 
static cliente* single_rotate_with_left( cliente* k2 )
{
    cliente* k1 = NULL;
 
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
 
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}
 
/*
    perform a rotation between a cliente (k1) and its right child
 
    note: call single_rotate_with_right only if
    the k1 cliente has a right child
*/
 
static cliente* single_rotate_with_right( cliente* k1 )
{
    cliente* k2;
 
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
 
    return k2;  /* New root */
}
 
/*
 
    perform the left-right double rotation,
 
    note: call double_rotate_with_left only if k3 cliente has
    a left child and k3's left child has a right child
*/
 
static cliente* double_rotate_with_left( cliente* k3 )
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
 
 
 
static cliente* double_rotate_with_right( cliente* k1 )
{
    /* rotate between K3 and k2 */
    k1->right = single_rotate_with_left( k1->right );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_right( k1 );
}
 
/*
    insert a new cliente into the tree
*/
static cliente* insert(char* data, cliente* t )
{
    int bal=0;
    if( t == NULL )
    {
        /* Create and return a one-cliente tree */
        t = (cliente*)malloc(sizeof(cliente));
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
    remove a cliente in the tree
*/

/*
static cliente* delete( int e, cliente* t )
{
    printf( "Sorry; Delete is unimplemented; %d remains\n", e );
    return t;
}
*/
 
/*
    data data of a cliente
*/
/*
static int get(cliente* n)
{
    return n->data;
}
 
*/
/*
    Recursively display AVL tree or subtree
*/
/*
static void display_avl(cliente* t)
{
    if (t == NULL)
        return;
    printf("%d",t->data);
 
    if(t->left != NULL)
        printf("(L:%d)",t->left->data);
    if(t->right != NULL)
        printf("(R:%d)",t->right->data);
    printf("\n");
 
    display_avl(t->left);
    display_avl(t->right);
}
*/

static char** run_inorder(cliente* t, char** strArr){
    
    
    if(t->left!=NULL){
        strArr=run_inorder(t->left, strArr);
    }   
    strArr[count]=strdup2(t->data);
    
    
    count++;
    strArr = (char**) realloc (strArr,sizeof(char*)*(count+1));
    
    if(t->right!=NULL){
        strArr=run_inorder(t->right, strArr);
    }
    return strArr;
}
int containsCliente(CClientes catalogo, char* codCliente){
    int id=codCliente[0]-'A';
    
    if(find(codCliente, catalogo[id].t))return 1;
    return 0;        
}
char** get_clientList(CClientes cat, char letter){
    char **strArr=NULL;
    cliente *c=NULL;
    count=0;
    
    c=cat[letter-'A'].t;
    if(c!=NULL){
    strArr= (char**) malloc (sizeof(char*));
    strArr=run_inorder(c, strArr);
    strArr[count]=NULL;
    
    return strArr;}
    return NULL;
}
char **get_all_clients(CClientes cat){
    int i,j,size,n;
    char letter='0';
    char **arr,**clients;
    arr=NULL;
    clients=NULL;
    clients=(char **) malloc(20000*sizeof(char*));
    n=0;
    for(i=n=0;i<26;i++){
        
        letter='A'+i;
        
        arr=NULL;
        arr=get_clientList(cat,letter);
        if(arr){
        size=0;
        for(j=0;arr[j];j++,n++){
            clients[n]=strdup2(arr[j]);
            
            
        }
        size=j;
        
            

        for(j=0;j<size;j++){
            
            free(arr[j]);}
        free(arr);
        
        
        }
    }
    clients[n]=NULL;
    
    return clients;
}
CClientes init_CatalogoCliente(){
    CClientes new;
    int i;
    new=(CClientes) malloc(26*sizeof(struct array));
    for(i=0;i<26;i++)new[i].t=NULL;
    return new;
}
CClientes insert_CatalogoCliente(CClientes catalogo, char* cod){   
    char c=cod[0];
    int id=(c-'A'); ;        
    catalogo[id].t=insert(cod, catalogo[id].t);
    return catalogo;
}
