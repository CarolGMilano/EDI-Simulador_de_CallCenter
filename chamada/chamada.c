#include "chamada.h"
#include "../model/prioridade.h"

/*
  Descrição: Cria e prepara uma nova fila de chamadas. A fila começa vazia, 
              com início e fim apontando para NULL e o horário do último 
              cadastro definido como 08:45. Ao final, retorna a fila criada.
*/
FilaChamada* criarFilaChamada() {
  //Aloca memória para a nova fila
  FilaChamada* novaFilaChamada = (FilaChamada*)malloc(sizeof(FilaChamada));

    //Se a fila foi alocada com sucesso, inicializa seus ponteiros e valores
    if (novaFilaChamada != NULL) {
      novaFilaChamada->inicio = NULL; 
      novaFilaChamada->fim = NULL;
      novaFilaChamada->horarioUltimoCadastro.hora = 8;
      novaFilaChamada->horarioUltimoCadastro.minuto = 45;
    }

  //Retorna a fila criada
  return novaFilaChamada;
}

/*
  Descrição: Verifica se a fila de chamadas está vazia. Retorna true se não 
             houver nenhuma chamada na fila ou false se existir pelo menos uma.
*/
bool filaVazia(FilaChamada* filaChamada) {
  //Se o ponteiro inicio estiver NULL, retorne true (fila vazia)
  if(filaChamada->inicio == NULL) {
    return true;
  }

  //Se não, retorne false (fila não vazia)
  return false;
}

/*
  Descrição: Cadastra uma nova chamada na fila de atendimento. Preenche os dados 
             do cliente, ajusta o horário de chegada e insere a chamada na posição 
             correta da fila, de acordo com a prioridade. Retorna a chamada cadastrada.
*/
NoChamada* cadastrarChamada(FilaChamada* filaChamada, const char* nomeCliente, const char* motivo, Prioridade prioridade, Horario horarioRecebido) {
  //Aloca memória para a nova chamada
  NoChamada* novaChamada = (NoChamada*) malloc(sizeof(NoChamada));

  //Inicializa a nova chamada com as informações recebidas
  strcpy(novaChamada->chamada.nomeCliente, nomeCliente);
  strcpy(novaChamada->chamada.motivo, motivo);
  novaChamada->chamada.prioridade = prioridade;
  novaChamada->prox = NULL;

  //Atualiza horário com + 15 minutos e formata se os minutos passarem de 60
  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  //Grava esse horário tanto na chamada quanto no último cadastro da fila
  novaChamada->chamada.horario = horarioRecebido;
  filaChamada->horarioUltimoCadastro = horarioRecebido;

  //Se a fila estiver vazia
  if (filaVazia(filaChamada)) {
    //Adiciona a nova chamada no inicio da fila e atualiza ambos os ponteiros, sem se preocupar com prioridade
    filaChamada->inicio = novaChamada;
    filaChamada->fim = novaChamada;

    printf("\nChamada de [%s] com prioridade [%s] adicionada à fila de espera às %02d:%02d.\n",
                                                                                    novaChamada->chamada.nomeCliente,
                                                                                    prioridadeString(novaChamada->chamada.prioridade),
                                                                                    novaChamada->chamada.horario.hora,
                                                                                    novaChamada->chamada.horario.minuto);


    return novaChamada;
  }

  //Se a fila não estiver vazia e a prioridade da nova chamada é maior (número menor) que a da que está no inicio, substitui.
  if (novaChamada->chamada.prioridade < filaChamada->inicio->chamada.prioridade) {
    novaChamada->prox = filaChamada->inicio;
    filaChamada->inicio = novaChamada;

    printf("\nChamada de [%s] com prioridade [%s] adicionada à fila às %02d:%02d.\n",
                                                                                    novaChamada->chamada.nomeCliente,
                                                                                    prioridadeString(novaChamada->chamada.prioridade),
                                                                                    novaChamada->chamada.horario.hora,
                                                                                    novaChamada->chamada.horario.minuto);

    return novaChamada;
  }

  //Se não, percorre a fila
  NoChamada* atual = filaChamada->inicio;

  //Percorre até encontrar a última chamada com prioridade maior ou igual
  while (atual->prox != NULL && atual->prox->chamada.prioridade <= novaChamada->chamada.prioridade) {
    atual = atual->prox;
  }

  novaChamada->prox = atual->prox;
  atual->prox = novaChamada;

  //Se adicionar no final, atualiza o fim
  if (novaChamada->prox == NULL) {
    filaChamada->fim = novaChamada;
  }

  printf("\nChamada de [%s] com prioridade [%s] adicionada à fila às %02d:%02d.\n",
                                                                                  novaChamada->chamada.nomeCliente,
                                                                                  prioridadeString(novaChamada->chamada.prioridade),
                                                                                  novaChamada->chamada.horario.hora,
                                                                                  novaChamada->chamada.horario.minuto);

  return novaChamada;
}

/*
  Descrição: Remove a primeira chamada da fila de atendimento. Retorna a chamada com 
             maior prioridade para ser atendida, mas não a exclui da memória — 
             isso deve ser feito depois. Se a fila estiver vazia, retorna NULL.
*/
NoChamada* removerChamada(FilaChamada* filaChamada) {
  //Se a fila estiver vazia
  if (filaVazia(filaChamada)) {
    //Não existem itens para remover
    return NULL;
  }

  //Cria um novo nó apontando para primeiro elemento da fila
  NoChamada* chamadaAtendida = filaChamada->inicio;

  //Se o início da fila for igual ao fim, significa que só tem um elemento
  if (filaChamada->inicio == filaChamada->fim) {
    filaChamada->inicio = NULL;
    filaChamada->fim = NULL;
  } else {
    filaChamada->inicio = filaChamada->inicio->prox;
  }

  return chamadaAtendida;
}

/*
  Descrição: Mostra todas as chamadas que estão na fila de espera. Exibe os dados dos 
             clientes em ordem de atendimento, incluindo prioridade, nome, horário e 
             motivo da chamada. Se a fila estiver vazia, informa na tela.
*/
void exibirFilaEspera(FilaChamada* filaChamada) {
  //Se a fila estiver vazia
  if (filaVazia(filaChamada)) {
    //Retorna a mensagem para o usuário
    printf("\n\nFila de chamadas vazia.\n");

    return;
  }

  //Se não, retorna uma tabela com os campos prioridade, nome do cliente, horário de chegada e motivo da ligação
  printf("\n\nFILA DE ESPERA\n");
  printf("================================================================================================================\n");
  printf("|     Prioridade     |          Cliente         |     Horário de chegada     |              Motivo             |\n");
  printf("================================================================================================================\n");

  NoChamada* atual = filaChamada->inicio;

  while (atual != NULL) {
    const char* prioridadeStr = prioridadeString(atual->chamada.prioridade);

    printf("| %-18s | %-25s|            %02d:%02d           | %-31s |\n", prioridadeStr,
                                                                          atual->chamada.nomeCliente,
                                                                          atual->chamada.horario.hora,
                                                                          atual->chamada.horario.minuto,
                                                                          atual->chamada.motivo);

    printf("----------------------------------------------------------------------------------------------------------------\n");

    atual = atual->prox;
  }
}

/*
  Descrição: Libera toda a memória usada pela fila de chamadas, removendo todos os nós 
             e a estrutura da fila.
*/
void destruirFila(FilaChamada* filaChamada) {
  //Enquanto a fila não estiver vazia
  while (!filaVazia(filaChamada)) {
    //Cria um novo nó com o primeiro elemento
    NoChamada* noChamada = removerChamada(filaChamada);

    //Libera a memória da chamada
    free(noChamada);
  }

  //Libera a memória da fila
  free(filaChamada);
}