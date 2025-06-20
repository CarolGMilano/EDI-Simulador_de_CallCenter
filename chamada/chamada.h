#ifndef CHAMADA_H
#define CHAMADA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../model/prioridade.h"

#define MAX_NOME 100
#define MAX_MOTIVO 100

//Estrutura de horário
typedef struct {
  int hora;
  int minuto;
} Horario;

//Estrutura de uma chamada
typedef struct {
  char nomeCliente[MAX_NOME];
  char motivo[MAX_MOTIVO];
  Prioridade prioridade;
  Horario horario;
} Chamada;

//Estrutura de nó da fila de chamada
typedef struct NoChamada {
  Chamada chamada;    
  struct NoChamada *prox; 
} NoChamada;

//Estrutura da fila de chamadas
typedef struct {
  NoChamada* inicio;
  NoChamada* fim;
  Horario horarioUltimoCadastro;
} FilaChamada;

//Funções de criação, destruição da fila e verificação de se está vazia
FilaChamada* criarFilaChamada();
bool filaVazia(FilaChamada* filaChamada);
void destruirFila(FilaChamada* filaChamada);

//Funções de cadastro e remoção de chamadas da fila
NoChamada* cadastrarChamada(FilaChamada* filaChamada, const char* nomeCliente, const char* motivo, Prioridade prioridade, Horario horarioRecebido);
NoChamada* removerChamada(FilaChamada* filaChamada);

//Função de exibição de fila de espera
void exibirFilaEspera(FilaChamada* filaChamada);

#endif