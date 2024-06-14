/*Prototipos de funcoes e declaracoes de constantes*/

# include <stdio.h>


/*Constantes*/
# define TAM_OPCAO_MENU 30 
# define TAM_BUFFER 60

/*Declaracao de estruturas*/
typedef struct menus_programa
{
    /*Quem sera o pai do menu a ser criado*/
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

typedef struct arquivos
{
    /*Contem meus arquivos em matrizes*/
    char **matriz_arquivo_menu;
    char *vetor_arquivo_cores;
    int conta_linhas_arquivo;

}ARQUIVOS;



/*Funcao responsavel por ler os arquivos passados para realizar a verificacao se foram abertos e lidos de modo correto*/
void Abre_arquivos_e_aloca_memoria(char *, char *, ARQUIVOS *);

/*Funcao responsavel por criar meus menus de acordo com os arquivos passados como argumento*/
int Menu(char *, char *);

/*Funcao para inicializar estrutura contendo os menus*/
void Inicializa_estruturas_menus(MENU **, ARQUIVOS *);

