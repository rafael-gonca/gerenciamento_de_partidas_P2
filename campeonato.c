#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

// Função que lê os dados dos arquivos e atualiza os bancos de dados
void processar_dados(BDTimes *bd_t, BDPartidas *bd_p){
    carregar_times(bd_t);
    carregar_partidas(bd_p);

    PartidaNode *p_atual = get_primeira_partida(bd_p);
    
    while (p_atual != NULL) {
        Partida *p = get_dados_partida(p_atual);

        Time *t1 = buscar_time_por_id(bd_t, partida_get_t1(p));
        Time *t2 = buscar_time_por_id(bd_t, partida_get_t2(p));

        if (t1 != NULL && t2 != NULL) {
            int gols1 = partida_get_g1(p);
            int gols2 = partida_get_g2(p);

            time_add_gols(t1, gols1, gols2);
            time_add_gols(t2, gols2, gols1);
            
            if (gols1 > gols2){
                time_add_vitoria(t1);
                time_add_derrota(t2);
            } else if (gols1 < gols2){
                time_add_derrota(t1);
                time_add_vitoria(t2);
            } else {
                time_add_empate(t1);
                time_add_empate(t2);
            }
        }
        p_atual = get_proxima_partida(p_atual); 
    }
}

// Função que lê o prefixo e executa a consulta de times
void caso_1(BDTimes *bd_t){

    //inicializa uma variável para armazenar o nome ou prefixo do time
    char select_time[50];
    printf("Digite o nome ou prefixo do time: ");
    scanf(" %s", select_time);

    //faz a consulta de times
    consultar_times(bd_t, select_time);
}

// Função que lê o prefixo e executa a consulta de partidas, já com o modo selecionado no main
void caso_2(BDTimes *bd_t, BDPartidas *bd_p, int opt){

    //inicializa uma variável para armazenar o nome ou prefixo do time, para a consulta de partidas com esse time
    char prefixo[50];
    printf("Digite o nome: ");
    scanf("%s", prefixo);

    //faz a consulta de partidas já com o modo selecionado
    consultar_partidas(bd_p, bd_t, opt, prefixo);
}

// Função que lê o ID da partida e os novos gols, atualiza a partida
void caso_3(BDTimes *bd_t, BDPartidas *bd_p) {
    char prefixo[50];
    
    printf("Atualizar Partida\n");
    printf("Digite o nome ou prefixo do time para localizar a partida: ");
    scanf(" %s", prefixo);
    consultar_partidas(bd_p, bd_t, 3, prefixo); 

    int id_atualizar;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%d", &id_atualizar);

    // Busca a partida no BD
    Partida *p = buscar_partida_por_id(bd_p, id_atualizar);
    if (p == NULL) {
        printf("\nErro: Partida com ID %d nao encontrada.\n", id_atualizar);
        return;
    }

    Time *t1 = buscar_time_por_id(bd_t, partida_get_t1(p));
    Time *t2 = buscar_time_por_id(bd_t, partida_get_t2(p));

    char input_g1[10], input_g2[10];
    printf("\nPara manter o valor atual de um campo, digite '-'\n");
    
    printf("Digite o novo placar para o %s (Mandante): ", time_get_nome(t1));
    scanf(" %s", input_g1);
    
    printf("Digite o novo placar para o %s (Visitante): ", time_get_nome(t2));
    scanf(" %s", input_g2);

    // Lógica para manter o antigo (se for '-') ou converter o texto para número (atoi)
    int novo_g1;
    if (input_g1[0] == '-') {
        novo_g1 = partida_get_g1(p);
    } else {
        novo_g1 = atoi(input_g1);
    }

    int novo_g2;
    if (input_g2[0] == '-') {
        novo_g2 = partida_get_g2(p);
    } else {
        novo_g2 = atoi(input_g2);
    }

    // Confirmação
    printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
    printf("%-5s %-15s %-15s %-10s %-10s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
    printf("%-5d %-15s %-15s %-10d %-10d\n",
        partida_get_id(p), time_get_nome(t1), time_get_nome(t2),
        novo_g1, novo_g2
    );

    char conf;
    scanf(" %c", &conf);

    if (conf == 'S' || conf == 's') {
        int g1_velho = partida_get_g1(p);
        int g2_velho = partida_get_g2(p);

        if (t1 != NULL && t2 != NULL) {
            
            time_remove_gols(t1, g1_velho, g2_velho);
            time_remove_gols(t2, g2_velho, g1_velho);

            if (g1_velho > g2_velho) {
                time_remove_vitoria(t1);
                time_remove_derrota(t2);
            }
            else if (g1_velho < g2_velho) {
                time_remove_derrota(t1);
                time_remove_vitoria(t2);
            }
            else {
                time_remove_empate(t1);
                time_remove_empate(t2);
            }

            // Atualiza o placar
            partida_set_placar(p, novo_g1, novo_g2);

            time_add_gols(t1, novo_g1, novo_g2);
            time_add_gols(t2, novo_g2, novo_g1);
            if (novo_g1 > novo_g2) {
                time_add_vitoria(t1);
                time_add_derrota(t2);
            }
            else if (novo_g1 < novo_g2) {
                time_add_derrota(t1);
                time_add_vitoria(t2);
            }
            else {
                time_add_empate(t1);
                time_add_empate(t2);
            }
        }
        
        printf("\nRegistro atualizado com sucesso.\n");
    } else {
        printf("\nOperacao cancelada.\n");
    }
}

// Função que lê o ID da partida a ser removida, confirma com o usuário e remove a partida
void caso_4(BDTimes *bd_t, BDPartidas *bd_p) {
    char prefixo[50];

    // Pede o nome ou prefixo do time para localizar a partida
    printf("Digite o nome do time para localizar o ID da partida: ");
    scanf(" %s", prefixo);
    consultar_partidas(bd_p, bd_t, 3, prefixo); 

    // Pede o ID da partida que vai ser removida
    int id_remover;
    printf("\nDigite o ID do registro a ser removido: ");
    scanf("%d", &id_remover);

    // Busca a partida no BD
    Partida *p = buscar_partida_por_id(bd_p, id_remover);
    if (p == NULL) {
        printf("\nErro: Partida com ID %d nao encontrada.\n", id_remover);
        return;
    }

    Time *t1 = buscar_time_por_id(bd_t, partida_get_t1(p));
    Time *t2 = buscar_time_por_id(bd_t, partida_get_t2(p));

    // Confirmação
    printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n");
    printf("%-5s %-15s %-15s %-10s %-10s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
    printf("%-5d %-15s %-15s %-10d %-10d\n",
        partida_get_id(p), time_get_nome(t1), time_get_nome(t2),
        partida_get_g1(p), partida_get_g2(p)
    );

    char conf;
    scanf(" %c", &conf);
    
    if (conf == 'S' || conf == 's') {
        int gols1 = partida_get_g1(p);
        int gols2 = partida_get_g2(p);

        if (t1 != NULL && t2 != NULL) {
            time_remove_gols(t1, gols1, gols2);
            time_remove_gols(t2, gols2, gols1);

            if (gols1 > gols2) {
                time_remove_vitoria(t1);
                time_remove_derrota(t2);
            } else if (gols1 < gols2) {
                time_remove_derrota(t1);
                time_remove_vitoria(t2);
            } else {
                time_remove_empate(t1);
                time_remove_empate(t2);
            }
        }

        // Deleta a partida da lista encadeada
        if (remover_partida_por_id(bd_p, id_remover)) {
            printf("\nRegistro removido com sucesso.\n");
        } else {
            printf("\nErro ao remover a partida da memoria.\n");
        }
    } else {
        printf("\nOperacao cancelada.\n");
    }
}

// Função que lê os dados da nova partida, confirma com o usuário e insere a partida
void caso_5(BDTimes *bd_t, BDPartidas *bd_p) {
    int id_t1, id_t2, g1, g2;
    
    printf("\nInserir nova partida\n");
    
    printf("Digite o ID do Time 1 (Mandante): ");
    scanf("%d", &id_t1);
    
    printf("Digite o ID do Time 2 (Visitante): ");
    scanf("%d", &id_t2);
    
    printf("Digite os Gols do Time 1: ");
    scanf("%d", &g1);
    
    printf("Digite os Gols do Time 2: ");
    scanf("%d", &g2);

    Time *t1 = buscar_time_por_id(bd_t, id_t1);
    Time *t2 = buscar_time_por_id(bd_t, id_t2);

    if (t1 == NULL || t2 == NULL) {
        printf("\nUm ou mais times informados nao existem no sistema.\n");
        return;
    }

    int novo_id = get_proximo_id_partida(bd_p);

    // Confirmação
    printf("\nConfirma a insercao do registro abaixo? (S/N)\n");
    printf("%-5s %-15s %-15s %-10s %-10s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
    printf("%-5d %-15s %-15s %-10d %-10d\n", novo_id, time_get_nome(t1), time_get_nome(t2), g1, g2);

    char conf;
    scanf(" %c", &conf);

    if (conf == 'S' || conf == 's') {

        Partida *nova_partida = criar_partida(novo_id, id_t1, id_t2, g1, g2);
        inserir_partida_bd(bd_p, nova_partida);

        time_add_gols(t1, g1, g2);
        time_add_gols(t2, g2, g1);
        
        if (g1 > g2) {
            time_add_vitoria(t1);
            time_add_derrota(t2);
        } else if (g1 < g2) {
            time_add_derrota(t1);
            time_add_vitoria(t2);
        } else {
            time_add_empate(t1);
            time_add_empate(t2);
        }

        printf("\nO registro foi inserido com sucesso.\n");
    } else {
        printf("\nOperacao cancelada.\n");
    }
}