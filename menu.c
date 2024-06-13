/*Lógica das funções utilizadas no decorrer do programa*/

/*Inclusão de bibliotecas*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "funcoes.h"

/*Lembrança
Id pai é o identificador se é um menu ou submenu, caso seja 0 é menu e deve ser impresso na posição horizontal, caso seja 1 é um submenu
e deve ser impresso em posição vertical*/

/*Id, cada menu tem seu id, quando um submenu é criado, o id_pai dele vai estar vinculado ao id de algum menu que veio antes dele, pois tem que ter
essa ligação, para saber de qual menu veio o submenu criado*/

/*A ordem refere-se a ordem que os elementos vão ser colocados na tela, caso haja 2 ids_pais com valor 0, há dois menu principal, algum deles vai ser impresso
primeiro, a ordem determinará isso*/


/*Função responsável por ler os arquivos passados como parametros na função Menu()*/
void Abre_arquivos_e_aloca_memoria(char *arquivo_menus, char *arquivo_cores)
{
    /*Ponteiro para um arquivo*/
    FILE *retornos;
    MENU *menus;
    char verifica_final_arquivo;
    int conta_caracteres_no_arquivo = 0;

    /*Verificação da abertura dos arquivos iniciais*/   
    retornos = fopen(arquivo_menus, "r");
    if(retornos != NULL)
    {
        /*Chama a função para alocar memoria para minha estrutura*/
        do
        {
            /*Pega cada caractere do arquivo*/
            verifica_final_arquivo = fgetc(retornos);

            /*Verificação para caso chegue ao final do arquivo*/
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
        
        /*Aloca memoria para minha estrutura contendo os menus*/
        menus = (MENU *)malloc(conta_caracteres_no_arquivo * sizeof(MENU));
        
        /*Verificação se a estrutura foi alocada corretamente*/
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

/*Função resonsável por automatizar a criação de menus*/
int Menu(char *arquivo_menus, char *arquivo_cores)
{
    /*Chamada da função para realizar a abertura e leitura dos arquivos*/
    Abre_arquivos_e_aloca_memoria(arquivo_menus, arquivo_cores);

    return 1;
}
