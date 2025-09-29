#ifndef UTIL_H
#define UTIL_H

// -----------------------------------------------------------
// Arquivo: util.h
// Propósito: Contém funções utilitárias para manipulação
// de configurações clássicas de uma MTQ, incluindo
// comparação, cópia e impressão resumida.
// -----------------------------------------------------------

#include "mtq.h"

// -----------------------------------------------------------
// Compara duas configurações clássicas da MTQ
// -----------------------------------------------------------
// a: ponteiro para a primeira configuração
// b: ponteiro para a segunda configuração
// Retorna 1 se as configurações forem iguais (mesmo estado,
// mesma fita e posição da cabeça), 0 caso contrário
int configs_equal(const config_t *a, const config_t *b);

// -----------------------------------------------------------
// Cria uma cópia de uma configuração clássica
// -----------------------------------------------------------
// c: ponteiro para a configuração original
// Retorna a cópia da configuração
config_t copiarConfig(const config_t *c);

// -----------------------------------------------------------
// Imprime uma versão resumida da configuração clássica
// Útil para depuração rápida, mostrando estado, cabeça e fita
// -----------------------------------------------------------
// c: ponteiro para a configuração a ser impressa
void print_config_brief(const config_t *c);

#endif
