#include "util.h"

// ---------- Compara duas configurações clássicas ----------
// Retorna 1 se forem iguais (mesmo estado, posição da cabeça e fita), 0 caso contrário
int configs_equal(const config_t *a, const config_t *b) {
    if (a->estado != b->estado) return 0;           // estado diferente -> não igual
    if (a->cabeca != b->cabeca) return 0;           // posição da cabeça diferente -> não igual
    if (strncmp(a->fita, b->fita, FITA_TAM) != 0) return 0; // fita diferente -> não igual
    return 1;                                       // todas iguais
}

// ---------- Copia uma configuração clássica ----------
// Retorna uma nova configuração idêntica à passada como argumento
config_t copiarConfig(const config_t *c) {
    config_t nova;
    nova.estado = c->estado;                       // copia o estado
    nova.cabeca = c->cabeca;                       // copia a posição da cabeça
    memcpy(nova.fita, c->fita, FITA_TAM);         // copia toda a fita
    return nova;
}

// ---------- Imprime resumidamente uma configuração ----------
// Mostra apenas parte útil da fita (até o último símbolo não em branco) e posição da cabeça
void print_config_brief(const config_t *c) {
    int start = 0;
    int end = FITA_TAM - 1;

    // Determina último símbolo não em branco
    for (int i = FITA_TAM - 1; i >= 0; i--) {
        if (c->fita[i] != BLANK) {
            end = i;
            break;
        }
    }

    // Determina início da fita a mostrar (inclui 5 posições antes da cabeça se possível)
    for (int i = 0; i < FITA_TAM; i++) {
        if (c->fita[i] != BLANK) {
            start = (i < 5) ? 0 : i - 5;
            break;
        }
    }

    // Imprime a fita relevante
    printf("fita[");
    for (int i = start; i <= end; i++)
        putchar(c->fita[i]);
    printf("]");

    // Imprime posição da cabeça e estado atual
    printf(" head=%d state=%d", c->cabeca, c->estado);
}
