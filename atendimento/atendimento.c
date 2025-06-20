#include "atendimento.h"
#include "../model/prioridade.h"

/*
  Descrição: Atende a próxima chamada da fila de prioridade. Remove a chamada da fila, calcula 
              o horário de término do atendimento baseado na prioridade, e registra os dados
              do atendimento. Libera a chamada da memória após o atendimento. Retorna o registro 
              do atendimento realizado.
*/
Atendimento* atenderProximaChamada(FilaChamada* filaChamada, Horario horarioRecebido) {
  //Aloca memória para o novo atendimento
  Atendimento* atendimento = (Atendimento*) malloc(sizeof(Atendimento));
  //Cria um nó com o primeiro elemento da fila
  NoChamada* chamadaAtendida = removerChamada(filaChamada);

  //Copia dados da chamada para atendimento
  atendimento->chamada = chamadaAtendida->chamada;

  //Com base na prioridade da chamada, pega o tempo de atendimento
  int duracao = tempoDeAtendimento(chamadaAtendida->chamada.prioridade);

  //Atualiza o horário com base na duração do atendimento
  horarioRecebido.minuto += duracao;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto = horarioRecebido.minuto % 60;

  //Atualiza o horário de atendimento
  atendimento->horarioFimAtendimento.hora = horarioRecebido.hora;
  atendimento->horarioFimAtendimento.minuto = horarioRecebido.minuto;
  
  printf("\nChamada de [%s] atendida com sucesso às %02d:%02d.\n",
                                                              atendimento->chamada.nomeCliente,
                                                              atendimento->horarioFimAtendimento.hora,
                                                              atendimento->horarioFimAtendimento.minuto);

  //Libera a memória da chamada atendida
  free(chamadaAtendida);

  return atendimento;
}