#include <math.h>
#include <complex.h>
#include "mtq.h"       // Define rule_t, estados e estruturas da MTQ
#include "deutsch.h"   // Declaração da função criar_regras_deutsch

// -----------------------------------------------------------------------------
// Função: criar_regras_deutsch
// Propósito: Cria as regras da Máquina de Turing Quântica para o Algoritmo
// de Deutsch, para uma função booleana simples f: {0,1} -> {0,1}.
// -----------------------------------------------------------------------------
// Parâmetros:
//  - rules_out: vetor onde serão armazenadas as regras geradas
//  - f_type: tipo da função Deutsch (constante zero, constante um, identidade, NOT)
// Retorno:
//  - número de regras criadas
// -----------------------------------------------------------------------------
int criar_regras_deutsch(rule_t *rules_out, int f_type) {
    int idx = 0;  // índice para inserir regras no vetor
    double complex h_amp = 1.0 / sqrt(2.0);  // amplitude do Hadamard (superposição)

    // ---------- Passo 0: superposição inicial ----------
    // Q0, símbolo em branco: gera superposição |0> e |1>
    rules_out[idx++] = (rule_t){Q0, BLANK, Q1, '0', 0, h_amp};
    rules_out[idx++] = (rule_t){Q0, BLANK, Q1, '1', 0, h_amp};

    // ---------- Define f(x) ----------
    // Variáveis para armazenar f(0) e f(1)
    int f0 = 0, f1 = 0;
    switch(f_type) {
        case F_CONST_ZERO: f0 = 0; f1 = 0; break; // função constante 0
        case F_CONST_ONE:  f0 = 1; f1 = 1; break; // função constante 1
        case F_IDENTITY:   f0 = 0; f1 = 1; break; // função identidade
        case F_NOT:        f0 = 1; f1 = 0; break; // função NOT
    }

    // ---------- Passo 1: oráculo Uf ----------
    // Implementa a transformação quântica que aplica f(x)
    // Usando XOR para construir o resultado do oráculo
    char w0 = (0 ^ f0) ? '1' : '0';
    char w1 = (1 ^ f1) ? '1' : '0';

    // Transições do estado Q1 para Q2 com resultado do oráculo
    rules_out[idx++] = (rule_t){Q1, '0', Q2, w0, 0, 1.0 + 0.0*I};
    rules_out[idx++] = (rule_t){Q1, '1', Q2, w1, 0, 1.0 + 0.0*I};

    // ---------- Passo 2: Hadamard final ----------
    // Aplica Hadamard para interferência e revelar se a função é constante ou balanceada
    rules_out[idx++] = (rule_t){Q2, '0', Q3, '0', 0, h_amp};
    rules_out[idx++] = (rule_t){Q2, '0', Q3, '1', 0, h_amp};
    rules_out[idx++] = (rule_t){Q2, '1', Q3, '0', 0, h_amp};
    rules_out[idx++] = (rule_t){Q2, '1', Q3, '1', 0, -h_amp};

    // ---------- Passo 3: mover até início e medir ----------
    // Estado final Q3: transições que levam à medição (estado QF)
    rules_out[idx++] = (rule_t){Q3, BLANK, QF, BLANK, 0, 1.0 + 0.0*I};
    rules_out[idx++] = (rule_t){Q3, '0', QF, '0', 0, 1.0 + 0.0*I};
    rules_out[idx++] = (rule_t){Q3, '1', QF, '1', 0, 1.0 + 0.0*I};

    return idx; // retorna a quantidade de regras criadas
}
