#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HeapMaximo* criarHeap() {

    HeapMaximo* heap = (HeapMaximo*)malloc(sizeof(HeapMaximo));
    

    if (heap == NULL) {
        printf("Erro ao alocar memória para o heap!\n");
        return NULL;
    }
    
    // Aloca memória para o vetor de ponteiros (capacidade 20)
    heap->pacientes = (Registro**)malloc(20 * sizeof(Registro*));

    // Verifica se a alocação do vetor foi bem sucedida
    if (heap->pacientes == NULL) {
        printf("Erro ao alocar memória para o vetor de pacientes!\n");
        free(heap);  // Libera a memória já alocada
        return NULL;
    }
    heap->tamanho = 0;
    heap->capacidade = 20; 
    return heap;
}


void destruirHeap(HeapMaximo* heap) {
    if (heap == NULL) {
        printf("Heap não existe!\n");
        return;
    }

    free(heap->pacientes);

    free(heap);
}


int inserirPaciente(HeapMaximo* heap, Registro* paciente) {
    // 1. Verificar se o heap está cheio
    if(heapCheio(heap)) {
        printf("Erro: Heap está cheio!\n");
        return 0;  // Retorna 0 indicando falha
    }
    
    // 2. Inserir o paciente no final do vetor
    heap->pacientes[heap->tamanho] = paciente;
    
    // 3. Ajustar o heap para cima (subir)
    subir(heap, heap->tamanho);
    
    // 4. Incrementar o tamanho
    heap->tamanho++;
    
    // 5. Retornar 1 indicando sucesso
    return 1;
}


Registro* removerPaciente(HeapMaximo* heap) {
    // 1. Verificar se o heap está vazio
    if(heapVazio(heap)) {
        printf("Erro: Heap está vazio!\n");
        return NULL;
    }
    
    // 2. Salvar o paciente da raiz (maior prioridade)
    Registro* paciente = heap->pacientes[0];
    
    // 3. Mover o último elemento para a raiz
    heap->pacientes[0] = heap->pacientes[heap->tamanho - 1];
    
    // 4. Decrementar o tamanho
    heap->tamanho--;
    
    // 5. Ajustar o heap para baixo (descer)
    if(heap->tamanho > 0) {  // Só ajusta se ainda houver elementos
        descer(heap, 0);
    }
    
    // 6. Retornar o paciente removido
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
    // 1. Calcular o índice do pai
    int pai = (indice - 1) / 2;  // Fórmula para encontrar o pai

    // 2. Verificar se não é a raiz (indice > 0) e se o filho é maior que o pai
    if(indice > 0 && heap->pacientes[indice]->idade > heap->pacientes[pai]->idade) {
        // 3. Trocar pai e filho
        trocar(&heap->pacientes[indice], &heap->pacientes[pai]);
        // 4. Continuar subindo a partir da nova posição do pai
        subir(heap, pai);
    }
    // 5. Se chegou na raiz ou o pai é maior, a função termina
}


void descer(HeapMaximo* heap, int indice) {
    // 1. Calcular os índices dos filhos
    int esquerda = 2 * indice + 1;  // Filho esquerdo
    int direita = 2 * indice + 2;   // Filho direito
    int maior = indice;             // Assume que o pai é o maior

    // 2. Encontrar o maior entre pai e filhos
    // Verifica se o filho esquerdo existe e é maior que o pai
    if(esquerda < heap->tamanho && 
       heap->pacientes[esquerda]->idade > heap->pacientes[maior]->idade) {
        maior = esquerda;
    }
    
    // Verifica se o filho direito existe e é maior que o maior até agora
    if(direita < heap->tamanho && 
       heap->pacientes[direita]->idade > heap->pacientes[maior]->idade) {
        maior = direita;
    }
    
    // 3. Se o maior não for o pai, trocar e continuar descendo
    if(maior != indice) {
        trocar(&heap->pacientes[indice], &heap->pacientes[maior]);
        descer(heap, maior);  // Continua descendo a partir da nova posição
    }

}


void trocar(Registro** a, Registro** b) {
    Registro* temp = *a;  // Guarda o valor do primeiro ponteiro
    *a = *b;             // Primeiro ponteiro recebe o valor do segundo
    *b = temp;           // Segundo ponteiro recebe o valor guardado
}


void imprimirHeap(HeapMaximo* heap) {

    if(heapVazio(heap)) {
        printf("Heap vazio!\n");
        return;
    }
    for(int i = 0; i < heap->tamanho; i++) {
        printf("Nome: %s\n", heap->pacientes[i]->nome);
        printf("Idade: %d\n", heap->pacientes[i]->idade);
        printf("RG: %s\n", heap->pacientes[i]->rg);
        printf("Data: %d/%d/%d\n", heap->pacientes[i]->entrada->dia, heap->pacientes[i]->entrada->mes, heap->pacientes[i]->entrada->ano);
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

}

void imprimirProximoAtendimento(HeapMaximo* heap) {
    // 1. Verificar se o heap está vazio
    if(heapVazio(heap)) {
        printf("Não há pacientes na fila prioritária!\n");
        return;
    }
    
    // 2. Imprimir os dados do paciente na raiz
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
}

void desenfileirarPaciente(HeapMaximo* heap, const char* rg) {
    if(heapVazio(heap)) {
        printf("Não há pacientes na fila prioritária!\n");
        return;
    }

    // Criar um heap temporário
    HeapMaximo* temp = criarHeap();
    int encontrado = 0;
    
    // Procurar o paciente e mover os outros para o heap temporário
    while(!heapVazio(heap)) {
        Registro* paciente = removerPaciente(heap);
        if(strcmp(paciente->rg, rg) == 0) {
            printf("\nPaciente desenfileirado:\n");
            printf("Nome: %s\n", paciente->nome);
            printf("Idade: %d\n", paciente->idade);
            printf("RG: %s\n", paciente->rg);
            encontrado = 1;
        } else {
            inserirPaciente(temp, paciente);
        }
    }
    
    // Mover todos de volta para o heap original
    while(!heapVazio(temp)) {
        Registro* paciente = removerPaciente(temp);
        inserirPaciente(heap, paciente);
    }
    
    if(!encontrado) {
        printf("Paciente não encontrado na fila prioritária!\n");
    }
    
    destruirHeap(temp);
}

void enfileirarPaciente(HeapMaximo* heap, Lista* lista, const char* rg) {
    Elista* atual = lista->inicio;
    
    // Procura o paciente na lista pelo RG
    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }
    
    if(atual == NULL) {
        printf("Paciente não encontrado!\n");
        return;
    }
    
    if(heapCheio(heap)) {
        printf("Fila prioritária cheia! Máximo de 20 pacientes por dia.\n");
        return;
    }
    
    inserirPaciente(heap, atual->dados);
    printf("Paciente enfileirado com sucesso!\n");
}

