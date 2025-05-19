#include "estruturas.h"
#include "menu.h"
#include "lista.h"
#include "fila.h"
#include "heap.h"
#include "arvore.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void print_color(const char* texto, const char* cor) {
    printf("%s%s", cor, texto);
}

void confirma() {
    char input[10];
    printf(LIGHT_BLUE);
    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("|  Pressione enter para continuar   |\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(RESET);
    limpar_buffer();
    fgets(input, sizeof(input), stdin);
}

void sobre() {
    printf(LIGHT_BLUE);
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("| Nome dos desenvolvedores:                |\n");
    printf("| Artur Chaves Paiva - 22.223.023-7        |\n");
    printf("| Giovanni Antonio Moreira - 22.223.010-4  |\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
    printf("| Curso: Ciência da Computação - 4 Ciclo   |\n");
    printf("| Disciplina: Estrutura de Dados           |\n");
    printf("| Data: ?                                  |\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf(RESET);
    confirma();
}

void cadastro(Lista *lista, Contexto *c) {
    Operacao op;
    int opcao = 0;
    while(opcao != 6) {
        printf(LIGHT_BLUE);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|     Cadastro de Pacientes       |    ");
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Cadastrar paciente           |\n");
        printf("| 2. Consultar último paciente    |\n");
        printf("| 3. Listar pacientes             |\n");
        printf("| 4. Alterar dados do paciente    |\n");
        printf("| 5. Excluir paciente             |\n");
        printf("| 6. Voltar                       |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        printf(RESET);
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Registro *registro = malloc(sizeof(Registro));
                printf(LIGHT_BLUE);
                printf("Nome do paciente: ");
                printf(RESET);
                scanf("%s", registro->nome);
                limpar_buffer();
                printf(LIGHT_BLUE);
                printf("Idade do paciente: ");
                printf(RESET);
                scanf("%d", &registro->idade);
                limpar_buffer();
                printf(LIGHT_BLUE);
                printf("RG do paciente: ");
                printf(RESET);
                scanf("%s", registro->rg);
                limpar_buffer();
                registro->entrada = malloc(sizeof(Data));
            
                printf(LIGHT_BLUE);
                printf("Data (dd mm aaaa): ");
                printf(RESET);
                scanf("%d %d %d", &registro->entrada->dia, &registro->entrada->mes, &registro->entrada->ano);

                cadastrar_paciente(lista, registro);
                printf(GREEN);
                printf("\nPaciente %s cadastrado com sucesso!", registro->nome);
                
                op.tipo = OP_CADASTRO;
                op.registro = *registro; 

                op.registro.entrada = malloc(sizeof(Data));
                *(op.registro.entrada) = *(registro->entrada);

                empilhar(c->pilha_operacoes, op);
                confirma();
                break;
            }   
            case 2:
                consultar_ultimo_paciente(lista);
                confirma();
                break;
            case 3:
                mostrarLista(lista);
                confirma();
                break;
            case 4:
                atualizar_paciente(lista);
                confirma();
                break;
            case 5: {
                if(lista->inicio == NULL) {
                    printf(RED);
                    printf("\nAinda não há pacientes cadastrados.");
                    break;
                }
                char rg[9];
                printf(LIGHT_BLUE);
                printf("RG do paciente a ser removido: ");
                printf(RESET);
                scanf("%s", rg);
                
                op.tipo = OP_REMOCAO;
                empilhar(c->pilha_operacoes, op);
                remover_paciente(lista, rg);
                limpar_buffer();
                confirma();
                break;
            }
            case 6:
                printf(LIGHT_BLUE);
                printf("Voltando...\n");
                printf(RESET);
                break;
        }
    }
}

void atendimento(Fila *fila, Lista *lista, Contexto *c) {
    int opcao = 0;
    Operacao op;
    while(opcao != 4) {
        printf(LIGHT_BLUE);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|     Atendimento de Pacientes   |    ");
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Adicionar à fila            |\n");
        printf("| 2. Realizar atendimento        |\n");
        printf("| 3. Mostrar fila                |\n");
        printf("| 4. Voltar                      |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        printf(RESET);
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                char rg[9];
                Elista *atual = lista->inicio;
                printf(LIGHT_BLUE);
                printf("RG do paciente: ");
                printf(RESET);
                scanf("%s", rg);
                while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
                    atual = atual->proximo;
                }
                if(atual == NULL) {
                    printf(RED);
                    printf("\nERRO - Paciente não encontrado!");
                    printf(RESET);
                } else {
                    op.tipo = OP_ENFILEIRAR;
                    op.registro = *atual->dados;
                    empilhar(c->pilha_operacoes, op);
                    enqueue_paciente(fila, atual->dados);
                    printf(GREEN);
                    printf("\nPaciente adicionado à fila!");
                    printf(RESET);
                }
                confirma();
                break;
            }
            case 2:
                op.tipo = OP_DESENFILEIRAR;
                op.registro = *fila->head->dados;
                empilhar(c->pilha_operacoes, op);
                dequeue_paciente(fila);
                printf(GREEN);
                printf("\nPaciente %s desenfileirado!\n", fila->head->dados->nome);
                printf(RESET);
                confirma();
                break;
            case 3:
                mostrar_queue(fila);
                confirma();
                break;
            case 4:
                printf("Voltando...\n");
                break;
        }
    }
}

void atendimento_prioritario(HeapMaximo* heap, Lista* lista) {
    int opcao = 0;
    while(opcao != 6) {
        printf(LIGHT_BLUE);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|   Atendimento Prioritário       |    ");
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Enfileirar paciente          |\n");
        printf("| 2. Desenfileirar paciente       |\n");
        printf("| 3. Realizar atendimento         |\n");
        printf("| 4. Mostrar fila prioritária     |\n");
        printf("| 5. Próximo atendimento          |\n");
        printf("| 6. Voltar                       |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        printf(RESET);
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                char rg[9];
                printf(LIGHT_BLUE);
                printf("RG do paciente: ");
                printf(RESET);
                scanf("%s", rg);
                enfileirarPaciente(heap, lista, rg);
                confirma();
                break;
            }
            case 2: {
                char rg[9];
                printf(LIGHT_BLUE);
                printf("RG do paciente para desenfileirar: ");
                printf(RESET);
                scanf("%s", rg);
                desenfileirarPaciente(heap, rg);
                confirma();
                break;
            }
            case 3: {
                if(heapVazio(heap)) {
                    printf(RED);
                    printf("Não há pacientes na fila prioritária!\n");
                } else {
                    Registro* paciente = removerPaciente(heap);
                    printf(LIGHT_BLUE);
                    printf("\nAtendendo paciente prioritário:\n");
                    printf("Nome: %s\n", paciente->nome);
                    printf("Idade: %d\n", paciente->idade);
                    printf("RG: %s\n", paciente->rg);
                    printf(RESET);
                }
                confirma();
                break;
            }
            case 4:
                imprimirHeap(heap);
                confirma();
                break;
            case 5:
                imprimirProximoAtendimento(heap);
                confirma();
                break;
            case 6:
                printf("Voltando...\n");
                break;
        }
    }
}

// função auxiliar para buscar paciente na lista pelo RG
static Registro* buscar_paciente_na_lista(Lista* lista, const char* rg) {
    Elista* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados->rg, rg) == 0) {
            return atual->dados;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void menu_busca(Lista* lista) {
    static ABB* arvore = NULL;
    if (arvore == NULL) {
        arvore = criar_abb();
    }
    int opcao = 0;
    while (opcao != 6) {
        printf(LIGHT_BLUE);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|         Menu de Pesquisa         |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Inserir paciente na árvore   |\n");
        printf("| 2. Mostrar por ano de registro  |\n");
        printf("| 3. Mostrar por mês de registro  |\n");
        printf("| 4. Mostrar por dia de registro  |\n");
        printf("| 5. Mostrar por idade            |\n");
        printf("| 6. Voltar                       |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        printf(RESET);
        scanf("%d", &opcao);
        limpar_buffer();
        switch(opcao) {
            case 1: {
                char rg[9];
                printf(LIGHT_BLUE);
                printf("RG do paciente para inserir na árvore: ");
                printf(RESET);
                scanf("%s", rg);
                limpar_buffer();
                Elista *atual = lista->inicio;
                while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
                    atual = atual->proximo;
                }
                if (atual != NULL) {
                    inserir_abb(arvore, atual->dados);
                    printf(GREEN);
                    printf("Paciente inserido na árvore de busca!\n");
                } else {
                    printf(RED);
                    printf("Paciente não encontrado!\n");
                }
                printf(RESET);
                limpar_buffer();
                confirma();
                break;
            }
            case 2: {
                if (arvore->raiz == NULL) {
                    printf(RED);
                    printf("Árvore vazia!\n");
                } else {
                    ABB* temp = criar_abb();
                    inserir_todos_ano(arvore->raiz, temp);
                    int count = 1;
                    printf(LIGHT_BLUE);
                    printf("\n--- Pacientes ordenados por ANO de registro ---\n");
                    mostrar_por_ano(temp->raiz, &count);
                    liberar_abb(temp);
                }
                limpar_buffer();
                confirma();
                break;
            }
            case 3: {
                if (arvore->raiz == NULL) {
                    printf(RED);
                    printf("Árvore vazia!\n");
                } else {
                    ABB* temp = criar_abb();
                    inserir_todos_mes(arvore->raiz, temp);
                    int count = 1;
                    printf(LIGHT_BLUE);
                    printf("\n--- Pacientes ordenados por MÊS de registro ---\n");
                    mostrar_por_mes(temp->raiz, &count);
                    liberar_abb(temp);
                }
                limpar_buffer();
                confirma();
                break;
            }
            case 4: {
                if (arvore->raiz == NULL) {
                    printf(RED);
                    printf("Árvore vazia!\n");
                } else {
                    ABB* temp = criar_abb();
                    inserir_todos_dia(arvore->raiz, temp);
                    int count = 1;
                    printf(LIGHT_BLUE);
                    printf("\n--- Pacientes ordenados por DIA de registro ---\n");
                    mostrar_por_dia(temp->raiz, &count);
                    liberar_abb(temp);
                }
                limpar_buffer();
                confirma();
                break;
            }
            case 5: {
                if (arvore->raiz == NULL) {
                    printf(RED);
                    printf("Árvore vazia!\n");
                } else {
                    ABB* temp = criar_abb();
                    inserir_todos_idade(arvore->raiz, temp);
                    int count = 1;
                    printf(LIGHT_BLUE);
                    printf("\n--- Pacientes ordenados por IDADE ---\n");
                    mostrar_por_idade(temp->raiz, &count);
                    liberar_abb(temp);
                }
                limpar_buffer();
                confirma();
                break;
            }
            case 6:
                printf("Voltando...\n");
                break;
        }
    }
}

void menu() {
    Lista* lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qntd = 0;

    Fila* fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qntd = 0;

    HeapMaximo* heap = criarHeap();

    Contexto* c = malloc(sizeof(Contexto));
    c->lista_pacientes = lista;
    c->fila_pacientes = fila;
    c->pilha_operacoes = criar_pilha();

    int opcao = 0;
    while(opcao != 8) {
        printf(LIGHT_BLUE);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|   Gerenciador de Atendimento   |    ");
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Cadastro de Pacientes       |\n");
        printf("| 2. Atendimento                 |\n");
        printf("| 3. Atendimento Prioritário     |\n");
        printf("| 4. Pesquisa                    |\n");
        printf("| 5. Desfazer                    |\n");
        printf("| 6. Carregar/Salvar             |\n");
        printf("| 7. Sobre                       |\n");
        printf("| 8. Sair                        |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        printf(RESET);
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastro(lista, c);
                break;
            case 2:
                atendimento(fila, lista, c);
                break;
            case 3:
                atendimento_prioritario(heap, lista);
                break;
            case 4:
                menu_busca(lista);
                break;
            case 5:
                desfazer_ultima_operacao(c);
                confirma();
                break;
            case 6: {
                int subopcao = 0;
                while(subopcao != 3) {
                    printf(LIGHT_BLUE);
                    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("|     Carregar/Salvar Dados       |    ");
                    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("| 1. Carregar dados               |\n");
                    printf("| 2. Salvar dados                 |\n");
                    printf("| 3. Voltar                       |\n");
                    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("\nEscolha uma opção: ");
                    printf(RESET);
                    scanf("%d", &subopcao);

                    switch(subopcao) {
                        case 1: {
                            char nomeArquivo[100];
                            printf(LIGHT_BLUE);
                            printf("Nome do arquivo para carregar: ");
                            printf(RESET);
                            scanf("%s", nomeArquivo);
                            carregarLista(lista, nomeArquivo);
                            confirma();
                            break;
                        }
                        case 2: {
                            char nomeArquivo[100];
                            printf(LIGHT_BLUE);
                            printf("Nome do arquivo para salvar: ");
                            printf(RESET);
                            scanf("%s", nomeArquivo);
                            salvarLista(lista, nomeArquivo);
                            confirma();
                            break;
                        }
                        case 3:
                            printf(LIGHT_BLUE);
                            printf("Voltando...\n");
                            break;
                    }
                }
                break;
            }
            case 7:
                sobre();
                break;
            case 8:
                printf(LIGHT_BLUE);
                printf("Saindo...\n");
                destruirHeap(heap);
                break;
        }
    }
} 