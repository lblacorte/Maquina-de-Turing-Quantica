#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mtq.h"
#include "quantum.h"
#include "util.h"
#include "deutsch.h"
#include "linguagem_a.h"

// Protótipo da função de criação de regras da Linguagem A
int criar_regras_linguagem_a(rule_t *rules_out, char *entrada);

int main(int argc, char **argv) {
    // Inicializa semente aleatória (para simulação quântica / medições)
    srand((unsigned)time(NULL));

    int sim_type = 0; // 0 = Deutsch, 1 = Linguagem A
    if (argc >= 2) sim_type = atoi(argv[1]);

    printf("Simulador MTQ (tipo=%d): 0=Deutsch, 1=Linguagem A\n", sim_type);

    // ---------- Configuração inicial ----------
    config_t init_cfg;
    init_cfg.estado = Q0;   // Estado inicial
    init_cfg.cabeca = 0;    // Cabeça da fita inicia na posição 0
    for (int i = 0; i < FITA_TAM; i++) init_cfg.fita[i] = BLANK; // fita em branco

    // Vetor de regras e número de regras
    rule_t rules[128];
    int numRules = 0;

    // ---------- Seleção do tipo de simulação ----------
    if (sim_type == 0) {
        // Tipo Deutsch
        int f_type = F_CONST_ZERO;  // função padrão
        if (argc >= 3) f_type = atoi(argv[2]);
        printf("Função Deutsch (f_type=%d): 0=const0,1=const1,2=identity,3=not\n", f_type);

        // Cria regras do algoritmo de Deutsch
        numRules = criar_regras_deutsch(rules, f_type);

        // Imprime regras detalhadas
        printf("Numero de regras: %d\n", numRules);
        printf("Regras:\n");
        for (int i = 0; i < numRules; i++) {
            printf("  [%d] (q%d,'%c') -> (q%d,'%c', move=%d) amp=(%.6f%+.6fi)\n",
                   i,
                   rules[i].estado_in, rules[i].simbolo_in,
                   rules[i].estado_out, rules[i].simbolo_out,
                   rules[i].move,
                   creal(rules[i].amp), cimag(rules[i].amp));
        }

    } else if (sim_type == 1) {
        // Linguagem A
        if (argc < 3) {
            fprintf(stderr, "Erro: forneça a entrada para a Linguagem A (ex: 000111)\n");
            return 1;
        }
        char *entrada = argv[2];

        // Copia a entrada para a fita inicial
        for (int i = 0; i < (int)strlen(entrada) && i < FITA_TAM; i++)
            init_cfg.fita[i] = entrada[i];

        // Cria regras da MTQ para Linguagem A
        numRules = criar_regras_linguagem_a(rules, entrada);
        printf("Numero de regras: %d\n", numRules);

    } else {
        fprintf(stderr, "Tipo de simulacao desconhecido.\n");
        return 1;
    }

    // ---------- Inicializa configuração quântica ----------
    quantum_config_t configs[MAX_CONFIGS];
    configs[0].config = init_cfg;
    configs[0].amplitude = 1.0 + 0.0*I;
    int numConfigs = 1;

    // ---------- Loop de passos discretos ----------
    int maxSteps = 20;
    for (int step = 0; step < maxSteps; step++) {
        printf("\n--- Passo %d ---\n", step);
        print_state(configs, numConfigs);

        // Verifica se toda amplitude está no estado final
        double prob_final = 0.0;
        for (int i = 0; i < numConfigs; i++)
            if (configs[i].config.estado == QF)
                prob_final += cabs(configs[i].amplitude) * cabs(configs[i].amplitude);

        if (prob_final > 1.0 - 1e-12) {
            printf("Toda amplitude em estado final (QF). Parando antes dos %d passos.\n", maxSteps);
            break;
        }

        // Aplica transições para gerar novas configurações
        quantum_config_t novas[MAX_CONFIGS];
        int numNovas = transicao(configs, numConfigs, rules, numRules, novas);
        if (numNovas == 0) {
            printf("Nenhuma nova configuracao gerada; parando.\n");
            break;
        }

        // Atualiza configurações atuais
        numConfigs = numNovas;
        for (int i = 0; i < numConfigs; i++) configs[i] = novas[i];
    }

    // ---------- Estado final antes da medição ----------
    printf("\n--- Estado final antes da medicao ---\n");
    print_state(configs, numConfigs);

    // ---------- Medição do estado final ----------
    quantum_config_t resultado = medir(configs, numConfigs);
    printf("\n--- Resultado da medicao ---\n");
    printf("Amplitude escolhida: (%.6f%+.6fi)\n", creal(resultado.amplitude), cimag(resultado.amplitude));
    printf("Config medida: ");
    print_config_brief(&resultado.config);
    printf("\n");

    // ---------- Decisão final ----------
    if (sim_type == 0) {
        // Algoritmo de Deutsch: decisão entre função constante ou balanceada
        char simbolo0 = resultado.config.fita[0];
        if (simbolo0 == '0') printf("Decisao: FUNCAO CONSTANTE\n");
        else if (simbolo0 == '1') printf("Decisao: FUNCAO BALANCEADA\n");
        else printf("Decisao indeterminada.\n");
    } else {
        // Linguagem A: apenas exibe estado final e fita
        printf("Resultado final da Linguagem A (estado=%d, fita[0]=%c)\n",
               resultado.config.estado, resultado.config.fita[0]);
    }

    return 0;
}
