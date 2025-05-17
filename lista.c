#include "estruturas.h"
#include "lista.h"

void mostrarLista(Lista *lista) {
    Elista *atual = lista->inicio;
    if(atual == NULL) { 
        printf("\nAinda não há pacientes cadastrados.");
    }
    while(atual != NULL) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Nome: %s \n", atual->dados->nome);
        printf("Idade: %d \n", atual->dados->idade);
        printf("RG: %s \n", atual->dados->rg);
        printf("Data: %d/%d/%d \n", atual->dados->entrada->dia, atual->dados->entrada->mes ,atual->dados->entrada->ano );
        atual = atual->proximo;
    }
    printf("\n");
}

Elista *criar_celula(Registro *registro) {
    Elista *nova = malloc(sizeof(Elista));
    nova->proximo = NULL;
    nova->dados = registro;
    return nova;
}

void cadastrar_paciente(Lista *lista, Registro *registro) {
    Elista *nova = criar_celula(registro);

    if(lista->inicio == NULL) {
        lista->inicio = nova;
        lista->qntd++;
        return;
    }
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && atual->dados->entrada->ano < nova->dados->entrada->ano) {
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior == NULL && atual != NULL) {
        nova->proximo = atual;
        lista->inicio = nova;
        lista->qntd++;
        return;
    } 
    else if(anterior != NULL && atual == NULL) {
        anterior->proximo = nova;
        lista->qntd++;
        return;
    }
    else if(anterior != NULL && atual != NULL) {
        anterior->proximo = nova;
        nova->proximo = atual;
        lista->qntd++;
        return;
    }
}

void consultar_ultimo_paciente(Lista *lista) {
    Elista *atual = lista->inicio;
    if(atual == NULL) {
        printf("\nAinda não há pacientes cadastrados.");
    } else {
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Nome: %s \n", atual->dados->nome);
        printf("Idade: %d \n", atual->dados->idade);
        printf("RG: %s \n", atual->dados->rg);
        printf("Data: %d/%d/%d \n", atual->dados->entrada->dia, atual->dados->entrada->mes ,atual->dados->entrada->ano );
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    }
}

void remover_paciente(Lista *lista) {
    char rg[9];
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    
    if(atual == NULL) {
        printf("\nAinda não há pacientes cadastrados.");
        return;
    }

    printf("RG do paciente a ser removido: ");
    scanf("%s", rg);

    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if(anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual->dados->entrada);
    free(atual->dados);
    printf("Paciente removido com sucesso!");
    lista->qntd--;
}

void atualizar_paciente(Lista *lista) {
    char rg[9];
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;

    if(atual == NULL) {
        printf("\nAinda não há pacientes cadastrados.");
        return;
    }

    printf("RG do paciente a ser removido: ");
    scanf("%s", rg);

    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL) {
        printf("Erro - Paciente não encontrado.\n");
        return;
    } else {
        printf("Atualizando dados do usuário\n");
        printf("Nome do paciente: ");
        scanf("%s", atual->dados->nome);
        limpar_buffer();
        printf("Idade do paciente: ");
        scanf("%d", &atual->dados->idade);
        limpar_buffer();
        printf("RG do paciente: ");
        scanf("%s", atual->dados->rg);
        limpar_buffer();
        printf("\nUsuário atualizado com sucesso!");
    }
} 