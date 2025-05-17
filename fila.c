#include "estruturas.h"
#include "fila.h"

void enqueue_paciente(Fila *queue, Registro *dados) {
    Efila *novo = malloc(sizeof(Efila));
    novo->dados = dados;
    novo->proximo = NULL;

    if(queue->head == NULL) {
        queue->head = novo;
        queue->tail = novo;
    } else {
        queue->tail->proximo = novo;
        queue->tail = novo;
    }
    queue->qntd++;
}

void dequeue_paciente(Fila *queue) {
    if(queue->head == NULL) {
        printf("\nFila vazia!");
        return;
    }

    Efila *temp = queue->head;
    queue->head = queue->head->proximo;
    free(temp);
    queue->qntd--;

    if(queue->head == NULL) {
        queue->tail = NULL;
    }
}

void mostrar_queue(Fila *q) {
    Efila *atual = q->head;
    if(atual == NULL) {
        printf("\nFila vazia!");
        return;
    }
    while(atual != NULL) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Nome: %s \n", atual->dados->nome);
        printf("Idade: %d \n", atual->dados->idade);
        printf("RG: %s \n", atual->dados->rg);
        printf("Data: %d/%d/%d \n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
        atual = atual->proximo;
    }
} 