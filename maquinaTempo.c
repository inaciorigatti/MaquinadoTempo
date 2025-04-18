#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maquinaTempo.h"

typedef struct eras {
  char nome[50];
  int limite;
  int embarcados;
  struct eras *proximo; 
} Eras; 

typedef struct espera {
  char nome[50];
  char destino[50];
  struct espera *proximo; 
} Espera;

typedef struct embarcado {
    char nome[50];
    char destino[50];
    struct embarcado *anterior;
    struct embarcado *proximo;
} Embarcado;

typedef struct erasEncadeado {
    Eras *inicio;
} ErasEncadeado;

typedef struct esperaEncadeado {
    Espera *inicio;
} EsperaEncadeado;

typedef struct embarcadosDuploEncadeado {
    Embarcado *inicio;
    Embarcado *fim;
} EmbarcadosDuploEncadeado;

Eras *criarNoEras(char nome[], int limite) {
    Eras *eras = (Eras*) calloc(1, sizeof(Eras));
    
    strcpy(eras->nome, nome);
    eras->limite = limite;
    eras->embarcados = 0; 
    eras->proximo = NULL;

    return eras;
}

Espera *criarNoEspera(char nome[], char destino[]) {
    Espera *espera = (Espera *) calloc(1, sizeof(Espera));
    
    strcpy(espera->nome, nome);
    strcpy(espera->destino, destino);
    espera->proximo = NULL;

    return espera;
}

Embarcado *criarNoEmbarcado(char nome[], char destino[]) {
    Embarcado *embarcado = (Embarcado *) calloc(1, sizeof(Embarcado));
    
    strcpy(embarcado->nome, nome);
    strcpy(embarcado->destino, destino);
    embarcado->anterior = NULL;
    embarcado->proximo = NULL;

    return embarcado;
}


ErasEncadeado *criarListaEncadeadaEras(){
    ErasEncadeado *lista = (ErasEncadeado *) calloc(1, (sizeof(ErasEncadeado)));
    lista->inicio = NULL;

    return lista;
}

EsperaEncadeado *criarListaEncadeadaEspera(){
    EsperaEncadeado *lista = (EsperaEncadeado *) calloc(1, (sizeof(EsperaEncadeado)));
    lista->inicio = NULL;

    return lista;
}

EmbarcadosDuploEncadeado *criarListaDuplaEmbarcados() {
    EmbarcadosDuploEncadeado *lista = (EmbarcadosDuploEncadeado *) calloc(1, sizeof(EmbarcadosDuploEncadeado));
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

void adicionarNoInicioEras(ErasEncadeado *lista, char nome[], int limite) {
    Eras *no = criarNoEras(nome, limite);
    no->proximo = lista->inicio;
    lista->inicio = no;
}

void adicionarNoFinalEspera(EsperaEncadeado *lista, char nome[], char destino[]) {
    Espera *novoNo = criarNoEspera(nome, destino);

    if (lista->inicio == NULL) {
        
        lista->inicio = novoNo;
    } else {

        Espera *noAxu = lista->inicio;
        while (noAxu->proximo != NULL) {
            noAxu = noAxu->proximo;
        }
        noAxu->proximo = novoNo;
    }

    system("clear");
    printf("[LOG] Passageiro '%s' embarcado para '%s'.\n", nome, destino);
}

void imprimirEras(const ErasEncadeado *lista) {
    Eras *eras = lista->inicio;
    while (eras != NULL) {
        printf("Nome: %s Limite: %d -> ", eras->nome, eras->limite);
        eras = eras->proximo;
    }
    printf("NULL\n");
}

void imprimirEspera(const EsperaEncadeado *lista) {
    system("clear");
    Espera *espera = lista->inicio;
    int i = 0;
    while (espera != NULL) {
        i++;
        printf("%d. Nome: %s Destino: %s -> ", i, espera->nome, espera->destino);
        espera = espera->proximo;
    }
    printf("NULL\n");
}

void imprimirEmbarcados(const EmbarcadosDuploEncadeado *lista) {
    system("clear");
    Embarcado *embarcado = lista->inicio;
    int i = 0;

    while (embarcado != NULL) {
        i++;
        printf("%d. Nome: %s Destino: %s -> ", i, embarcado->nome, embarcado->destino);
        embarcado = embarcado->proximo;
    }

    if (i == 0) {
        system("clear");
        printf("[LOG] Nenhum passageiro embarcado.\n");
    } else {
        printf("NULL\n");
    }
}


void adicionarPrimeiroAoEmbarque(EsperaEncadeado *listaEspera, EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras) {
    if (listaEspera->inicio == NULL) {
        system("clear");
        printf("[LOG] A lista de espera está vazia.\n");
        return;
    }

    // Pega o primeiro da lista de espera
    Espera *passageiro = listaEspera->inicio;

    // Busca a era de destino na lista de eras
    Eras *destinoEra = listaEras->inicio;
    while (destinoEra != NULL && strcmp(destinoEra->nome, passageiro->destino) != 0) {
        destinoEra = destinoEra->proximo;
    }

    if (destinoEra == NULL) {
        system("clear");
        printf("[LOG] Destino '%s' não encontrado na lista de eras.\n", passageiro->destino);
        return;
    }

    // Verifica se há vaga
    if (destinoEra->embarcados >= destinoEra->limite) {
        system("clear");
        printf("[LOG] Limite de embarque atingido para a era '%s'.\n", destinoEra->nome);
        return;
    }

    // Cria novo nó embarcado
    Embarcado *novoEmbarcado = criarNoEmbarcado(passageiro->nome, passageiro->destino);

    // Adiciona ao final da lista duplamente encadeada
    if (listaEmbarcados->inicio == NULL) {
        // Lista está vazia
        listaEmbarcados->inicio = novoEmbarcado;
        listaEmbarcados->fim = novoEmbarcado;
    } else {
        // Insere no fim
        novoEmbarcado->anterior = listaEmbarcados->fim; //anterior aponta para o fim da lista
        listaEmbarcados->fim->proximo = novoEmbarcado; 
        listaEmbarcados->fim = novoEmbarcado;
    }

    // Atualiza o número de embarcados na era
    destinoEra->embarcados++;

    // Remove o primeiro da lista de espera
    Espera *remover = listaEspera->inicio;
    listaEspera->inicio = remover->proximo;
    remover->proximo = NULL;

    system("clear");
    printf("[LOG] Passageiro '%s' embarcado para '%s'.\n", novoEmbarcado->nome, novoEmbarcado->destino);
}

void adicionarUltimoAoEmbarque(EsperaEncadeado *listaEspera, EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras) {
    if (listaEspera->inicio == NULL) {
        system("clear");
        printf("[LOG] Lista de espera vazia.\n");
        return;
    }

    // Encontrar o último da lista de espera
    Espera *anterior = NULL;
    Espera *ultimo = listaEspera->inicio;

    while (ultimo->proximo != NULL) {
        anterior = ultimo;
        ultimo = ultimo->proximo;
    }

    // Encontrar a era de destino
    Eras *destino = listaEras->inicio;
    while (destino != NULL && strcmp(destino->nome, ultimo->destino) != 0) {
        destino = destino->proximo;
    }

    // Verificar se há vagas na era
    if (destino == NULL) {
        system("clear");
        printf("[LOG] Destino '%s' não encontrado.\n", ultimo->destino);
        return;
    }

    if (destino->embarcados >= destino->limite) {
        system("clear");
        printf("[LOG] Limite de passageiros atingido para a era '%s'.\n", destino->nome);
        return;
    }

    // Criar o nó de embarcado
    Embarcado *novoEmbarcado = criarNoEmbarcado(ultimo->nome, ultimo->destino);

    // Inserir no fim da lista de embarcados
    if (listaEmbarcados->inicio == NULL) {
        listaEmbarcados->inicio = novoEmbarcado;
        listaEmbarcados->fim = novoEmbarcado;
    } else {
        novoEmbarcado->anterior = listaEmbarcados->fim;
        listaEmbarcados->fim->proximo = novoEmbarcado;
        listaEmbarcados->fim = novoEmbarcado;
    }

    // Atualizar contagem da era
    destino->embarcados++;

    // Remover último da lista de espera
    if (anterior == NULL) {
        // Só há um elemento na lista
        listaEspera->inicio = NULL;
    } else {
        anterior->proximo = NULL;
    }

    
    system("clear");
    printf("[LOG] Passageiro '%s' embarcado para '%s'.\n", novoEmbarcado->nome, novoEmbarcado->destino);
}

void adicionarEspecificoAoEmbarque(EsperaEncadeado *listaEspera, EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras, int posicao) {
    if (listaEspera->inicio == NULL) {
        system("clear");
        printf("[LOG] Lista de espera vazia.\n");
        return;
    }

    if (posicao < 1) {
        system("clear");
        printf("[LOG] Posição inválida.\n");
        return;
    }

    Espera *atual = listaEspera->inicio;
    Espera *anterior = NULL;
    int contador = 1;

    // Localiza o passageiro na posição desejada
    while (atual != NULL && contador < posicao) {
        anterior = atual;
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL) {
        system("clear");
        printf("[LOG] Não existe passageiro na posição %d da lista de espera.\n", posicao);
        return;
    }

    // Busca a era de destino
    Eras *destino = listaEras->inicio;
    while (destino != NULL && strcmp(destino->nome, atual->destino) != 0) {
        destino = destino->proximo;
    }

    if (destino == NULL) {
        system("clear");
        printf("[LOG] Destino '%s' não encontrado.\n", atual->destino);
        return;
    }

    if (destino->embarcados >= destino->limite) {
        system("clear");
        printf("[LOG] Limite de passageiros atingido para a era '%s'.\n", destino->nome);
        return;
    }

    // Criar o novo nó na lista de embarcados
    Embarcado *novoEmbarcado = criarNoEmbarcado(atual->nome, atual->destino);

    // Inserir no fim da lista de embarcados
    if (listaEmbarcados->inicio == NULL) {
        listaEmbarcados->inicio = novoEmbarcado;
        listaEmbarcados->fim = novoEmbarcado;
    } else {
        novoEmbarcado->anterior = listaEmbarcados->fim;
        listaEmbarcados->fim->proximo = novoEmbarcado;
        listaEmbarcados->fim = novoEmbarcado;
    }

    // Atualizar embarcados da era
    destino->embarcados++;

    // Remover da lista de espera
    if (anterior == NULL) {
        // Era o primeiro da lista
        listaEspera->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }


    system("clear");
    printf("[LOG] Passageiro '%s' embarcado para '%s'.\n", novoEmbarcado->nome, novoEmbarcado->destino);
}

void desembarcarPrimeiro(EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras) {
    if (listaEmbarcados->inicio == NULL) {
        system("clear");
        printf("[LOG] A lista de embarcados está vazia.\n");
        return;
    }

    // Aponta para o primeiro embarcado
    Embarcado *desembarcar = listaEmbarcados->inicio;

    // Busca a era correspondente ao destino
    Eras *destinoEra = listaEras->inicio;
    while (destinoEra != NULL && strcmp(destinoEra->nome, desembarcar->destino) != 0) {
        destinoEra = destinoEra->proximo;
    }

    if (destinoEra != NULL && destinoEra->embarcados > 0) {
        destinoEra->embarcados--;  // Decrementa o número de embarcados
    } else if (destinoEra == NULL) {
        system("clear");
        printf("[LOG] Era de destino '%s' não encontrada.\n", desembarcar->destino);
    }

    // Atualiza ponteiros da lista duplamente encadeada
    if (listaEmbarcados->inicio == listaEmbarcados->fim) {
        // Apenas um elemento na lista
        listaEmbarcados->inicio = NULL;
        listaEmbarcados->fim = NULL;
    } else {
        // Há mais de um elemento
        listaEmbarcados->inicio = desembarcar->proximo;
        listaEmbarcados->inicio->anterior = NULL;
    }

    system("clear");
    printf("[LOG] Passageiro '%s' desembarcou '%s' (Primeiro da Lista).\n", desembarcar->nome, desembarcar->destino);

}

void desembarcarUltimo(EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras) {
    if (listaEmbarcados->fim == NULL) {
        system("clear");
        printf("[LOG] Nenhum passageiro está embarcado.\n");
        return;
    }

    Embarcado *ultimo = listaEmbarcados->fim;

    // Procurar a era correspondente ao destino para decrementar embarcados
    Eras *era = listaEras->inicio;
    while (era != NULL) {
        if (strcmp(era->nome, ultimo->destino) == 0) {
            if (era->embarcados > 0) {
                era->embarcados--;
            }
            break;
        }
        era = era->proximo;
    }

    // Atualiza os ponteiros da lista duplamente encadeada
    if (ultimo->anterior != NULL) {
        listaEmbarcados->fim = ultimo->anterior;
        listaEmbarcados->fim->proximo = NULL;
    } else {
        // Caso fosse o único nó na lista
        listaEmbarcados->inicio = NULL;
        listaEmbarcados->fim = NULL;
    }

    system("clear");
    printf("[LOG] Passageiro '%s' desembarcou da era '%s' (Ultimo da Lista).\n", ultimo->nome, ultimo->destino);

}

void desembarcarPorPosicao(EmbarcadosDuploEncadeado *listaEmbarcados, ErasEncadeado *listaEras, int posicao) {
    if (listaEmbarcados->inicio == NULL) {
        system("clear");
        printf("[LOG] Nenhum passageiro está embarcado.\n");
        return;
    }

    Embarcado *atual = listaEmbarcados->inicio;
    
    int contador = 1;
    // Percorre até o nó da posição informada
    while (atual != NULL && contador < posicao) {
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL) {
        system("clear");
        printf("[LOG] Não há passageiro nesta posição.\n");
        return;
    }

    // Atualiza a era de destino
    Eras *era = listaEras->inicio;
    while (era != NULL) {
        if (strcmp(era->nome, atual->destino) == 0) {
            if (era->embarcados > 0) {
                era->embarcados--;
            }
            break;
        }
        era = era->proximo;
    }

    // Atualiza os ponteiros da lista duplamente encadeada
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        // Era o primeiro da lista
        listaEmbarcados->inicio = atual->proximo;
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    } else {
        // Era o último da lista
        listaEmbarcados->fim = atual->anterior;
    }
    
    system("clear");
    printf("[LOG] Passageiro '%s'foi desembarcado em '%s'.\n", atual->nome, atual->destino);
}
