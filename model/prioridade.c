#include "prioridade.h"

/*
  Descrição: Retorna a string correspondente ao nível de prioridade.
             Converte o valor enum para uma palavra legível ("Alta", "Média", "Baixa").
*/
const char* prioridadeString(Prioridade prioridade) {
  switch (prioridade) {
    case alta: return "Alta";
    case media: return "Média";
    case baixa: return "Baixa";
    default: return "Desconhecida";
  }
}

/*
  Descrição: Retorna o tempo de atendimento (em minutos) baseado na prioridade.
             Chamadas de alta prioridade levam mais tempo e as de baixa, menos.
*/
int tempoDeAtendimento(Prioridade prioridade) {
  switch (prioridade) {
    case alta: return 30;
    case media: return 20;
    case baixa: return 10;
    default: return 15;
  }
}