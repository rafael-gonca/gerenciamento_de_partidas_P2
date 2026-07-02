#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "bd_times.h"
#include "bd_partidas.h"
#include "campeonato.h"

// Limpa a tela do terminal
void limpar_cmd(){
    printf("\033[H\033[J");
}

// Limpa o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe o menu de opções principal
void menu_display(){
    printf("\nSistema de Gerenciamento de Partidas\n\n1 - Consultar time\n2 - Consultar partidas\n3 - Atualizar partida\n4 - Remover partida\n5 - Inserir partida\n6 - Imprimir tabela de classificação\nQ - Sair\n\n");
}

int main(){
    setlocale(LC_ALL, "");

    BDTimes *meus_times = criar_bd_times();
    BDPartidas *minhas_partidas = criar_bd_partidas();

    processar_dados(meus_times, minhas_partidas);

    limpar_cmd();

    char menu_option = '0';

    // Inicia o menu principal
    while (menu_option != 'Q' && menu_option != 'q'){

        menu_display();
        scanf(" %c", &menu_option);
        limpar_buffer();

        // Mostra as opções
        switch (menu_option){
            case '1':
                limpar_cmd();
                
                // Roda a consulta de times
                caso_1(meus_times);
                break;
            case '2':
                limpar_cmd();
                char case_2_option = '0';

                // Inicia o menu secundario para consulta de partidas
                while (case_2_option != '4'){

                    // Pega a opção de consulta
                    printf("\nEscolha o modo de consulta:\n1 - Por time mandante\n2 - Por time visitante\n3 - Por time mandante ou visitante\n4 - Retornar ao menu principal\n\n");
                    scanf(" %c", &case_2_option);
                    limpar_buffer();

                    // O if verifica se a opção é válida, se for, ele envia o número para a função caso_2, se não, ele mostra mensagem de erro ou fecha o menu
                    if (case_2_option == '1' || case_2_option == '2' || case_2_option == '3'){
                        limpar_cmd();
                        int opt = case_2_option - '0';
                        caso_2(meus_times, minhas_partidas, opt);
                    }
                    else if (case_2_option == '4') {
                        limpar_cmd();
                        break;
                    }
                    else {
                        limpar_cmd();
                        printf("selecione uma opção válida\n");
                    }
                }   

                break;

            case '3':
                limpar_cmd();
                // Roda a função para atualizar uma partida
                caso_3(meus_times, minhas_partidas);
                break;

            case '4':
                limpar_cmd();
                // Roda a função para remover uma partida
                caso_4(meus_times, minhas_partidas);
                break;

            case '5':
                limpar_cmd();
                // Roda a função para inserir uma nova partida
                caso_5(meus_times, minhas_partidas);
                break;

            case '6':
                limpar_cmd();
                // Roda a função para imprimir a tabela de classificação, sem outros argumentos ou prefixos
                tabela_classificacao(meus_times);
                break;

            // Fecha o menu e o programa
            case 'Q':
            case 'q':
                limpar_cmd();
                break;

            default:
                limpar_cmd();
                printf("\nselecione uma opção válida \n");
        }
    }
    
    destruir_bd_times(meus_times);
    destruir_bd_partidas(minhas_partidas);

    return 0;
}
