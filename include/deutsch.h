#ifndef DEUTSCH_H
#define DEUTSCH_H

// -----------------------------------------------------------
// Arquivo: deutsch.h
// Propósito: Declaração das funções relacionadas ao
// Algoritmo de Deutsch para a Máquina de Turing Quântica (MTQ).
// Permite criar as regras específicas para funções booleanas
// simples (constantes ou identidades).
// -----------------------------------------------------------

#include "mtq.h"  
// Inclui a definição de tipos e estruturas da MTQ, como:
// - rule_t: estrutura que representa uma regra de transição
// - outras definições necessárias para manipular a máquina

// -----------------------------------------------------------
// Função: criar_regras_deutsch
// Propósito: Preencher o vetor 'rules_out' com as regras
// específicas do algoritmo de Deutsch, de acordo com o tipo
// de função 'f_type'.
// Parâmetros:
//   rule_t *rules_out -> ponteiro para o vetor onde as regras
//                        serão armazenadas.
//   int f_type        -> tipo da função booleana a ser testada:
//                        0 = const0, 1 = const1, 2 = identity, 3 = not
// Retorno:
//   int -> número de regras criadas
// -----------------------------------------------------------
int criar_regras_deutsch(rule_t *rules_out, int f_type);

#endif
