#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <complex.h>

// tamanho da fita fixo e maximo de configuracoes
#define FITA_TAM 100
#define MAX_CONFIGS 100

char fita[FITA_TAM];

// configuracao mt
typedef struct {
    int estado;
    int cabeca;
    char *fita;
} config_t;

// configuracao quantica
typedef struct {
    config_t config;
    double complex amplitude;
} quantum_config_t;

// regras de transição
typedef struct {
    int estado_in;
    char simbolo_in;
    int estado_out;
    char simbolo_out;
    int move;
    double complex amp;
} rule_t;

// funcao para copiar uma configuracao
config_t copiarConfig(config_t c) {
    config_t nova;
    nova.estado = c.estado;
    nova.cabeca = c.cabeca;
    strcpy(nova.fita, c.fita);
    return nova;
}

void normalize(quantum_config_t *configs, int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += pow(cabs(configs[i].amplitude), 2);
    }
    soma = sqrt(soma);
    if (soma == 0) return;
    for (int i = 0; i < n; i++) {
        configs[i].amplitude /= soma;
    }
}

// funcao de transicao quantica
int transicao(quantum_config_t *configs, int numConfigs, rule_t rule, inbt numRules, quantum_config_t *novasConfigs) {
    int numNovas = 0;

    for (int i = 0; i < numConfigs; i++) {
        quantum_config_t qc = config[i];
        config_t config = qc.config;

        char simbolo = c.fita[c.cabeca];
        int estado = c.estado;

        // procura regras aplicaveis 
        for (int r = 0; r < numRules; r++) {
            if(rules[r].estado_in == estado && rules[r].simbolo_in == simbolo) {
               quantum_config_t nova;
               nova.config = copiarConfig(c);
               nova.config.estado = rules[r].estado_out;
               nova.config.fita[nova.config.cabeca] = rules[r].simbolo_out;
               nova.config.cabeca += rules[r].move;

               nova.amplitude = qc.amplitude * rules[r].amp;

               novasConfigs[numNovas++] = nova;
            }
        }
    }
    normalize(novasConfigs, numNovas); // normalização das amplitudes do novo estado 
    return numNovas;
}

// função para medir a máquina quântica
quantum_config_t medir(quantum_config_t *configs, int n) {
    double probs[MAX_CONFIGS];
    double soma = 0.0

    for (int i = 0; i < n; i++) {
        probs[i] = pow(cabs(configs[i].amplitude), 2);
        soma += probs[i];
    }

    // normalização, pois as vezes as somas das probabilidades pode ser ligeramente diferente
    for (int i = 0; i < n; i++) {
        probs[i] /= soma;
    }

    double r = ((double) rand()) / RAND_MAX;
    double acumulado = 0.0;
    for (int i = 0; i < n; i++) {
        acumulado += probs[i];
        if (r <= acumulado) return configs[i]; 
    }

    return configs[n - 1];

}

int main() {

}