#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct eras Eras;
typedef struct espera Espera;
typedef struct embarcado Embarcado;
typedef struct erasEncadeado ErasEncadeado;
typedef struct esperaEncadeado EsperaEncadeado;
typedef struct embarcadosDuploEncadeado EmbarcadosDuploEncadeado;

void copiarChar(char destino[], const char origem[]);

Eras *criarNoEras(char nome[], int limite);
Espera *criarNoEspera(char nome[], char destino[]);
Embarcado *criarNoEmbarcado(char nome[], char destino[]);
ErasEncadeado *criarListaEncadeadaEras();
EsperaEncadeado *criarListaEncadeadaEspera();
EmbarcadosDuploEncadeado *criarListaDuplaEmbarcados();

int charIguais(char char1[], char char2[]);

void adicionarNoInicioEras(ErasEncadeado *lista, char nome[], int limite);
void adicionarNoFinalEspera(EsperaEncadeado *lista, char nome[], char destino[]);
void imprimirEras(const ErasEncadeado *lista);
void imprimirEspera(const EsperaEncadeado *lista);
void imprimirEmbarcados(const EmbarcadosDuploEncadeado *lista);

void adicionarPrimeiroAoEmbarque(EsperaEncadeado *listaEspera, EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras);
void adicionarUltimoAoEmbarque(EsperaEncadeado *listaEspera, EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras);
void adicionarEspecificoAoEmbarque(EsperaEncadeado *listaEspera, EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras, int posicao);

void desembarcarPrimeiro(EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras);
void desembarcarUltimo(EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras);
void desembarcarPorPosicao(EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras, int posicao);