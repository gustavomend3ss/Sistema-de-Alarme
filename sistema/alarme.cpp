#include <Arduino.h>
#include "alarme.h"
#include "config.h"
#include "entradas.h"
#include "fsm.h"

static bool buzzerLigado = false;


void configurarAlarme() {

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(LED_VERMELHO, LOW);
  noTone(PIN_BUZZER);
}


static void controlarAlarme(bool ligar) {

  digitalWrite(LED_VERMELHO, ligar ? HIGH : LOW);

  if (ligar && !buzzerLigado) {
    tone(PIN_BUZZER, FREQUENCIA_BUZZER);
    buzzerLigado = true;
  }
  else if (!ligar && buzzerLigado) {
    noTone(PIN_BUZZER);
    buzzerLigado = false;
  }
}


void atualizarAlarme() {

  /*
    A = luminosidade
    P = sensor D2
    J = sensor D4
  */

  bool A = sensorLuminosidadeAcionado();
  bool P = sensor2Acionado();
  bool J = sensor3Acionado();

  // Lógica de maioria: S = (A.P) + (A.J) + (P.J)
  bool maioria = (A && P) || (A && J) || (P && J);

  // Override de segurança: os três sensores disparam em qualquer estado.
  bool overrideEmergencia = A && P && J;

  bool dispararAlarme = false;

  if (overrideEmergencia) {
    dispararAlarme = true;
  }
  // Dois sensores só disparam quando ATIVADO.
  else if (estadoAtual == ATIVADO && maioria) {
    dispararAlarme = true;
  }

  controlarAlarme(dispararAlarme);
}
