#ifndef HEAP_H
#define HEAP_H

#include "estruturas.h"

// Estrutura do Heap Máximo
typedef struct {
    Registro** pacientes;    // Vetor de ponteiros para Registro
    int tamanho;            // Tamanho atual do heap
    int capacidade;         // Capacidade máxima (20 pacientes)
} HeapMaximo;

// Funções principais do Heap
HeapMaximo* criarHeap();                    // Aloca e inicializa o heap
void destruirHeap(HeapMaximo* heap);        // Libera a memória do heap

// Funções de manipulação
int inserirPaciente(HeapMaximo* heap, Registro* paciente);  // Insere paciente no heap
Registro* removerPaciente(HeapMaximo* heap);               // Remove e retorna o paciente com maior prioridade
void enfileirarPaciente(HeapMaximo* heap, Lista* lista, const char* rg);
void desenfileirarPaciente(HeapMaximo* heap, const char* rg); // Desenfileira um paciente pelo RG
int heapVazio(HeapMaximo* heap);                           // Verifica se o heap está vazio
int heapCheio(HeapMaximo* heap);                           // Verifica se o heap está cheio

// Funções auxiliares
void subir(HeapMaximo* heap, int indice);                  // Ajusta o heap para cima
void descer(HeapMaximo* heap, int indice);                 // Ajusta o heap para baixo
void trocar(Registro** a, Registro** b);                   // Troca dois elementos do heap

// Funções de visualização
void imprimirHeap(HeapMaximo* heap);                       // Imprime todos os pacientes no heap
void imprimirProximoAtendimento(HeapMaximo* heap);        // Imprime o próximo paciente a ser atendido



#endif // HEAP_H 