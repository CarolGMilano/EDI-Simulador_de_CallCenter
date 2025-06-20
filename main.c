#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include "chamada/chamada.h"
#include "atendimento/atendimento.h"
#include "historico/historico.h"
#include "model/prioridade.h"
#include "dados_teste/dados_teste.h"

void mostrarSistemaCallCenter() {
  printf("\n============================================");
  printf("\n   SISTEMA DE ATENDIMENTO - CALL CENTER");
  printf("\n============================================\n");

  printf("           [ CHAMADAS ]\n");
  printf("  1 ▸ Cadastrar nova chamada\n");

  printf("\n           [ ATENDIMENTO ]\n");
  printf("  2 ▸ Mostrar fila de espera\n");
  printf("  3 ▸ Atender próxima chamada\n");
  printf("  4 ▸ Listar histórico de atendimentos\n");

  printf("\n           [ RELATÓRIOS ]\n");
  printf("  5 ▸ Gerar relatório final\n");

  printf("\n  0 ▸ Sair do sistema");

  printf("\n============================================\n");
  printf("Escolha uma opção: ");
}

void mostrarMotivos(){
  printf("\n============================================");
  printf("\n             MOTIVO DA LIGAÇÃO");
  printf("\n============================================\n");

  printf("  1 ▸ Cancelamento de serviço\n");
  printf("  2 ▸ Reclamação grave\n");
  printf("  3 ▸ Dúvida sobre fatura\n");
  printf("  4 ▸ Problema técnico\n");
  printf("  5 ▸ Orientação geral\n");
  printf("  6 ▸ Mudança cadastral\n");

  printf("============================================\n");
  printf("Escolha um motivo: ");
}

void setarPrioridade(int escolha, char* motivo, Prioridade* prioridade) {
  switch (escolha) {
    case 1:
      strcpy(motivo, "Cancelamentos de serviço");
      *prioridade = alta;
    break;

    case 2:
      strcpy(motivo, "Reclamações graves");
      *prioridade = alta;
    break;

    case 3:
      strcpy(motivo, "Dúvidas sobre faturas");
      *prioridade = media;
    break;

    case 4:
      strcpy(motivo, "Problemas técnicos");
      *prioridade = media;
    break;

    case 5 :
      strcpy(motivo, "Orientações gerais");
      *prioridade = baixa;
    break;

    case 6:
      strcpy(motivo, "Mudanças cadastrais");
      *prioridade = baixa;
    break;

    default:
      strcpy(motivo, "Outros");
      *prioridade = baixa;
  }
}

bool horarioMenor(Horario h1, Horario h2) {
  if (h1.hora < h2.hora) return true;
  if (h1.hora == h2.hora && h1.minuto < h2.minuto) return true;
  return false;
}

int main() {
  SetConsoleOutputCP(65001);

  FilaChamada* filaChamada = criarFilaChamada();
  PilhaHistorico* pilhaHistorico = criarPilhaHistorico();
  
  int sistemaCallCenter = -1;
  int escolherMotivo = -1;
  
  char nomeCliente[100], motivo[100];
  
  Prioridade prioridade;
  Horario horarioRecebido;

  popularChamadas(filaChamada);
  system("cls");
  
  do {
    mostrarSistemaCallCenter();
    scanf("%d", &sistemaCallCenter);

    switch(sistemaCallCenter) {
      case 1:
        printf("\n\n============================================\n");
        printf("              CADASTRAR CHAMADA       \n");
        printf("============================================\n");

        printf("\nDigite o nome do cliente: ");
        scanf("%s", nomeCliente);

        do{
          mostrarMotivos();
          scanf("%d", &escolherMotivo);

          if(escolherMotivo < 1 || escolherMotivo > 6) {
            printf("\nMotivo inválido. Tente novamente!\n");
          }
        } while (escolherMotivo < 1 || escolherMotivo > 6);

        setarPrioridade(escolherMotivo, motivo, &prioridade);

         if(horarioMenor(filaChamada->horarioUltimoCadastro, pilhaHistorico->horarioUltimoAtendimento)){
          horarioRecebido = pilhaHistorico->horarioUltimoAtendimento;
        } else {
          horarioRecebido = filaChamada->horarioUltimoCadastro;
        }

        cadastrarChamada(filaChamada, nomeCliente, motivo, prioridade, horarioRecebido);
      break;
        
      case 2: 
        exibirFilaEspera(filaChamada);
      break;

      case 3:        
        if(horarioMenor(filaChamada->horarioUltimoCadastro, pilhaHistorico->horarioUltimoAtendimento)){
          horarioRecebido = pilhaHistorico->horarioUltimoAtendimento;
        } else {
          horarioRecebido = filaChamada->horarioUltimoCadastro;
        }

        empilharAtendimentos(pilhaHistorico, atenderProximaChamada(filaChamada, horarioRecebido));
      break;
      
      case 4: 
        listarHistoricoAtendimentos(pilhaHistorico);
      break;
      
      case 5: 
        gerarRelatorio(pilhaHistorico);
      break;

      case 0:
        printf("\nEncerrando programa...\n");

        destruirFila(filaChamada);      
        destruirPilha(pilhaHistorico);      
      break;

      default:
       printf("\nOpção inválida. Tente novamente.\n");
    }
  } while (sistemaCallCenter != 0);
}