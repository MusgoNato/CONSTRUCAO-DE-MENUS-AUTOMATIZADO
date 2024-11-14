# CONSTRUÇÃO DE MENUS AUTOMATIZADOS

![GitHub repo size](https://img.shields.io/github/repo-size/iuricode/README-template?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/iuricode/README-template?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/iuricode/README-template?style=for-the-badge)

<img src="/video-code/video-menu.gif" alt="Codigo Rodando">

> O programa exibe o último ID do menu ou submenu selecionado, permitindo o acesso a eles por teclas de atalho. É possível a adição de mais menus e submenus, assim como a modificação das cores referentes a janela, texto, bordas e fundo da janela.

## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:

- Você instalou a versão mais recente da linguagem `<C>`
- Você instalou a versão mais recente do `<GCC>`
- Você tem uma máquina `<Windows / Linux / Mac>`.

## 🚀 Veja o Projeto

Siga estas etapas:

- Baixe os arquivos do repositório.
- Instale o gcc mais recente para compilar e executar o programa.
- Abra o CMD na pasta aonde foi baixado o repositório e insira os seguintes comandos para compilar e executar o código:

Compilação:

``` 
gcc main.c -o main.exe console_v1.5.5.c conio_v3.2.4.c menu.c -Wall -pedantic -Wextra -Werror
```

Execução:

```
main.exe
```

## ℹ️ Funcionamento do Programa

Existem 2 arquivos essencias em todo este projeto.

- config.txt
- menu.txt

Cada arquivo é referente ao preenchimento de cores ou informações do menu.

- [config.txt] conterá a seguinte linha abaixo:

```
1  7  15  2  15  12  7  0  15  2  15  12  1  7  7 1 70  20  50
```

Onde a listagem a seguir explica cada valor:
 
* O 1° valor até o 16° valor são referentes a cores, como fundo da janela, borda dos submenus abertos, cor da fonte, cor do fundo da opção selecionada, etc.
* 17° valor é referente a largura que a janela ocupará.
* 18° valor é referente a altura que a janela ocupará.
* 19° valor é o espaçamento que terá entre uma opção e outra.

- [menu.txt] conterá as seguintes informações:

```
0 1 1 "Arquivo" A
0 2 2 "Salvar" S
0 23 3 "Gastos" G
1 3 1 "Dados pessoais" D
1 4 3 "Alimentação" A
1 5 2 "Investimentos" I
2 6 1 "ARQUIVOS" Q
6 7 1 "DADOS PESSOAIS" D
6 8 2 "INVESTIMENTOS" I
6 9 3 "ALIMENTAÇÃO" A
4 10 1 "Adicionar refeição" i
4 11 2 "Adicionar bebida" b
4 12 3 "Calorias totais" C
5 13 1 "CDB" C
5 14 2 "Ações" s
5 15 3 "Poupança" P
5 16 4 "Criptoativos" C
10 17 1 "Pão com mortadela" m
10 18 2 "Presunto" P
11 19 1 "Suco de limão" l
```
- [ID_DO_PAI]: O ID do pai de algum submenu.
- [ID_DO_MENU]: ID do próprio menu.
- [DESCRIÇÃO]: Descrição do titulo daquele menu.
- [TECLA_DE_ATALHO]: Tecla de atalho para acesso do menu.

## 🤝 Desenvolvedor
<table>
    <td align="center">
      <a href="https://github.com/MusgoNato" title="Perfil Github">
        <img src="https://avatars.githubusercontent.com/u/131496781?v=4" width="100px;" alt="Foto do Hugo"/><br>
        <sub>
          <b>Hugo Josué Lema Das Neves</b>
        </sub>
      </a>
    </td>
  </tr>
</table>