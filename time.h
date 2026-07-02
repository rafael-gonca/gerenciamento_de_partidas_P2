#ifndef TIME_H
#define TIME_H

typedef struct time Time;

Time* criar_time(int id, const char* nome, int v, int e, int d, int gm, int gs);

void destruir_time(Time* t);



int time_get_id(Time* t);

char* time_get_nome(Time* t);

int time_get_v(Time* t);

int time_get_e(Time* t);

int time_get_d(Time* t);

int time_get_gm(Time* t);

int time_get_gs(Time* t);



void time_add_gols(Time* t, int gm, int gs);

void time_add_vitoria(Time* t);

void time_add_empate(Time* t);

void time_add_derrota(Time* t);



void time_remove_gols(Time* t, int gm, int gs);

void time_remove_vitoria(Time* t);

void time_remove_empate(Time* t);

void time_remove_derrota(Time* t);



int calcula_pontos(Time* t);

int calcula_saldo(Time* t);

#endif