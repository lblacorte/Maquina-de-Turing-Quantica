#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "mtq.h"       // Estruturas gerais de MTQ
#include "util.h"      // Funções auxiliares (como configs_equal)
#include "quantum.h"   // Protótipos das funções quânticas

// ---------- Normaliza vetor de amplitudes (norma L2 -> 1) ----------
void normalize(quantum_config_t *configs, int n) {
    double soma = 0.0;

    // Soma das magnitudes ao quadrado (||psi||^2)
    for (int i = 0; i < n; i++) {
        double mag = cabs(configs[i].amplitude);
        soma += mag * mag;
    }

    // Evita divisão por zero
    if (soma <= 0.0) return;

    double norm = sqrt(soma);

    // Divide cada amplitude pela norma total
    for (int i = 0; i < n; i++) configs[i].amplitude /= norm;
}

// ---------- Soma amplitudes em configurações iguais ----------
int merge_equal_configs(quantum_config_t *src, int nsrc, quantum_config_t *dst) {
    int ndst = 0;

    // Percorre todas configurações de origem
    for (int i = 0; i < nsrc; i++) {
        int found = -1;

        // Procura se já existe configuração igual em dst
        for (int j = 0; j < ndst; j++) {
            if (configs_equal(&src[i].config, &dst[j].config)) {
                found = j;
                break;
            }
        }

        if (found >= 0) {
            // Se existir, soma amplitudes
            dst[found].amplitude += src[i].amplitude;
        } else {
            // Senão, adiciona nova configuração
            if (ndst >= MAX_CONFIGS) {
                fprintf(stderr, "ERRO: excedeu MAX_CONFIGS ao mesclar.\n");
                exit(1);
            }
            dst[ndst++] = src[i];
        }
    }

    return ndst;
}

// ---------- Executa transição quântica ----------
int transicao(quantum_config_t *configs, int numConfigs, rule_t *rules, int numRules, quantum_config_t *outConfigs) {
    quantum_config_t temp[MAX_CONFIGS];
    int tempCount = 0;

    // Para cada configuração atual
    for (int i = 0; i < numConfigs; i++) {
        quantum_config_t qc = configs[i];
        config_t c = qc.config;

        // Ignora configurações fora da fita
        if (c.cabeca < 0 || c.cabeca >= FITA_TAM) continue;

        char simbolo = c.fita[c.cabeca];
        int estado = c.estado;

        // Aplica todas regras compatíveis
        for (int r = 0; r < numRules; r++) {
            if (rules[r].estado_in == estado && rules[r].simbolo_in == simbolo) {
                // Cria nova configuração clássica
                config_t nova_cfg = copiarConfig(&c);
                nova_cfg.estado = rules[r].estado_out;
                nova_cfg.fita[nova_cfg.cabeca] = rules[r].simbolo_out;
                nova_cfg.cabeca += rules[r].move;

                // Garante que cabeça não sai da fita
                if (nova_cfg.cabeca < 0) nova_cfg.cabeca = 0;
                if (nova_cfg.cabeca >= FITA_TAM) nova_cfg.cabeca = FITA_TAM - 1;

                // Cria nova configuração quântica com amplitude multiplicada
                quantum_config_t qc_new;
                qc_new.config = nova_cfg;
                qc_new.amplitude = qc.amplitude * rules[r].amp;

                if (tempCount >= MAX_CONFIGS) {
                    fprintf(stderr, "ERRO: tempCount >= MAX_CONFIGS no transicao\n");
                    exit(1);
                }

                temp[tempCount++] = qc_new;
            }
        }
    }

    // Mescla configurações iguais e normaliza amplitudes
    int ndst = merge_equal_configs(temp, tempCount, outConfigs);
    normalize(outConfigs, ndst);
    return ndst;
}

// ---------- Realiza medição aleatória ----------
quantum_config_t medir(quantum_config_t *configs, int n) {
    double probs[MAX_CONFIGS];
    double soma = 0.0;

    // Calcula probabilidades |amplitude|^2
    for (int i = 0; i < n; i++) {
        double mag = cabs(configs[i].amplitude);
        probs[i] = mag * mag;
        soma += probs[i];
    }

    if (soma <= 0.0) {
        fprintf(stderr, "Aviso: soma de probabilidades é zero na medicao.\n");
        return configs[0];
    }

    // Normaliza probabilidades
    for (int i = 0; i < n; i++) probs[i] /= soma;

    // Escolhe configuração aleatoriamente
    double r = ((double) rand()) / RAND_MAX;
    double acumulado = 0.0;
    for (int i = 0; i < n; i++) {
        acumulado += probs[i];
        if (r <= acumulado) return configs[i];
    }

    // Retorna última configuração como fallback
    return configs[n - 1];
}

// ---------- Imprime todas configurações quânticas ----------
void print_state(quantum_config_t *configs, int n) {
    printf("Estado com %d configuracoes:\n", n);
    for (int i = 0; i < n; i++) {
        double mag = cabs(configs[i].amplitude);
        double prob = mag * mag;
        printf("  #%d: amp=(%.6f %+.6fi) |psi|^2=%.6f ", i, creal(configs[i].amplitude), cimag(configs[i].amplitude), prob);
        print_config_brief(&configs[i].config); // imprime estado clássico resumido
        printf("\n");
    }
}
