#ifndef INDICADORES_H
#define INDICADORES_H

void configurarIndicadores();

// Acende o amarelo e reinicia o temporizador do pisca.
void iniciarPiscaBloqueio();

// Verde = DESATIVADO | Amarelo = ATIVADO | Amarelo piscando = BLOQUEIO
void atualizarIndicadores();

#endif
