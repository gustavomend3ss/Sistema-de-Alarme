#ifndef FSM_H
#define FSM_H

enum EstadoSistema {
  DESATIVADO,
  ATIVADO,
  BLOQUEIO
};

extern EstadoSistema estadoAtual;

void atualizarFSM(bool enterPressionado);

#endif
