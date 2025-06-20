#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "../chamada/chamada.h"

//Estrutura de atendimento
typedef struct {
  Chamada chamada;
  Horario horarioFimAtendimento;
} Atendimento;

//Estrutura do nó de atendimento
typedef struct NoAtendimento {
    Atendimento* atendimento;
    struct NoAtendimento* prox;
} NoAtendimento;

//Função de atendimento de chamada
Atendimento* atenderProximaChamada(FilaChamada* filaChamada, Horario horarioRecebido);

#endif