/*Logica das funcoes utilizadas no decorrer do programa*/

/*Inclusao de bibliotecas*/
# include <ctype.h> /*isdigit()*/
# include <stdio.h> /*fclose(), fgetc(), fgets(), fopen(), fseek(), printf() putchar()*/
# include <stdlib.h> /*atoi(), malloc(), free()*/
# include <string.h> /*strchr(), strcpy(), strlen(), strtok() */
# include "console_v1.5.5.h" /*Evento(), hit(), setCursorStatus()*/
# include "conio_v3.2.4.h" /*gotoxy(), texbackground(), texcolor(), wherexy()*/
# include "funcoes.h" /*Abre_arquivos_e_aloca_memoria(), Contagem_menus_submenus(), Desenha_Janela_Principal(), Desenha_Janela_submenus(),
Exibe_menu_principal(), Exibe_submenus(), Inicializa_estrutura_cores(), Inicializa_estruturas_menus(), Menu(), Ordena_menus()*/

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
        /*Aloco espaco para minha Tela de salvamento apos os arquivos serem abertos corretamente*/
        arquivos->limite_maximo_da_janela = MaxDimensaoJanela();


        /*Chamo a funcao para inicializar as estruturas*/
        Inicializa_estruturas_menus(menus, arquivos, &menu_config);
    }
}

/*Funcao responsavel por contar a quantidade de menus e submenus*/
void Contagem_menus_submenus(MENU **menus, ARQUIVOS *arquivos)
{
    int i;

    for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
    {
        /*Caso seja pai*/
        if(menus[i]->id_pai == 0)
        {
            arquivos->cont_menu_principal++;
        }   
        /*Caso seja submenu*/
        else
        {
            arquivos->cont_submenus++;
        }
    }

    /*Alocacao da minha tela de save para o menu principal*/
    arquivos->Tela_menu_principal = (char *)malloc(arquivos->limite_maximo_da_janela.X * arquivos->limite_maximo_da_janela.Y * 2 * sizeof(char));

    /*Liberacao de memoria caso de errado a alocacao*/
    if(arquivos->Tela_menu_principal == NULL)
    {
        free(arquivos->Tela_menu_principal);
    }

    /*Aloca minha tela de save da janela do cmd*/
    arquivos->Tela = (char **)malloc(arquivos->cont_submenus * sizeof(char *));
    
    /*Verificacao da alocacao se foi correta ou nao*/
    if(arquivos->Tela == NULL)
    {
        /*Libera a memoria alocada*/
        free(arquivos->Tela);
    }
    else
    {
        /*Inicializaocao para minhas telas*/
        for(i = 0; i < arquivos->cont_submenus; i++)
        {
            arquivos->Tela[i] = (char *)malloc(arquivos->limite_maximo_da_janela.X * arquivos->limite_maximo_da_janela.Y * 2 * sizeof(char));
        }
    }

    

    /*Alocacao da minha pilha*/
    arquivos->vetor_ids_coord_sub = (VETOR_IDS_COOR_SUBS **)malloc(arquivos->cont_submenus * sizeof(VETOR_IDS_COOR_SUBS *));
    
    /*Verificacao da alocacao caso de certo*/
    if(arquivos->vetor_ids_coord_sub != NULL)
    {   
        /*Alocacao para minhas posições*/
        for(i = 0; i < arquivos->cont_submenus; i++)
        {   
            /*Aloco para cada ponteiro da minha piha o valor do tipo int*/
            arquivos->vetor_ids_coord_sub[i] = (VETOR_IDS_COOR_SUBS *)malloc(sizeof(VETOR_IDS_COOR_SUBS));
        }
    }
    else
    {
        /*Libera memoria alocada*/
        free(arquivos->vetor_ids_coord_sub);
    }
    

    
}

/*Funcao responsavel por desenhar a janela principal*/
void Desenha_Janela_Principal(MENU_CONFIG *menu_config, int tam_menus_desenhado)
{
    int i, j;

    /*Os caracteres representados por numeros dentro do putchar correspondem ao numero da tabela ascii code page 850
    para caracteres especiais para desenhos de quadros, eles sao encontrados na ultima pagina.
    https://www.comp.uems.br/~ricardo/PCII/Aulas/Arquivos%20%c3%bateis/Mat%c3%a9ria%200%20-%20Tabela%20ASCII/
    */

    /*Desenha a janela toda*/
    for(i = 0; i < menu_config->altura; i++)
    {
        for(j = 0; j < tam_menus_desenhado; j++)
        {
            gotoxy(menu_config->posicao_menu_principal.X + j, menu_config->posicao_menu_principal.Y + menu_config->altura/menu_config->largura + 1 + i);
            
            /*Cor do fundo da janela principal*/
            textbackground(menu_config->cor13);
            printf(" ");
        }
    }

    /*Linha superior*/
    for(i = 0; i < tam_menus_desenhado; i++)
    {
        /*Seta a posicao de impressao*/
        gotoxy(menu_config->posicao_menu_principal.X + i, menu_config->posicao_menu_principal.Y + menu_config->altura/menu_config->largura + 1);
        
        /*Cor da borda da janela e cor de fundo da borda da janela*/
        textcolor(menu_config->cor15);
        textbackground(menu_config->cor16);

        /*Desenha o caractere de desenho para quadros*/
        if(i == 0)
        {
            /*┌*/
            putchar(218);
        }

        /*Imprime o caractere especial de desenho de quadros*/
        if(i == tam_menus_desenhado - 1)
        {
            /*┐*/
            putchar(191);
            break;
        }
        
        putchar(196);
    }

    /*Coluna esquerda*/
    for(i = 0; i < menu_config->altura - 1; i++)   
    {
        gotoxy(menu_config->posicao_menu_principal.X, menu_config->posicao_menu_principal.Y + menu_config->altura/menu_config->largura + i + ESPACAMENTO_INICIO_FINAL_OPCAO);
        textcolor(menu_config->cor15);
        textbackground(menu_config->cor16);
        putchar(179);
    }

    /*Coluna direita*/
    for(i = 0; i < menu_config->altura - 1; i++)
    {
        gotoxy(tam_menus_desenhado, menu_config->posicao_menu_principal.Y + menu_config->altura/menu_config->largura + i + ESPACAMENTO_INICIO_FINAL_OPCAO);
        textcolor(menu_config->cor15);
        textbackground(menu_config->cor16);
        putchar(179);
    }

    /*Linha inferior*/
    for(i = 0; i < tam_menus_desenhado; i++)
    {   
        gotoxy(menu_config->posicao_menu_principal.X + i, menu_config->posicao_menu_principal.Y + menu_config->altura/menu_config->largura + menu_config->altura + 1);
        textcolor(menu_config->cor15);
        textbackground(menu_config->cor16);

        if(i == 0)
        {
            /*└*/
            putchar(192);
        }

        /*Imprime ao atingir o final do loop o caractere especial*/
        if(i == tam_menus_desenhado - 1)
        {
            /*┘*/
            putchar(217);
            break;
        }
        
        /*Caractere especial para desenho de quadros (─)*/
        putchar(196);
    }
    

}

/*Funcao responsavel por imprimir meus submenus*/
void Desenha_Janela_submenus(MENU_CONFIG *menu_config, ARQUIVOS *arquivos, int quantidade_submenus, int largura_janela_submenu)
{
    int i, j, index_para_espacos = 0;

    /*Mini janela dos submenus*/
    for(i = 0; i < quantidade_submenus + ESPACAMENTO_INICIO_FINAL_OPCAO; i++)
    {
        for(j = 0; j < largura_janela_submenu; j++)
        {
            /*Adiciona espacos adicionais no comeco da linha*/
            if(j == 0)
            {
                /*Seto o lugar de impressao*/
                gotoxy(arquivos->posicao_submenus.X + j, arquivos->posicao_submenus.Y + i + 1);

                /*Caso seja igual a 0 o j, coloco espacos adicionais, pra dar uma profundidade*/
                for(index_para_espacos = 0; index_para_espacos < ESPACAMENTO_INICIO_FINAL_OPCAO; index_para_espacos++)
                {
                    /*Muda o fundo do submenu*/
                    textbackground(menu_config->cor7);
                    printf(" ");
                }    
            }

            /*Volto a setar as coordenadas, porem dessa vez somando o espamento inicial dado*/
            gotoxy(arquivos->posicao_submenus.X + j + ESPACAMENTO_INICIO_FINAL_OPCAO, arquivos->posicao_submenus.Y + i + 1);
            textbackground(menu_config->cor7);
            printf(" ");

            /*Verifico se cheguei no final da largura, caso sim imprime os espacos finais adicionais*/
            if(j == largura_janela_submenu - 1)
            {
                for(index_para_espacos = 0; index_para_espacos < ESPACAMENTO_INICIO_FINAL_OPCAO; index_para_espacos++)
                {
                    textbackground(menu_config->cor7);
                    printf(" ");
                }
            }
        }
    }

    /*Os caracteres representados por numeros dentro do putchar correspondem ao numero da tabela ascii code page 850
    para caracteres especiais para desenhos de quadros, eles sao encontrados na ultima pagina.
    https://www.comp.uems.br/~ricardo/PCII/Aulas/Arquivos%20%c3%bateis/Mat%c3%a9ria%200%20-%20Tabela%20ASCII/
    */

    /*Linha superior*/
    for(i = 0; i < largura_janela_submenu + ESPACAMENTO_INICIO_FINAL_OPCAO * 2; i++)
    {
        /*Cor de fundo das janelas dos submenus*/
        gotoxy(arquivos->posicao_submenus.X + i, arquivos->posicao_submenus.Y + 1);

        /*A cor do texto vai ser preta como padrao, pois no arquivo de consulta nao dizia se mudaria ou nao*/
        textcolor(BLACK);
        textbackground(menu_config->cor7);

        /*Desenha o caractere de desenho para quadros*/
        if(i == 0)
        {
            /*┌*/
            putchar(218);
        }

        /*Imprime o caractere especial de desenho de quadros*/
        if(i == largura_janela_submenu + ESPACAMENTO_INICIO_FINAL_OPCAO * 2 - 1)
        {
            /*┐*/
            putchar(191);
            break;
        }
        
        /*Imprime o caractere especial para desenho de quadro (─)*/
        putchar(196);
    }

    /*Coluna esquerda*/
    for(i = 0; i < quantidade_submenus; i++)
    {
        gotoxy(arquivos->posicao_submenus.X, arquivos->posicao_submenus.Y + i + ESPACAMENTO_INICIO_FINAL_OPCAO);
        textcolor(BLACK);
        textbackground(menu_config->cor7);
        /*Caractere especial para desenho de quadros (│)*/
        putchar(179);
    }

    /*Coluna direita*/
    for(i = 0; i < quantidade_submenus; i++)
    {
        gotoxy(arquivos->posicao_submenus.X + largura_janela_submenu + ESPACAMENTO_INICIO_FINAL_OPCAO + 1, arquivos->posicao_submenus.Y + i + ESPACAMENTO_INICIO_FINAL_OPCAO);
        textcolor(BLACK);
        textbackground(menu_config->cor7);
        /*Caractere especial para desenho de quadros (│)*/
        putchar(179);
    }

    /*Linha inferior*/
    for(i = 0; i < largura_janela_submenu + ESPACAMENTO_INICIO_FINAL_OPCAO * 2; i++)
    {   
        gotoxy(arquivos->posicao_submenus.X + i, arquivos->posicao_submenus.Y + quantidade_submenus + ESPACAMENTO_INICIO_FINAL_OPCAO);
        textcolor(BLACK);
        textbackground(menu_config->cor7);

        if(i == 0)
        {
            /*└*/
            putchar(192);
        }

        /*Imprime ao atingir o final do loop o caractere especial*/
        if(i == largura_janela_submenu + ESPACAMENTO_INICIO_FINAL_OPCAO * 2 - 1)
        {
            /*┘*/
            putchar(217);
            break;
        }
        
        /*Caractere especial para desenho de quadros (─)*/
        putchar(196);
    }

}

/*Funcao responsavel por exibir os menus*/
void Exibe_menu_principal(MENU **menus, MENU_CONFIG *menu_config, ARQUIVOS *arquivos)
{
    int i;
    int tam_menus_desenhado = 0;
    int tamanho_nome_menu = 0;
    char *posicao_letra;
    int index_letra_atalho;
    int saida = 1;
    char atalho_menu;
    
    /*Imprime os menus principais, id_pai == 0*/
    for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
    {
        /*Verifica se é um id_pai*/
       if(menus[i]->id_pai == 0)
       {
            /*Pega o tamanho de todos os ids pais*/
            tam_menus_desenhado += strlen(menus[i]->nome_menu) + menu_config->espacamento;
       }
    }

    /*O ultimo id_pai eh incrementado com o espacamento fixo, por isso eh necessario decrementar aqui*/
    tam_menus_desenhado -= menu_config->espacamento;

    /*Chama a funcao para fazer as linhas e colunas da borda da janela principal, aonde estara os submenus*/
    Desenha_Janela_Principal(menu_config, tam_menus_desenhado);

    /*Impressao do fundo do menu principal*/
    for(i = 0; i < tam_menus_desenhado; i++)
    {
        /*Percorre as coordenadas preechendo com espacos*/
        gotoxy(menu_config->posicao_menu_principal.X + i, menu_config->posicao_menu_principal.Y);

        /*Representa a cor de fundo da barra principal*/
        textbackground(menu_config->cor1);
        printf(" ");
    }

    /*Loop para pegar os eventos do teclado e imprimir o menu*/
    do
    {
        /*Controle de impressao do meu menu principal*/
        if(arquivos->controla_impressao)
        {
            /*Eh zerada a variavel para nao extrapolar a impressao novamente, pois esta dentro de um loop infinito*/
            tamanho_nome_menu = 0;

            /*For para percorrer os menus principais*/
            for(i = 0; i < arquivos->cont_menu_principal; i++)
            {
                /*Verificacao caso usuario aperte uma letra de atalho*/
                if(atalho_menu == menus[i]->letra_atalho)
                {   
                    arquivos->enter_pressionado = 1;
                    arquivos->posicao_teclas_user = menus[i]->ordem;
                    
                    /*Pego a coordenada do menu atual para impressao correta do submenu*/
                    arquivos->posicao_submenus.X = wherex();
                    arquivos->posicao_submenus.Y = wherey();
                }

                /*Seta o lugar de impressao*/
                gotoxy(menu_config->posicao_menu_principal.X + tamanho_nome_menu, menu_config->posicao_menu_principal.Y);

                /*Verificacao para navegacao e exibicao da selecao de um menu*/
                if(arquivos->posicao_teclas_user == menus[i]->ordem)
                {
                    /*Pego a coordenada do menu atual caso o usuario pressione o enter, diferente da tecla alt*/
                    arquivos->posicao_submenus.X = wherex();
                    arquivos->posicao_submenus.Y = wherey();

                    /*Representa a cor de texto e fundo da opcao selecionada*/
                    textcolor(menu_config->cor3);
                    textbackground(menu_config->cor4);       

                }

                /*Imprime o menu*/
                printf("%s", menus[i]->nome_menu);

                /*Pego a posicao da primeira ocorrencia da letra de atalho*/
                posicao_letra = strchr(menus[i]->nome_menu, menus[i]->letra_atalho);
                index_letra_atalho = posicao_letra - menus[i]->nome_menu;

                /*Seta o lugar da onde deve ser impresso os menu*/
                gotoxy(menu_config->posicao_menu_principal.X + tamanho_nome_menu + index_letra_atalho, menu_config->posicao_menu_principal.Y);

                /*Verifica a posicao do usuario na navegacao do menu*/
                if(arquivos->posicao_teclas_user == menus[i]->ordem)
                {
                    /*Cor da letra de atalho quando for selecionada*/
                    textcolor(menu_config->cor6);
                }
                else
                {
                    /*Cor da letra de atalho quando nao esta selecionada a opcao*/
                    textcolor(menu_config->cor5);
                }

                /*Imprime a letra de atalho*/
                printf("%c", menus[i]->nome_menu[index_letra_atalho]);

                /*Caso o enter_pressionado ainda esta com o valor 1, entra nessa verificacao para chamar a funcao que imprimira os submenus*/
                if(arquivos->enter_pressionado)
                {
                    /*Chamada da funcao para exibir os submenus, a posicao_teclas_user deve receber -1 pois seu valor varia,
                    caso nao receba a impressao na hora da chamada da funcao saira errada*/
                    arquivos->retorno = Exibe_submenus(menus, menu_config, arquivos, menus[arquivos->posicao_teclas_user - 1]->id);
                    arquivos->nivel = 0;
                    arquivos->index_vetor = 0;
                    saida = 0;

                    /*Forca o i para sair do loop*/ 
                    i = arquivos->cont_menu_principal;
                
                }

                /*Representa a cor da opcao nao selecionada de um menu*/
                textcolor(menu_config->cor2);
                textbackground(menu_config->cor1);

                /*Armazena o espacamento de cada nome de menu, entre um e outro*/
                tamanho_nome_menu += strlen(menus[i]->nome_menu) + menu_config->espacamento;

            }

            /*O controle do enter volta a zerar*/
            arquivos->enter_pressionado = 0;

            /*Volta a zerar o controle de impressao*/
            arquivos->controla_impressao = 0;
        }

        /*Verifico se ha um hit do teclado*/
        if(hit(KEYBOARD_HIT))
        {
            /*Pego a tecla do teclado*/
            arquivos->teclas_evento = Evento();
        
            /*Verifico se eh um evento do teclado*/
            if(arquivos->teclas_evento.tipo_evento & KEY_EVENT)
            {
                /*Verifico se esta libreada a tecla*/
                if(arquivos->teclas_evento.teclado.status_tecla == LIBERADA)
                {
                    /*Pego as teclas*/
                    switch(arquivos->teclas_evento.teclado.key_code)
                    {   
                        /*Saida temporaria do programa*/
                        case ESC:
                        {
                            saida = 0;
                            break;
                        }

                        case SETA_PARA_DIREITA:
                        {
                            /*Verificacao a posicao em que o usuario esta, se caso for maior do que 0 e menor do que a contagem dos menus principais*/
                            if(arquivos->posicao_teclas_user < arquivos->cont_menu_principal)
                            {
                                /*Incremento a posicao onde o usuario esta e volto a seta a variavel de controle para 1, para impreimir novamente meu menu*/
                                arquivos->posicao_teclas_user += 1;
                                arquivos->controla_impressao = 1;   
                            }
                            break;
                        }

                        case SETA_PARA_ESQUERDA:
                        {
                            /*Verifcacao para decremento da navegacao do menu principal, tem que ser > que 1 pois a ordem dos menus comeca pelo numero 1*/
                            if(arquivos->posicao_teclas_user > 1)
                            {
                                arquivos->posicao_teclas_user -= 1;
                                arquivos->controla_impressao = 1;
                            }
                            break;
                        }

                        case ENTER:
                        {
                            arquivos->enter_pressionado = 1;
                            arquivos->controla_impressao = 1;
                            break;
                        }

                    }
                }
                else
                {
                    /*Verifica se eh o alt esquerdo sendo pressionado*/
                    if(arquivos->teclas_evento.teclado.status_teclas_controle & ALT_ESQUERDO)
                    {
                        /*Pego a proxima tecla a ser presionada, para verificacao dos menus*/
                        atalho_menu = arquivos->teclas_evento.teclado.ascii_code;

                        /*Volto a imprimir meu menu*/
                        arquivos->controla_impressao = 1;
                    }
                }
            }
        }

    }while(saida);

}

/*Funcao que exibira os submenus*/
int Exibe_submenus(MENU **menus, MENU_CONFIG *menu_config, ARQUIVOS *arquivos, int id_menu_principal)
{
    int i, quantidade_submenus = 0, largura_janela_submenu = 0;
    int tamanho = 0, posicao = 0;
    int saida = 1;

    /*Variavel que recebera o indice atual da selecao de um submenu*/
    int selecao_submenu = -1;

    /*char caractere_atalho;*/
    char *posicao_atalho;
    int indice_letra_atalho;

    while(saida)
    {
        /*Controle para impressao dos submenus*/
        if(arquivos->controla_impressao_submenus)
        {
            /*Como esta dentro de um loop infinito, eh necessario zerar a variavel para nao incrementar a quantidade de submenus novamente*/
            quantidade_submenus = 0;

            /*Posicao zera para posicionar corretamente meus submenus*/
            posicao = 0;

            /*loop para pegar a string de maior tamanho, que servira como largura do desenho da minha janela*/
            for(i = arquivos->cont_menu_principal; i < arquivos->cont_submenus + arquivos->cont_menu_principal; i++)
            {
                /*Verificacao para caso haja algum submenu na opcao selecionada do menu principal*/
                if(menus[i]->id_pai == id_menu_principal)
                {
                    /*Pego o tamanho da string atual*/
                    tamanho = strlen(menus[i]->nome_menu);
                    
                    /*Verificacao da maior string para desenhar posteriormente o quadrado que acomodara os submenus*/
                    if(tamanho > largura_janela_submenu)
                    {
                        /*Achei o maior faco a troca*/
                        largura_janela_submenu = tamanho;
                    }

                    /*Incrementa minha quantidade de submenus para desenhar minha janela*/
                    quantidade_submenus++;

                }
            }
            
            /*Caso haja submenus, desenha a janela e imprime as opcoes*/
            if(quantidade_submenus > 0)
            {
                /*Chama a funcao para desenhar minha janela de submenus*/
                Desenha_Janela_submenus(menu_config, arquivos, quantidade_submenus, largura_janela_submenu);

                /*Loop que percorre os submenus, o i comeca com a quantidade de menus principais contados ate a quantidade de menus como um todo*/
                for(i = arquivos->cont_menu_principal; i < arquivos->cont_submenus + arquivos->cont_menu_principal; i++)
                {
                    /*Verificacao para caso haja algum submenu na opcao selecionada do menu principal*/
                    if(menus[i]->id_pai == id_menu_principal)
                    {
                        /*Seta a posicao a ser impressa*/
                        gotoxy(arquivos->posicao_submenus.X + ESPACAMENTO_INICIO_FINAL_OPCAO, arquivos->posicao_submenus.Y + menu_config->altura/menu_config->largura + posicao + ESPACAMENTO_INICIO_FINAL_OPCAO);
                        
                        /*Verificacao para navegacao do submenu*/
                        if(arquivos->setas_submenus == menus[i]->ordem)
                        {
                            /*Cor de fundo da opcao e texto de navegacao*/
                            textcolor(menu_config->cor9);
                            textbackground(menu_config->cor10);

                            /*Ao estar em uma opcao, atribuo o valor para a variavel selecao_submenu, recebendo o indice atual*/
                            selecao_submenu = i;
                        }
                        else
                        {
                            /*Opcao nao selecionada de um submenu*/
                            textcolor(menu_config->cor8);
                        }

                        /*Imprime o submenu*/
                        printf("%s", menus[i]->nome_menu);

                        /*Pego a posicao da primeira ocorrencia da letra de atalho*/
                        posicao_atalho = strchr(menus[i]->nome_menu, menus[i]->letra_atalho);
                        indice_letra_atalho = posicao_atalho - menus[i]->nome_menu;

                        /*Seta a coordenada para a imressao da minha letra de atalho*/
                        gotoxy(arquivos->posicao_submenus.X + ESPACAMENTO_INICIO_FINAL_OPCAO + indice_letra_atalho, arquivos->posicao_submenus.Y + menu_config->altura/menu_config->largura + posicao + ESPACAMENTO_INICIO_FINAL_OPCAO);

                        /*Se o usuario esta na opcao, a cor da letra de atalho muda*/
                        if(arquivos->setas_submenus == menus[i]->ordem)
                        {
                            /*Letra de atalho selecionada*/
                            textcolor(menu_config->cor12);
                        }
                        else
                        {
                            /*Letra de atalho nao selecionada*/
                            textcolor(menu_config->cor11);
                        }
                        
                        /*Imprime a letra de atalho*/
                        printf("%c", menus[i]->nome_menu[indice_letra_atalho]);

                        /*Cor de fundo da janela do submenu, caso nao coloque, o fundo da selecao de um submenu continua e fica ruim visualmente*/
                        textbackground(menu_config->cor7);
                        posicao++;
                    }
                }
            }
            else
            {
                /*Faco minha pilha de ids receber o menu atual que foi impresso*/
                arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->id_submenu = id_menu_principal;   

                /*Decremento o nivel*/
                arquivos->nivel--;
                break;
            }

            /*Seta a 0 o controle de impressao novamente*/
            arquivos->controla_impressao_submenus = 0;

        }

        /*Pega uma acao do teclado*/
        if(hit(KEYBOARD_HIT))
        {
            /*Pega os eventos originarios do teclado e verifica pressionamento*/
            arquivos->eventos_submenus = Evento();

            if(arquivos->eventos_submenus.tipo_evento & KEY_EVENT)
            {
                if(arquivos->eventos_submenus.teclado.status_tecla == LIBERADA)
                {
                    switch(arquivos->eventos_submenus.teclado.key_code)
                    {
                        case ESC:
                        {
                            /*Verifico o nivel onde estou*/
                            if(arquivos->nivel > 0)
                            {
                                /*Coloco o save da minha ultima janela salva*/
                                puttext(1, 1, arquivos->limite_maximo_da_janela.X, arquivos->limite_maximo_da_janela.Y, arquivos->Tela[--arquivos->nivel]);

                                /*O id do menu a ser impresso agora recebe uma posição anterior ao do meu vetor de ids*/
                                id_menu_principal = arquivos->vetor_ids_coord_sub[--arquivos->index_vetor]->id_submenu;

                                /*Recoloco a coordenada anterior para ser impresso no lugar correto*/
                                arquivos->posicao_submenus.X = arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->coordenadas_para_sub.X;
                                arquivos->posicao_submenus.Y = arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->coordenadas_para_sub.Y;

                                /*Zero tanto as setas de controle de navegação e imprimo meu menu novamente*/
                                arquivos->setas_submenus = 1;
                                arquivos->controla_impressao_submenus = 1;
                            }
                            else
                            {
                                /*Zera a saida*/
                                saida = 0;
                            }
                            break;
                        }

                        case SETA_PARA_BAIXO:
                        {
                            /*Verificacao para navegacao no submenu*/
                            if(arquivos->setas_submenus < quantidade_submenus)
                            {
                                arquivos->setas_submenus++;
                                arquivos->controla_impressao_submenus = 1;
                            }
                            break;
                        }

                        case SETA_PARA_CIMA:
                        {
                            /*Verificacao a-para navegacao so submenu para cima*/
                            if(arquivos->setas_submenus > 1)
                            {
                                arquivos->setas_submenus--;
                                arquivos->controla_impressao_submenus = 1;
                            }
                            break;
                        }

                        case ENTER:
                        {
                            /*Verificacao caso seja selecionado um submenu*/
                            if(selecao_submenu != -1)
                            {
                                /*Guarda a tela da janela atual*/
                                _gettext(1, 1, arquivos->limite_maximo_da_janela.X, arquivos->limite_maximo_da_janela.Y, arquivos->Tela[arquivos->nivel]);
                                arquivos->nivel++;

                                /*O id principal vai para meu vetor de ids*/
                                arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->id_submenu = id_menu_principal;

                                /*Pego a posicao atual da coordenada do menu atual que vai para meu vetor de coordenadas dos submenus*/
                                arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->coordenadas_para_sub.X = arquivos->posicao_submenus.X;
                                arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->coordenadas_para_sub.Y = arquivos->posicao_submenus.Y;

                                /*Incremento o indice do vetor*/
                                arquivos->index_vetor++;

                                /*Id recebe o valor da aonde estou navegando*/
                                id_menu_principal = menus[selecao_submenu]->id;

                                /*Volta a imprimir novamente os submenus*/
                                arquivos->controla_impressao_submenus = 1;
                                arquivos->setas_submenus = 1;
                                
                                /*Faco as coordenadas receberem o tamanho da string selecionada, para o proximo menu ser impresso na linha do menu atual selecionado*/
                                tamanho = strlen(menus[selecao_submenu]->nome_menu) + ESPACAMENTO_INICIO_FINAL_OPCAO;
                                arquivos->posicao_submenus.X += tamanho;
                                arquivos->posicao_submenus.Y += menus[selecao_submenu]->ordem;

                                /*Chama novamente a funcao apra exibico de um novo submenu*/
                                Exibe_submenus(menus, menu_config, arquivos, id_menu_principal);

                                /*Recoloco o id anterior ao menu principal*/
                                id_menu_principal = arquivos->vetor_ids_coord_sub[arquivos->index_vetor]->id_submenu;
                            }     
                            break;
                        }
                    }
                }
                else
                {
                    /*Verificacao do pressionamento do alt*/
                    if(arquivos->eventos_submenus.teclado.status_teclas_controle & ALT_ESQUERDO)
                    {
                        /*Pego o caractere de atalho
                        caractere_atalho = arquivos->eventos_submenus.teclado.ascii_code;*/
                    }
                }
            }
        }
        
    }

    /*Retorna o ultimo menu selecionado*/
    return id_menu_principal;

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

    /*Atribuo a coordenada para impressao dos menus principais*/
    menu_config->posicao_menu_principal.X = 1;
    menu_config->posicao_menu_principal.Y = 1;

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

                    /*Converto e atribuo para o valor correspondente da estrutura*/
                    menus[i]->id_pai = atoi(corta_string);
                    corta_string = strtok(NULL, " ");
                    menus[i]->id = atoi(corta_string);
                    corta_string = strtok(NULL, " ");
                    menus[i]->ordem = atoi(corta_string);
                }
            }
        }
    }

    /*Tokenizo a string de acordo com os espacos*/
    delimitador = strtok(arquivos->vetor_arquivo_cores, " ");

    /*Loop para pegar cada caractere e transformar em inteiro para meu vetor auxiliar, esse loop e para o arquivo config.txt*/
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

    /*Depois da alocacao e inicializacao das estruturas, chamo a funcao para ordenar os menus como um todo*/
    Ordena_menus(menus, arquivos);

    /*Chama a funcao para contagem dos menus e submenus das estruturas*/
    Contagem_menus_submenus(menus, arquivos);

    /*Como os menus ja foram ordenados, chamo a funcao responsavel por exibir cada menu principal*/
    Exibe_menu_principal(menus, menu_config, arquivos);
}

/*Funcao responsavel por inicializar varaiveis que serao usadas no decorrer do programa como um todo*/
void Inicializa_variaveis_diversas(ARQUIVOS *arquivos)
{
    /*Inicializacoes*/
    arquivos->controla_impressao = 1;
    arquivos->tamanho_cada_string = 0;
    arquivos->posicao_teclas_user = 1;
    arquivos->index_menus = 0;
    arquivos->controla_atalho = 0;
    arquivos->enter_pressionado = 0;
    arquivos->cont_menu_principal = 0;
    arquivos->cont_submenus = 0;
    arquivos->controla_impressao_submenus = 1;
    arquivos->setas_submenus = 1;
    arquivos->nivel = 0;
    arquivos->index_vetor = 0;
    arquivos->retorno = 0;
}
    

/*Funcao resonsavel por automatizar a criacao de menus*/
int Menu(char *arquivo_menus, char *arquivo_cores)
{
    ARQUIVOS arquivos;

    /*Chamada da funcao para inicializacao de diversas variaveis que serao usada no programa*/
    Inicializa_variaveis_diversas(&arquivos);
    
    /*Desliga o cursor*/
    setCursorStatus(DESLIGAR);

    /*Chamada da funcao para realizar a abertura e leitura dos arquivos*/
    Abre_arquivos_e_aloca_memoria(arquivo_menus, arquivo_cores, &arquivos);

    /*seta as cores originais do cmd*/
    setCursorStatus(LIGAR);
    textcolor(LIGHTGRAY);
    textbackground(BLACK);

    /*Retorna o ultimo id selecionado para impressao na main*/
    return arquivos.retorno;
}


/*Funcao responsavel por ordenar todos menus*/
void Ordena_menus(MENU **menus, ARQUIVOS *arquivos)
{
    int i, j, indice_para_troca;

    /*Estrutura auxiliar que sera resposavel por trocar com outras de menor valor, baseados no id_pai e ordem*/
    MENU *troca;

    /*Percorre as estruturas*/
    for(i = 0; i < arquivos->conta_linhas_arquivo - 1; i++)
    {
        /*O indice que vai servir para trocar as estruturas para ordenacao recebe a posicao do i*/
        indice_para_troca = i;

        /*Percorre novamente o arquivo*/
        for(j = i + 1; j < arquivos->conta_linhas_arquivo; j++)
        {
            /*Verificacao para saber qual pai e menor que o outro na posicao onde o indice_para_troca foi pego, nesse modelo tanto o id_pai eh ordenado quanto o campo ordem de cada estrutura,
            assim na impressao me gera a estrutura sequencialmente ordenada, do menor para o maior valor ordenado, pelo id_pai e ordem.*/
            if(menus[j]->id_pai < menus[indice_para_troca]->id_pai || (menus[j]->id_pai == menus[indice_para_troca]->id_pai && menus[j]->ordem < menus[indice_para_troca]->ordem))
            {
                /*Pego o indice atual de j, para fazer a troca depois na verificacao*/
                indice_para_troca = j;
            }
        }
        
        /*Caso o indice de indice_para_troca seja diferente de j, faz a troca*/
        if(indice_para_troca != i)
        {
            /*A estrutura troca recebe toda a estrutura atual do indice de menus na posicao i*/
            troca = menus[i];

            /*No mesmo indice i, na estrutura menus, o valor do elemento na posicao indice_para_troca eh atribuido a menus[i]*/
            menus[i] = menus[indice_para_troca];

            /*Na estrutura a paritr do indice_para_troca, faco a troca de estruturas com a estrutura 'troca', pois ela esta com a estrutura que deve ser trocada*/
            menus[indice_para_troca] = troca;

            /*A troca acima eh realizada para toda estrutura, ou seja, ao inves de trocar as ordens de cada estrutura ou o id_pai, melhor trocar a estrutura
            como um todo, porque ai e ir imprimindo sequencialmente nesse caso, pois as estruturas ja foram armazenadas e ordenadas como um todo*/

        }
    }

}