#ifndef BDTIMES_H
#define BDTIMES_H

#include "time.h"

typedef struct bd_times BDTimes; 

typedef struct time_node TimeNode;

void carregar_times(BDTimes *bd);

BDTimes* criar_bd_times();

void destruir_bd_times(BDTimes *bd);

void consultar_times(BDTimes* bd, char* prefixo);

void tabela_classificacao(BDTimes *bd_t);

Time* buscar_time_por_id(BDTimes *bd, int id_procurado);

TimeNode* get_primeiro_time(BDTimes *bd);
TimeNode* get_proximo_time(TimeNode *no);
Time* get_dados_time(TimeNode *no);

#endif