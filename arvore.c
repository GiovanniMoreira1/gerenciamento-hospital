#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Cria e inicializa uma nova árvore binária de busca (ABB)
// Retorna um ponteiro para a ABB criada
ABB* criar_abb() {
    // Aloca memória para a estrutura da árvore
    ABB *arvore = (ABB*)malloc(sizeof(ABB));
    // Inicializa a raiz como NULL (árvore vazia)
    arvore->raiz = NULL;
    // Inicializa a quantidade de nós como 0
    arvore->qtde = 0;
    // Retorna o ponteiro para a árvore criada
    return arvore;
}

// Cria um novo nó (EABB) para a árvore, armazenando o ponteiro para o paciente
// Retorna o ponteiro para o nó criado
EABB* criar_no(Registro *paciente) {
    // Aloca memória para o novo nó
    EABB *novo = (EABB*)malloc(sizeof(EABB));
    // Associa o registro do paciente ao nó
    novo->dados = paciente;
    // Inicializa os ponteiros dos filhos como NULL
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;
    // Retorna o ponteiro para o novo nó
    return novo;
}

// Insere um paciente já cadastrado na árvore, sem ordenação (sempre à esquerda)
// Isso permite que a árvore seja reordenada depois conforme o filtro desejado
void inserir_abb(ABB *arvore, Registro *paciente) {
    // Cria um novo nó para o paciente
    EABB *novo = criar_no(paciente);
    // Se a árvore está vazia, o novo nó vira a raiz
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        // Caso contrário, percorre sempre para a esquerda até encontrar o último nó
        EABB *atual = arvore->raiz;
        while (atual->filhoEsq != NULL) {
            atual = atual->filhoEsq;
        }
        // Insere o novo nó como filho esquerdo do último nó
        atual->filhoEsq = novo;
    }
    // Incrementa a quantidade de nós na árvore
    arvore->qtde++;
}

// Libera recursivamente todos os nós da árvore (EABB)
// Não libera os registros dos pacientes, apenas os nós da árvore
void liberar_eabb(EABB *no) {
    // Caso base: nó nulo, retorna
    if (no == NULL) return;
    // Libera recursivamente o filho esquerdo
    liberar_eabb(no->filhoEsq);
    // Libera recursivamente o filho direito
    liberar_eabb(no->filhoDir);
    // Libera o nó atual
    free(no);
}

// Libera toda a árvore ABB, incluindo todos os nós
void liberar_abb(ABB *arvore) {
    // Se a árvore é nula, não faz nada
    if (arvore == NULL) return;
    // Libera todos os nós a partir da raiz
    liberar_eabb(arvore->raiz);
    // Libera a estrutura da árvore
    free(arvore);
}

// ===================== Funções auxiliares para reordenação e exibição =====================
// Cada uma monta uma árvore temporária ordenada pelo critério desejado

// Insere um paciente na árvore ordenando por ANO de registro
// Utiliza recursão para posicionar o nó conforme o valor do ano
static void inserir_ordenado_ano(EABB **raiz, Registro *paciente) {
    // Se a posição está vazia, insere o novo nó aqui
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } 
    // Se o ano do paciente é menor que o do nó atual, vai para a esquerda
    else if (paciente->entrada->ano < (*raiz)->dados->entrada->ano) {
        inserir_ordenado_ano(&((*raiz)->filhoEsq), paciente);
    } 
    // Caso contrário, vai para a direita
    else {
        inserir_ordenado_ano(&((*raiz)->filhoDir), paciente);
    }
}

// Percorre e exibe a árvore ordenada por ANO de registro (em ordem crescente)
// Utiliza percurso em ordem (in-order)
void mostrar_por_ano(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_ano(raiz->filhoEsq, count);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    mostrar_por_ano(raiz->filhoDir, count);
}

// Insere um paciente na árvore ordenando por MÊS de registro
// Utiliza recursão para posicionar o nó conforme o valor do mês
static void inserir_ordenado_mes(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } else if (paciente->entrada->mes < (*raiz)->dados->entrada->mes) {
        inserir_ordenado_mes(&((*raiz)->filhoEsq), paciente);
    } else {
        inserir_ordenado_mes(&((*raiz)->filhoDir), paciente);
    }
}

// Percorre e exibe a árvore ordenada por MÊS de registro (em ordem crescente)
void mostrar_por_mes(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_mes(raiz->filhoEsq, count);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    mostrar_por_mes(raiz->filhoDir, count);
}

// Insere um paciente na árvore ordenando por DIA de registro
// Utiliza recursão para posicionar o nó conforme o valor do dia
static void inserir_ordenado_dia(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } else if (paciente->entrada->dia < (*raiz)->dados->entrada->dia) {
        inserir_ordenado_dia(&((*raiz)->filhoEsq), paciente);
    } else {
        inserir_ordenado_dia(&((*raiz)->filhoDir), paciente);
    }
}

// Percorre e exibe a árvore ordenada por DIA de registro (em ordem crescente)
void mostrar_por_dia(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_dia(raiz->filhoEsq, count);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    mostrar_por_dia(raiz->filhoDir, count);
}

// Insere um paciente na árvore ordenando por IDADE do paciente
// Utiliza recursão para posicionar o nó conforme o valor da idade
static void inserir_ordenado_idade(EABB **raiz, Registro *paciente) {
    if (*raiz == NULL) {
        *raiz = criar_no(paciente);
    } else if (paciente->idade < (*raiz)->dados->idade) {
        inserir_ordenado_idade(&((*raiz)->filhoEsq), paciente);
    } else {
        inserir_ordenado_idade(&((*raiz)->filhoDir), paciente);
    }
}

// Percorre e exibe a árvore ordenada por IDADE do paciente (em ordem crescente)
void mostrar_por_idade(EABB *raiz, int *count) {
    if (raiz == NULL) return;
    mostrar_por_idade(raiz->filhoEsq, count);
    printf("%2d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d\n",
           (*count)++,
           raiz->dados->nome,
           raiz->dados->idade,
           raiz->dados->rg,
           raiz->dados->entrada->dia,
           raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    mostrar_por_idade(raiz->filhoDir, count);
}

// Funções para inserir todos os pacientes em árvores temporárias ordenadas
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