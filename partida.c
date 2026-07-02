#include <stdlib.h>
#include "partida.h"

struct partida {
    int ID;
    int Time1ID; int Time2ID;
    int GolsTime1; int GolsTime2;
};

// Funções de criação e destruição de partidas

Partida* criar_partida(int id, int t1, int t2, int g1, int g2) {

    Partida* p = (Partida*) malloc(sizeof(Partida));
    p->ID = id;
    p->Time1ID = t1;
    p->Time2ID = t2;
    p->GolsTime1 = g1;
    p->GolsTime2 = g2;
    return p;
}

void destruir_partida(Partida* p) {
    free(p);
}

// Funções de acesso aos dados da partida

void partida_set_placar(Partida* p, int g1, int g2) {
    if(p) {
        p->GolsTime1 = g1;
        p->GolsTime2 = g2;
    }
}

int partida_get_id(Partida* p) {
    if (p != NULL) {
        return p->ID;
    } else {
        return -1;
    }
}

int partida_get_t1(Partida* p) {
    if (p != NULL) {
        return p->Time1ID;
    } else {
        return -1;
    }
}

int partida_get_t2(Partida* p) {
    if (p != NULL) {
        return p->Time2ID;
    } else {
        return -1;
    }
}

int partida_get_g1(Partida* p) {
    if (p != NULL) {
        return p->GolsTime1;
    } else {
        return 0;
    }
}

int partida_get_g2(Partida* p) {
    if (p != NULL) {
        return p->GolsTime2;
    } else {
        return 0;
    }
}