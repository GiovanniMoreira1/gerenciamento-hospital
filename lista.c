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

void salvarLista(Lista* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    Elista* atual = lista->inicio;
    while (atual != NULL) {
        // Escreve os dados do paciente no arquivo
        fprintf(arquivo, "%s %d %s %d %d %d\n",
                atual->dados->nome,
                atual->dados->idade,
                atual->dados->rg,
                atual->dados->entrada->dia,
                atual->dados->entrada->mes,
                atual->dados->entrada->ano);
        
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Lista salva com sucesso no arquivo %s!\n", nomeArquivo);
}

void carregarLista(Lista* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    // Limpa a lista atual
    while (lista->inicio != NULL) {
        Elista* temp = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
    }
    lista->qntd = 0;

    char nome[50];
    int idade;
    char rg[9];
    int dia, mes, ano;

    // Lê os dados do arquivo e insere na lista
    while (fscanf(arquivo, "%s %d %s %d %d %d",
                  nome, &idade, rg, &dia, &mes, &ano) == 6) {
        
        Registro* novoRegistro = malloc(sizeof(Registro));
        novoRegistro->entrada = malloc(sizeof(Data));
        
        strcpy(novoRegistro->nome, nome);
        novoRegistro->idade = idade;
        strcpy(novoRegistro->rg, rg);
        novoRegistro->entrada->dia = dia;
        novoRegistro->entrada->mes = mes;
        novoRegistro->entrada->ano = ano;

        cadastrar_paciente(lista, novoRegistro);
    }

    fclose(arquivo);
    printf("Lista carregada com sucesso do arquivo %s!\n", nomeArquivo);
} 