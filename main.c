#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // capacidade maxima da fila circular

/*
 * Struct Peca
 * Representa uma peca do jogo Tetris Stack.
 * Cada peca tem:
 * - nome: caractere ('I', 'O', 'T', 'L')
 * - id: numero unico de criacao
 */
typedef struct {
    char nome;
    int id;
} Peca;

/*
 * Variaveis de controle da fila circular
 * - frente: indice do primeiro elemento
 * - tras: indice do ultimo elemento
 * - tamanho: quantidade atual de elementos
 */
int frente = 0;
int tras = 0;
int tamanho = 0;

/*
 * Funcao: gerarPeca
 * Gera automaticamente uma nova peca aleatoria.
 * Os tipos possiveis sao: I, O, T, L.
 */
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;

    p.nome = tipos[rand() % 4];
    p.id = id;

    return p;
}

/*
 * Funcao: enqueue
 * Insere uma nova peca no final da fila circular,
 * caso haja espaco.
 */
void enqueue(Peca fila[], Peca nova) {
    if (tamanho == TAM_FILA) {
        printf("Fila cheia! Nao foi possivel adicionar nova peca.\n");
        return;
    }

    fila[tras] = nova;
    tras = (tras + 1) % TAM_FILA;
    tamanho++;

    printf("Peca [%c %d] adicionada.\n", nova.nome, nova.id);
}

/*
 * Funcao: dequeue
 * Remove a peca da frente da fila e retorna o valor removido.
 */
Peca dequeue(Peca fila[]) {
    Peca vazia = {'-', -1};

    if (tamanho == 0) {
        printf("Fila vazia! Nao ha peca para jogar.\n");
        return vazia;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    tamanho--;

    printf("Peca jogada: [%c %d]\n", removida.nome, removida.id);
    return removida;
}

/*
 * Funcao: mostrarFila
 * Exibe todas as pecas atuais da fila circular na ordem correta.
 */
void mostrarFila(Peca fila[]) {
    printf("\n=== Fila de pecas ===\n");

    if (tamanho == 0) {
        printf("Fila vazia.\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < tamanho; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\n======================\n");
}

int main() {
    Peca fila[TAM_FILA];
    int opcao;
    int contadorID = 0;

    srand(time(NULL));

    // Inicializa com 5 pecas automaticamente
    printf("Inicializando fila de pecas...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila, gerarPeca(contadorID++));
    }

    mostrarFila(fila);

    do {
        printf("\nAcoes disponiveis:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            dequeue(fila);
            mostrarFila(fila);
        }
        else if (opcao == 2) {
            Peca nova = gerarPeca(contadorID++);
            enqueue(fila, nova);
            mostrarFila(fila);
        }
        else if (opcao == 0) {
            printf("Encerrando sistema...\n");
        }
        else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
