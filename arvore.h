#ifndef ARVORE_H
#define ARVORE_H

#include "estruturas.h"

// Estrutura do nó da árvore
typedef struct EABB {
    Registro *dados;
    struct EABB *filhoEsq;
    struct EABB *filhoDir;
} EABB;

// Estrutura da árvore
typedef struct {
    EABB *raiz;
    int qtde;
} ABB;

// Funções principais
ABB* criar_abb();
void inserir_abb(ABB *arvore, Registro *paciente);
void liberar_abb(ABB *arvore);

// Funções de ordenação
void mostrar_por_ano(EABB *raiz, int *count);
void mostrar_por_mes(EABB *raiz, int *count);
void mostrar_por_dia(EABB *raiz, int *count);
void mostrar_por_idade(EABB *raiz, int *count);

// Funções para inserir todos os pacientes em árvores temporárias ordenadas
void inserir_todos_ano(EABB* no, ABB* temp);
void inserir_todos_mes(EABB* no, ABB* temp);
void inserir_todos_dia(EABB* no, ABB* temp);
void inserir_todos_idade(EABB* no, ABB* temp);

#endif // ARVORE_H 