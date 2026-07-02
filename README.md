# Sistema de Gerenciamento de Partidas (Estrutura de Dados - Parte I)

Neste trabalho prático, desenvolvemos um sistema de gerenciamento de partidas de um campeonato para a disciplina de Estrutura de Dados. Neste primeiro momento, o sistema é limitado a **consultar times**, **consultar partidas** e **imprimir a tabela de classificação** por meio de um menu interativo. Os dados dos times e partidas são carregados de dois arquivos (`times.csv` e `partidas.csv`) externos.

## Estrutura do Sistema

- `main.c`: Arquivo principal que contém o loop de execução e gerencia as opções do menu interativo.
- `campeonato.c` / `campeonato.h`: Responsável por processar os resultados das partidas para atualizar as estatísticas de vitórias, derrotas e empates dos times, além de gerenciar algumas funcionalidades do menu.
- `bd_times.c` / `bd_times.h`: Gerencia a "base de dados" dos times na memória. É responsável por carregar os dados do `times.csv`, buscar times específicos e imprimir a tabela de classificação.
- `bd_partidas.c` / `bd_partidas.h`: Gerencia a base de dados das partidas. É responsável por carregar os dados do `partidas.csv` e executar a lógica de listagem e filtragem de jogos.
- `time.c` / `time.h`: Define a estrutura (struct) de um Time e contém as funções de calcular os pontos e o saldo de gols.
- `partida.h`: Define a estrutura (struct) básica de uma partida.
- `Makefile`: Contém o comando de compilação, execução e limpeza dos arquivos gerados pelo programa.

## TADs (Tipos Abstratos de Dados) 

- `partida.h`: Define a estrutura de uma partida.
```c
typedef struct {
    int ID;
    int Time1ID;
    int Time2ID;
    int Time3ID;
    int GolsTime1;
    int GolsTime2;
    int GolsTime3;
} Partida;
```
/* matheus esteve aquii novamente
*/
- `time.h`: Define a estrutura de um time.
```c
typedef struct {
    int ID;
    char Nome[49];
    int V;
    int E;
    int D;
    int GM;
    int GS;
} Time;
```

- `bd_times.h`: Define a estrutura dos times.
```c
typedef struct {
    int quantidade;
    Time times[10];
} BDTimes;
```

- `bd_partidas.h`: Define a estrutura das partidas.
```c
typedef struct {
    int quantidade;
    Partida partidas[80];
    int quantidade2;
} BDPartidas;
```

## Funcionalidades Implementadas

Atualmente o sistema funciona com as seguintes opções do menu interativo:

- **Consultar time (Opção 1):** Permite buscar um time específico digitando seu nome ou prefixo. O sistema calcula e exibe Vitórias, Empates, Derrotas, Gols Marcados, Gols Sofridos, Saldo de Gols e Pontuação Total.
- **Consultar partidas (Opção 2):** Filtra e exibe o histórico de jogos cadastrados. Possui três modos de busca:
  - Exibir partidas onde o time foi mandante (Opção 1).
  - Exibir partidas onde o time foi visitante (Opção 2).
  - Exibir todas as partidas em que o time foi mandante ou visitante (Opção 3).
- **Imprimir tabela de classificação (Opção 6):** Exibe a tabela completa do campeonato, formatada e alinhada dinamicamente na tela, listando o desempenho completo de todas as equipes.

*Nota: As opções de **Atualizar partida**, **Remover partida** e **Inserir partida** (opções 3, 4 e 5) já estão no menu do sistema, mas serão implementadas na Parte II do trabalho.*

## Principais Decisões de Implementação

- **Uso de Vetores Estáticos:** Para facilitar o gerenciamento dos registros nesta primeira etapa, utilizamos vetores de tamanho fixo (10 times e 90 partidas) nas structs de BD. A escolha pelo vetor estático é baseada na simplicidade da implementação e na previsibilidade do consumo de memória.

- **Carregamento Inicial em CSV:** A leitura dos arquivos `times.csv` e `partidas.csv` ocorre apenas uma vez na inicialização do programa. Os dados ficam na memória, evitando leituras repetidas no disco durante a execução do menu.

- **Busca por Prefixo e Insensível a Caso:** Utilização da função `strncasecmp` nas consultas. Isso permite achar um time digitando seja apenas o começo do nome, ou o nome completo, evitando erros se o usuário misturar letras maiúsculas e minúsculas.

- **Correção de Alinhamento (UTF-8):** Utilização da biblioteca `<wchar.h>` e da função `mbstowcs`. Como os acentos ocupam "bytes extras" e quebram a formatação padrão do `printf`, essa função nos permite contar a quantidade real de letras visíveis, mantendo a tabela perfeitamente alinhada.

- **Modularização:** Fornece uma separação clara para manter boas práticas e evitar que o `main` fique gigante.

## Como Executar o Programa

### Pré-requisitos

Para rodar este programa, você precisará de um ambiente configurado com um compilador C.

Como utilizamos um `Makefile` para automatizar o processo de compilação e execução, você também precisará da ferramenta de automação `Make`.

Por fim, certifique-se de ter o `gcc` (GNU Compiler Collection) instalado:

- **No Linux (Debian/Ubuntu/Xubuntu):** Geralmente, basta instalar o pacote essencial de construção:
  ```bash
  sudo apt update
  sudo apt install build-essential
  ```
- **No Windows:** Recomendamos a utilização do [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/pt-br/windows/wsl/install).

### Baixando o Sistema

Clone este repositório via Git e acesse o diretório do projeto:
```bash
git clone https://github.com/rafael-gonca/gerenciamento_de_partidas_P1.git
cd gerenciamento_de_partidas_P1
```
*(Nota: Lembre-se de garantir que os arquivos `times.csv` e `partidas.csv` estejam no mesmo diretório que o código fonte antes de executar o programa).*

### Compilar e Executar (usando Makefile)

Para compilar todos os arquivos `.c` e iniciar o menu interativo automaticamente, execute o comando abaixo no terminal:

```bash
make all
```

### Limpeza dos Arquivos Gerados

Para manter o diretório do projeto limpo após o uso, removendo o arquivo executável gerado, utilize o comando de limpeza:

```bash
make clean
```