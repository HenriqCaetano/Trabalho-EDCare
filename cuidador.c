#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include "cuidador.h"
#include "local.h"
#include <stdio.h>


struct cuidador{
    Localizacao* local;
    char* nome;
};

Cuidador* inic_Cuidador(char* nome){
    Cuidador* cuidador = (Cuidador*)malloc(sizeof(Cuidador));

    cuidador->nome = strdup(nome);
    cuidador->local = inicLocal(0,0);
    
    return cuidador;
}

void imprimeCuidador(Cuidador* cuidador){
    printf("NOME CUIDADOR: %s\n",cuidador->nome);
}

char* retornaNomeCuidador(Cuidador* cuidador){
    return cuidador->nome;
}

void destroiCuidador(Cuidador* cuidador){
    if(cuidador != NULL){
        free(cuidador->nome);
        destroiLocal(cuidador->local);
        free(cuidador);
    }
}
