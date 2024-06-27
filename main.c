/*Programa: Construcao de Menus
Descri‡Æo: Programa sera capaz de construir menus com base em 2 arquivos .txt, 1ø armazena a quantidade de menus e submenus que o programa criara
e o 2ø as cores dos respectivos menus e submenus, cores de texto e fundo. O usuario podera navegar nesses menus com as setas de direcao e tambem podera
escolher qualquer um por meio da tecla ENTER.

Programador: Hugo Josue Lema Das Neves
RGM: 47159 
Data da Ultima modificacao: 23/06/2024*/

/*Copiar e colar no prompt de comando, apertar ENTER para executar
gcc main.c -o main.exe console_v1.5.5.c conio_v3.2.4.c menu.c -Wall -pedantic -Wextra -Werror
*/

/*Executavel gerado apos a linha de compilacao acima, copie, cole no terminal do cmd e execute apertando ENTER
main.exe*/

# include <locale.h> /*setlocale()*/
# include <stdio.h> /*printf()*/
# include "conio_v3.2.4.h" /*clrscr(), texbackground(), texcolor()*/
# include "console_v1.5.5.h" /*setDimensaoJanela(), MaxDimensaJanela()*/
# include "funcoes.h" /*Menu()*/

/*Main principal do programa*/
int main(int argc, char *argv[])
{
    /*Variavel para dimensionar a janela*/
    COORD Janela;

    /*Variavel do id retornado pelo submenu*/
    int id_retorno;
    
    /*Silenciar warnings*/
    argc = argc;
    argv = argv;

    /*Mudanca de texto para nativo do sistema*/
    setlocale(LC_ALL, " ");

    /*Pega a dimensao maxima da janela e seta a janela atual*/
    Janela = MaxDimensaoJanela();
    setDimensaoJanela(Janela.X, Janela.Y);

    /*Limpa a tela*/
    clrscr();

    /*Chamada da funcao Menu() para a criacao dos menus*/
    id_retorno = Menu("menu.txt", "config.txt");
      
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    printf("\nID DO MENU: %d", id_retorno);

    return 0;
}