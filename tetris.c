#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 10  // Tamanho máximo da fila
#define TAM_INICIAL 5  // Número de peças iniciais

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// Estrutura da peça
typedef struct {
    char nome;  // Tipo da peça
    int id;     // Identificador único
} Peca;

// Estrutura da fila
typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Prototipação
void inicializarFila(Fila* f);
int filaVazia(Fila* f);
int filaCheia(Fila* f);
void enfileirar(Fila* f, Peca nova);
void desenfileirar(Fila* f);
void exibirFila(Fila* f);
Peca gerarPeca();

// Variável global para controlar o ID único das peças
int proximoID = 0;

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    Fila fila;
    int opcao;
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    inicializarFila(&fila);

    // Preencher fila com TAM_INICIAL peças
    for (int i = 0; i < TAM_INICIAL; i++) {
        enfileirar(&fila, gerarPeca());
    }

    do {
        printf("\nConfira a seguir seu estado:\n");
        exibirFila(&fila);

        printf("\nOpções de ação:\n");
        printf("1\tJogar peça (dequeue)\n");
        printf("2\tInserir nova peça (enqueue)\n");
        printf("0\tSair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
      switch (opcao) {
            case 1:
                desenfileirar(&fila);
                break;
            case 2:
                if (!filaCheia(&fila)) {
                    enfileirar(&fila, gerarPeca());
                } else {
                    printf("Fila cheia! Não é possível adicionar mais peças.\n");
                }
                break;
            case 0:
               printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Inicializa a fila
void inicializarFila(Fila* f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila* f) {
    return f->tamanho == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila* f) {
    return f->tamanho == MAX_FILA;
}

// Enfileira uma nova peça
void enfileirar(Fila* f, Peca nova) {
    if (filaCheia(f)) {
        printf("Erro: Fila cheia\n");
        return;
    }

    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = nova;
    f->tamanho++;
}

// Remove a peça da frente
void desenfileirar(Fila* f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;

    printf("Peça [%c %d] jogada.\n", removida.nome, removida.id);
}

// Exibe o conteúdo atual da fila
void exibirFila(Fila* f) {
    printf("\nFila de peças:\n");
    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }

    for (int i = 0; i < f->tamanho; i++) {
        int idx = (f->frente + i) % MAX_FILA;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// Gera uma nova peça com tipo aleatório e ID único
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoID++;
    return nova;
}

