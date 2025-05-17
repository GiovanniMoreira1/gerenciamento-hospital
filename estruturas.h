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

// Funções utilitárias
void limpar_buffer();
void confirma();

#endif 