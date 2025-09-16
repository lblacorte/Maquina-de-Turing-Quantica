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

// funcao para copiar uma configuracao
config_t copiarConfig(config_t c) {
    config_t nova;
    nova.estado = c.estado;
    nova.cabeca = c.cabeca;
    strcpy(nova.fita, c.fita);
    return nova;
}

// funcao de transicao quantica
void transicao(quantum_config_t *configs, int numConfigs, quantum_config_t **novasConfigs, int *numNovasConfigs) {
    
}

quantum_config_t medir(quantum_config_t *configs, int numConfigs) {

}

int main() {

}