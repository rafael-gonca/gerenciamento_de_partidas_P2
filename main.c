#include <stdio.h>

void limpar_cmd(){
    printf("\033[H\033[J");
}

void menu_display(){
    printf("Sistema de Gerenciamento de Partidas\n\n1 - Consultar time\n2 - Consultar partidas\n3 - Atualizar partida\n4 - Remover partida\n5 - Inserir partida\n6 - Imprimir tabela de classificação\nQ - Sair\n\n");
}

int main(){
    char menu_option = '0';
    
    while (menu_option != 'Q'){
        limpar_cmd();
        menu_display();

        scanf("%c", &menu_option);
        
        switch (menu_option){
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case 'Q':
                break;
            default:
                printf("selecione uma opção válida");
        }
    }
    
    return 0;
}