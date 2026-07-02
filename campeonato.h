#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "bd_times.h"
#include "bd_partidas.h"

void processar_dados(BDTimes *bd_t, BDPartidas *bd_p);

void caso_1(BDTimes *bd_t);

void caso_2(BDTimes *bd_t, BDPartidas *bd_p, int opt);

void caso_3(BDTimes *bd_t, BDPartidas *bd_p);

void caso_4(BDTimes *bd_t, BDPartidas *bd_p);

void caso_5(BDTimes *bd_t, BDPartidas *bd_p);

#endif