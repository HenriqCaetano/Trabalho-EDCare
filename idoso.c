#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "local.h"
#include "idoso.h"
#include "listaIdoso.h"
#include "listaCuidador.h"



struct idoso
{
    char* nome;
    float temperatura;
    int queda;
    int morte;
    int contaFebre;
    Localizacao* local;
    ListCuidador* cuidadores;
    ListIdoso* amigos;
};

Idoso* inicIdoso(char* nome){
    
    Idoso* idoso = malloc(sizeof(idoso));

    idoso->nome = malloc(sizeof(nome));
    idoso-> nome = nome;
    idoso->temperatura= 0;
    idoso->queda = 0;
    idoso->morte = 0;
    idoso->contaFebre = 0;
    idoso->local = inicLocal(0, 0);

    idoso->cuidadores = inicListaCuidador();
    idoso->amigos = inicListaIdoso();

    return idoso;
}

void atualizaTemperaturaIdoso(Idoso* idoso, float temperatura){
    idoso->temperatura = temperatura;
    return;
}

void atualizaQuedaIdoso(Idoso* idoso, int queda){
    idoso->temperatura = queda;
    return;
}

void atualizaMorteIdoso(Idoso* idoso, int morte){
    idoso->temperatura = morte;
    return;
}

void atualizaLocalizacaoIdoso(Idoso* idoso, float latitude, float longitude){
    atualizaLocalizacao(idoso->local, latitude, longitude);
    return;
}

void incrementaContaFebreIdoso(Idoso* idoso){//provavelmente necessita mudança!!
    if(idoso->contaFebre == 3) idoso->contaFebre = 0;
    else idoso->contaFebre++;
    return;
}


void imprimeIdoso(Idoso* idoso){
    printf("NOME: %s\n", idoso->nome);
}

void faleceIdoso(Idoso* idoso);

