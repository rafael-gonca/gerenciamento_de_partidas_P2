#include <stdlib.h>
#include <string.h>
#include "time.h"

struct time {
    int ID;
    char Nome[50];
    int V; int E; int D;
    int GM; int GS;
};

// Funções de criação e destruição de times

Time* criar_time(int id, const char* nome, int v, int e, int d, int gm, int gs) {
    Time* t = (Time*) malloc(sizeof(Time));
    t->ID = id;
    strcpy(t->Nome, nome);
    t->V = v; t->E = e; t->D = d;
    t->GM = gm; t->GS = gs;
    return t;
}

void destruir_time(Time* t) {
    free(t);
}

// Funções de acesso aos dados do time

int time_get_id(Time* t) {
    if (t != NULL) {
        return t->ID;
    } else {
        return -1;
    }
}

char* time_get_nome(Time* t) {
    if (t != NULL) {
        return t->Nome;
    } else {
        return NULL;
    }
}

int time_get_v(Time* t) {
    if (t != NULL) {
        return t->V;
    } else {
        return 0;
    }
}

int time_get_e(Time* t) {
    if (t != NULL) {
        return t->E;
    } else {
        return 0;
    }
}

int time_get_d(Time* t) {
    if (t != NULL) {
        return t->D;
    } else {
        return 0;
    }
}

int time_get_gm(Time* t) {
    if (t != NULL) {
        return t->GM;
    } else {
        return 0;
    }
}

int time_get_gs(Time* t) {
    if (t != NULL) {
        return t->GS;
    } else {
        return 0;
    }
}

// Funções de modificação dos dados do time

void time_add_gols(Time* t, int gm, int gs) {
    if (t != NULL) {
        t->GM += gm;
        t->GS += gs;
    }
}

void time_add_vitoria(Time* t) {
    if (t != NULL) {
        t->V++;
    }
}

void time_add_empate(Time* t) {
    if (t != NULL) {
        t->E++;
    }
}

void time_add_derrota(Time* t) {
    if (t != NULL) {
        t->D++;
    }
}

void time_remove_gols(Time* t, int gm, int gs) {
    if (t != NULL) {
        t->GM -= gm;
        t->GS -= gs;
    }
}

void time_remove_vitoria(Time* t) {
    if (t != NULL) {
        t->V--;
    }
}

void time_remove_empate(Time* t) {
    if (t != NULL) {
        t->E--;
    }
}

void time_remove_derrota(Time* t) {
    if (t != NULL) {
        t->D--;
    }
}

// Funções de Cálculo

int calcula_pontos(Time* t) {
    if (t != NULL) {
        return (t->V * 3) + t->E;
    } else {
        return 0;
    }
}

int calcula_saldo(Time* t) {
    if (t != NULL) {
        return t->GM - t->GS;
    } else {
        return 0;
    }
}