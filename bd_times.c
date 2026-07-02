#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "bd_times.h"
#include "bd_partidas.h"

typedef struct time_node {
    Time *time_dados;
    struct time_node *next;
} TimeNode;

struct bd_times {
    int quantidade;
    TimeNode *first;
    TimeNode *last; 
};

// Carrega os times do arquivo CSV para a lista encadeada
void carregar_times(BDTimes *bd){

    // Abre o arquivo CSV
    FILE *file = fopen("times.csv", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo times.csv\n");
        return;
    }

    bd->quantidade = 0;
    bd->first = NULL;
    bd->last = NULL;

    // Lê o cabeçalho e ignora
    char cabecalho[100];
    fscanf(file, "%[^\n]\n", cabecalho);

    int temp_id;
    char temp_nome[50];

    // Lê cada linha do arquivo e cria um novo time, inserindo na lista encadeada
    while (fscanf(file, "%d,%[^\n]\n", &temp_id, temp_nome) == 2){
        
        // Cria o time com estatísticas iniciais zeradas
        Time *novo_time = criar_time(temp_id, temp_nome, 0, 0, 0, 0, 0);
        
        TimeNode *novo_no = (TimeNode*) malloc(sizeof(TimeNode));
        novo_no->time_dados = novo_time;
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

// Cria bd times dinâmicamente, inicializando a lista encadeada como vazia
BDTimes* criar_bd_times() {
    BDTimes *novo_bd = (BDTimes*) malloc(sizeof(BDTimes));
    novo_bd->quantidade = 0;
    novo_bd->first = NULL;
    novo_bd->last = NULL;
    return novo_bd;
}

// Função que destrói o banco de dados de times
void destruir_bd_times(BDTimes *bd) {
    if (bd == NULL)
        return;
    
    TimeNode *atual = bd->first;

    // Libera cada nó da lista encadeada e os dados do time
    while (atual != NULL) {
        TimeNode *proximo = atual->next; 
        destruir_time(atual->time_dados);
        free(atual);                     
        atual = proximo;                 
    }
    free(bd);
}

// Funções de acesso à lista encadeada de times
void consultar_times(BDTimes* bd, char* prefixo) {
    int tamanho_prefixo = strlen(prefixo);
    int encontrou = 0;

    printf("\n%-5s %-15s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    // Varre a lista de times e compara o prefixo com o nome do time
    TimeNode *atual = bd->first;
    while (atual != NULL) {
        Time *t = atual->time_dados;
        if (!strncasecmp(time_get_nome(t), prefixo, tamanho_prefixo)) {
            int saldo = calcula_saldo(t);
            int pontos = calcula_pontos(t);
            
            wchar_t w_nome[50];
            int qtd_letras = mbstowcs(w_nome, time_get_nome(t), 50);
            int pad = 15;
            if (qtd_letras != -1) pad += (strlen(time_get_nome(t)) - qtd_letras);

            // Imprime os dados do time com o tamanho correto para nomes com acentos
            printf("%-5d %-*s %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n", 
                   time_get_id(t), pad, time_get_nome(t), time_get_v(t), 
                   time_get_e(t), time_get_d(t), time_get_gm(t), time_get_gs(t), 
                   saldo, pontos);
            encontrou = 1;
        }
        atual = atual->next;
    }

    if (!encontrou) {
        printf("Erro: Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
    }
}

// Ordena os times internamente na lista encadeada com base nos critérios de desempate usando o bubble sort
void ordenar_times_internamente(BDTimes *bd) {
    if (bd == NULL || bd->first == NULL)
        return;

    int trocou = 1;
    TimeNode *atual;
    TimeNode *fim = NULL;

    while (trocou) {
        trocou = 0;
        atual = bd->first;

        while (atual->next != fim) {
            Time *t1 = atual->time_dados;
            Time *t2 = atual->next->time_dados;

            int pts1 = calcula_pontos(t1);
            int pts2 = calcula_pontos(t2);
            int v1 = time_get_v(t1);
            int v2 = time_get_v(t2);
            int s1 = calcula_saldo(t1);
            int s2 = calcula_saldo(t2);

            int deve_trocar = 0;

            // Critérios de desempate: pontos, vitórias, saldo de gols
            if (pts2 > pts1) {
                deve_trocar = 1;
            } else if (pts2 == pts1) {
                if (v2 > v1) {
                    deve_trocar = 1;
                } else if (v2 == v1) {
                    if (s2 > s1) {
                        deve_trocar = 1;
                    }
                }
            }

            if (deve_trocar) {
                // Troca os ponteiros dos times nos nós da lista encadeada
                atual->time_dados = t2;
                atual->next->time_dados = t1;
                trocou = 1;
            }
            atual = atual->next;
        }
        fim = atual;
    }
}

// Imprime a tabela de classificação dos times
void tabela_classificacao(BDTimes *bd_t) {

    // Ordena os times internamente antes de imprimir a tabela
    ordenar_times_internamente(bd_t);

    printf("\n%-5s %-15s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    
    // Varre a lista de times e imprime os dados de cada time
    TimeNode *atual = bd_t->first;
    while (atual != NULL) {
        Time *t = atual->time_dados;
        int saldo = calcula_saldo(t);
        int pontos = calcula_pontos(t); 

        wchar_t w_nome[50];
        int qtd_letras = mbstowcs(w_nome, time_get_nome(t), 50);
        int pad = 15;
        if (qtd_letras != -1) pad += (strlen(time_get_nome(t)) - qtd_letras);

        printf("%-5d %-*s %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n", 
               time_get_id(t), pad, time_get_nome(t), time_get_v(t), time_get_e(t), 
               time_get_d(t), time_get_gm(t), time_get_gs(t), saldo, pontos);
               
        atual = atual->next;
    } 
}

// Função de acesso à lista encadeada de times por ID
Time* buscar_time_por_id(BDTimes *bd, int id_procurado){
    // Varre a lista de times e compara o ID com o ID procurado
    TimeNode *atual = bd->first;
    while (atual != NULL) {
        if (time_get_id(atual->time_dados) == id_procurado){
            return atual->time_dados; 
        }
        atual = atual->next; 
    }
    return NULL; 
}

// Funções de acesso à lista encadeada de times

TimeNode* get_primeiro_time(BDTimes *bd) {
    return bd != NULL ? bd->first : NULL;
}

TimeNode* get_proximo_time(TimeNode *no) {
    return no != NULL ? no->next : NULL;
}

Time* get_dados_time(TimeNode *no) {
    return no != NULL ? no->time_dados : NULL; 
}