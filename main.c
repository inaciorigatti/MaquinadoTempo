#include <stdio.h>
#include <stdlib.h>

#include "maquinaTempo.h"

int main(void) {
    
  ErasEncadeado * listaEras = criarListaEncadeadaEras();
  EsperaEncadeado * listaEspera = criarListaEncadeadaEspera();
  EmbarcadosDuploEncadeado * listaEmbarcados = criarListaDuplaEmbarcados(); 

  adicionarNoInicioEras(listaEras, "Idade da Pedra", 5);
  adicionarNoInicioEras(listaEras, "Império Romano", 2);
  adicionarNoInicioEras(listaEras, "Brasil 2077", 4);

  int escolha = -1;

  while (escolha != 0) {
      printf("\n===== Agencia do Tempo =====\n");
      printf("1. Adicionar passageiro a espera\n");
      printf("2. Listar passageiros em espera\n");
      printf("3. Embarcar primeiro passageiro da espera\n");
      printf("4. Embarcar ultimo passageiro da espera\n");
      printf("5. Embarcar passageiro especifico\n");
      printf("6. Listar passageiros embarcados\n");
      printf("7. Desembarcar passageiro especifico\n");
      printf("8. Desembarcar primeiro passageiro\n");
      printf("9. Desembarcar ultimo passageiro\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &escolha);

      switch (escolha) {
          case 1: {
              char nome[50];
              printf("Nome do passageiro: ");
              scanf("%s", nome);
              
              int opcao = -1;
              while (opcao < 1 || opcao > 3) {
              printf("Era desejada:\n");
              printf("1. Idade da Pedra\n");
              printf("2. Império Romano\n");
              printf("3. Brasil 2077\n"); 
              printf("Escolha: ");
              scanf("%d", &opcao);

                switch (opcao) {
                  case 1:
                  adicionarNoFinalEspera(listaEspera, nome, "Idade da Pedra");
                  break;

                  case 2: 
                  adicionarNoFinalEspera(listaEspera, nome, "Império Romano");
                  break;

                  case 3:
                  adicionarNoFinalEspera(listaEspera, nome, "Brasil 2077");
                  break;

                  default:
                  printf("[LOG] Opcao invalida. Tente novamente.\n");
                }
              }

              break;
          }

          case 2:
              
              imprimirEspera(listaEspera);
              break;

          case 3:
              
              adicionarPrimeiroAoEmbarque(listaEspera, listaEmbarcados, listaEras);
              break;

          case 4:
              // Embarca o último passageiro da lista de espera
              adicionarUltimoAoEmbarque(listaEspera, listaEmbarcados, listaEras);
              break;

          case 5: {
              // Embarca um passageiro específico 
              int posicao;
              printf("Digite a posição: ");
              scanf("%d", &posicao);
              adicionarEspecificoAoEmbarque(listaEspera, listaEmbarcados, listaEras, posicao);
              break;
          }

          case 6:
              // Lista todos os passageiros embarcados
              imprimirEmbarcados(listaEmbarcados);
              break;

          case 7: {
               // Desembarca um passageiro específico pelo nome
              int posicao;
              printf("Posição do passageiro a desembarcar: ");
              scanf("%d", &posicao);
              desembarcarPorPosicao(listaEmbarcados, listaEras, posicao);
              break;
          }

          case 8: 
              
              desembarcarPrimeiro(listaEmbarcados, listaEras);
              break;

          case 9: // Desembarca o último passageiro da lista de embarcados
              
              desembarcarUltimo(listaEmbarcados, listaEras);
              break;

          case 0: // Encerra o programa
              
              printf("Saindo...\n");
              break;

          default:
              printf("[LOG] Opcao invalida. Tente novamente.\n");
      }
  }

  return 0;
}