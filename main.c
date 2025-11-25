#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5     // tamanho fixo da fila circular
#define TAM_PILHA 3    // tamanho maximo da pilha de reserva

/*
 * Struct Peca
 * Representa uma peca do jogo Tetris Stack.
 * nome: caractere ('I', 'O', 'T', 'L')
 * id: numero unico gerado automaticamente
 */
typedef struct {
    char nome;
    int id;
} Peca;

/*
 * Variaveis da FILA CIRCULAR
 */
int frente = 0;
int tras = 0;
int tamanhoFila = 0;

/*
 * Variaveis da PILHA
 */
int topo = -1;

/*
 * Funcao: gerarPeca
 * Gera uma nova peca aleatoria com id unico.
 */
Peca gerarPeca(int id) {
    Peca p;
    char tipos[4] = {'I','O','T','L'};
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

/*
 * Enqueue na fila circular
 * Insere peca no final, se houver espaco.
 */
void enqueue(Peca fila[], Peca nova) {
    if (tamanhoFila == TAM_FILA) {
        printf("Fila cheia! (isso nao deveria ocorrer pois o jogo substitui automaticamente)\n");
        return;
    }

    fila[tras] = nova;
    tras = (tras + 1) % TAM_FILA;
    tamanhoFila++;
}

/*
 * Dequeue da fila circular
 * Remove peca da frente da fila.
 */
Peca dequeue(Peca fila[]) {
    Peca vazia = {'-', -1};

    if (tamanhoFila == 0) {
        printf("Fila vazia! Nao ha o que jogar.\n");
        return vazia;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    tamanhoFila--;

    return removida;
}

/*
 * Push na pilha
 * Adiciona uma peca ao topo, se nao estiver cheia.
 */
void push(Peca pilha[], Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Nao e possivel reservar a peca.\n");
        return;
    }

    pilha[++topo] = p;
    printf("Peca [%c %d] reservada.\n", p.nome, p.id);
}

/*
 * Pop na pilha
 * Remove peca do topo.
 */
Peca pop(Peca pilha[]) {
    Peca vazia = {'-', -1};

    if (topo == -1) {
        printf("Pilha vazia! Nao ha peca reservada.\n");
        return vazia;
    }

    Peca removida = pilha[topo--];
    printf("Peca reservada usada: [%c %d]\n", removida.nome, removida.id);

    return removida;
}

/*
 * Mostrar estado da fila
 */
void mostrarFila(Peca fila[]) {
    printf("\nFila de pecas: ");

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
 * Mostrar estado da pilha
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
 * Mostrar estado geral do jogo
 */
void mostrarEstado(Peca fila[], Peca pilha[]) {
    printf("\n=== ESTADO ATUAL ===\n");
    mostrarFila(fila);
    mostrarPilha(pilha);
    printf("=====================\n");
}

int main() {
    Peca fila[TAM_FILA];
    Peca pilha[TAM_PILHA];
    int opcao;
    int contadorID = 0;

    srand(time(NULL));

    /*
     * Inicializa a Fila com 5 pecas automaticamente
     */
    printf("Inicializando fila com 5 pecas...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila, gerarPeca(contadorID++));
    }

    mostrarEstado(fila, pilha);

    /*
     * MENU PRINCIPAL
     */
    do {
        printf("\nAcoes disponiveis:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada (pop)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Jogar peca da fila
            Peca jogada = dequeue(fila);
            if (jogada.id != -1) {
                printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
            }

            // Manter fila sempre cheia
            enqueue(fila, gerarPeca(contadorID++));
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 2) {
            // Reservar peca (fila -> pilha)
            Peca removida = dequeue(fila);

            if (removida.id != -1) {
                push(pilha, removida);
            }

            // Nova peca gerada
            enqueue(fila, gerarPeca(contadorID++));
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 3) {
            // Usar peca reservada
            pop(pilha);

            // Sempre criar nova peca para a fila
            enqueue(fila, gerarPeca(contadorID++));
            mostrarEstado(fila, pilha);
        }

        else if (opcao == 0) {
            printf("Saindo...\n");
        }

        else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
