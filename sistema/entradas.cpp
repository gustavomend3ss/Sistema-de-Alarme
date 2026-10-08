#include "entradas.h"
#include "config.h"

// Debounce do ENTER
static bool ultimaLeituraEnter = HIGH;
static bool estadoEstavelEnter = HIGH;
static unsigned long instanteUltimaMudancaEnter = 0;

// Histerese do sensor de luz
static bool sensorLuzAtivo = false;


void configurarEntradas() {

  // Switches da senha e ENTER: LOW = acionado
  for (uint8_t i = 0; i < TAMANHO_SENHA; i++) {
    pinMode(PIN_SENHA[i], INPUT_PULLUP);
  }

  pinMode(PIN_ENTER, INPUT_PULLUP);

  // Os testes mostraram que os sensores possuem saída própria.
  pinMode(PIN_SENSOR_2, INPUT);
  pinMode(PIN_SENSOR_3, INPUT);
}


bool detectarPressionamentoEnter() {

  bool leituraAtual = digitalRead(PIN_ENTER);

  // Detectou mudança elétrica
  if (leituraAtual != ultimaLeituraEnter) {
    instanteUltimaMudancaEnter = millis();
    ultimaLeituraEnter = leituraAtual;
  }

  // Aguarda estabilidade por TEMPO_DEBOUNCE
  if (millis() - instanteUltimaMudancaEnter >= TEMPO_DEBOUNCE) {

    if (leituraAtual != estadoEstavelEnter) {

      estadoEstavelEnter = leituraAtual;

      // INPUT_PULLUP: LOW = botão pressionado
      if (estadoEstavelEnter == LOW) {
        return true;
      }
    }
  }

  return false;
}


uint8_t lerSwitchSenha(uint8_t pino) {
  return digitalRead(pino) == LOW ? 1 : 0;
}


bool sensorLuminosidadeAcionado() {

  int valor = analogRead(PIN_SENSOR_LUZ);

  if (!sensorLuzAtivo && valor >= LIMIAR_LUZ_ATIVAR) {
    sensorLuzAtivo = true;
  }
  else if (sensorLuzAtivo && valor <= LIMIAR_LUZ_DESATIVAR) {
    sensorLuzAtivo = false;
  }

  return sensorLuzAtivo;
}


bool sensor2Acionado() {
  return digitalRead(PIN_SENSOR_2) == HIGH;
}

bool sensor3Acionado() {
  return digitalRead(PIN_SENSOR_3) == HIGH;
}
