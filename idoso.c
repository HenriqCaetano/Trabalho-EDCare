#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include "local.h"
#include "idoso.h"
#include "listaIdoso.h"
#include "listaCuidador.h"

#define input "./Testes/Testes/Teste1/Entradas/"
#define output "./Testes/Testes/Teste1/outputs/"

struct idoso
{
    char* nome;
    float temperatura;
    int queda;
    int contaFebre;
    Localizacao* local;
    ListCuidador* cuidadores;
    ListIdoso* amigos;
    FILE* arqEnt;
    FILE* arqSaida;
};

Idoso* inicIdoso(char* nome){
    
    Idoso* idoso = (Idoso*) malloc(sizeof(Idoso));

    idoso->nome = strdup(nome);
    idoso->temperatura= 0;
    idoso->queda = 0;
    idoso->contaFebre = 0;
    idoso->local = inicLocal(0, 0);

    idoso->cuidadores = inicListaCuidador();
    idoso->amigos = inicListaIdoso();

    char in[100] = "\0", out[100] = "\0";
    strcat(in,input);
    strcat(in,nome);
    strcat(in,".txt");

    strcat(out,output);
    strcat(out,nome);
    strcat(out,"-saida.txt");

    idoso->arqEnt = fopen(in,"r");
    idoso->arqSaida = fopen(out,"w");

    return idoso;
}

void atualizaIdoso(Idoso* idoso){
    char* dado;
    char entrada[50];
    float lat,lon;
    fscanf(idoso->arqEnt,"%s",entrada);
    //verifica se idoso morreu
    if(strcmp(entrada,"falecimento")==0){
        //chamar função para matar o idoso
        fprintf(idoso->arqSaida,"%s morreu\n", idoso->nome);
        return;
    }
    //se está vivo, lê as entradas sensoriadas
    dado = strtok(entrada,";");
    idoso->temperatura = atof(dado);

    dado = strtok(NULL,";"); //obtem a latitude
    lat = atof(dado);
    dado = strtok(NULL,";"); //obtem a longitude
    lon = atof(dado);
    atualizaLocalizacao(idoso->local,lat,lon);

    dado = strtok(NULL,";");//obtem o verificador de queda
    idoso->queda = atoi(dado);
    
    return;
}

void processaDadosIdoso(Idoso* idoso){
    //esta função ja considera que o idoso está vivo
    //verifica se o idoso caiu: chama cuidador
    if(idoso->queda){
        //verificar se houve febre baixa para atualizar o contador
        if(idoso->temperatura > 37 && idoso->temperatura < 38){
            idoso->contaFebre++;
        }
        //chamar o cuidador mais proximo!
        fprintf(idoso->arqSaida,"queda, acionou %s\n", obtemCuidadorMaisProximo(idoso->cuidadores, idoso));
        return;
    }

    //verifica se o idoso está com febre alta: chama cuidador
    else if(idoso->temperatura >= 38){
        //chama o cuidador mais próximo
        fprintf(idoso->arqSaida,"febre alta, acionou %s\n", obtemCuidadorMaisProximo(idoso->cuidadores,idoso));
        return;
    }

    //verifica se o idoso está com febre baixa: chama amigo(exceto na quarta vez)
    else if(idoso->temperatura > 37){
        idoso->contaFebre++;
        if(idoso->contaFebre == 4){
            //chama o cuidador mais proximo
            fprintf(idoso->arqEnt,"febre baixa pela quarta vez, acionou %s\n", obtemCuidadorMaisProximo(idoso->cuidadores, idoso));
        }
        else fprintf(idoso->arqSaida,"febre baixa, acionou amigo %s\n",obtemAmigoMaisProximo(idoso->amigos,idoso));
        return;
    }
    //no caso comum, o idoso está bem
    fprintf(idoso->arqSaida,"tudo ok\n");
}

void imprimeIdoso(Idoso* idoso){
    printf("NOME: %s\n", idoso->nome);
}

ListIdoso* obtemAmigosIdoso(Idoso* idoso){
    return idoso->amigos;
}

ListCuidador* obtemCuidadoresIdoso(Idoso* idoso){
    return idoso->cuidadores;
}


char* retornaNomeIdoso(Idoso* idoso){
    return idoso->nome;
}

Localizacao* retornaLocalIdoso(Idoso* idoso){
    return idoso->local;
}

void destroi_Idoso(Idoso* idoso){
    if(idoso != NULL){
        destroiLocal(idoso->local);
        destroiListaCuidador(idoso->cuidadores);
        destroiListaIdoso(idoso->amigos);
        free(idoso->nome);
        free(idoso);
    }
}   
void faleceIdoso(Idoso* idoso);