/*Programa: Construcao de Menus
Descri‡Æo: O programa tera 2 arquivos de entrada, um sendo o arquivo contendo os menus que serao impressos, outro sendo as configuracoes referente aos menus
no primeiro arquivo, o programa sera capaz de criar uma quantidade infinita de menus. O usuario tera podera navegar nas opcoes de um menu ou submenu usando as setas direcionais,
setas a direita e esquerda somente podera navegar naqueles menus que sao pais principais, exibidos na horizontal do programa, e as setas baixo e cima nos submenus
abertos, exibidos na vertical abaixo do menu pai principal. O usuario podera pressionar ENTER em uma opcao para abri seu submenu ou ESC para voltar ao menu anterior. no programa 
as letras de atalho coloridas em cada opcao de acordo com a cor no arquivo passado como segundo parametro para a funcao, serao letras de atalho onde o usuario podera pressionar a tecla
ALT + 'letra de atalho de alguma opcao', assim o usuario entrara em algum submenu atraves de atalhos caso haja algum.

NOTA :
1. O programa suporta a opcao ate no maximo 30 caracteres dentro das aspas duplas,
caso adicione uma opcao com mais de 30 caracteres nao funcionara corretamente.
2. Caso no arquivo .txt haja menus comecando na ordem acima de 1, o programa nao funcionara corretamente.
3. Caso o arquivo .txt haja letras de atalhos nao encontradas na opcao escrita dentro do ", o programa nao funcionara corretamente.


Programador: Hugo Josue Lema Das Neves
RGM: 47159 
Data da Ultima modificacao: 29/06/2024*/

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

    /*Retorna a cor original do cmd*/
    textcolor(LIGHTGRAY);
    textbackground(BLACK);

    /*imprime o ultimo id*/
    printf("\nID DO MENU: %d", id_retorno);

    return 0;
}