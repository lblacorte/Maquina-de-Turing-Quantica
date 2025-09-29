#ifndef LINGUAGEM_A_H
#define LINGUAGEM_A_H

// -----------------------------------------------------------
// Arquivo: linguagem_a.h
// Propósito: Declaração da função para criar as regras
// (transições) da Máquina de Turing Quântica (MTQ) que
// reconhece a Linguagem A = {0^n 1^n}.
// -----------------------------------------------------------

#include "mtq.h"  
// Inclui definições gerais da MTQ, como rule_t, estados, 
// tipos e funções auxiliares.

// -----------------------------------------------------------
// Função: criar_regras_linguagem_a
// Entrada:
//   - rules_out: ponteiro para array de rule_t que será 
//                preenchido com as regras da MTQ.
//   - entrada: string de entrada w ∈ Σ* que será inicialmente
//              colocada na fita.
// Retorno:
//   - inteiro representando o número de regras criadas.
//
// Descrição:
//   Esta função cria as transições (regras) necessárias para
//   que a MTQ reconheça a linguagem A. As regras consideram
//   a evolução quântica, permitindo superposição de 
//   configurações durante a computação.
// -----------------------------------------------------------
int criar_regras_linguagem_a(rule_t *rules_out, char *entrada);

#endif
