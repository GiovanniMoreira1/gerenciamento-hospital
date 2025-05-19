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
        printf(RED);
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

void desfazer_enqueue(Fila *queue) {
    if(queue == NULL || queue->head == NULL) {
        printf(RED);
        printf("\nFila vazia!\n");
        return;
    }

    Efila *temp = queue->tail;

    if (queue->head == queue->tail) {
        // fila tem tamanho 1
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        Efila *anterior = queue->head;
        while(anterior->proximo != queue->tail) {
            anterior = anterior->proximo;
        }
        anterior->proximo = NULL;
        queue->tail = anterior;
    }

    queue->qntd--;
    free(temp);
}

void desfazer_dequeue(Fila *queue, Registro *dados) {
    if (queue == NULL || dados == NULL) {
        printf(RED);
        printf("\nErro: parâmetros inválidos.\n");
        return;
    }

    Efila *nova = malloc(sizeof(Efila));
    nova->dados = dados;
    nova->proximo = queue->head;

    queue->head = nova;
    queue->qntd++;

    if (queue->tail == NULL) {
        queue->tail = nova;
    }

}

void mostrar_queue(Fila *q) {
    Efila *atual = q->head;
    if(atual == NULL) {
        printf(RED);
        printf("\nFila vazia!");
        return;
    }
    while(atual != NULL) {
        printf(LIGHT_BLUE);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf(LIGHT_BLUE "Nome: " RESET "%s \n", atual->dados->nome);
        printf(LIGHT_BLUE "Idade: " RESET "%d \n", atual->dados->idade);
        printf(LIGHT_BLUE "RG: " RESET "%s \n", atual->dados->rg);
        printf(LIGHT_BLUE "Data: " RESET "%d/%d/%d \n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
        atual = atual->proximo;
    }
} 