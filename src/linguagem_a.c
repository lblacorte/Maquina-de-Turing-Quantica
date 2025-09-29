#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linguagem_a.h"

// -----------------------------------------------------------------------------
// Função: criar_regras_linguagem_a
// Propósito: Cria o conjunto de regras (transições) da Máquina de Turing Quântica
// para reconhecer a linguagem A = {0^n 1^n}.
// Entrada:
//   - rules_out: vetor de regras a ser preenchido
//   - entrada: string inicial na fita (não usada diretamente aqui, mas pode
//              ser útil para extensões)
// Retorno: número de regras criadas
// -----------------------------------------------------------------------------
int criar_regras_linguagem_a(rule_t *rules_out, char *entrada) {
    int idx = 0;
    double amp = 1.0;  // amplitude real simples (para MT clássica/quântica simplificada)

    // ---------- Estados da MTQ ----------
    // Q0: estado inicial
    // Q1: procurando e marcando zeros
    // Q2: voltando para encontrar próximo zero não marcado
    // QF: estado final (aceitação)

    // -------------------
    // Q0: estado inicial
    // Se lê '0': marca com '#' e move para Q1 para procurar 1 correspondente
    rules_out[idx++] = (rule_t){Q0, '0', Q1, '#', +1, amp};

    // Se lê '#': fim da entrada ou zero já marcado, aceita
    rules_out[idx++] = (rule_t){Q0, '#', QF, '#', 0, amp};

    // -------------------
    // Q1: mover à direita até encontrar '1' correspondente
    // Se lê '0': continua ignorando zeros
    rules_out[idx++] = (rule_t){Q1, '0', Q1, '0', +1, amp};

    // Se lê '1': marca com '#' e volta para Q2 para retornar
    rules_out[idx++] = (rule_t){Q1, '1', Q2, '#', -1, amp};

    // Se lê '#': chegou ao fim da fita ou bloco já marcado, volta para Q2
    rules_out[idx++] = (rule_t){Q1, '#', Q2, '#', -1, amp};

    // -------------------
    // Q2: retorna à esquerda para encontrar próximo zero a marcar
    rules_out[idx++] = (rule_t){Q2, '0', Q2, '0', -1, amp};
    rules_out[idx++] = (rule_t){Q2, '1', Q2, '1', -1, amp};

    // Se lê '#': encontrou zero já marcado ou início, move para Q0 para processar próximo par
    rules_out[idx++] = (rule_t){Q2, '#', Q0, '#', +1, amp};

    return idx; // retorna número total de regras criadas
}
