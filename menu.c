/*Logica das funcoes utilizadas no decorrer do programa*/

/*Inclusao de bibliotecas*/
# include <ctype.h>
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
void Abre_arquivos_e_aloca_memoria(char *arquivo_menus, char *arquivo_cores, ARQUIVOS *arquivos)
{
    /*Ponteiro para um arquivo*/
    FILE *arq_menus, *arq_config;
    MENU **menus;
    MENU_CONFIG menu_config;
    char caractere;
    int index_congiftxt = 0;
    char verifica_final_arquivo;
    char *verifica_final_linhas_arq;
    int conta_caracteres_no_arquivo = 0;
    int i = 0;

    arquivos->conta_linhas_arquivo = 0;

    /*Verificacao da abertura dos arquivos iniciais*/   
    arq_menus = fopen(arquivo_menus, "r");
    if(arq_menus != NULL)
    {
        /*Chama a funcao para alocar memoria para minha estrutura*/
        do
        {
            /*Pega cada caractere do arquivo*/
            verifica_final_arquivo = fgetc(arq_menus);

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
        fseek(arq_menus, 0, SEEK_SET);

        /*Aloca memoria para minha matriz que contera meus arquivos*/
        arquivos->matriz_arquivo_menu = (char **)malloc(conta_caracteres_no_arquivo * sizeof(char *));

        /*Se caso a alocacao der certo entra para alocar as linhas para minha matriz*/
        if(arquivos->matriz_arquivo_menu != NULL)
        {
            /*Loop para pegar cada linha do meu arquivo*/
            while(1)
            {
                arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo] = (char *)malloc(TAM_BUFFER * sizeof(char));
                if(arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo] != NULL)
                {
                    /*Armazena cada linha do meu arquivo aberto na minha matriz*/
                    verifica_final_linhas_arq = fgets(arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo], TAM_BUFFER, arq_menus);

                    /*Saida caso a alocacao der errado*/
                    if(verifica_final_linhas_arq == NULL)
                    {
                        fclose(arq_menus);
                        break;
                    }
                }
                else
                {
                    break;
                }

                /*Incremento da linha da stirng do arquivo*/
                arquivos->conta_linhas_arquivo += 1;
            }

            /*A alocaca do meu vetor de estruturas deve ser feita aqui, pois somente preciso das linhas para serem alocadas, mais nada*/
            menus = (MENU **)malloc(arquivos->conta_linhas_arquivo * sizeof(MENU *));

            /*Caso a alocacao der errada, libera a memoria alocada*/
            if(menus == NULL)
            {
                /*Libera memoria da estrutura*/
                free(menus);
            }
            else
            {
                /*Percorre a quantidade de linhas do arquivo armazenando nos ponteiros para minha estrutura*/
                for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
                {
                    /*Aloca meus ponteiros para estruturas*/
                    menus[i] = (MENU *)malloc(sizeof(MENU));
                }

            }
        }   
        else
        {
            /*Libera a memoria alocada para minha matriz*/
            free(arquivos->matriz_arquivo_menu);
        }
    }
    else
    {
        printf("Erro na abertura do arquivo 'menu.txt'!\n");
    }

    /*Fecha o arquivo menu.txt*/
    fclose(arq_menus);
    
    /*Abro o arquivo que contem as configuracoes*/
    arq_config = fopen(arquivo_cores, "r");
    if(arq_config != NULL)
    {
        do
        {
            /*Pego o caractere dentro do meu arquivo*/
            caractere = fgetc(arq_config);

            /*Verifico se chegou ao fim*/
            if(caractere != EOF)    
            {
                /*Faco a atribuicao*/
                arquivos->vetor_arquivo_cores[index_congiftxt] = caractere;

            }
            else
            {
                /*Caso chegue ao final somente colocar \0 no final da string*/
                arquivos->vetor_arquivo_cores[index_congiftxt] = '\0';
                break;
            }

            /*Incrementa o contador para a string*/
            index_congiftxt++;
            
        }while(caractere != EOF);
        
    }
    
    /*Fecha o arquivo config.txt*/
    fclose(arq_config);

    /*Se caso os dois arquivos, seus retornos sao diferente de NULL, significa que foram abertos corretamente*/
    if(arq_config != NULL && arq_menus != NULL)
    {
        Inicializa_estruturas_menus(menus, arquivos, &menu_config);
        /*Exibe_menu_principal(menus, &menu_config, arquivos);*/
    }

}

/*Funcao que exibe o menu
void Exibe_menu_principal(MENU **menus, MENU_CONFIG *menu_config, ARQUIVOS *arquivos)
{
    int i;
    int tamanho = 0;

    A coordenada para impressao e setada pra 1, onde sera impresso meu menu principal
    menu_config->posicao_menu_principal.X = 1;
    menu_config->posicao_menu_principal.Y = 1; 

    Imprime meu menu na horizontal
    for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
    {
        Verifico se e um menu principal, que sera impresso na horizontal
        if(menus[i]->id_pai == 0)
        {
            Seto a impressao e imprimo o menu
            gotoxy(menu_config->posicao_menu_principal.X + tamanho, menu_config->posicao_menu_principal.Y);
            textbackground(menu_config->cor1);
            printf("%s", menus[i]->nome_menu);

            Faco o tamanho receber o tamanho da opcao mais o espacamento que tem na variavel da estrutura de configuracoes do menu
            tamanho = strlen(menus[i]->nome_menu) + menu_config->espacamento;
        }
        
    }
}*/

/*Funcao resonsavel por automatizar a criacao de menus*/
int Menu(char *arquivo_menus, char *arquivo_cores)
{
    ARQUIVOS arquivos;
    
    /*Chamada da funcao para realizar a abertura e leitura dos arquivos*/
    Abre_arquivos_e_aloca_memoria(arquivo_menus, arquivo_cores, &arquivos);

    /*seta as cores originais do cmd*/
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    return 1;
}

/*Funcao para inicializar os campos dos meus menus, ids, ordem, etc*/
void Inicializa_estruturas_menus(MENU **menus, ARQUIVOS *arquivos, MENU_CONFIG *menu_config)
{
    int i, j, index_string = 0;
    char caractere;
    int tamanho = 0;


    /*Esse loop mais externo percorre as linhas do meu arquivo menu.txt*/
    for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
    {
        /*Pega o tamanho de cada string na minha matriz contendo as linhas do arquivo*/
        tamanho = strlen(arquivos->matriz_arquivo_menu[i]);

        /*Este loop percorre caractere por caractere da linha atual*/
        for(j = 0; j < tamanho; j++)
        {
            /*Pega o caractere dentro da minha matriz contendo o arquivo*/
            caractere = arquivos->matriz_arquivo_menu[i][j];

            /*Verifica o espaco em branco de cada paramentro dentro da minha matriz de linhas do arquivo*/
            if(caractere != ' ')
            {
                /*Quando o caractere for uma aspas duplas, significa que ela sera a string referente a minha opcao no menu*/
                if(caractere == '"')
                {
                    while(1)
                    {
                        /*Incrementa de comeco para nao pegar a propria aspas duplas, pois esta na posicao dela antes do incremento*/
                        j++;

                        /*Coloco cada caractere dentro da minha string da estrutura menus*/
                        menus[i]->nome_menu[index_string] = arquivos->matriz_arquivo_menu[i][j];

                        /*Verifica o fim da minha string*/
                        if(menus[i]->nome_menu[index_string] == '"')
                        {
                            /*Coloco o \0 para completar o nome da minha opcao do menu*/
                            menus[i]->nome_menu[index_string] = '\0';
                            break;
                        }

                        /*Incrementa o contador da minha string*/
                        index_string++;
                    }
                    
                    /*Como minha string ja foi encontrada, zero a varivel que sera o indice para a proxima leitura*/
                    index_string = 0;

                }
                
                /*Como a alocacao pega o \n e tem o \0 tambem, faco essa verificacao para pegar a letra de atalho, quando chega na ultima linha
                entao nao e necessario pegar o -2, pois nao ha \n e sim o \0. Eh o que a outra parte da verificacao compara (j == tamanho - 1)*/
                if((j == tamanho - 2 && caractere != '\n') || j == tamanho - 1)        
                {
                    /*Atribui a tecla de atalho na estrutura menus*/
                    menus[i]->letra_atalho = caractere;
                    break; 
                }

                /*Verifica se e um digito o caractere*/
                if(isdigit(caractere))
                {
                    /*Se caso j for 0, esta no id_pai*/
                    if(j == 0)
                    {
                        menus[i]->id_pai = caractere - '0';
                    }

                    /*Verifico o caractere anterior pra pegar o id unico do menu*/
                    if(j == 2)
                    {
                        menus[i]->id = caractere - '0';
                    }

                    /*Pego a ordem do menu que sera apresentado, ja que a posicao nao muda, entao pego ele na posicao fixa do arquivo*/
                    if(j == 4)
                    {
                        menus[i]->ordem = caractere - '0';
                    }
                }
            }
        }
    }
    
    /*O sscanf le dados de uma string passada como primeiro parametro, como sao inteiros dentro de uma estrutura, somente e necessario passar a quantidade de inteiros
    que serao lidos no segundo parametro da funcao, assim eu tenho o valor armazenado em cada inteiro da estrutura menu_config.
    Como consegue delimitar o espaco presente dentro da string e converter o numero em inteiro, essa forma foi mais facil de atribuir os valores a estrutura*/
    sscanf(arquivos->vetor_arquivo_cores, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &menu_config->cor1, &menu_config->cor2, &menu_config->cor3, &menu_config->cor4,
    &menu_config->cor5, &menu_config->cor6, &menu_config->cor7, &menu_config->cor8, &menu_config->cor9, &menu_config->cor10, &menu_config->cor11, &menu_config->cor12, &menu_config->cor13,
    &menu_config->cor14, &menu_config->cor15, &menu_config->cor16, &menu_config->largura, &menu_config->altura, &menu_config->espacamento);


}
