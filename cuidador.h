#ifndef CUIDADOR_H
#define CUIDADOR_H

#include "local.h"

typedef struct cuidador Cuidador;

Cuidador* inic_Cuidador(float latitude, float longitude, char* nome);

void destroiCuidador(Cuidador* cuidador);

#endif