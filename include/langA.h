#ifndef LANGA_H
#define LANGA_H

// -----------------------------------------------------------
// Arquivo: langa.h
// Propósito: Declaração de estruturas e funções para simular
// a Máquina de Turing Quântica (MTQ) específica da
// Linguagem A, A = {0^n 1^n}.
// -----------------------------------------------------------

#include "mtq.h"  
// Inclui definições gerais da MTQ, como tipos básicos e
// estruturas auxiliares.

// -----------------------------------------------------------
// Estados da MTQ para a Linguagem A
// Enumerados de QA0 a QAF, permitindo referência clara e
// legível no código das transições.
enum {
    QA0 = 0,  // Estado inicial
    QA1,      // Estado intermediário
    QA2,      // Estado intermediário
    QA3,      // Estado intermediário
    QA4,      // Estado intermediário
    QAF       // Estado final
};

// -----------------------------------------------------------
// Número de símbolos no alfabeto da Linguagem A
#define ALFABETO_A 3  // '0', '1', '#' (símbolo marcador)

// -----------------------------------------------------------
// Estrutura de transição para a Linguagem A
typedef struct {
    int proximo_estado;       // Estado que será alcançado
    char escrever;            // Símbolo a ser escrito na fita
    char direcao;             // Movimento do cabeçote: 'L' (esquerda) ou 'R' (direita)
    double complex amplitude; // Amplitude quântica associada à transição
} Transicao;

// -----------------------------------------------------------
// Estrutura principal da MTQ para Linguagem A
typedef struct {
    char alfabeto[ALFABETO_A];             // Conjunto de símbolos da fita
    int num_simbolos;                      // Quantidade de símbolos do alfabeto
    int num_estados;                        // Quantidade de estados da MTQ
    int num_trans[6][ALFABETO_A];          // Número de transições por estado/símbolo
    Transicao* delta[6][ALFABETO_A][2];    // Ponteiros para até 2 transições por símbolo
                                           // delta[estado][símbolo][i]
} MTQ_A;

// -----------------------------------------------------------
// Função que cria e inicializa a MTQ para a Linguagem A
// Retorna uma estrutura MTQ_A pronta para uso
MTQ_A criar_mtq_langA();

#endif
