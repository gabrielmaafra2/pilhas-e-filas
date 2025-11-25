#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

/*
 * Struct Peca
 * Representa cada peca do jogo Tetris Stack.
 * nome: caractere ('I','O','T','L')
 * id: numero unico incremental
 */
typedef struct {
    char nome;
    int id;
} Peca;

/*
 * Variaveis globais da FILA CIRCULAR
 */
int frente = 0;
int tras = 0;
int tamanhoFila = 0;

/*
 * Variavel global da PILHA (topo)
 */
int topo = -1;

/*
 * Gerar peca aleatoria
 */
Peca gerarPeca(int id) {
    char tipos[4] = {'I','O','T','L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

/*
 * Enqueue: insere no fim da fila circular
 */
void enqueue(Peca fila[], Peca nova) {
    if (tamanhoFila == TAM_FILA) {
        printf("Fila cheia! (erro inesperado)\n");
        return;
    }
    fila[tras] = nova;
    tras = (tras + 1) % TAM_FILA;
    tamanhoFila++;
}

/*
 * Dequeue: remove da frente da fila
 */
Peca dequeue(Peca fila[]) {
    Peca vazia = {'-', -1};
    if (tamanhoFila == 0) {
        printf("Fila vazia!\n");
        return vazia;
    }
    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    tamanhoFila--;
    return removida;
}

/*
 * Push: insere no topo da pilha
 */
void push(Peca pilha[], Peca nova) {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Nao e possivel reservar.\n");
        return;
    }
    pilha[++topo] = nova;
    printf("Peca [%c %d] reservada.\n", nova.nome, nova.id);
}

/*
 * Pop: remove do topo da pilha
 */
Peca pop(Peca pilha[]) {
    Peca vazia = {'-', -1};
    if (topo == -1) {
        printf("Pilha vazia! Nao ha peca reservada.\n");
        return vazia;
    }
    return pilha[topo--];
}

/*
 * Mostrar fila circular
 */
void mostrarFila(Peca fila[]) {
    printf("Fila de pecas: ");
    if (tamanhoFila == 0) {
        printf("(vazia)\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < tamanhoFila; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

/*
 * Mostrar pilha
 */
void mostrarPilha(Peca pilha[]) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (topo == -1) {
        printf("(vazia)\n");
        return;
    }
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

/*
 * Mostrar estado geral
 */
void mostrarEstado(Peca fila[], Peca pilha[]) {
    printf("\n=== ESTADO ATUAL ===\n");
    mostrarFila(fila);
    mostrarPilha(pilha);
    printf("=====================\n");
}

/*
 * Trocar uma peca da frente da fila com o topo da pilha
 */
void trocarSimples(Peca fila[], Peca pilha[]) {
    if (tamanhoFila == 0 || topo == -1) {
        printf("Nao e possivel trocar: fila ou pilha esta vazia.\n");
        return;
    }

    // frente da fila
    int idx = frente;

    // troca simples
    Peca temp = fila[idx];
    fila[idx] = pilha[topo];
    pilha[topo] = temp;

    printf("Troca simples realizada.\n");
}

/*
 * Troca multipla: 3 primeiras da fila <-> 3 da pilha
 */
void trocarMultipla(Peca fila[], Peca pilha[]) {
    if (tamanhoFila < 3 || topo < 2) {
        printf("Nao ha pecas suficientes para troca multipla.\n");
        return;
    }

    int idx = frente;

    // troca 3 elementos
    for (int i = 0; i < 3; i++) {
        int posFila = (idx + i) % TAM_FILA;
        Peca temp = fila[posFila];
        fila[posFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("Troca multipla concluida (3 pecas).\n");
}

/*
 * Programa principal
 */
int main() {
    Peca fila[TAM_FILA];
    Peca pilha[TAM_PILHA];
    int opcao;
    int contadorID = 0;

    srand(time(NULL));

    // Inicializa a fila com 5 pecas
    printf("Inicializando fila com 5 pecas...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila, gerarPeca(contadorID++));
    }

    mostrarEstado(fila, pilha);

    do {
        printf("\nOpcoes:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada (pop)\n");
        printf("4 - Trocar peca da fila com topo da pilha\n");
        printf("5 - Troca multipla (3 da fila <-> 3 da pilha)\n");
        printf("6 - Mostrar estado\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // JOGAR PECA
            Peca jogada = dequeue(fila);
            if (jogada.id != -1) {
                printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
            }

            // Gerar nova peca
            enqueue(fila, gerarPeca(contadorID++));
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 2) {
            // RESERVAR PECA
            Peca p = dequeue(fila);
            if (p.id != -1) {
                push(pilha, p);
            }

            enqueue(fila, gerarPeca(contadorID++));
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 3) {
            // USAR PECA RESERVADA
            Peca usada = pop(pilha);
            if (usada.id != -1) {
                printf("Peca usada: [%c %d]\n", usada.nome, usada.id);
            }

            enqueue(fila, gerarPeca(contadorID++));
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 4) {
            // TROCA SIMPLES
            trocarSimples(fila, pilha);
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 5) {
            // TROCA MULTIPLA
            trocarMultipla(fila, pilha);
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 6) {
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 0) {
            printf("Finalizando...\n");
        }

        else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
