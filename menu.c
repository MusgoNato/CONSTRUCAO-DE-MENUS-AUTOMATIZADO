/*Logica das funcoes utilizadas no decorrer do programa*/

/*Inclusao de bibliotecas*/
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "funcoes.h"

/*Lembran�a
Id pai � o identificador se � um menu ou submenu, caso seja 0 � menu e deve ser impresso na posi��o horizontal, caso seja 1 � um submenu
e deve ser impresso em posi��o vertical*/

/*Id, cada menu tem seu id, quando um submenu � criado, o id_pai dele vai estar vinculado ao id de algum menu que veio antes dele, pois tem que ter
essa ligacao, para saber de qual menu veio o submenu criado*/

/*A ordem refere-se a ordem que os elementos v�o ser colocados na tela, caso haja 2 ids_pais com valor 0, ha dois menu principal, algum deles vai ser impresso
primeiro, a ordem determinara isso*/


/*Funcao responsavel por ler os arquivos passados como parametros na funcao Menu()*/
void Abre_arquivos_e_aloca_memoria(char *arquivo_menus, char *arquivo_cores, ARQUIVOS *arquivos)
{
    /*Ponteiro para um arquivo*/
    FILE *arq_menus, *arq_config;
    MENU **menus;
    MENU_CONFIG menu_config;
    int pega_tamanho_linha = 0;
    char caractere;
    int index_congiftxt = 0;
    char verifica_final_arquivo;
    char *verifica_final_linhas_arq;
    int conta_caracteres_no_arquivo = 0;
    int i = 0;
    menu_config = menu_config;
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

                    /*Verifico o primeiro caractere, caso seja \n, libero a memoria da alocacao da linha, caso nao for */
                    if(arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo][0] == '\n')
                    {
                        /*Libero a memoria alocada para a string*/
                        free(arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo]);
                    }
                    else
                    {
                        /*Pego o tamanho de cada linha*/
                        pega_tamanho_linha = strlen(arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo]);

                        /*Verifico se a string tem um \n, caso tenho retiro colocando um \0 no lugar*/
                        if(pega_tamanho_linha > 0 && arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo][pega_tamanho_linha - 1] == '\n')
                        {
                            /*Coloco \0 no final da minha string*/
                            arquivos->matriz_arquivo_menu[arquivos->conta_linhas_arquivo][pega_tamanho_linha - 1] = '\0';
                        }

                        /*Incremento da linha da stirng do arquivo*/
                        arquivos->conta_linhas_arquivo += 1;
                    }
                    
                }
                else
                {
                    break;
                }

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
        /*Chamo a funcao para inicializar as estruturas*/
        Inicializa_estruturas_menus(menus, arquivos, &menu_config);
    }
}

/*Funcao resonsavel por automatizar a criacao de menus*/
int Menu(char *arquivo_menus, char *arquivo_cores)
{
    ARQUIVOS arquivos;

    /*Desliga o cursor*/
    setCursorStatus(DESLIGAR);

    /*Chamada da funcao para realizar a abertura e leitura dos arquivos*/
    Abre_arquivos_e_aloca_memoria(arquivo_menus, arquivo_cores, &arquivos);

    /*seta as cores originais do cmd*/
    setCursorStatus(LIGAR);
    textcolor(LIGHTGRAY);
    textbackground(BLACK);

    return 1;
}

/*Inicializa a estrutura contendo as configuracoes do menu*/
void Inicializa_estrutura_cores(MENU_CONFIG *menu_config, int vetor_aux[])
{
    menu_config->cor1 = vetor_aux[0];
    menu_config->cor2 = vetor_aux[1];
    menu_config->cor3 = vetor_aux[2];
    menu_config->cor4 = vetor_aux[3];
    menu_config->cor5 = vetor_aux[4];
    menu_config->cor6 = vetor_aux[5];
    menu_config->cor7 = vetor_aux[6];
    menu_config->cor8 = vetor_aux[7];
    menu_config->cor9 = vetor_aux[8];
    menu_config->cor10 = vetor_aux[9];
    menu_config->cor11 = vetor_aux[10];
    menu_config->cor12 = vetor_aux[11];
    menu_config->cor13 = vetor_aux[12];
    menu_config->cor14 = vetor_aux[13];
    menu_config->cor15 = vetor_aux[14];
    menu_config->cor16 = vetor_aux[15];
    menu_config->largura = vetor_aux[16];
    menu_config->altura = vetor_aux[17];
    menu_config->espacamento = vetor_aux[18];
}

/*Funcao para inicializar os campos dos meus menus, ids, ordem, etc*/
void Inicializa_estruturas_menus(MENU **menus, ARQUIVOS *arquivos, MENU_CONFIG *menu_config)
{
    int i, j, index_string = 0;
    char caractere;
    char *delimitador;
    char *corta_string;
    char string_aux[TAM_BUFFER];
    int tamanho = 0;
    int index_aux = 0;
    int vetor_aux[TAM_VETOR_AUX_TOKENIZACAO];

    menu_config = menu_config;
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
                
                /*Verifico o final do arquivo, caso o indice chega ate la, pego o caractere correspondente, que sempre ficara no final do arquivo*/
                if(j == tamanho - 1)        
                {
                    /*Atribui a tecla de atalho na estrutura menus*/
                    menus[i]->letra_atalho = caractere;
                    break; 
                }

                /*Verifica se e um digito o caractere*/
                if(isdigit(caractere))
                {
                    /*Copio para uma string auxiliar a minha original, pois strtok destroi a original*/
                    strcpy(string_aux, arquivos->matriz_arquivo_menu[i]);

                    /*Corto minha strings atraves do espaco em cada string*/
                    corta_string = strtok(string_aux, " ");
                    
                    while(corta_string) 
                    {   
                        /*Verifico se na primeira posicao da minha substring tem o ", caso tenha nao e necessario continuar o loop*/
                        if(corta_string[0] == '"')
                        {
                            break;
                        }
                        else
                        {
                            /*Faz a atribuicao em cada variavel, VERIFICAR ESSA PARTE************/
                            /*IDEIA DE CRIAR UM VETOR AUXILIAR QUE A CADA CORTE DA STRING COLOCO O ID CORRESPONDENTE*/
                            menus[i]->id_pai = atoi(corta_string);
                            menus[i]->id = atoi(corta_string);
                            menus[i]->ordem = atoi(corta_string);
                            corta_string = strtok(NULL, " ");
                        }
   
                    }
                }
            }
        }
    }

    /*Tokenizo a string de acordo com os espacos*/
    delimitador = strtok(arquivos->vetor_arquivo_cores, " ");

    /*Loop para pegar cada caractere e transformar em inteiro para meu vetor auxiliar*/
    while(delimitador)
    {
        /*A cada indice do meu vetor faco a atribuicao em inteiro no meu vetor de inteiros, usando a funcao atoi()*/
        vetor_aux[index_aux] = atoi(delimitador);

        /*Tokenizo novamento a string, porem apartir da ultima tokenizacao feita, pois ha a atribuicao do \0 ao final de cada tokenizacao da string original*/
        delimitador = strtok(NULL, " ");        
        index_aux++;
    }

    /*Chamo a funcao para inicializar a estrutura contendo as variaveis para as cores do menu e suas configuracoes*/
    Inicializa_estrutura_cores(menu_config, vetor_aux);

    /*Depois da alocacao e inicializacao das estruturas, chamo a funcao para exibir o menu
    Exibe_menu_principal(menus, menu_config, arquivos);*/
}


/*Funcao que exibe meu menu*/
void Exibe_menu_principal(MENU **menus, MENU_CONFIG *menu_config, ARQUIVOS *arquivos)
{
    int i, j;
    int tamanho = 0;

    /*A coordenada para impressao e setada pra 1, onde sera impresso meu menu principal*/
    menu_config->posicao_menu_principal.X = 1;
    menu_config->posicao_menu_principal.Y = 1; 

    /*Imprime meu menu na horizontal*/
    for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
    {
        /*Verifico se e um menu principal, que sera impresso na horizontal*/
        if(menus[i]->id_pai == 0)
        {
            /*Seto a impressao e imprimo o menu*/
            gotoxy(menu_config->posicao_menu_principal.X + tamanho, menu_config->posicao_menu_principal.Y);
            textbackground(menu_config->cor1);
            printf("%s", menus[i]->nome_menu);

            /*Faco o tamanho receber o tamanho da opcao mais o espacamento que tem na variavel da estrutura de configuracoes do menu*/
            tamanho = strlen(menus[i]->nome_menu) + menu_config->espacamento;
        }
        else
        {
            for(j = 0; j < arquivos->conta_linhas_arquivo; j++)
            {
                /*Verifico os submenus*/
                if(menus[i]->id_pai == menus[j]->id)
                {
                    gotoxy(menu_config->posicao_menu_principal.X, menu_config->posicao_menu_principal.Y + i);
                    printf("%s", menus[i]->nome_menu);
                }
            }
            
        }
        
    }

    /*Verifica-se se e uma acao do teclado*/
    if(hit(KEYBOARD_HIT))
    {
        /*Pego o evento*/
        arquivos->teclas_evento = Evento();

        /*Caso seja do teclado*/
        if(arquivos->teclas_evento.tipo_evento & KEY_EVENT)
        {
            /*Verifico a liberacao da tecla pressionada*/
            if(arquivos->teclas_evento.teclado.status_tecla == LIBERADA)
            {
                /*Verifico o codigo da tecla*/
                if(arquivos->teclas_evento.teclado.key_code == ESC)
                {
                    /*Ativa o cursor novamente*/
                    setCursorStatus(LIGAR);
                    exit(0);
                }
            }
        }
    }
    
}