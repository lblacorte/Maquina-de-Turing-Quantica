# ----------------------------
# Makefile para MTQ Deutsch + Linguagem A
# ----------------------------

# Compilador C
CC = gcc

# Flags de compilação:
# -std=c11 -> usar padrão C11
# -O2      -> otimização de nível 2
# -Wall    -> habilita todos avisos
# -Iinclude -> adiciona pasta "include" para headers
CFLAGS = -std=c11 -O2 -Wall -Iinclude

# Flags de linkedição: -lm -> biblioteca matemática
LDFLAGS = -lm

# Lista de arquivos fonte
SRC = src/mtq_deutsch.c src/util.c src/quantum.c src/deutsch.c src/linguagem_a.c

# Cria lista de arquivos objeto correspondente
OBJ = $(SRC:.c=.o)

# Nome do executável final
EXEC = mtq_deutsch

# ----------------------------
# Regra padrão: compila tudo
# ----------------------------
all: $(EXEC)

# ----------------------------
# Compilar executável a partir dos objetos
# $@ -> nome do alvo (EXEC)
# $(OBJ) -> lista de objetos
# $(LDFLAGS) -> bibliotecas
# ----------------------------
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

# ----------------------------
# Regra genérica: compilar cada .c para .o
# $< -> primeiro dependente (arquivo .c)
# $@ -> alvo (arquivo .o)
# ----------------------------
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------
# Rodar programa (exemplo: Deutsch f_type=0)
# ----------------------------
run: $(EXEC)
	./$(EXEC) 0

# ----------------------------
# Limpar arquivos objeto e executável
# ----------------------------
clean:
	rm -f src/*.o $(EXEC)
