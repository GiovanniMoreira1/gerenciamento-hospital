#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "estruturas.h"

ABB* criar_abb() {
    ABB *arvore = (ABB*)malloc(sizeof(ABB));
    arvore->raiz = NULL;
    arvore->qtde = 0;

    return arvore;
}

EABB* criar_no(Registro *paciente) {
    EABB *novo = (EABB*)malloc(sizeof(EABB));
    novo->dados = paciente;
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;

    return novo;
}

void inserir_abb(ABB *arvore, Registro *paciente) {
    EABB *novo = criar_no(paciente);
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        EABB *atual = arvore->raiz;
        while (atual->filhoEsq != NULL) {
            atual = atual->filhoEsq;
        }
        atual->filhoEsq = novo;
    }
    arvore->qtde++;
}

void liberar_eabb(EABB *no) {
    if (no == NULL) return;
    liberar_eabb(no->filhoEsq);
    liberar_eabb(no->filhoDir);

    free(no);
}

void liberar_abb(ABB *arvore) {
    if (arvore == NULL) return;
    liberar_eabb(arvore->raiz);

    free(arvore);
}


static void inserir_ordenado_ano(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } 
    else if (paciente->entrada->ano < (*raiz)->dados->entrada->ano) {
        inserir_ordenado_ano(&((*raiz)->filhoEsq), paciente);
    } 
    else {
        inserir_ordenado_ano(&((*raiz)->filhoDir), paciente);
    }
}

void mostrar_por_ano(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_ano(raiz->filhoEsq, count);
    printf(LIGHT_BLUE);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    printf(RESET);
    mostrar_por_ano(raiz->filhoDir, count);
}

static void inserir_ordenado_mes(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } else if (paciente->entrada->mes < (*raiz)->dados->entrada->mes) {
        inserir_ordenado_mes(&((*raiz)->filhoEsq), paciente);
    } else {
        inserir_ordenado_mes(&((*raiz)->filhoDir), paciente);
    }
}

void mostrar_por_mes(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_mes(raiz->filhoEsq, count);
    printf(LIGHT_BLUE);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    printf(RESET);
    mostrar_por_mes(raiz->filhoDir, count);
}

static void inserir_ordenado_dia(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } else if (paciente->entrada->dia < (*raiz)->dados->entrada->dia) {
        inserir_ordenado_dia(&((*raiz)->filhoEsq), paciente);
    } else {
        inserir_ordenado_dia(&((*raiz)->filhoDir), paciente);
    }
}

void mostrar_por_dia(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_dia(raiz->filhoEsq, count);
    printf(LIGHT_BLUE);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    printf(RESET);
    mostrar_por_dia(raiz->filhoDir, count);
}

static void inserir_ordenado_idade(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } else if (paciente->idade < (*raiz)->dados->idade) {
        inserir_ordenado_idade(&((*raiz)->filhoEsq), paciente);
    } else {
        inserir_ordenado_idade(&((*raiz)->filhoDir), paciente);
    }
}

void mostrar_por_idade(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_idade(raiz->filhoEsq, count);
    printf(LIGHT_BLUE);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    printf(RESET);
    mostrar_por_idade(raiz->filhoDir, count);
}

void inserir_todos_ano(EABB* no, ABB* temp) {
    if (no == NULL) return;
    inserir_ordenado_ano(&temp->raiz, no->dados);
    inserir_todos_ano(no->filhoEsq, temp);
    inserir_todos_ano(no->filhoDir, temp);
}
void inserir_todos_mes(EABB* no, ABB* temp) {
    if (no == NULL) return;
    inserir_ordenado_mes(&temp->raiz, no->dados);
    inserir_todos_mes(no->filhoEsq, temp);
    inserir_todos_mes(no->filhoDir, temp);
}
void inserir_todos_dia(EABB* no, ABB* temp) {
    if (no == NULL) return;
    inserir_ordenado_dia(&temp->raiz, no->dados);
    inserir_todos_dia(no->filhoEsq, temp);
    inserir_todos_dia(no->filhoDir, temp);
}
void inserir_todos_idade(EABB* no, ABB* temp) {
    if (no == NULL) return;
    inserir_ordenado_idade(&temp->raiz, no->dados);
    inserir_todos_idade(no->filhoEsq, temp);
    inserir_todos_idade(no->filhoDir, temp);
} 