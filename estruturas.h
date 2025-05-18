#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nome[30];
    int idade;
    char rg[9];
    Data *entrada;
} Registro;


typedef enum {
    OP_CADASTRO,
    OP_REMOCAO,
    OP_ENFILEIRAR,
    OP_DESINFILEIRAR
    // adicionar conforme for usar no desfazer
} TipoOperacao;

typedef struct Operacao {
    TipoOperacao tipo;
    Registro registro;  // Cópia do paciente envolvido
} Operacao;

typedef struct E_pilha {
    Operacao operacao;
    struct E_pilha* proximo;
} E_pilha;

typedef struct Pilha {
    E_pilha* topo;
    int tamanho;
} Pilha;

typedef struct Elista {
    Registro *dados;
    struct Elista *proximo;
} Elista;

typedef struct {
    Elista *inicio;
    int qntd;
} Lista;

typedef struct Efila {
    Registro *dados;
    struct Efila *proximo;
} Efila;

typedef struct Fila {
    Efila *head;
    Efila *tail;
    int qntd;
} Fila;

typedef struct {
    Lista* lista_pacientes;
    Fila* fila_pacientes;
    Pilha* pilha_operacoes;
} Contexto;

// Funções utilitárias
void limpar_buffer();
void confirma();

#endif 