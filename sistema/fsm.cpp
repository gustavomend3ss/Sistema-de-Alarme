#include <Arduino.h>
#include "fsm.h"
#include "config.h"
#include "entradas.h"
#include "indicadores.h"

EstadoSistema estadoAtual = DESATIVADO;

static EstadoSistema estadoAntesDoBloqueio = DESATIVADO;
static unsigned long inicioBloqueio = 0;
static uint8_t indiceSenha = 0;


static void alterarEstado(EstadoSistema novoEstado) {

  estadoAtual = novoEstado;

  switch (estadoAtual) {

    case DESATIVADO:
      Serial.println(F("ESTADO -> DESATIVADO"));
      break;

    case ATIVADO:
      Serial.println(F("ESTADO -> ATIVADO"));
      break;

    case BLOQUEIO:
      Serial.println(F("ESTADO -> BLOQUEIO"));
      iniciarPiscaBloqueio();
      break;
  }
}


static void entrarEmBloqueio() {

  estadoAntesDoBloqueio = estadoAtual;
  inicioBloqueio = millis();

  alterarEstado(BLOQUEIO);

  Serial.println(F("Sistema bloqueado por 2 segundos."));
}


/*
  Cada ENTER lê um bit:
    ENTER 1 -> D10, ENTER 2 -> D11, ENTER 3 -> D12, ENTER 4 -> D13

  Senha completa alterna entre DESATIVADO e ATIVADO.
  Qualquer bit errado leva ao BLOQUEIO.
*/
static void processarSenha() {

  uint8_t pinoAtual = PIN_SENHA[indiceSenha];
  uint8_t bitDigitado = lerSwitchSenha(pinoAtual);

  Serial.print(F("Bit "));
  Serial.print(indiceSenha + 1);
  Serial.print(F(" | D"));
  Serial.print(pinoAtual);
  Serial.print(F(" = "));
  Serial.println(bitDigitado);

  // Bit correto
  if (bitDigitado == SENHA_CORRETA[indiceSenha]) {

    indiceSenha++;

    Serial.print(F("Correto: "));
    Serial.print(indiceSenha);
    Serial.print(F("/"));
    Serial.println(TAMANHO_SENHA);

    // Senha completa
    if (indiceSenha >= TAMANHO_SENHA) {

      indiceSenha = 0;

      Serial.println(F("SENHA CORRETA!"));

      if (estadoAtual == DESATIVADO) {
        alterarEstado(ATIVADO);
      }
      else if (estadoAtual == ATIVADO) {
        alterarEstado(DESATIVADO);
      }
    }
  }

  // Bit incorreto
  else {

    Serial.println(F("SENHA INCORRETA!"));

    indiceSenha = 0;

    entrarEmBloqueio();
  }
}


void atualizarFSM(bool enterPressionado) {

  switch (estadoAtual) {

    // A mesma senha ativa e desativa o sistema.
    case DESATIVADO:
    case ATIVADO:
      if (enterPressionado) {
        processarSenha();
      }
      break;

    /*
      Durante o bloqueio o ENTER é ignorado.
      Como usamos millis(), os sensores continuam
      sendo monitorados normalmente.
    */
    case BLOQUEIO:
      if (millis() - inicioBloqueio >= TEMPO_BLOQUEIO) {

        indiceSenha = 0;

        alterarEstado(estadoAntesDoBloqueio);

        Serial.println(F("Bloqueio encerrado."));
      }
      break;
  }
}
