#include "dados_teste.h"

void popularChamadas(FilaChamada* filaChamada) {
  Horario horarioRecebido;

  horarioRecebido.hora = 8;
  horarioRecebido.minuto = 45;

  cadastrarChamada(filaChamada, "Ana_Ferreira", "Cancelamentos de serviço", 1, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Beatriz_Silva", "Reclamações graves", 1, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Clara_Oliveira", "Dúvidas sobre faturas", 2, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Daniela_Souza", "Problemas técnicos", 2, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Elisa_Costa", "Orientações gerais", 3, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Fernanda_Lima", "Mudanças cadastrais", 3, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Gabriela_Rocha", "Reclamações graves", 1, horarioRecebido);

  horarioRecebido.minuto += 15;
  horarioRecebido.hora += horarioRecebido.minuto / 60;
  horarioRecebido.minuto %= 60;

  cadastrarChamada(filaChamada, "Helena_Martins", "Problemas técnicos", 2, horarioRecebido);
}
