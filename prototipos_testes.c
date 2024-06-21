
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

    /*Funcao que exibe meu menu*/
void Exibe_menu_principal(MENU **menus, MENU_CONFIG *menu_config, ARQUIVOS *arquivos)
{
    int i, j;
    int tamanho = 0;

    /*A coordenada para impressao e setada pra 1, onde sera impresso meu menu principal*/
    menu_config->posicao_menu_principal.X = 1;
    menu_config->posicao_menu_principal.Y = 1; 


   
    
}

/*Funcao para inicializar os campos dos meus menus, ids, ordem, etc*/
void Inicializa_estruturas_menus(MENU **menus, ARQUIVOS *arquivos, MENU_CONFIG *menu_config)
{
    int i, j, index_string = 0;
    char caractere;
    char *delimitador;
    int tamanho = 0;
    int index_aux = 0;
    int vetor_aux[TAM_VETOR_AUX_TOKENIZACAO];

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

    /*Depois da alocacao e inicializacao das estruturas, chamo a funcao para exibir o menu*/
    Exibe_menu_principal(menus, menu_config, arquivos);


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


    /*Imprime meu menu na horizontal*/
    for(i = 0; i < arquivos->conta_linhas_arquivo; i++)
    {
        /*Verifico se e um menu principal, que sera impresso na horizontal*/
        if(menus[i]->id_pai == 0)
        {
            /*Seto a impressao e imprimo o menu*/
            gotoxy(menu_config->posicao_menu_principal.X + tamanho, menu_config->posicao_menu_principal.Y);
            textbackground(menu_config->cor1);
            
            /*Faco o tamanho receber o tamanho da opcao mais o espacamento que tem na variavel da estrutura de configuracoes do menu*/
            tamanho += strlen(menus[i]->nome_menu) + menu_config->espacamento;
        }
        else
        {
            /*Loop para submenus*/
            for(j = 0; j < arquivos->conta_linhas_arquivo; j++)
            {
                /*Verifico os submenus*/
                if(menus[i]->id_pai == menus[j]->id)
                {
                    gotoxy(menu_config->posicao_menu_principal.X + j, menu_config->posicao_menu_principal.Y + i);
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
                switch(arquivos->teclas_evento.teclado.key_code)
                {
                    case ESC:
                    {
                        setCursorStatus(LIGAR);
                        textbackground(BLACK);
                        textcolor(LIGHTGRAY);
                        exit(0);
                        break;
                    }
                }
            }
        }



        /*PROTOTIPO DA FUNÇÃO PARA IMPRESSAO DO MENU COM  ALGUMAS CORES*/
        /*Variavel evento para pegar as teclas do teclado*/
    EVENTO tecla;

    while(1)
    {
        /*Verifico se e um menu pai*/
        if(menus[arquivos->index_menus]->id_pai == 0)
        {
            /*Seto o lugar de impressao na tela*/
            gotoxy(menu_config->posicao_menu_principal.X + arquivos->tamanho_cada_string, menu_config->posicao_menu_principal.Y + menu_config->altura/menu_config->largura/2);

            /*Verifico se o usuario esta na opcao correta*/
            if(arquivos->tamanho_cada_string == arquivos->posicao_teclas_user)
            {
                /*Cor de texto e fundo da opcao selecionada do menu principal*/
                textcolor(menu_config->cor3);
                textbackground(menu_config->cor4);
            }
            
            /*Imprime a opcao do menu*/
            printf("%s", menus[arquivos->index_menus]->nome_menu);
            
            /*Cor das opcoes nao selecionadas do menu*/
            textbackground(menu_config->cor2);

            /*Espacamento de cada string*/
            arquivos->tamanho_cada_string += strlen(menus[arquivos->index_menus]->nome_menu) + menu_config->espacamento;

            arquivos->index_menus++;
        }


        /*TENTAR VERIFICAR A ORDEM DOS MENUS, TENTAR ENCAIXAR ESSA LOGICA NA FUNCAO RECURSIVA,
        OU CRIAR ALGO PARA FAZER LOOP E PEGAR A ORDEM MENOR DOS MENUS PAIS OU SUBMENUS*/

        /*Pego uma acao do teclado*/
        if(hit(KEYBOARD_HIT))
        {
            tecla = Evento();
            
            /*Pego o evento do teclado*/
            if(tecla.tipo_evento & KEY_EVENT)
            {
                /*Verifico a liberacao da tecla*/
                if(tecla.teclado.status_tecla == LIBERADA)
                {
                    /*Cases para as teclas do teclado*/
                    switch(tecla.teclado.key_code)
                    {
                        /*Saida por enquanto*/
                        case ESC:
                        {
                            setCursorStatus(LIGAR);
                            textcolor(LIGHTGRAY);
                            textbackground(BLACK);
                            exit(0);
                            break;
                        }

                        /*Navegacao no menu*/
                        case SETA_PARA_DIREITA:
                        {
                            arquivos->posicao_teclas_user = arquivos->tamanho_cada_string;
                            break;
                        }

                    }
                }
            }
        }

        
    }

     /*Loop para percorrer e ordenar a ordem dos menus que serao impressos*/
    for(i = 0 ; i < arquivos->conta_linhas_arquivo; i++)
    {
        /*Percorre para trocar os valores*/
        for(j = 0; j < arquivos->conta_linhas_arquivo - i - 1; j++)
        {
            /*Se caso for maior*/
            if(menus[j]->ordem > menus[j + 1]->ordem && (menus[j]->id_pai == 0 && menus[j + 1]->id_pai == 0))
            {
                /*Variavel recebe o maior elemento*/
                troca = menus[j]->ordem;
                
                /*O menor uma posicao a frente eh colocado na posicao atual, a do maior elemento*/
                menus[j]->ordem = menus[j + 1]->ordem;
                
                /*A posicao com o menor elemento encontrado agora recebe o maior*/
                menus[j + 1]->ordem = troca;
            }
        }
        
    }