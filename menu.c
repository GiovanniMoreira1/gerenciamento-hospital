#include "estruturas.h"
#include "menu.h"
#include "lista.h"
#include "fila.h"
#include "heap.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void confirma() {
    char input[10];
    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("|  Pressione enter para continuar   |\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    limpar_buffer();
    fgets(input, sizeof(input), stdin);
    if(strcmp(input, "\n") == 0 || sizeof(input) >= 0) {
        return;
    } else {
        confirma();
    }
}

void sobre() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("| Nome dos desenvolvedores:                |\n");
    printf("| Artur Chaves Paiva - 22.223.023-7        |\n");
    printf("| Giovanni Antonio Moreira - 22.223.010-4  |\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
    printf("| Curso: Ciência da Computação - 4 Ciclo   |\n");
    printf("| Disciplina: Estrutura de Dados           |\n");
    printf("| Data: ?                                  |\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    confirma();
}

void cadastro(Lista *lista, Contexto *c) {
    Operacao op;
    int opcao = 0;
    while(opcao != 6) {
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
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Registro *registro = malloc(sizeof(Registro));

                printf("Nome do paciente: ");
                scanf("%s", registro->nome);
                limpar_buffer();
                printf("Idade do paciente: ");
                scanf("%d", &registro->idade);
                limpar_buffer();
                printf("RG do paciente: ");
                scanf("%s", registro->rg);
                limpar_buffer();
                registro->entrada = malloc(sizeof(Data));
            
                printf("Data (dd mm aaaa): ");
                scanf("%d %d %d", &registro->entrada->dia, &registro->entrada->mes, &registro->entrada->ano);

                cadastrar_paciente(lista, registro);
                
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
            case 5:
                char rg[9];
                printf("RG do paciente a ser removido: ");
                scanf("%s", rg);
                remover_paciente(lista, rg);
                
                op.tipo = OP_REMOCAO;
                empilhar(c->pilha_operacoes, op);
                limpar_buffer();
                confirma();
                break;
            case 6:
                printf("Voltando...\n");
                break;
        }
    }
}

void atendimento(Fila *fila, Lista *lista) {
    int opcao = 0;
    while(opcao != 4) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|     Atendimento de Pacientes    |    ");
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Adicionar à fila            |\n");
        printf("| 2. Realizar atendimento        |\n");
        printf("| 3. Mostrar fila                |\n");
        printf("| 4. Voltar                      |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                char rg[9];
                Elista *atual = lista->inicio;
                printf("RG do paciente: ");
                scanf("%s", rg);
                while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
                    atual = atual->proximo;
                }
                if(atual == NULL) {
                    printf("Paciente não encontrado!\n");
                } else {
                    enqueue_paciente(fila, atual->dados);
                    printf("Paciente adicionado à fila!\n");
                }
                confirma();
                break;
            }
            case 2:
                dequeue_paciente(fila);
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
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                char rg[9];
                printf("RG do paciente: ");
                scanf("%s", rg);
                enfileirarPaciente(heap, lista, rg);
                confirma();
                break;
            }
            case 2: {
                char rg[9];
                printf("RG do paciente para desenfileirar: ");
                scanf("%s", rg);
                desenfileirarPaciente(heap, rg);
                confirma();
                break;
            }
            case 3: {
                if(heapVazio(heap)) {
                    printf("Não há pacientes na fila prioritária!\n");
                } else {
                    Registro* paciente = removerPaciente(heap);
                    printf("\nAtendendo paciente prioritário:\n");
                    printf("Nome: %s\n", paciente->nome);
                    printf("Idade: %d\n", paciente->idade);
                    printf("RG: %s\n", paciente->rg);
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
    while(opcao != 7) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|     Gerenciador de Atendimento  |    ");
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
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastro(lista, c);
                break;
            case 2:
                atendimento(fila, lista);
                break;
            case 3:
                atendimento_prioritario(heap, lista);
                break;
            case 4:
                printf("Funcionalidade em desenvolvimento...\n");
                confirma();
                break;
            case 5:
                desfazer_ultima_operacao(c);
                confirma();
                break;
            case 6: {
                int subopcao = 0;
                while(subopcao != 3) {
                    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("|     Carregar/Salvar Dados       |    ");
                    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("| 1. Carregar dados               |\n");
                    printf("| 2. Salvar dados                 |\n");
                    printf("| 3. Voltar                       |\n");
                    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                    printf("\nEscolha uma opção: ");
                    scanf("%d", &subopcao);

                    switch(subopcao) {
                        case 1: {
                            char nomeArquivo[100];
                            printf("Nome do arquivo para carregar: ");
                            scanf("%s", nomeArquivo);
                            carregarLista(lista, nomeArquivo);
                            confirma();
                            break;
                        }
                        case 2: {
                            char nomeArquivo[100];
                            printf("Nome do arquivo para salvar: ");
                            scanf("%s", nomeArquivo);
                            salvarLista(lista, nomeArquivo);
                            confirma();
                            break;
                        }
                        case 3:
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
                printf("Saindo...\n");
                destruirHeap(heap);
                break;
        }
    }
} 