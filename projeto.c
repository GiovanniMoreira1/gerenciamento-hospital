#include <stdio.h>
#include <stdlib.h>

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

typedef struct {
    Registro *dados;
    struct Elista *proximo;
} Elista;

typedef struct {
    Elista *inicio;
    int qntd;
} Lista;

typedef struct {
    Registro *dados;
    struct Efila *proximo;
} Efila;

typedef struct {
    Efila *head;
    Efila *tail;
    int qntd;
} Fila;



void cadastro() {
    int opcao = 0;
    while(opcao != 6) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Cadastrar paciente           |\n");
        printf("| 2. Consultar paciente cadastrado|\n");
        printf("| 3. Listar pacientes             |\n");
        printf("| 4. Alterar dados do paciente    |\n");
        printf("| 5. Excluir paciente             |\n");
        printf("| 6. Voltar                       |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
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
    int opc = 0;
    while(opc != 8){
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("| 1. Cadastrar paciente           |\n");
        printf("| 2. Atendimento                  |\n");   
        printf("| 3. Atendimento prioritário      |\n");
        printf("| 4. Pesquisar                    |\n");
        printf("| 5. Desfazer                     |\n");
        printf("| 6. Carregar / Salvar            |\n");
        printf("| 7. Sobre                        |\n");
        printf("| 8. Sair                         |\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opc);

        switch(opc) {
            case 1:
                cadastro();
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