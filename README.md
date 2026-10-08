# Sistema de Alarme Residencial com FSM

Alarme para Arduino Uno controlado por uma máquina de estados (FSM), com senha de 4 bits, três sensores e indicação por LEDs e buzzer.

## Estados

| Estado     | LED              | Descrição                                           |
|------------|------------------|-----------------------------------------------------|
| DESATIVADO | Verde            | Estado inicial. Senha correta → ATIVADO             |
| ATIVADO    | Amarelo          | Senha correta → DESATIVADO                          |
| BLOQUEIO   | Amarelo piscando | Após bit errado; dura 2 s e volta ao estado anterior |

O LED vermelho e o buzzer indicam **alarme disparado**.

## Senha

Senha: **1 → 1 → 0 → 1**. Cada aperto do ENTER (D9) lê um bit, na ordem D10, D11, D12, D13.
Switch fechado (LOW) = 1, aberto (HIGH) = 0. Qualquer bit errado leva ao BLOQUEIO.

## Lógica do alarme

Sensores: **A** = luminosidade (A0), **P** = D2, **J** = D4.

- **Maioria** `S = A·P + A·J + P·J`: dispara somente no estado ATIVADO.
- **Override** `A·P·J`: os três acionados disparam em qualquer estado.

O sensor de luz usa histerese: ativa com leitura ≥ 550 e desativa com ≤ 450.

## Pinagem

| Pino       | Função                |
|------------|-----------------------|
| A0         | Sensor de luminosidade |
| D2, D4     | Sensores digitais (HIGH = acionado) |
| D3         | Buzzer                |
| D5         | LED vermelho          |
| D6         | LED verde             |
| D8         | LED amarelo           |
| D9         | ENTER (INPUT_PULLUP)  |
| D10–D13    | Switches da senha (INPUT_PULLUP) |

## Estrutura do código

```
sistema/
├── sistema.ino       setup() e loop()
├── config.h          pinagem, tempos, limiares e senha
├── entradas.h/.cpp   ENTER com debounce, switches e sensores
├── fsm.h/.cpp        estados e processamento da senha
├── alarme.h/.cpp     lógica de disparo, LED vermelho e buzzer
└── indicadores.h/.cpp LEDs verde e amarelo
```

## Como usar

1. Abra `sistema/sistema.ino` na Arduino IDE (os demais arquivos abrem como abas).
2. Selecione a placa **Arduino Uno** e faça o upload.
3. Abra o Monitor Serial em **9600 baud** para acompanhar os bits digitados e as mudanças de estado.
