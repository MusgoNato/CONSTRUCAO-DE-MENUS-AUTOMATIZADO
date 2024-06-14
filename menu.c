/*Logica das funcoes utilizadas no decorrer do programa*/

/*Inclusao de bibliotecas*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "funcoes.h"

/*Lembrança
Id pai é o identificador se é um menu ou submenu, caso seja 0 é menu e deve ser impresso na posição horizontal, caso seja 1 é um submenu
e deve ser impresso em posição vertical*/

/*Id, cada menu tem seu id, quando um submenu é criado, o id_pai dele vai estar vinculado ao id de algum menu que veio antes dele, pois tem que ter
essa ligacao, para saber de qual menu veio o submenu criado*/

/*A ordem refere-se a ordem que os elementos vão ser colocados na tela, caso haja 2 ids_pais com valor 0, ha dois menu principal, algum deles vai ser impresso
primeiro, a ordem determinara isso*/


/*Funcao responsavel por ler os arquivos passados como parametros na funcao Menu()*/
void Abre_arquivos_e_aloca_memoria(char *arquivo_menus, char *arquivo_cores, ARQUIVOS *arquivos, MENU *menus)
{
    /*Ponteiro para um arquivo*/
    FILE *retornos;
    char verifica_final_arquivo;
    char *verifica_final_linhas_arq;
    int conta_caracteres_no_arquivo = 0;
    int indice_matrizes = 0;
    int i;

    /*Verificacao da abertura dos arquivos iniciais*/   
    retornos = fopen(arquivo_menus, "r");
    if(retornos != NULL)
    {
        /*Chama a funcao para alocar memoria para minha estrutura*/
        do
        {
            /*Pega cada caractere do arquivo*/
            verifica_final_arquivo = fgetc(retornos);

            /*Verificacao para caso chegue ao final do arquivo*/
            if(verifica_final_arquivo == EOF)
            {
                break;
            }
            else
            {
                /*Conta a quantidade de caracteres dentro do arquivo aberto*/
                conta_caracteres_no_arquivo++;
            }
        }while(verifica_final_arquivo != EOF);

        /*Apos a leitura jogo o ponteiro para o arquivo no comeco do arquivo novamente*/
        fseek(retornos, 0, SEEK_SET);
        
        /*Aloca memoria para minha estrutura contendo os menus*/
        menus = (MENU *)malloc(conta_caracteres_no_arquivo * sizeof(MENU));

        /*Aloca memoria para minha matriz que contera meus arquivos*/
        arquivos->matriz_arquivo_menu = (char **)malloc(conta_caracteres_no_arquivo * sizeof(char *));

        /*Se caso a alocacao der certo entra para alocar as linhas para minha matriz*/
        if(arquivos->matriz_arquivo_menu != NULL)
        {
            /*Loop para pegar cada linha do meu arquivo*/
            while(1)
            {
                arquivos->matriz_arquivo_menu[indice_matrizes] = (char *)malloc(TAM_BUFFER * sizeof(char));
                if(arquivos->matriz_arquivo_menu[indice_matrizes] != NULL)
                {
                    /*Armazena cada linha do meu arquivo aberto na minha matriz*/
                    verifica_final_linhas_arq = fgets(arquivos->matriz_arquivo_menu[indice_matrizes], TAM_BUFFER, retornos);

                    /*Saida caso a alocacao der errado*/
                    if(verifica_final_linhas_arq == NULL)
                    {
                        fclose(retornos);
                        break;
                    }
                }
                else
                {
                    break;
                }

                /*Incremento da linha da stirng do arquivo*/
                indice_matrizes += 1;
            }
        }   
        else
        {
            /*Libera a memoria alocada para minha matriz*/
            free(arquivos->matriz_arquivo_menu);
        }
        
        /*Verificacao se a estrutura foi alocada corretamente*/
        if(menus == NULL)
        {   
            printf("Memoria nao alocada!");
        }
    }
    else
    {
        printf("Erro na abertura do arquivo 'menu.txt'!\n");
    }

    /*Fecha o arquivo menu.txt*/
    fclose(retornos);

    for(i = 0; i < indice_matrizes; i++)
    {
        printf("%s", arquivos->matriz_arquivo_menu[i]);
    }

    retornos = fopen(arquivo_cores, "r");
    if(retornos != NULL)
    {
        printf("Deu certo 2!\n");
    }
    else
    {
        printf("Erro na abertura do arquivo 'config.txt'!\n");
    }

    /*Fecha o arquivo config.txt*/
    fclose(retornos);
}

/*Funcao resonsavel por automatizar a criacao de menus*/
int Menu(char *arquivo_menus, char *arquivo_cores)
{
    MENU menus;
    ARQUIVOS arquivos;

    /*Chamada da funcao para realizar a abertura e leitura dos arquivos*/
    Abre_arquivos_e_aloca_memoria(arquivo_menus, arquivo_cores, &arquivos, &menus);

    /*Funcao para inicializar estrutura*/
    Inicializa_estrutura(&menus);
    
    return 1;
}

/**/
