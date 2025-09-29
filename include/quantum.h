#ifndef QUANTUM_H
#define QUANTUM_H

// -----------------------------------------------------------
// Arquivo: quantum.h
// Propósito: Contém declarações de funções relacionadas à
// manipulação de configurações quânticas de uma MTQ, incluindo
// normalização, transições, medição e impressão do estado.
// -----------------------------------------------------------

#include "mtq.h"

// -----------------------------------------------------------
// Normaliza as amplitudes de uma lista de configurações quânticas
// Garantindo que a soma dos quadrados das amplitudes seja 1
// -----------------------------------------------------------
// configs: vetor de configurações quânticas
// n: número de configurações no vetor
void normalize(quantum_config_t *configs, int n);

// -----------------------------------------------------------
// Combina configurações quânticas iguais somando suas amplitudes
// Evita redundância de configurações idênticas na superposição
// -----------------------------------------------------------
// src: vetor de configurações de entrada
// nsrc: número de configurações de entrada
// dst: vetor de configurações de saída unificadas
// Retorna o número de configurações resultantes em dst
int merge_equal_configs(quantum_config_t *src, int nsrc, quantum_config_t *dst);

// -----------------------------------------------------------
// Aplica uma transição quântica às configurações atuais
// de acordo com um conjunto de regras (rule_t)
// -----------------------------------------------------------
// configs: vetor de configurações atuais
// numConfigs: número de configurações atuais
// rules: vetor de regras de transição
// numRules: número de regras disponíveis
// outConfigs: vetor de saída para armazenar novas configurações
// Retorna o número de configurações geradas
int transicao(quantum_config_t *configs, int numConfigs, rule_t *rules, int numRules, quantum_config_t *outConfigs);

// -----------------------------------------------------------
// Realiza a medição de uma superposição quântica
// Escolhe uma configuração de acordo com as probabilidades
// (quadrado das amplitudes)
// -----------------------------------------------------------
// configs: vetor de configurações quânticas
// n: número de configurações
// Retorna a configuração escolhida
quantum_config_t medir(quantum_config_t *configs, int n);

// -----------------------------------------------------------
// Imprime o estado atual da superposição quântica
// Mostra cada configuração, sua amplitude e probabilidade
// -----------------------------------------------------------
// configs: vetor de configurações quânticas
// n: número de configurações
void print_state(quantum_config_t *configs, int n);

#endif
