/*Protótipos de funções e declarações de constantes*/

# include <stdio.h>


/*Constantes*/
# define TAM_OPCAO_MENU 30 

/*Declaração de estruturas*/
typedef struct menus_programa
{
    /*Quem será o pai do menu a ser criado*/
    int id_pai;

    /*O id do proprio menu*/
    int id;

    /*A ordem em que ele deve aparecer*/
    int ordem;

    /*O nome do menu*/
    char nome_menu[TAM_OPCAO_MENU];

    /*Tecla de atalho*/
    char letra_atalho;
}MENU;

/*Função responsável por ler os arquivos passados para realizar a verificação se foram abertos e lidos de modo correto*/
void Abre_arquivos_e_aloca_memoria(char *, char *);

/*Função responsável por criar meus menus de acordo com os arquivos passados como argumento*/
int Menu(char *, char *);

