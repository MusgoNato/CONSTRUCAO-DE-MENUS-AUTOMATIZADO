/*Lógica das funções utilizadas no decorrer do programa*/

/*Inclusão de bibliotecas*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "funcoes.h"

/*Função resonsável por automatizar a criação de menus*/
int Menu(char *arquivo_menus, char *arquivo_cores)
{
    FILE *retornos;

    /*Verificação da abertura dos arquivos iniciais*/
    retornos = fopen(arquivo_menus, "r");
    if(retornos != NULL)
    {
        printf("deu certo\n");
    }
    retornos = fopen(arquivo_cores, "r");
    if(retornos != NULL)
    {
        printf("Deu certo 2!\n");
    }
    return 1;
}