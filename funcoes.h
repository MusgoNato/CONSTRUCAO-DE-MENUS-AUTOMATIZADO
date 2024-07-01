/*Prototipos de funcoes e declaracoes de constantes*/

/*Constantes*/
# define TAM_OPCAO_MENU 30
# define TAM_BUFFER 100
# define TAM_LINHA_CONFIG 100
# define TAM_VETOR_MENU_CONFIG 30 
# define TAM_VETOR_AUX_TOKENIZACAO 19
# define ESPACAMENTO_INICIO_FINAL_OPCAO 2
# define ALT_ESQUERDO LEFT_ALT_PRESSED

/*Declaracao de estruturas*/

/*Estrutura com as informacoes dos menus*/
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

/*Estrutura para coordenadas e ids dos submenus ja acessados*/
typedef struct ids_e_coordenadas
{
    COORD coordenadas_para_sub;
    int id_submenu;

}VETOR_IDS_COOR_SUBS;

/*Estrutura contendo varias varaives que serao usadas no decorrer do programa*/
typedef struct arquivos
{
    /*Contem meu arquivo menu em uma matriz*/
    char **matriz_arquivo_menu;
    
    /*Contem meu arquivo cores em um vetor*/
    char vetor_arquivo_cores[TAM_LINHA_CONFIG];

    /*Variavel para contar as linhas do arquivo, pegar eventos do teclado, controlar a navegacao do usuario, saber o tamanho de uma string e uma variavel
    para servir de indice para meus menus*/
    int conta_linhas_arquivo;
    EVENTO teclas_evento;
    int posicao_teclas_user;
    int tamanho_cada_string;
    int index_menus;
    
    /*Variaveis para controlar o enter a ser pressionado, impressoes, controles de atalho, um contador de menus principais e contador de submenus*/
    int enter_pressionado;
    int controla_impressao;
    int controla_atalho;
    int cont_menu_principal;
    int cont_submenus;

    /*Coordenadas das posicoes dos submenus, controlador de impressao de submenus, teclas de evento para os submenus e controle das setas de navegacao
    em um submenu*/
    COORD posicao_submenus;
    int controla_impressao_submenus;
    EVENTO eventos_submenus;
    int setas_submenus;

    /*Coordenadas para pegar o limite maximo da janela, um vetor de string para guardar telas do programa, variavel para servir de nivel, referente as minhas telas guardadas,
    um vetor contendo ids e coordenadas que servirao para imprimir novamente um menu anterior ao ser pressionado o ESC, indice para meu vetor, variavel de retorno, referente ao id retornado e
    uma string para guardar minha tela principal*/
    COORD limite_maximo_da_janela;
    char **Tela;
    int nivel;
    VETOR_IDS_COOR_SUBS **vetor_ids_coord_sub;
    int index_vetor;
    int retorno;
    char *Tela_menu_principal;

}ARQUIVOS;

/*Estrutura que contem as variaveis referente as configuracoes dos menus*/
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


/*Funcao responsavel por ler os arquivos passados para realizar a verificacao se foram abertos e lidos de modo correto, caso forem lidos corretamente as
informacoes dentro do arquivo sera passado para uma matriz, onde esta contera as linhas do arquivo, essa etapa ocorre para os dois arquivos.
Parametros:
1 -> Um tipo char *, este paramentro sera a string passada como primeiro argumento para meu programa, sendo o arquivo .txt contendo os menus .
2 -> Um tipo char *, este parametro sera o nome do arquivo .txt para configuracao de exibicao dos menus (cores, espacamento, altura, largura, etc).
3 -> Um tipo ponteiro para estrutura, este parametro armazena meus arquivos abertos para que eu possa trata-los e guarda-los em matrizes ou vetores.
Retorno : Nenhum
*/
void Abre_arquivos_e_aloca_memoria(char *, char *, ARQUIVOS *);

/*Funcao responsavel por fazer a contagem de menus e submenus
Parametros:
1 -> Um ponteiro para ponteiro, para uma estrutura, este parametro eh um vetor de estruturas,
a estrutura em si conta com cada identificador do menu, o identificador pai, sua ordem, seu nome e letra de atalho presente.  
2 -> Um ponteiro para estrutura arquivos, a estrutura arquivos contem variaveis que servirao se contagem para submenus e menus principais,
pois preciso desses valores em outras funcoes usadas no decorrer do programa.
Retorno : Nenhum
*/
void Contagem_menus_submenus(MENU **, ARQUIVOS *);

/*Funcao responsavel por desenhar a janela principal dos menus
Parametros:
1 -> Um ponteiro para estrutura MENU_CONFIG, como somente sera uma linha no arquivo contendo as configuracoes dos menus, somente foi necessario criar uma estrutura
contendo todos os valores e assim inicializa-los, nesta funcao ela eh usada para desenhar a janela principal, pois ela contem as configuracoes do menu.
2 -> Um tipo int, na funcao 'Exibe_menu_Principal' eh contado quantos menus foram impressos a partir do id pai, com isso eh passado para esta funcao para saber ate onde deve-se desenhar a janela.
Retorno : Nenhum
*/
void Desenha_Janela_Principal(MENU_CONFIG *, int );

/*Funcao responsavel por desenhar a janela dos submenus
Parametros:
1 -> Um ponteiro para estrutura MENU_CONFIG, na funcao eh passado este parametro justamento para desenhar as janelas dos submenus, assim como a funcao Desenha_Janela_Principal().
2 -> Um ponteiro para estrutura ARQUIVOS, a estrutura arquivos contem as coordenadas de onde a janela deve ser impressa.
3 -> Um tipo int, representa a quantidade de submenus que foram contados na funcao 'Exibe_submenus'.
4 -> Um tipo int, representa a largura da janela do submenu a ser impressa, para desenhar e caber a maior opcao dos menus, essa variavel serve para desenhar a janela referente a maior opcao.
Retorno : Nenhum*/
void Desenha_Janela_submenus(MENU_CONFIG *, ARQUIVOS *, int, int);

/*Funcao resposanvel por exibir os menus principais
Parametros:
1 -> Um ponteiro para ponteiro para estrutura MENU, eh responsavel por exibir meu menu principal, com os ids iguais a 0.
2 -> Um ponteiro para estrutura MENU_CONFIG, eh acessada a estrutura para configurar meu menu principal impresso.
3 -> Um ponteiro para estrutura ARQUIVOS, eh acessada pois contem informacoes uteis de controle para impressao, navegacao do usuario por meio das setas, verificacao do enter pressionado, etc.
Retorno : Nenhum*/
void Exibe_menu_principal(MENU **, MENU_CONFIG *, ARQUIVOS *);

/*Funcao responsavel por exibir meus submenus de forma recursiva
Parametros:
1 -> Um ponteiro de ponteiro para estrutura MENU, a estrutura menus contem as informacoes de cada menu, assim sendo a funcao percorre os menus exibindo o submenu selecionado por meio do pressionamento
da tecla ENTER e sai por meio do pressionamento da tecla ESC.
2 -> Um ponteiro para estrutura MENU_CONFIG, como tem que imprimir os submenus e cada um deles tem as cores separadas das demais, a estrutura MENU_CONFIG traz as configuracoes necessarias
para a correta impressao, suas cores de texto, fundo, letra de atalho, etc.
3 -> Um ponteiro para estrutura ARQUIVOS, como comentado em outras funcoes, a estrutura arquivo contem varias informacoes, nessa funcao ela eh acessada para controles, quer seja de exibicao do submenu ou algum outro
tipo de controle, impressoes corretas por meio das coordenadas armazenadas na mesma e outras informacoes.
4 -> Um tipo int, representa o id do menu a ser impresso, ao pressionar enter, esse id eh modificado para o id da selecao da opcao aonde o usuario esta navegado, eh chamada recursivamente a funcao trocando
o valor do id e imprimindo o proximo menu caso haja o mesmo.
Retorno : Id retornado do ultimo menu selecionado que nao contenha submenus*/
int Exibe_submenus(MENU **, MENU_CONFIG *, ARQUIVOS *, int);

/*Funcao responsavel por inicializar estruturas da configuracao do menu, cores, espacamento, largura, etc
Parametros:
1 -> Um ponteiro para estrutura MENU_CONFIG, eh acessada a estrutura para preencher seus campos, inicializando ela.
2 -> Um vetor, neste vetor foi colocado cada numero presente no arquivo com as configuracoes do meu menu, assim sendo, somente atribuo para minha estrutura que contera os campos
para cada configuracao, como cores, espacamento, largura, altura, etc.
Retorno : Nenhum*/
void Inicializa_estrutura_cores(MENU_CONFIG *, int []);

/*Funcao para inicializar estrutura contendo os menus
Parametros:
1 -> Um ponteiro para ponteiro para estrutura MENU, a estrutura eh acessada para incicializacao, todos seus campos sao preenchidos com os valores encontrados no arquivo com os menus.
2 -> Um ponteiro para estrutura ARQUIVOS, eh acessada a estrutura pois contem algumas varaiveis necessarias para atribuicoes no meu vetor de estruturas MENU.
3 -> Um ponteiro para estrutura MENU_CONFIG, ela sera um parametro para chamada de outras funcoes dentro da inicializacao de estruturas MENU.
Retorno : Nenhum*/
void Inicializa_estruturas_menus(MENU **, ARQUIVOS *,  MENU_CONFIG *);

/*Funcao responsavel por inicializar varias variaveis que serao usadas durante o programa
Parametros:
1 -> Ponteiro para estrutura ARQUIVOS, eh necessario acessar a estrutura e inicializar todas as variaveis necessarias para a execucao correta do programa.
Retorno : Nenhum*/
void Inicializa_variaveis_diversas(ARQUIVOS *);

/*Funcao responsavel por criar meus menus de acordo com os arquivos passados como argumento
Parametros:
1 -> Um tipo char *, representa o nome do arquivo que contem os menus.
2 -> Um tipo char *, representa o nome do arquivo que contem as configuracoes dos menus.
Retorno : Numero id do ultimo menu selecionado pelo usuario*/
int Menu(char *, char *);

/*Funcao responsavel por ordenar os menus, tanto os id pai quanto a ordem de cada menu em relacao ao outro
Parametros:
1 -> Um ponteiro para ponteiro para estrutura MENU, como a funcao ordena os ids_pais e ordem, eh necessario acessar cada um individuamente para saber quem eh o maior ou menor, e trocalos
para posicao correta, isso ajudara na hora que for imprimir os menus e submenus, pois somente a impressao sera sequencial, ja que estao ordenados.
2 -> Um ponteiro para estrutura ARQUIVOS, a estrutura eh acessada pois contem a varaivel que contou anteriormente os menus, assim consigo percorrer todos eles, ordenando.
Retorno : Nenhum*/
void Ordena_menus(MENU **, ARQUIVOS *);