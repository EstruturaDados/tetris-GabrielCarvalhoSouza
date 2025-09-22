#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX 5

char letras[] = {'I', 'O', 'T', 'L'};
int tamanho = sizeof(letras) / sizeof(letras[0]);

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

typedef struct {
    Peca peca[3];
    int topo;
} Pilha;

Peca retornaPecaAleatoria() {
    int indice = rand() % tamanho;
    Peca p = {letras[indice], id};
    return p;
}

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void inserirFila(Fila *fila, Peca peca) {
    peca.id = id;
    id++;
    fila->peca[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % MAX;
    fila->total++;
}

void inserirPilha(Pilha *pilha, Peca peca) {
    pilha->topo++;
    pilha->peca[pilha->topo] = peca;
}

void removerFila(Fila *fila, Peca *peca) {
    *peca = fila->peca[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->total--;
    inserirFila(fila, retornaPecaAleatoria());
}

void removerPilha(Pilha *pilha, Peca *peca) {
    *peca = pilha->peca[pilha->topo];
    pilha->topo--;
}

void mostrarFila(Fila *fila) {
    printf("Fila de peças: ");
    for (int i = 0, idx = fila->inicio; i < fila->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c,%d] ", fila->peca[idx].tipo, fila->peca[idx].id);
    }
    printf("\n");
}

void mostrarPilha(Pilha *pilha) {
    printf("Pilha de peças: ");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%c,%d] ", pilha->peca[i].tipo, pilha->peca[i].id);
    }
    printf("\n");
}

void trocarFrenteComTopo(Fila *fila, Pilha *pilha) {
    Peca tmp = fila->peca[fila->inicio];
    fila->peca[fila->inicio] = pilha->peca[pilha->topo];
    pilha->peca[pilha->topo] = tmp;
}

void trocarTres(Fila *fila, Pilha *pilha) {
    // assumimos que pilha->topo == 2 e fila->total >= 3 (checado antes)
    int idx0 = fila->inicio;
    int idx1 = (fila->inicio + 1) % MAX;
    int idx2 = (fila->inicio + 2) % MAX;

    // troca direto, correspondência: pilha[2] é topo (último empilhado)
    // vamos trocar pilha[2], pilha[1], pilha[0] com idx0, idx1, idx2 (ordem arbitrária, desde que consistente)
    Peca tmp0 = fila->peca[idx0];
    Peca tmp1 = fila->peca[idx1];
    Peca tmp2 = fila->peca[idx2];

    fila->peca[idx0] = pilha->peca[0];
    fila->peca[idx1] = pilha->peca[1];
    fila->peca[idx2] = pilha->peca[2];

    pilha->peca[0] = tmp0;
    pilha->peca[1] = tmp1;
    pilha->peca[2] = tmp2;
}

int main() {
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

    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    Pilha pilha;
    inicializarPilha(&pilha);

    for (int i = 0; i < MAX; i++) {
        inserirFila(&fila, retornaPecaAleatoria());
    }

    mostrarFila(&fila);
    mostrarPilha(&pilha);

    int opcao;
    do {
        printf("Menu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Jogar peça reservada\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (filaVazia(&fila)) {
                    printf("Fila vazia! Não é possível remover peça.\n");
                    break;
                }

                Peca pecaRemovida;

                removerFila(&fila, &pecaRemovida);
                printf("Peça jogada: [%c,%d]\n", pecaRemovida.tipo, pecaRemovida.id);

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);

                break;
            case 2:
                if (pilhaCheia(&pilha)) {
                    printf("Pilha cheia! Não é possível reservar peça.\n");
                    break;
                }

                Peca pecaReservada;
                removerFila(&fila, &pecaReservada);
                inserirPilha(&pilha, pecaReservada);
                printf("Peça reservada: [%c,%d]\n", pecaReservada.tipo, pecaReservada.id);

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            case 3:
                if (pilhaVazia(&pilha)) {
                    printf("Pilha vazia! Não é possível usar peça.\n");
                    break;
                }

                Peca pecaUsada;


                removerPilha(&pilha, &pecaUsada);
                printf("Peça usada: [%c,%d]\n", pecaUsada.tipo, pecaUsada.id);

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            case 4:
                if (pilhaVazia(&pilha) || filaVazia(&fila)) {
                    printf("Pilha ou fila vazia! Não é possível trocar peça.\n");
                    break;
                }

                trocarFrenteComTopo(&fila, &pilha);
                printf("Troca concluida!\n");

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            case 5:
                if (pilha.topo + 1 < 3 || fila.total < 3) {
                    printf("Pilha ou fila com menos de 3 peças! Não é possível trocar peças.\n");
                    break;
                }
                
                trocarTres(&fila, &pilha);
                printf("Troca concluida!\n");

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}
