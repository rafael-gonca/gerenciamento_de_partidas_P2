# Sistema de Gerenciamento de Partidas (Estrutura de Dados - Parte II)

Neste trabalho prático, desenvolvemos um sistema completo de gerenciamento de dados para um campeonato de futebol. Nesta segunda etapa, o foco principal é a manutenção dos dados (inserção, remoção e atualização de partidas) e a ordenação da tabela de classificação baseada no mérito esportivo, utilizando alocação dinâmica e listas simplesmente encadeadas.

## Estrutura do Sistema

- `main.c`: Arquivo principal que contém o loop de execução e gerencia as opções do menu interativo.
- `campeonato.c` / `campeonato.h`: Responsável por processar os resultados das partidas para atualizar as estatísticas de vitórias, derrotas, empates e saldo de gols dos times, além de gerenciar as funcionalidades do menu.
- `bd_times.c` / `bd_times.h`: Gerencia a coleção de times utilizando uma **lista encadeada**. É responsável por carregar os dados de `times.csv`, buscar registros e ordenar a tabela de classificação.
- `bd_partidas.c` / `bd_partidas.h`: Gerencia o histórico de confrontos através de uma **lista encadeada**. Lida com o espelhamento do `partidas.csv` em memória e as operações de manutenção (inserção, atualização e exclusão).
- `time.c` / `time.h`: Define a estrutura (struct) de um Time e encapsulan seus dados e estatísticas (Pontos, Saldo de Gols, etc.).
- `partida.h` / `partida.c`: Define a abstração de um confronto, encapsulando os IDs dos times envolvidos e o placar.
- `Makefile`: Contém o comando de compilação, execução e limpeza dos arquivos gerados pelo programa.

## Funcionalidades Implementadas

O sistema permite a execução de 6 operações principais a partir do menu interativo:

1. **Consultar time:** Permite buscar um time específico digitando seu nome ou prefixo. O sistema calcula e exibe Vitórias, Empates, Derrotas, Gols Marcados, Gols Sofridos, Saldo de Gols e Pontuação Total.
2. **Consultar partidas:** Filtra e exibe o histórico de jogos cadastrados. Possui três modos de busca: por time mandante, visitante, ou ambos.
3. **Atualizar partida:** Permite alterar o placar de um jogo existente, recalculando automaticamente as estatísticas de ambos os times na tabela.
4. **Remover partida:** Exclui um registro do sistema definitivamente (após confirmação), revertendo os pontos e gols associados com aquele confronto.
5. **Inserir partida:** Adiciona um novo confronto com geração automática de ID e atualiza imediatamente a pontuação das equipes envolvidas.
6. **Imprimir tabela de classificação (Opção 6):** Exibe a tabela completa do campeonato, formatada e alinhada dinamicamente na tela, listando o desempenho completo de todas as equipes.

## Principais Decisões de Implementação

- **Listas Encadeadas e Alocação Dinâmica:** Para o gerenciamento de registros nesta etapa, abandonamos os vetores estáticos em favor de listas simplesmente encadeadas em `BDTimes` e `BDPartidas`. Isso permite a manipulação da memória sob demanda durante as operações de inserção e remoção de partidas.

- **TADs e Encapsulamento:** As estruturas (`structs`) reais de `Time` e `Partida` estão ocultas nos arquivos `.c`. Apenas os ponteiros são expostos nos cabeçalhos (`.h`), forçando a manipulação segura dos dados exclusivamente por meio de métodos "getters", "setters" e funções de soma/remoção de estatísticas.

- **Algoritmo de Ordenação (Bubble Sort):** Para gerar a tabela de classificação, a lista encadeada de times é ordenada internamente. Para otimizar a operação e evitar o risco de perder referências (memory leaks), o algoritmo apenas troca os ponteiros dos dados (cargas úteis) entre os nós, em vez de reordenar os nós físicos da lista.

- **Rollback de Resultados:** Nas rotinas de atualização e exclusão de partidas, o sistema reverte as estatísticas antigas (`time_remove_gols`, `time_remove_vitoria`) antes de aplicar as novas, eliminando a necessidade de recalcular todo o campeonato do zero a cada alteração.

- **Correção de Alinhamento UTF-8:** Utilização da biblioteca `<wchar.h>` e da função `mbstowcs`. Como os acentos ocupam "bytes extras" e quebram a formatação padrão do `printf`, essa função nos permite contar a quantidade real de letras visíveis, mantendo a tabela perfeitamente alinhada.

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
