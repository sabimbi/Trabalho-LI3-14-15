#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CatalogoProdutos.h"
#include "Contabilidade.h"
#include "Compras.h"
#include "CatalogoClientes.h"
#define MAX 100

char *trim(char *linha) {
    int len = 0;
    while (isspace((linha[0]))) {
        (linha)++;
    }
    len = strlen(linha);
    while (isalnum(linha[len]) == 0) {
        linha[len] = '\0';
        len--;
    }


    return linha;
}

char** sep(CProdutos cat, CClientes c, char* line) {
    char** r = (char**) malloc(sizeof (char*)*6);
    int j=0;
    
    char *aux=strdup(line);
    
   aux=strtok(aux," ");
   while(aux ){
       
       r[j]=strdup(aux);
       j++;
    
   aux=strtok(NULL," ");
   
   }
   for(j=0;j<6;j++){
       r[j]=trim(r[j]);
   }
   if(containsProduto(cat,r[0])==1 && containsCliente(c,r[4])==1 && ((strcmp(r[3],"P")==0) || (strcmp(r[3],"N")==0))){
       return r;
   }else{
       
    return NULL;
}
}
double get_ExecutionTime(clock_t Begin, clock_t End) {
    double r = ((double) End - Begin) / CLOCKS_PER_SEC;
    return r;
}

void Menu() {
    printf("Bem vindo ao GESTHIPER\n");
    printf("1: Ler os 3 ficheiros (Produtos, Clientes e Compras)\n");
    printf("2: Determinar a lista e o total de produtos cujo código se inicia por uma dada letra(maiúscula)\n");
    printf("3: Dado um mês e um código de produto válidos, determinar e apresentar o número total de vendas em modo N e em modo P, e o total facturado com esse produto em tal mês\n");
    printf("4: Determinar a lista de códigos de produtos (e o seu número total), que ninguém comprou\n");
    printf("5: Dado um código de cliente, criar uma tabela com o número total de produtos comprados, mês a mês\n");
    printf("6: Determinar a lista de todos os códigos de clientes iniciados pela letra dada como parâmetro\n");
    printf("7: Dado um intervalo fechado de meses, determinar o total de compras registadas nesse intervalo e o total facturado\n");
    printf("8: Dado um código de produto, determinar os códigos (e número total) dos clientes que o compraram, distinguido entre compra N e compra P\n");
    printf("9:  Dado um código de cliente e um mês, determinar a lista de códigos de produtos que mais comprou, por ordem descendente\n");
    printf("10:  Determinar a lista de códigos de clientes que realizaram compras em todos osmeses do ano\n");
    printf("11: Criar um ficheiro em formato CSV, contendo para cada mês em que há compras registadas, o número de compras realizadas e onúmero total de clientes que realizaram tais compras\n");
    printf("12: Criar uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas\n");
    printf("13: Dado um código de cliente determinar quais os 3 produtos que mais comproudurante o ano\n");
    printf("14: Determinar o número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou\n");
    printf("15: Sair\n");
    printf("Opção: ");

}

void query3(char* codProduto, int mes) {
    int n = 0, p = 0;

    double r = 0.0;


    printf("Total de Produtos Vendidos em Normal: %d\n", n);
    printf("Total de Produtos Vendidos em Promoção: %d\n", p);
    printf("Total Facturado: %f\n", r);

}

void query4(Contabilidade cont) {
    char **prod = NULL;
    int n = 0, i = 0;
    Field g=NULL;

    n=get_products_not_bought(cont);

   
    



    printf("Nº de produtos que ninguem comprou: %d\n", n);








}

void query2() {
    char** list=NULL;
    int i = 0, count, e = 1;
    char s;
    while (e) {
        for (count = 0; list[i] && count < 10 && e; i++, count++) {
            printf("%s\n", list[i]);
        }
        e = 0;
        s = getc(stdin);
        if (s == '\n') e = 1;
        if (s == 27) e = 0;

    }
}

int main(int argc, char** argv) {
    char* line = NULL, *file1 = NULL, *file2 = NULL, *file3 = NULL;
    char** lineInfo;
    FILE* fp;
    int i = 0;
    CProdutos catalogop=NULL;
    CClientes catalogoc=NULL;
    Contabilidade contabilidade=NULL;
    Compras compras=NULL;
    
    clock_t begin, end;
    begin = clock();
    while (i != 15) {
        Menu();
        if (scanf("%d", &i) <= 0) {
            printf("Opção inválida!\n");
        }
        getchar();
        switch (i) {
            case 1:
            {
                catalogop = init_CatalogoProduto();

                catalogoc = init_CatalogoCliente();
                contabilidade = init_Contabilidade();
                compras = init_Compras();
                line = (char*) malloc(sizeof (char)*MAX);
                file1 = (char*) malloc(sizeof (char)*MAX);
                file2 = (char*) malloc(sizeof (char)*MAX);
                file3 = (char*) malloc(sizeof (char)*MAX);
                printf("Ficheiro de Produtos: ");
                if (fgets(file1, MAX, stdin)) printf("Ficheiro de Clientes: ");
                if (fgets(file2, MAX, stdin)) printf("Ficheiro de Compras: ");
                file3 = fgets(file3, MAX, stdin);

                file1 = trim(file1);
                file2 = trim(file2);
                file3 = trim(file3);

                if (strcmp(file1, "") == 0) {file1 = strdup("FichProdutos.txt");}
                if (strcmp(file2, "") == 0) {file2 = strdup("FichClientes.txt");}
                if (strcmp(file3, "") == 0) {file3 =strdup("Compras.txt");}


                fp = fopen(file1, "r");
                begin = clock();
                while ((line = fgets(line, MAX, fp))) {
                    line = trim(line);
                    contabilidade = insert_Contabilidade(contabilidade, line, 0, 'P', 0, 0.0);

                    catalogop = insert_CatalogoProduto(catalogop, line);
                }
                end = clock();

                printf("Tempo de Execução Catálogo de Produtos + Produtos Contabilidade: %fs \n", get_ExecutionTime(begin, end));
                fclose(fp);

                free(file1);
                free(line);
                line = (char*) malloc(sizeof (char)*MAX);
                begin = clock();
                fp = fopen(file2, "r");
                while ((line = fgets(line, MAX, fp))) {
                    line = trim(line);
                    catalogoc = insert_CatalogoCliente(catalogoc, line);
                }
                free(line);
                free(file2);
                line = (char*) malloc(sizeof (char)*MAX);
                end = clock();
                printf("Tempo de Execução Catálogo de Clientes: %fs \n", get_ExecutionTime(begin, end));
                fclose(fp);


                fp = fopen(file3, "r");
                while ((line = fgets(line, MAX, fp))) {
                    line = trim(line);
                    lineInfo=sep(catalogop, catalogoc, line);
                    if (lineInfo !=NULL) {
                        
                        contabilidade = insert_Contabilidade(contabilidade, lineInfo[0], atoi(lineInfo[5]), lineInfo[3][0], atoi(lineInfo[2]), atof(lineInfo[1]) * atoi(lineInfo[2]));
                        
                        compras=insert_Compras(compras, lineInfo[0], lineInfo[4], atoi(lineInfo[2]), atoi(lineInfo[5]));
                        
                        for (i = 0; i < 5; i++) {
                            free(lineInfo[i]);
                        }
                        free(lineInfo);
                    }
                }
                
                free(line);
                free(file3);
                end = clock();
                printf("Tempo de Execução de Compras+Contabilidade: %fs \n", get_ExecutionTime(begin, end));
                fclose(fp);
                getClientes(compras,"HO2918");
                break;
            }
            case 2:
            {
                query2();
                break;
            }
            case 3:
            {
                query3("HO2918", 6);
                break;
            }
            case 4:
            {
                if(contabilidade){query4(contabilidade);}
                break;
            }
        }
    }
    /*
     */
    return (EXIT_SUCCESS);
}



