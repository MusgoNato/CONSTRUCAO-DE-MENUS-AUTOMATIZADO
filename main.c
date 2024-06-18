/*Programa: Construcao de Menus
Descri‡Æo: Programa sera capaz de construir menus com base em 2 arquivos .txt, 1ø armazena a quantidade de menus e submenus que o programa criara
e o 2ø as cores dos respectivos menus e submenus, cores de texto e fundo. O usuario podera navegar nesses menus com as setas de direcao e tambem podera
escolher qualquer um por meio da tecla ENTER.

Programador: Hugo Josue Lema Das Neves
RGM: 47159 
Data da Ultima modificacao: 12/06/2024*/

/*Copiar e colar no prompt de comando, apertar ENTER para executar
gcc main.c -o main.exe console_v1.5.5.c conio_v3.2.4.c menu.c -Wall -pedantic -Wextra -Werror
*/

/*Executavel gerado apos a linha de compilacao acima, copie, cole no terminal do cmd e execute apertando ENTER
main.exe*/

# include <stdio.h>
# include <stdlib.h>
# include <locale.h>
# include "conio_v3.2.4.h"
# include "console_v1.5.5.h"
# include "funcoes.h"

/*Main principal do programa*/
int main(int argc, char *argv[])
{
    /*Variavel do id retornado pelo submenu*/
    int id_retorno;
    
    /*Silenciar warnings*/
    argc = argc;
    argv = argv;

    setlocale(LC_ALL, " ");

    clrscr();
 
    /*Chamada da funcao Menu() para a criacao dos menus*/
    id_retorno = Menu("menu.txt", "config.txt");
    printf("Main : %d", id_retorno);

    
    return 0;
}