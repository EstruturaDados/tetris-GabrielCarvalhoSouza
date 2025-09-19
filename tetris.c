#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX 5

int id = 0;

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca peca[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserirFila(Fila *fila, Peca peca) {
    peca.id = id;
    id++;
    fila->peca[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % MAX;
    fila->total++;
}

void removerFila(Fila *fila, Peca *peca) {
    *peca = fila->peca[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->total--;
}

void mostrarFila(Fila *fila) {
    printf("Fila de peças:\n");
    for (int i = 0, idx = fila->inicio; i < fila->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c,%d] ", fila->peca[idx].tipo, fila->peca[idx].id);
    }
    printf("\n");
}

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
    Peca p1 = {'I'};
    Peca p2 = {'O'};
    Peca p3 = {'T'};
    Peca p4 = {'L'};
    Peca p5 = {'I'};

    Fila fila;
    inicializarFila(&fila);

    inserirFila(&fila, p1);
    inserirFila(&fila, p2);
    inserirFila(&fila, p3);
    inserirFila(&fila, p4);
    inserirFila(&fila, p5);

    int opcao;
    do {
        printf("Menu:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Inserir peça na fila\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Peca pecaRemovida;
                if (filaVazia(&fila)) {
                    printf("Fila vazia! Não é possível remover peça.\n");
                    break;
                }
                removerFila(&fila, &pecaRemovida);
                printf("Peça removida: [%c,%d]\n", pecaRemovida.tipo, pecaRemovida.id);
                break;
            case 2:
                Peca novaPeca;
                if (filaCheia(&fila)) {
                    printf("Fila cheia! Não é possível inserir peça.\n");
                    break;
                }
                printf("Digite o tipo da peça: ");
                scanf("%c", &novaPeca.tipo);
                novaPeca.id = id;
                id++;
                inserirFila(&fila, novaPeca);
                break;
            case 3:
                mostrarFila(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}
