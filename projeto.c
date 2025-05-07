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
    } Elista; // celula LDE

    typedef struct {
        Elista *inicio;
        int qntd;
    } Lista; // LDE

    typedef struct {
        Registro *dados;
        struct Efila *proximoimo;
    } Efila;

    typedef struct {
        Efila *head;
        Efila *tail;
        int qntd;
    } Fila;

    void limpar_buffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    void mostrarLista(Lista *lista) {
        Elista *atual = lista->inicio;
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
        Elista *nova = malloc(sizeof(Elista)); // aloca na memória o tamanho de Celula
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

        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("Nome: %s \n", atual->dados->nome);
        printf("Idade: %d \n", atual->dados->idade);
        printf("RG: %s \n", atual->dados->rg);
        printf("Data: %d/%d/%d \n", atual->dados->entrada->dia,     atual->dados->entrada->mes ,atual->dados->entrada->ano );
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    }

    void remover_paciente(Lista *lista, char rg[9]) {
        Elista *anterior = NULL;
        Elista *atual = lista->inicio;

        while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
            anterior = atual;
            atual = atual->proximo;
        }
        if(atual == NULL) {
            return;
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

    void atualizar_paciente(Lista *lista, char rg[9]) {
        Elista *anterior = NULL;
        Elista *atual = lista->inicio;

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

    void cadastro(Lista *lista) {
        char rg[9];
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
                    break;
                }   
                case 2:
                    consultar_ultimo_paciente(lista);
                    break;
                case 3:
                    mostrarLista(lista);
                    break;
                case 4:
                    printf("RG do paciente que deseja alterar: ");
                    scanf("%s", rg);
                    atualizar_paciente(lista, rg);
                    break;
                case 5:
                    printf("RG do paciente a ser removido: ");
                    scanf("%s", rg);
                    remover_paciente(lista, rg);
                    break;
                case 6:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        }
    }


    void atendimento() {
        int opc = 0;
        while(opc != 4) {
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("| 1. Enfileirar paciente            |\n");
            printf("| 2. Desenfileirar paciente         |\n");
            printf("| 3. Mostrar fila                   |\n");
            printf("| 4. Voltar                         |\n");
            printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("\nEscolha uma opção: ");
            scanf("%d", &opc);

            switch(opc) {
                case 1:
                    
                    break;
                case 2:
                    
                    break;
                case 3:
                    
                    break;
                case 4:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
            }
        }
    }

    void atendimento_prioritario() {

    }

    void pesquisa() {

    }

    void desfazer() {

    }

    void carregar_salvar() {

    }

    void sobre() {
        printf("teste");
    }

    void menu() {
        Lista *lista = malloc(sizeof(Lista));
        lista->inicio = NULL;
        lista->qntd = 0;
        
        int opc = 0;
        while(opc != 8){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("|  Gerenciador de Sistema de Saúde  |");
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("| 1. Cadastrar paciente             |\n");
            printf("| 2. Atendimento                    |\n");   
            printf("| 3. Atendimento prioritário        |\n");
            printf("| 4. Pesquisar                      |\n");
            printf("| 5. Desfazer                       |\n");
            printf("| 6. Carregar / Salvar              |\n");
            printf("| 7. Sobre                          |\n");
            printf("| 8. Sair                           |\n");
            printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("\nEscolha uma opção: ");
            scanf("%d", &opc);

            switch(opc) {
                case 1:
                    cadastro(lista);
                    break;
                case 2:
                    atendimento();
                    break;
                case 3:
                    atendimento_prioritario();
                    break;
                case 4:
                    pesquisa();
                    break;
                case 5:
                    desfazer();
                    break;
                case 6:
                    carregar_salvar();
                    break;
                case 7:
                    sobre();
                    break;
                case 8:
                    printf("Saindo...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
            }
        }
    }

    int main() {
        menu();
        return 0;
    }