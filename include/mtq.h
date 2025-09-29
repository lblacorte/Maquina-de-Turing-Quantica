#ifndef MTQ_H
#define MTQ_H

// -----------------------------------------------------------
// Arquivo: mtq.h
// Propósito: Contém definições principais da Máquina de
// Turing Quântica (MTQ), incluindo estados, estruturas
// para regras, transições, configurações clássicas e 
// quânticas, bem como constantes gerais.
// -----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <complex.h>  // suporte a números complexos (amplitudes)

// --------- constantes e enums ----------

// Tamanho máximo da fita da MTQ
#define FITA_TAM 100

// Número máximo de configurações quânticas simultâneas
#define MAX_CONFIGS 200

// Símbolo em branco usado na fita
#define BLANK 'b'

// Número máximo de transições possíveis por (estado, símbolo)
#define MAX_TRANS 4

// Estados de exemplo para o algoritmo de Deutsch (podem ser expandidos)
enum {
    Q0 = 0,
    Q1,
    Q2,
    Q3,
    Q4,
    QF  // estado final
};

// Enum para identificar o tipo de função de Deutsch
enum {
    F_CONST_ZERO = 0,  // função constante 0
    F_CONST_ONE,       // função constante 1
    F_IDENTITY,        // função identidade
    F_NOT              // função NOT
};

// ---------- structs ----------

// Estrutura de regra para o algoritmo de Deutsch
typedef struct {
    int estado_in;         // estado de entrada
    char simbolo_in;       // símbolo lido na fita
    int estado_out;        // estado de saída após a transição
    char simbolo_out;      // símbolo a escrever na fita
    int move;              // movimento da cabeça (-1=L, 0=N, +1=R)
    double complex amp;    // amplitude complexa da transição
} rule_t;

// Estrutura genérica de transição para qualquer MTQ
typedef struct {
    char escrever;         // símbolo a escrever na fita
    int proximo_estado;    // índice do próximo estado
    char direcao;          // direção da cabeça ('L' ou 'R')
    double amplitude;      // amplitude real (pode ser complexa em futuras versões)
} Transicao;

// Estrutura da Máquina de Turing Quântica genérica
typedef struct {
    char *Q[10];                         // nomes dos estados
    int num_estados;                      // quantidade de estados
    char alfabeto[10];                    // símbolos permitidos na fita
    int num_simbolos;                     // quantidade de símbolos
    int qi;                               // índice do estado inicial
    int qf;                               // índice do estado final
    Transicao *delta[10][10][MAX_TRANS];  // transições por (estado, símbolo)
    int num_trans[10][10];                // número de transições existentes por (estado, símbolo)
} MTQ;

// Estrutura representando uma configuração clássica da MTQ
typedef struct {
    int estado;               // estado atual
    int cabeca;               // posição da cabeça de leitura/escrita
    char fita[FITA_TAM];      // conteúdo da fita
} config_t;

// Estrutura representando uma configuração quântica da MTQ
typedef struct {
    config_t config;          // configuração clássica
    double complex amplitude; // amplitude associada a esta configuração
} quantum_config_t;

// ---------- includes de headers auxiliares ----------

// Funções utilitárias gerais
#include "util.h"

// Funções específicas para manipulação quântica
#include "quantum.h"

// Funções para criar regras do algoritmo de Deutsch
#include "deutsch.h"

#endif
