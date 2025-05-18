#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Registro* clonar_registro(const Registro* original) {
    Registro* novo = malloc(sizeof(Registro));
    strcpy(novo->nome, original->nome);
    strcpy(novo->rg, original->rg);
    novo->idade = original->idade;

    novo->entrada = malloc(sizeof(Data));
    *(novo->entrada) = *(original->entrada); // cópia da data

    return novo;
}

Pilha* criar_pilha() {
    Pilha* p = malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void empilhar(Pilha* pilha, Operacao op) {
    E_pilha* nova = malloc(sizeof(E_pilha));
    nova->operacao = op;
    nova->proximo = pilha->topo;
    pilha->topo = nova;
    pilha->tamanho++;
}

int esta_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

Operacao desempilhar(Pilha* pilha) {
    Operacao op_vazia = {0};  // Retorna uma operação "vazia" se necessário
    if (esta_vazia(pilha)) return op_vazia;

    E_pilha* temp = pilha->topo;
    Operacao op = temp->operacao;

    pilha->topo = temp->proximo;
    free(temp);
    pilha->tamanho--;
    return op;
}

void desfazer_ultima_operacao(Contexto *c) {
    Pilha* pilha = c->pilha_operacoes;
    Lista* lista = c->lista_pacientes;
    Fila* fila = c->fila_pacientes;

    if (esta_vazia(pilha)) {
        printf("Nenhuma operação para desfazer.\n");
        return;
    }

    Operacao op = desempilhar(pilha);

    printf("Deseja desfazer a operação? (S/N): ");
    char resposta;
    scanf(" %c", &resposta);
    limpar_buffer();

    if (resposta != 'S' && resposta != 's') {
        printf("Operação cancelada.\n");
        return;
    }

    switch (op.tipo) {
        case OP_CADASTRO:
            printf("Desfazendo cadastro de %s\n", op.registro.nome);
            remover_paciente(lista, op.registro.rg);
            break;

        case OP_REMOCAO:
            printf("Desfazendo remoção de %s\n", op.registro.nome);
            Registro* copia = clonar_registro(&op.registro);
            cadastrar_paciente(lista, copia);
            break;

        case OP_ENFILEIRAR:
            printf("Desfazendo enfileiramento de %s\n", op.registro.nome);
            
            printf("Operação não pode ser totalmente desfeita (limite de fila).\n");
            break;
    }
}