#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "langA.h"   // Declarações da MTQ_A e estados

// -----------------------------------------------------------------------------
// Função: criar_mtq_langA
// Propósito: Cria e inicializa a Máquina de Turing Quântica para reconhecer
// a linguagem A = {0^n1^n}.
// Retorno: MTQ_A com estados, alfabeto e transições configuradas.
// -----------------------------------------------------------------------------
MTQ_A criar_mtq_langA() {
    MTQ_A mtq;

    // ---------- Inicialização ----------
    mtq.num_simbolos = ALFABETO_A;  // 3 símbolos: '0', '1', '#'
    mtq.num_estados = 6;            // QA0 a QA4 + estado final QAF

    // Define o alfabeto
    mtq.alfabeto[0] = '0';
    mtq.alfabeto[1] = '1';
    mtq.alfabeto[2] = '#';  // símbolo marcador ou branco

    // Inicializa a quantidade de transições como zero
    for (int e = 0; e < 6; e++)
        for (int s = 0; s < ALFABETO_A; s++)
            mtq.num_trans[e][s] = 0;

    // -------------------
    // Estado QA0: estado inicial
    // δ(QA0, 0) -> (QA1, #, R)
    Transicao *t0 = malloc(sizeof(Transicao));
    t0->proximo_estado = QA1;
    t0->escrever = '#';
    t0->direcao = 'R';
    t0->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA0][0][0] = t0;
    mtq.num_trans[QA0][0] = 1;

    // δ(QA0, #) -> (QAF, #, R)  -> caso de fita vazia ou fim da entrada
    Transicao *t1 = malloc(sizeof(Transicao));
    t1->proximo_estado = QAF;
    t1->escrever = '#';
    t1->direcao = 'R';
    t1->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA0][2][0] = t1;
    mtq.num_trans[QA0][2] = 1;

    // -------------------
    // Estado QA1: processa os '0's antes dos '1's
    // δ(QA1,0) -> (QA1,0,R)  -> avança sobre 0
    Transicao *t2 = malloc(sizeof(Transicao));
    t2->proximo_estado = QA1;
    t2->escrever = '0';
    t2->direcao = 'R';
    t2->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA1][0][0] = t2;
    mtq.num_trans[QA1][0] = 1;

    // δ(QA1,1) -> superposição para lidar com balanceamento 0^n1^n
    // Transição 1: move para QA2 e escreve '#', direção L, amplitude 1/√2
    Transicao *t3 = malloc(sizeof(Transicao));
    t3->proximo_estado = QA2;
    t3->escrever = '#';
    t3->direcao = 'L';
    t3->amplitude = 1.0/sqrt(2.0) + 0.0*I;
    mtq.delta[QA1][1][0] = t3;

    // Transição 2: permanece em QA1, escreve '1', direção R, amplitude 1/√2
    Transicao *t4 = malloc(sizeof(Transicao));
    t4->proximo_estado = QA1;
    t4->escrever = '1';
    t4->direcao = 'R';
    t4->amplitude = 1.0/sqrt(2.0) + 0.0*I;
    mtq.delta[QA1][1][1] = t4;
    mtq.num_trans[QA1][1] = 2;

    // δ(QA1,#) -> (QA2,#,L)  -> marcador de fim de bloco de 1
    Transicao *t5 = malloc(sizeof(Transicao));
    t5->proximo_estado = QA2;
    t5->escrever = '#';
    t5->direcao = 'L';
    t5->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA1][2][0] = t5;
    mtq.num_trans[QA1][2] = 1;

    // -------------------
    // Estado QA2: move para o início do bloco
    // δ(QA2,0) -> (QA2,0,L)  -> volta sobre 0
    Transicao *t6 = malloc(sizeof(Transicao));
    t6->proximo_estado = QA2;
    t6->escrever = '0';
    t6->direcao = 'L';
    t6->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA2][0][0] = t6;
    mtq.num_trans[QA2][0] = 1;

    // δ(QA2,1) -> (QA2,1,L)  -> volta sobre 1
    Transicao *t7 = malloc(sizeof(Transicao));
    t7->proximo_estado = QA2;
    t7->escrever = '1';
    t7->direcao = 'L';
    t7->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA2][1][0] = t7;
    mtq.num_trans[QA2][1] = 1;

    // δ(QA2,#) -> (QA0,#,R)  -> volta ao início para processar próximo par
    Transicao *t8 = malloc(sizeof(Transicao));
    t8->proximo_estado = QA0;
    t8->escrever = '#';
    t8->direcao = 'R';
    t8->amplitude = 1.0 + 0.0*I;
    mtq.delta[QA2][2][0] = t8;
    mtq.num_trans[QA2][2] = 1;

    return mtq;
}
