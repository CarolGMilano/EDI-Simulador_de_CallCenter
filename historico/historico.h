#ifndef HISTORICO_H
#define HISTORICO_H

#include "../atendimento/atendimento.h"

//Estrutura da pilha de histórico de atendimentos
typedef struct {
  NoAtendimento* topo;
  Horario horarioUltimoAtendimento;
} PilhaHistorico;

//Funções de criação, destruição da pilha e verificação de se está vazia
PilhaHistorico* criarPilhaHistorico();
bool pilhaVazia(PilhaHistorico* pilhaHistorico);
void destruirPilha(PilhaHistorico* pilhaHistorico);

//Função de empilhamento de atendimentos da pilha 
bool empilharAtendimentos(PilhaHistorico* pilhaHistorico, Atendimento* atendimento);

//Funções de listagem de histórico de atendimentos e geração de relatório
void listarHistoricoAtendimentos(PilhaHistorico* pilhaHistorico);
void gerarRelatorio(PilhaHistorico* pilhaHistorico);

#endif
