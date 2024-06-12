/*Programa: Construção de Menus
Descrição: Programa será capaz de construir menus com base em 2 arquivos .txt, 1° armazena a quantidade de menus e submenus que o programa criará
e o 2° as cores dos respectivos menus e submenus, cores de texto e fundo. O usuario poderá navegar nesses menus com as setas de direção e tambem poderá
escolher qualquer um por meio da tecla ENTER.

Programador: Hugo Josué Lema Das Neves
RGM: 47159 
Data da última modificação: 12/06/2024*/

/*Copiar e colar no prompt de comando, apertar ENTER para executar
gcc main.c -o main.exe console_v1.5.5.c conio_v3.2.4.c menu.c -Wall -pedantic -Wextra -Werror
*/

/*Executavel gerado após a linha de compilação acima, copie, cole no terminal do cmd e execute apertando ENTER
main.exe*/

# include <stdio.h>
# include "conio_v3.2.4.h"
# include "console_v1.5.5.h"
# include "funcoes.h"

/*Main principal do programa*/
int main(int argc, char *argv[])
{
    /*Criado uma matriz que conterá o nome dos arquivos .txt*/
    char *arquivos_na_matriz[50] = {"menu.txt", "config.txt"};

    /*Variavel do id retornado pelo submenu*/
    int id_retorno;
    
    /*Silenciar warnings*/
    argc = argc;
    argv = argv;

    /*Chamada da função Menu() para a criação dos menus*/
    id_retorno = Menu(arquivos_na_matriz[0], arquivos_na_matriz[1]);

    /*Impressão do id do menu retornado*/
    printf("%d", id_retorno);

    return 0;
}