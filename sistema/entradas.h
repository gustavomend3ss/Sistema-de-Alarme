#ifndef ENTRADAS_H
#define ENTRADAS_H

#include <Arduino.h>

void configurarEntradas();

// Retorna true uma única vez a cada pressionamento (com debounce).
bool detectarPressionamentoEnter();

// LOW (switch acionado) -> 1 | HIGH (switch aberto) -> 0
uint8_t lerSwitchSenha(uint8_t pino);

// Leitura com histerese do sensor em A0.
bool sensorLuminosidadeAcionado();

// Sensores digitais: HIGH = acionado
bool sensor2Acionado();
bool sensor3Acionado();

#endif
