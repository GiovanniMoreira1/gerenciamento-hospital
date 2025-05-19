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
    char resposta;
    Pilha* pilha = c->pilha_operacoes;
    Lista* lista = c->lista_pacientes;
    Fila* fila = c->fila_pacientes;


    if (esta_vazia(pilha)) {
        printf(RED);
        printf("\nNenhuma operação para desfazer.\n");
        return;
    }

    Operacao op = desempilhar(pilha);

    printf(LIGHT_BLUE);
    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("| Última operação: %s\n", 
           op.tipo == OP_CADASTRO ? "Cadastro" :
           op.tipo == OP_REMOCAO ? "Remoção" :
           op.tipo == OP_ENFILEIRAR ? "Enfileirar" : "Desinfileirar");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Deseja desfazer a operação? (S/N): ");

    limpar_buffer();
    printf(RESET);
    scanf("%c", &resposta);

    if (resposta != 'S' && resposta != 's') {
        printf(RED);
        printf("Operação cancelada.\n");
        return;
    }

    switch (op.tipo) {
        case OP_CADASTRO:
            printf(GREEN);
            printf("Desfazendo cadastro de %s\n", op.registro.nome);
            remover_paciente(lista, op.registro.rg);
            printf(RESET);
            break;

        case OP_REMOCAO:
            printf(GREEN);
            printf("Desfazendo remoção de %s\n", op.registro.nome);
            Registro* copia = clonar_registro(&op.registro);
            cadastrar_paciente(lista, copia);
            printf(RESET);
            break;

        case OP_ENFILEIRAR:
            printf(GREEN);
            printf("Desfazendo enfileiramento de %s\n", op.registro.nome);
            desfazer_enqueue(fila);
            printf(RESET);
            break;
        case OP_DESENFILEIRAR:
            printf(GREEN);
            printf("Desfazendo desinfileiramento de %s\n", op.registro.nome);
            Registro* clone = clonar_registro(&op.registro);
            desfazer_dequeue(fila, clone);
            printf(RESET);
            break;
    }
}