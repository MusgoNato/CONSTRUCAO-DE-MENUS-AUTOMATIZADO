/*Prototipos de funcoes e declaracoes de constantes*/

/*Constantes*/
# define TAM_OPCAO_MENU 35
# define TAM_BUFFER 100
# define TAM_LINHA_CONFIG 100
# define TAM_VETOR_MENU_CONFIG 20 
# define TAM_VETOR_AUX_TOKENIZACAO 19
# define ESPACAMENTO_INICIO_FINAL_OPCAO 2
# define ALT_ESQUERDO LEFT_ALT_PRESSED

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

    /*Cada opcao contera sua determinada localizacao, coordenada de onde esta sendo impresso na tela*/
    COORD posicao_menu;
}MENU;

typedef struct arquivos
{
    /*Contem meus arquivos em matrizes*/
    char **matriz_arquivo_menu;
    char vetor_arquivo_cores[TAM_LINHA_CONFIG];
    int conta_linhas_arquivo;
    EVENTO teclas_evento;
    int posicao_teclas_user;
    int tamanho_cada_string;
    int index_menus;
    
    int enter_pressionado;
    int controla_impressao;
    int controla_atalho;
    int cont_menu_principal;
    int cont_submenus;

    int controla_alt;
    int largura_dos_submenus;
    COORD posicao_submenus;
    int controla_impressao_submenus;
    EVENTO eventos_submenus;
    int setas_submenus;

}ARQUIVOS;

typedef struct config
{
    /*Representa a cor de fundo da barra do menu principal*/
    int cor1;

    /*Representa a cor das opcoes do menu principal quando nao estao selecionadas*/
    int cor2;

    /*Representa a cor das opcoes menu principal selecionadas*/
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

    /*Representa a cor da letra de atalho das opcoes dos submenus quando nao estao selecionadas*/
    int cor11;

    /*Representa a cor da letra de atalho dos subemnus quando estao selecionadas*/
    int cor12;

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

    /*Pega a posicao do menu menu principal para imprimir na tela*/
    COORD posicao_menu_principal;

    
}MENU_CONFIG;


/*Funcao responsavel por ler os arquivos passados para realizar a verificacao se foram abertos e lidos de modo correto
Parametros:
1 -> 
2 -> 
3 ->
Retorno : Nenhum
*/
void Abre_arquivos_e_aloca_memoria(char *, char *, ARQUIVOS *);

void Contagem_menus_submenus(MENU **, ARQUIVOS *);

void Desenha_Janela_Principal(MENU_CONFIG *, int );

void Desenha_Janela_submenus(MENU_CONFIG *, ARQUIVOS *, int, int);

/*Funcao responsavel por exibir os submenus*/
void Exibe_submenus(MENU **, MENU_CONFIG *, ARQUIVOS *, int);

/*Funcao resposanvel por exibir os menus principais*/
void Exibe_menu_principal(MENU **, MENU_CONFIG *, ARQUIVOS *);

/*Funcao responsavel por inicializar estruturas da configuracao do menu, cores, espacamento, largura, etc*/
void Inicializa_estrutura_cores(MENU_CONFIG *, int []);

/*Funcao para inicializar estrutura contendo os menus*/
void Inicializa_estruturas_menus(MENU **, ARQUIVOS *,  MENU_CONFIG *);

/*Funcao responsavel por criar meus menus de acordo com os arquivos passados como argumento*/
int Menu(char *, char *);

/*Funcao responsavel por exibir o menu principal*/
void Ordena_menus(MENU **, ARQUIVOS *);