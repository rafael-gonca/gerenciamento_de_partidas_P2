#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "bd_partidas.h"

typedef struct partida_node {

    Partida *partida_dados;
    struct partida_node *next;
} PartidaNode;

struct bd_partidas {

    int quantidade;
    PartidaNode *first;
    PartidaNode *last;
};

// Carrega as partidas do arquivo CSV para a lista encadeada
void carregar_partidas(BDPartidas *bd){
    
    // Abre o arquivo CSV
    FILE *file = fopen("partidas.csv", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo partidas.csv\n");
        return;
    }

    // Lê o cabeçalho e ignora
    char cabecalho[100];
    fscanf(file, "%[^\n]\n", cabecalho);

    // Variáveis temporárias para armazenar os dados lidos do arquivo
    int t_id, t_t1, t_t2, t_g1, t_g2;

    // Lê cada linha do arquivo e cria uma nova partida, inserindo na lista encadeada
    while (fscanf(file, "%d,%d,%d,%d,%d\n", &t_id, &t_t1, &t_t2, &t_g1, &t_g2) == 5){

        Partida *nova_partida = criar_partida(t_id, t_t1, t_t2, t_g1, t_g2);

        PartidaNode *novo_no = (PartidaNode*) malloc(sizeof(PartidaNode));
        novo_no->partida_dados = nova_partida;
        novo_no->next = NULL;

        if (bd->first == NULL) {
            bd->first = novo_no;
        } else {
            bd->last->next = novo_no;
        }
        bd->last = novo_no;
        bd->quantidade++;
    }
    fclose(file);
}

// Cria bd partidas dinâmicamente, inicializando a lista encadeada como vazia
BDPartidas* criar_bd_partidas() {

    BDPartidas *novo_bd = (BDPartidas*) malloc(sizeof(BDPartidas));
    novo_bd->quantidade = 0;
    novo_bd->first = NULL;
    novo_bd->last = NULL;
    return novo_bd;
}

// Função que destrói o banco de dados de partidas
void destruir_bd_partidas(BDPartidas *bd) {

    if (bd == NULL)
        return;
    
    PartidaNode *atual = bd->first;
    while (atual != NULL) {
        PartidaNode *proximo = atual->next;    
        destruir_partida(atual->partida_dados);
        free(atual);                           
        atual = proximo;                       
    }
    free(bd);
}

// Cria o nó e joga a partida para o final da lista
void inserir_partida_bd(BDPartidas *bd, Partida *nova_partida) {
    if (bd == NULL || nova_partida == NULL)
        return;
    
    PartidaNode *novo_no = (PartidaNode*) malloc(sizeof(PartidaNode));
    novo_no->partida_dados = nova_partida;
    novo_no->next = NULL; // Vai pro fim, então não tem ninguém depois

    if (bd->first == NULL) {
        bd->first = novo_no;
    } else {
        bd->last->next = novo_no;
    }
    bd->last = novo_no;
    bd->quantidade++;
}

// Função que remove uma partida pelo ID, ajustando a lista encadeada
int remover_partida_por_id(BDPartidas *bd, int id) {
    PartidaNode *atual = bd->first;
    PartidaNode *anterior = NULL;

    while (atual != NULL) {

        if (partida_get_id(atual->partida_dados) == id) {
            if (anterior == NULL) { 
                bd->first = atual->next;
            } else { 
                anterior->next = atual->next;
            }

            if (atual == bd->last) { 
                bd->last = anterior;
            }

            destruir_partida(atual->partida_dados);
            free(atual);
            bd->quantidade--;
            return 1;
        }
        anterior = atual;
        atual = atual->next;
    }
    return 0;
}

// Função que busca uma partida pelo ID
Partida* buscar_partida_por_id(BDPartidas *bd, int id) {

    PartidaNode *atual = bd->first;
    while (atual != NULL) {
        if (partida_get_id(atual->partida_dados) == id)
            return atual->partida_dados;
        atual = atual->next;
    }
    return NULL;
}

// Função que consulta partidas com base no prefixo do time e no modo selecionado
void consultar_partidas(BDPartidas* bd_p, BDTimes* bd_t, int modo, char* prefixo) {

    int tamanho_prefixo = strlen(prefixo);
    int encontrou_algum = 0;
    int ids_encontrados[100] = {0};

    // Varre a lista de times para marcar quais IDs correspondem ao prefixo
    TimeNode *t_atual = get_primeiro_time(bd_t);
    while (t_atual != NULL) {
        Time *t = get_dados_time(t_atual); 
        
        if (!strncasecmp(time_get_nome(t), prefixo, tamanho_prefixo)) {
            ids_encontrados[time_get_id(t)] = 1;
            encontrou_algum = 1;
        }
        t_atual = get_proximo_time(t_atual); 
    }

    if (!encontrou_algum) {
        printf("\nNenhum time foi encontrado com o prefixo '%s'. \n", prefixo);
        return;
    }
    
    int encontrou_partida = 0;
    printf("\n%-5s %-15s %-10s %-15s\n", "ID", "Time1", "Placar", "Time2");

    // Varre a lista de partidas e imprime aquelas que correspondem aos IDs encontrados
    PartidaNode *p_atual = bd_p->first;
    while (p_atual != NULL) {
        Partida *p = p_atual->partida_dados;
        int mostrar_partida = 0;

        // Verifica se a partida deve ser mostrada com base no modo e nos IDs encontrados
        if (modo == 1 && ids_encontrados[partida_get_t1(p)])
            mostrar_partida = 1;

        else if (modo == 2 && ids_encontrados[partida_get_t2(p)])
            mostrar_partida = 1;
        
        else if (modo == 3 && (ids_encontrados[partida_get_t1(p)] || ids_encontrados[partida_get_t2(p)]))
            mostrar_partida = 1;

        if (mostrar_partida) {
            char nome1[50] = "\0", nome2[50] = "\0";

            // Busca os nomes dos times com base nos IDs da partida
            TimeNode *t_busca = get_primeiro_time(bd_t);
            while (t_busca != NULL) {

                Time *t2 = get_dados_time(t_busca);

                if (time_get_id(t2) == partida_get_t1(p))
                    strcpy(nome1, time_get_nome(t2));

                if (time_get_id(t2) == partida_get_t2(p))
                    strcpy(nome2, time_get_nome(t2));

                t_busca = get_proximo_time(t_busca);
            }

            wchar_t w_nome1[50], w_nome2[50];
            int qtd_letras1 = mbstowcs(w_nome1, nome1, 50);
            int qtd_letras2 = mbstowcs(w_nome2, nome2, 50);
            int pad1 = 15;
            int pad2 = 15;

            if (qtd_letras1 != -1)
                pad1 += (strlen(nome1) - qtd_letras1);
            if (qtd_letras2 != -1)
                pad2 += (strlen(nome2) - qtd_letras2);

            printf("%-5d %-*s %d x %d      %-*s\n", 
                   partida_get_id(p), pad1, nome1, partida_get_g1(p), partida_get_g2(p), pad2, nome2);
            
            encontrou_partida = 1;
        }
        p_atual = p_atual->next;
    }

    if (!encontrou_partida) {
        printf("Nenhuma partida encontrada para os criterios informados.\n");
    }
}

// Varre a lista toda, acha o maior ID e soma 1
int get_proximo_id_partida(BDPartidas *bd) {
    if (bd == NULL || bd->first == NULL)
        return 0;
    
    int max_id = -1;
    PartidaNode *atual = bd->first;
    
    while (atual != NULL) {
        int id_atual = partida_get_id(atual->partida_dados);
        if (id_atual > max_id) {
            max_id = id_atual;
        }
        atual = atual->next;
    }
    return max_id + 1;
}

// Funções de acesso à lista encadeada de partidas

PartidaNode* get_primeira_partida(BDPartidas *bd) {

    if (bd != NULL) {
        return bd->first;
    } else {
        return NULL;
    }
}

PartidaNode* get_proxima_partida(PartidaNode *no) {

    if (no != NULL) {
        return no->next;
    } else {
        return NULL;
    }
}

Partida* get_dados_partida(PartidaNode *no) {

    if (no != NULL) {
        return no->partida_dados;
    } else {
        return NULL;
    }
}