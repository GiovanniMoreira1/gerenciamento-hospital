#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "estruturas.h"

HeapMaximo* criarHeap() {

    HeapMaximo* heap = (HeapMaximo*)malloc(sizeof(HeapMaximo));
    

    if (heap == NULL) {
        printf(RED);
        printf("Erro ao alocar memória para o heap!\n");
        return NULL;
    }
    
    heap->pacientes = (Registro**)malloc(20 * sizeof(Registro*));

    if (heap->pacientes == NULL) {
        printf(RED);
        printf("Erro ao alocar memória para o vetor de pacientes!\n");
        free(heap);
        return NULL;
    }
    heap->tamanho = 0;
    heap->capacidade = 20; 
    return heap;
}


void destruirHeap(HeapMaximo* heap) {
    if (heap == NULL) {
        printf(RED);
        printf("Heap não existe!\n");
        return;
    }

    free(heap->pacientes);

    free(heap);
}


int inserirPaciente(HeapMaximo* heap, Registro* paciente) {
    if(heapCheio(heap)) {
        printf(RED);
        printf("Erro: Heap está cheio!\n");
        return 0; 
    }
    heap->pacientes[heap->tamanho] = paciente;
    subir(heap, heap->tamanho);
    heap->tamanho++;
    
    return 1;
}


Registro* removerPaciente(HeapMaximo* heap) {
    if(heapVazio(heap)) {
        printf(RED);
        printf("Erro: Heap está vazio!\n");
        return NULL;
    }
    Registro* paciente = heap->pacientes[0];
    heap->pacientes[0] = heap->pacientes[heap->tamanho - 1];
    heap->tamanho--;
    if(heap->tamanho > 0) {
        descer(heap, 0);
    }

    return paciente;
}


int heapVazio(HeapMaximo* heap) {
    if(heap->tamanho == 0) {
        return 1;
    }
    return 0;
}


int heapCheio(HeapMaximo* heap) {

    if(heap->tamanho == heap->capacidade) {
        return 1;
    }
    return 0;
}


void subir(HeapMaximo* heap, int indice) {
    int pai = (indice - 1) / 2;
    if(indice > 0 && heap->pacientes[indice]->idade > heap->pacientes[pai]->idade) {
        trocar(&heap->pacientes[indice], &heap->pacientes[pai]);
        subir(heap, pai);
    }
}


void descer(HeapMaximo* heap, int indice) {
    int esquerda = 2 * indice + 1;  // filho esquerdo
    int direita = 2 * indice + 2;   // filho direito
    int maior = indice;          

    if(esquerda < heap->tamanho && 
       heap->pacientes[esquerda]->idade > heap->pacientes[maior]->idade) {
        maior = esquerda;
    }

    if(direita < heap->tamanho && 
       heap->pacientes[direita]->idade > heap->pacientes[maior]->idade) {
        maior = direita;
    }
    
    if(maior != indice) {
        trocar(&heap->pacientes[indice], &heap->pacientes[maior]);
        descer(heap, maior);  // Continua descendo a partir da nova posição
    }

}


void trocar(Registro** a, Registro** b) {
    Registro* temp = *a;  // guarda o valor do primeiro ponteiro
    *a = *b;             // primeiro ponteiro recebe o valor do segundo
    *b = temp;          
}


void imprimirHeap(HeapMaximo* heap) {

    if(heapVazio(heap)) {
        printf(RED);
        printf("Heap vazio!\n");
        return;
    }
    for(int i = 0; i < heap->tamanho; i++) {
        printf(LIGHT_BLUE);
        printf("\nPaciente %d:\n", i + 1);
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Nome: %s\n", heap->pacientes[i]->nome);
        printf("Idade: %d\n", heap->pacientes[i]->idade);
        printf("RG: %s\n", heap->pacientes[i]->rg);
        printf("Data: %d/%d/%d\n", heap->pacientes[i]->entrada->dia, heap->pacientes[i]->entrada->mes, heap->pacientes[i]->entrada->ano);
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(RESET);

}

void imprimirProximoAtendimento(HeapMaximo* heap) {
    if(heapVazio(heap)) {
        printf(RED);
        printf("Não há pacientes na fila prioritária!\n");
        return;
    }

    printf(LIGHT_BLUE);
    printf("\nPróximo paciente a ser atendido:\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Nome: %s\n", heap->pacientes[0]->nome);
    printf("Idade: %d\n", heap->pacientes[0]->idade);
    printf("RG: %s\n", heap->pacientes[0]->rg);
    printf("Data de entrada: %d/%d/%d\n", 
           heap->pacientes[0]->entrada->dia,
           heap->pacientes[0]->entrada->mes,
           heap->pacientes[0]->entrada->ano);
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(RESET);
}

void desenfileirarPaciente(HeapMaximo* heap, const char* rg) {
    if(heapVazio(heap)) {
        printf(RED);
        printf("Não há pacientes na fila prioritária!\n");
        return;
    }

    HeapMaximo* temp = criarHeap();
    int encontrado = 0;

    while(!heapVazio(heap)) {
        Registro* paciente = removerPaciente(heap);
        if(strcmp(paciente->rg, rg) == 0) {
            printf(LIGHT_BLUE);
            printf("\nPaciente desenfileirado:\n");
            printf("Nome: %s\n", paciente->nome);
            printf("Idade: %d\n", paciente->idade);
            printf("RG: %s\n", paciente->rg);
            encontrado = 1;
        } else {
            inserirPaciente(temp, paciente);
        }
    }
    while(!heapVazio(temp)) {
        Registro* paciente = removerPaciente(temp);
        inserirPaciente(heap, paciente);
    }
    if(!encontrado) {
        printf(RED);
        printf("Paciente não encontrado na fila prioritária!\n");
    }
    
    destruirHeap(temp);
}

void enfileirarPaciente(HeapMaximo* heap, Lista* lista, const char* rg) {
    Elista* atual = lista->inicio;

    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }
    
    if(atual == NULL) {
        printf(RED);
        printf("Paciente não encontrado!\n");
        return;
    }
    
    if(heapCheio(heap)) {
        printf(RED);
        printf("Fila prioritária cheia! Máximo de 20 pacientes.\n");
        return;
    }
    
    inserirPaciente(heap, atual->dados);
    printf(GREEN);
    printf("Paciente enfileirado com sucesso!\n");
    printf(RESET);
}

