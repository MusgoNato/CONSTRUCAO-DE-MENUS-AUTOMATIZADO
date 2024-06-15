/*Prototipos de funcoes e declaracoes de constantes*/

# include <stdio.h>


/*Constantes*/
# define TAM_OPCAO_MENU 35
# define TAM_BUFFER 60
# define TAM_LINHA_CONFIG 100

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
    char vetor_arquivo_cores[TAM_LINHA_CONFIG];
    int conta_linhas_arquivo;

}ARQUIVOS;

typedef struct config
{
    /*Representa a cor de fundo da barra do menu principal*/
    int cor1;

    /*Representa a cor das opcoes quando nao estao selecionadas*/
    int cor2;

    /*Representa a cor das opcoes selecionadas*/
    int cor3;

    /*Representa a cor do fundo das opcoes do menu principal quando estao selecionadas*/
    int cor4;

    /*Representa a cor da letra de atalho das opcoes quando nao estao selecionadas*/
    int cor5;

    /*Representa a cor da letra de atalho quando selecionada*/
    int cor6;

    /*Representa a cor de fundo das janelas dos submenus*/
    int cor7;

    /*Representa a cor das opcoes dos submenus, quando nao estao selecionadas*/
    int cor8;

    /*Representa a cor das opcoes dos submenus quando estao selecionadas*/
    int cor9;

    /*Representa a cor de fundo do submenu quando estao selecionadas*/
    int cor10;

    /*Representa a cor da letra de atalho das opcoes dos submenus*/
    int cor11;

    /*Representa a cor de fundo da janela principal*/
    int cor13;

    /*Representa a cor do texto impresso na janela principal*/
    int cor14;

    /*Representa a cor da borda da janela principal*/
    int cor15;

    /*Representa a cor de fundo da borda da janela principal*/
    int cor16;

    /*Representa a largura incluindo as bordas da janela principal*/
    int largura;

    /*Representa a altura incluindo a borda inferior e o menu principal da janela principal*/
    int altura;

    /*Representa a quantidade de espacamento a ser dado entre as opcoes do menu principal*/
    int espacamento;
    
}MENU_CONFIG;



/*Funcao responsavel por ler os arquivos passados para realizar a verificacao se foram abertos e lidos de modo correto*/
void Abre_arquivos_e_aloca_memoria(char *, char *, ARQUIVOS *);

/*Funcao responsavel por criar meus menus de acordo com os arquivos passados como argumento*/
int Menu(char *, char *);

/*Funcao para inicializar estrutura contendo os menus*/
void Inicializa_estruturas_menus(MENU **, ARQUIVOS *);

