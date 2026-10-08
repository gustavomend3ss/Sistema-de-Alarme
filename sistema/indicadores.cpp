#include <Arduino.h>
#include "indicadores.h"
#include "config.h"
#include "fsm.h"

static unsigned long ultimoPisca = 0;


void configurarIndicadores() {

  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);
}


void iniciarPiscaBloqueio() {

  ultimoPisca = millis();
  digitalWrite(LED_AMARELO, HIGH);
}


void atualizarIndicadores() {

  switch (estadoAtual) {

    case DESATIVADO:
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARELO, LOW);
      break;

    case ATIVADO:
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARELO, HIGH);
      break;

    // Amarelo piscando sem delay()
    case BLOQUEIO:
      digitalWrite(LED_VERDE, LOW);

      if (millis() - ultimoPisca >= TEMPO_PISCA) {
        ultimoPisca = millis();
        digitalWrite(LED_AMARELO, !digitalRead(LED_AMARELO));
      }
      break;
  }
}
