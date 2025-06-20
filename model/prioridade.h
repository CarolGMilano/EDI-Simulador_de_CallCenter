#ifndef PRIORIDADE_H
#define PRIORIDADE_H

//Enum para prioridade
typedef enum {
  alta = 1,
  media = 2,
  baixa = 3
} Prioridade;

const char* prioridadeString(Prioridade prioridade);
int tempoDeAtendimento(Prioridade prioridade);

#endif
