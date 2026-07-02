#ifndef PARTIDA_H
#define PARTIDA_H

typedef struct partida Partida; // PONTEIRO OPACO!

Partida* criar_partida(int id, int t1, int t2, int g1, int g2);

void destruir_partida(Partida* p);

void partida_set_placar(Partida* p, int g1, int g2);

int partida_get_id(Partida* p);
int partida_get_t1(Partida* p);
int partida_get_t2(Partida* p);
int partida_get_g1(Partida* p);
int partida_get_g2(Partida* p);

#endif