#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

#include "partida.h"
#include "bd_times.h" 

typedef struct bd_partidas BDPartidas; 

typedef struct partida_node PartidaNode;

void carregar_partidas(BDPartidas *bd);

BDPartidas* criar_bd_partidas();

void destruir_bd_partidas(BDPartidas *bd);

void inserir_partida_bd(BDPartidas *bd, Partida *nova_partida);

int remover_partida_por_id(BDPartidas *bd, int id);

Partida* buscar_partida_por_id(BDPartidas *bd, int id);

void consultar_partidas(BDPartidas* bd_p, BDTimes* bd_t, int modo, char* prefixo);

int get_proximo_id_partida(BDPartidas *bd);

PartidaNode* get_primeira_partida(BDPartidas *bd);
PartidaNode* get_proxima_partida(PartidaNode *no);
Partida* get_dados_partida(PartidaNode *no);

#endif