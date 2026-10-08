#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================
// PINAGEM
// ============================================================

// Senha (D10..D13 -> bits 1..4)
const uint8_t PIN_SENHA[] = { 10, 11, 12, 13 };
const uint8_t PIN_ENTER = 9;

// LEDs
const uint8_t LED_AMARELO  = 8;
const uint8_t LED_VERDE    = 6;
const uint8_t LED_VERMELHO = 5;

// Buzzer
const uint8_t PIN_BUZZER = 3;

// Sensores
const uint8_t PIN_SENSOR_LUZ = A0;
const uint8_t PIN_SENSOR_2   = 2;
const uint8_t PIN_SENSOR_3   = 4;


// ============================================================
// CONFIGURAÇÕES
// ============================================================

const unsigned long TEMPO_DEBOUNCE = 50UL;
const unsigned long TEMPO_BLOQUEIO = 2000UL;
const unsigned long TEMPO_PISCA    = 250UL;

const unsigned int FREQUENCIA_BUZZER = 2000;

/*
  Sensor de luminosidade (0..1023), com histerese:
  Acima de 550 -> ativado
  Abaixo de 450 -> desativado
  Essa diferença evita oscilações perto do limite.
*/
const int LIMIAR_LUZ_ATIVAR    = 550;
const int LIMIAR_LUZ_DESATIVAR = 450;


// ============================================================
// SENHA: 1 -> 1 -> 0 -> 1
// ============================================================

const uint8_t SENHA_CORRETA[] = { 1, 1, 0, 1 };
const uint8_t TAMANHO_SENHA = 4;

#endif
