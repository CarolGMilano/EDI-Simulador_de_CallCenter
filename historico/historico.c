#include "historico.h"
#include "../model/prioridade.h"

/*
  Descrição: Verifica se a pilha de histórico está vazia. Retorna true se não 
             houver nenhum atendimento registrado ou false caso contrário.
*/
bool pilhaVazia(PilhaHistorico* pilhaHistorico) {
  //Retorna se a pilha está vazia ou não
  return pilhaHistorico->topo == NULL;
}

/*
  Descrição: Cria e inicializa uma nova pilha de histórico de atendimentos. Define o topo 
             como vazio e o horário do último atendimento como 08:45. Retorna a pilha criada.
*/
PilhaHistorico* criarPilhaHistorico(){
  //Aloca memória para a nova pilha
  PilhaHistorico* novaPilhaHistorico = (PilhaHistorico*)malloc(sizeof(PilhaHistorico));

  //Se a alocação for bem-sucedida, inicializa os ponteiros e valores
  if (novaPilhaHistorico != NULL) {
    novaPilhaHistorico->topo = NULL; 
    novaPilhaHistorico->horarioUltimoAtendimento.hora = 8;
    novaPilhaHistorico->horarioUltimoAtendimento.minuto = 45;
  }

  //Retorna a nova pilha criada
  return novaPilhaHistorico;
}

/*
  Descrição: Adiciona um atendimento no topo da pilha de histórico. Atualiza o horário do 
             último atendimento registrado. Retorna true após a inserção.
*/
bool empilharAtendimentos(PilhaHistorico* pilhaHistorico, Atendimento* atendimento) {
  //Aloca memória para o novo nó de atendimentos da pilha
  NoAtendimento* novoNo = malloc(sizeof(NoAtendimento));

  //Inicializa o novo nó com os valores recebidos
  novoNo->atendimento = atendimento;
  novoNo->prox = pilhaHistorico->topo;
  pilhaHistorico->topo = novoNo;
  pilhaHistorico->horarioUltimoAtendimento = atendimento->horarioFimAtendimento;

  return true;
}

/*
  Descrição: Exibe a lista de todos os atendimentos registrados no histórico. Mostra prioridade, 
             nome do cliente, horário de chegada e de saída. Se a pilha estiver vazia, informa 
             que não há atendimentos.
*/
void listarHistoricoAtendimentos(PilhaHistorico* pilhaHistorico){
  //Se a pilha estar vazia
  if (pilhaVazia(pilhaHistorico)) {
    //Retorna ao usuário
    printf("\nPilha de atendimentos vazia.\n");

    return;
  }

  //Se não, retorna uma tabela com as informações dos atendimentos realizados com a prioridade, nome do cliente, horário de chegada e horário de atendimento
  printf("\nATENDIMENTOS REALIZADOS\n");
  printf("=======================================================================\n");
  printf("|     Prioridade     |          Cliente         |     Atendido às     |\n");
  printf("=======================================================================\n");

  NoAtendimento* atual = pilhaHistorico->topo;

  while (atual != NULL) {
    const char* prioridadeStr = prioridadeString(atual->atendimento->chamada.prioridade);

    printf("| %-18s | %-25s|        %02d:%02d        |\n", prioridadeStr,
                                                           atual->atendimento->chamada.nomeCliente,                                                            
                                                           atual->atendimento->horarioFimAtendimento.hora,
                                                           atual->atendimento->horarioFimAtendimento.minuto);

    printf("-----------------------------------------------------------------------\n");

    atual = atual->prox;
  }
}

/*
  Descrição: Gera um relatório final com informações dos atendimentos realizados. Mostra os 
             clientes atendidos, quantidade de atendimentos por prioridade e o tempo médio 
             de espera simulado para cada nível de prioridade.
*/
void gerarRelatorio(PilhaHistorico* pilhaHistorico) {
  //Inicializa variáveis locais de lógica interna
  int atendimentosAlta = 0, atendimentosMedia = 0, atendimentosBaixa = 0;
  int somaEsperaAlta = 0, somaEsperaMedia = 0, somaEsperaBaixa = 0;
  int contAlta = 0, contMedia = 0, contBaixa = 0;

  //Inicializa um nó atual apontando para o topo da pilha
  NoAtendimento* atual = pilhaHistorico->topo;

  printf("\n============== RELATÓRIO FINAL =============\n\n");

  //Exibe uma tabela com as informações dos clientes atendidos com nome do cliente, prioridade, horário de chegada e horário de atendimento.
  printf("CLIENTES ATENDIDOS\n");
  printf("===================================================================================\n");
  printf("|     Prioridade     |          Cliente         |     Chegada     |     Saída     |\n");
  printf("===================================================================================\n");

  //Enquanto não chegar ao final da pilha
  while (atual != NULL) {
    //Aloca um atendimento para exibir suas informações
    Atendimento* atendimento = atual->atendimento;

    //Com base na prioridade da chamada, busca o nome legível 
    const char* prioridadeStr = prioridadeString(atendimento->chamada.prioridade);

    printf("| %-18s | %-25s|      %02d:%02d      |     %02d:%02d     |\n", prioridadeStr,
                                                                           atendimento->chamada.nomeCliente,
                                                                           atendimento->chamada.horario.hora,
                                                                           atendimento->chamada.horario.minuto,
                                                                           atendimento->horarioFimAtendimento.hora,
                                                                           atendimento->horarioFimAtendimento.minuto
    );

    printf("-----------------------------------------------------------------------------------\n");

    //Calcula o tempo de espera do atendimento, em minutos
    int tempoEspera = (atendimento->horarioFimAtendimento.hora - atendimento->chamada.horario.hora) * 60 +
                      (atendimento->horarioFimAtendimento.minuto - atendimento->chamada.horario.minuto);

    //Com base na prioridade, atualiza as variáveis locais para o cálculo de média e exibição do número de atendimentos atendidos por prioridade
    switch (atendimento->chamada.prioridade) {
      case alta:
        atendimentosAlta++;
        somaEsperaAlta += tempoEspera;
        contAlta++;
      break;

      case media:
        atendimentosMedia++;
        somaEsperaMedia += tempoEspera;
        contMedia++;
      break;

      case baixa:
        atendimentosBaixa++;
        somaEsperaBaixa += tempoEspera;
        contBaixa++;
      break;
    }

    atual = atual->prox;
  }

  printf("\nQUANTIDADE DE ATENDIMENTOS POR PRIORIDADE\n");
  printf("====================================\n");
  printf("|   Alta   |   Média   |   Baixa   |\n");
  printf("====================================\n");
  printf("|   %-6d |   %-7d |   %-7d |\n", atendimentosAlta, atendimentosMedia, atendimentosBaixa);
  printf("====================================\n");

  printf("\nTEMPO MÉDIO DE ESPERA POR PRIORIDADE (EM MINUTOS)\n");
  printf("====================================\n");
  printf("|   Alta   |   Média   |   Baixa   |\n");
  printf("====================================\n");
  printf("|   %-6d |   %-7d |   %-7d |\n", contAlta > 0 ? somaEsperaAlta / contAlta : 0,
                                           contMedia > 0 ? somaEsperaMedia / contMedia : 0,
                                           contBaixa > 0 ? somaEsperaBaixa / contBaixa : 0);
  printf("====================================\n");
}

/*
  Descrição: Libera toda a memória usada pela pilha de histórico, removendo cada atendimento e 
             os nós da pilha. Deve ser chamada quando a pilha não for mais necessária.
*/
void destruirPilha(PilhaHistorico* pilhaHistorico) {
  //Enquanto a pilha não estiver vazia
  while (!pilhaVazia(pilhaHistorico)) {
    //Cria um nó apontando para o topo da pilha
    NoAtendimento* noTopo = pilhaHistorico->topo;
    //Cria um atendimento apontando para o atendimento do nó do topo da pilha
    Atendimento* atendimento = noTopo->atendimento;

    pilhaHistorico->topo = noTopo->prox;

    //Libera a memória do atendimento
    free(atendimento);
    //Libera a memória do nó do topo
    free(noTopo);
  }

  //Libera a memória da pilha
  free(pilhaHistorico);
}