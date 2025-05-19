# Lista Encadeada de Pacientes

## Estrutura
- **Lista**: Estrutura principal que armazena ponteiro para o início da lista e quantidade de elementos.
- **Elista**: Nó da lista, armazena ponteiro para Registro e para o próximo nó.

## Funções Detalhadas

### void mostrarLista(Lista *lista)
Exibe todos os pacientes cadastrados na lista.
- **Parâmetro:** lista
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Elista *atual = lista->inicio;`
   - Inicializa ponteiro para o início da lista.
2. `if(atual == NULL) { ... }`
   - Verifica se a lista está vazia.
3. `printf("\nAinda não há pacientes cadastrados.");`
   - Se vazia, exibe mensagem informativa.
4. `while(atual != NULL) { ... }`
   - Percorre a lista até o final.
5. `printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
   - Imprime separador visual.
6. `printf("Nome: %s \n", atual->dados->nome);`
   - Imprime o nome do paciente.
7. `printf("Idade: %d \n", atual->dados->idade);`
   - Imprime a idade.
8. `printf("RG: %s \n", atual->dados->rg);`
   - Imprime o RG.
9. `printf("Data: %d/%d/%d \n", atual->dados->entrada->dia, atual->dados->entrada->mes ,atual->dados->entrada->ano );`
   - Imprime a data de entrada.
10. `atual = atual->proximo;`
    - Avança para o próximo nó.
11. `printf("\n");`
    - Imprime linha em branco ao final.

### Elista *criar_celula(Registro *registro)
Cria um novo nó para a lista.
- **Parâmetro:** registro
- **Retorno:** ponteiro para novo nó

#### Funcionamento linha a linha:
1. `Elista *nova = malloc(sizeof(Elista));`
   - Aloca memória para o novo nó.
2. `nova->proximo = NULL;`
   - Inicializa o ponteiro para próximo como NULL.
3. `nova->dados = registro;`
   - Associa o registro ao nó.
4. `return nova;`
   - Retorna o ponteiro para o novo nó.

### void cadastrar_paciente(Lista *lista, Registro *registro)
Insere um novo paciente na lista, mantendo ordenação por ano.
- **Parâmetros:**
  - lista: ponteiro para a lista
  - registro: ponteiro para o registro do paciente
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Elista *nova = criar_celula(registro);`
   - Cria novo nó para o paciente.
2. `if(lista->inicio == NULL) { ... }`
   - Verifica se a lista está vazia.
3. `lista->inicio = nova;`
   - Se vazia, insere como primeiro elemento.
4. `lista->qntd++;`
   - Incrementa o contador de pacientes.
5. `return;`
   - Retorna após inserir no início.
6. `Elista *anterior = NULL;`
   - Inicializa ponteiro para nó anterior.
7. `Elista *atual = lista->inicio;`
   - Inicializa ponteiro para nó atual.
8. `while(atual != NULL && atual->dados->entrada->ano < nova->dados->entrada->ano) { ... }`
   - Percorre a lista até encontrar posição correta (ordenada por ano).
9. `anterior = atual;`
   - Atualiza ponteiro para nó anterior.
10. `atual = atual->proximo;`
    - Avança para próximo nó.
11. `if(anterior == NULL && atual != NULL) { ... }`
    - Se deve inserir no início.
12. `nova->proximo = atual;`
    - Novo nó aponta para o atual.
13. `lista->inicio = nova;`
    - Novo nó vira o início da lista.
14. `else if(anterior != NULL && atual == NULL) { ... }`
    - Se deve inserir no final.
15. `anterior->proximo = nova;`
    - Último nó aponta para o novo.
16. `else if(anterior != NULL && atual != NULL) { ... }`
    - Se deve inserir no meio.
17. `anterior->proximo = nova;`
    - Nó anterior aponta para o novo.
18. `nova->proximo = atual;`
    - Novo nó aponta para o atual.
19. `lista->qntd++;`
    - Incrementa o contador de pacientes.

### void consultar_ultimo_paciente(Lista *lista)
Exibe os dados do primeiro paciente da lista.
- **Parâmetro:** lista
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Elista *atual = lista->inicio;`
   - Inicializa ponteiro para o início da lista.
2. `if(atual == NULL) { ... }`
   - Verifica se a lista está vazia.
3. `printf("\nAinda não há pacientes cadastrados.");`
   - Se vazia, exibe mensagem.
4. `else { ... }`
   - Se há pacientes:
5. `printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
   - Imprime separador visual.
6. `printf("Nome: %s \n", atual->dados->nome);`
   - Imprime o nome do paciente.
7. `printf("Idade: %d \n", atual->dados->idade);`
   - Imprime a idade.
8. `printf("RG: %s \n", atual->dados->rg);`
   - Imprime o RG.
9. `printf("Data: %d/%d/%d \n", ...);`
   - Imprime a data de entrada.
10. `printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
    - Imprime separador visual.

### void remover_paciente(Lista *lista, char rg[9])
Remove um paciente da lista pelo RG.
- **Parâmetros:**
  - lista: ponteiro para a lista
  - rg: RG do paciente a ser removido
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Elista *anterior = NULL;`
   - Inicializa ponteiro para nó anterior.
2. `Elista *atual = lista->inicio;`
   - Inicializa ponteiro para nó atual.
3. `if(atual == NULL) { ... }`
   - Verifica se a lista está vazia.
4. `printf("\nAinda não há pacientes cadastrados.");`
   - Se vazia, exibe mensagem.
5. `return;`
   - Retorna após exibir mensagem.
6. `while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) { ... }`
   - Percorre a lista até encontrar o paciente pelo RG.
7. `anterior = atual;`
   - Atualiza ponteiro para nó anterior.
8. `atual = atual->proximo;`
   - Avança para próximo nó.
9. `if(anterior == NULL) { ... }`
   - Se deve remover do início.
10. `lista->inicio = atual->proximo;`
    - Atualiza início da lista.
11. `else { ... }`
    - Se deve remover do meio/fim.
12. `anterior->proximo = atual->proximo;`
    - Nó anterior aponta para o próximo do removido.
13. `free(atual->dados->entrada);`
    - Libera memória da data.
14. `free(atual->dados);`
    - Libera memória do registro.
15. `printf("Paciente removido com sucesso!");`
    - Exibe mensagem de sucesso.
16. `lista->qntd--;`
    - Decrementa o contador de pacientes.

### void atualizar_paciente(Lista *lista)
Atualiza os dados de um paciente existente.
- **Parâmetro:** lista
- **Retorno:** void

#### Funcionamento linha a linha:
1. `char rg[9];`
   - Declara variável para armazenar RG.
2. `Elista *anterior = NULL;`
   - Inicializa ponteiro para nó anterior.
3. `Elista *atual = lista->inicio;`
   - Inicializa ponteiro para nó atual.
4. `if(atual == NULL) { ... }`
   - Verifica se a lista está vazia.
5. `printf("\nAinda não há pacientes cadastrados.");`
   - Se vazia, exibe mensagem.
6. `return;`
   - Retorna após exibir mensagem.
7. `printf("RG do paciente a ser removido: ");`
   - Solicita RG do paciente.
8. `scanf("%s", rg);`
   - Lê o RG informado.
9. `while(atual != NULL && strcmp(atual->dados->rg, rg) != 0) { ... }`
   - Percorre a lista até encontrar o paciente pelo RG.
10. `anterior = atual;`
    - Atualiza ponteiro para nó anterior.
11. `atual = atual->proximo;`
    - Avança para próximo nó.
12. `if(atual == NULL) { ... }`
    - Se não encontrou o paciente.
13. `printf("Erro - Paciente não encontrado.\n");`
    - Exibe mensagem de erro.
14. `return;`
    - Retorna após exibir erro.
15. `printf("Atualizando dados do usuário\n");`
    - Exibe mensagem de atualização.
16. `printf("Nome do paciente: ");`
    - Solicita novo nome.
17. `scanf("%s", atual->dados->nome);`
    - Lê e atualiza o nome.
18. `limpar_buffer();`
    - Limpa o buffer de entrada.
19. `printf("Idade do paciente: ");`
    - Solicita nova idade.
20. `scanf("%d", &atual->dados->idade);`
    - Lê e atualiza a idade.
21. `limpar_buffer();`
    - Limpa o buffer de entrada.
22. `printf("RG do paciente: ");`
    - Solicita novo RG.
23. `scanf("%s", atual->dados->rg);`
    - Lê e atualiza o RG.
24. `limpar_buffer();`
    - Limpa o buffer de entrada.
25. `printf("\nUsuário atualizado com sucesso!");`
    - Exibe mensagem de sucesso.

### void salvarLista(Lista* lista, const char* nomeArquivo)
Salva os dados da lista em um arquivo.
- **Parâmetros:**
  - lista: ponteiro para a lista
  - nomeArquivo: nome do arquivo para salvar
- **Retorno:** void

#### Funcionamento linha a linha:
1. `FILE* arquivo = fopen(nomeArquivo, "a");`
   - Abre arquivo para escrita (append).
2. `if (arquivo == NULL) { ... }`
   - Verifica se conseguiu abrir o arquivo.
3. `printf("Erro ao abrir o arquivo para escrita!\n");`
   - Se erro, exibe mensagem.
4. `return;`
   - Retorna após exibir erro.
5. `Elista* atual = lista->inicio;`
   - Inicializa ponteiro para início da lista.
6. `while (atual != NULL) { ... }`
   - Percorre a lista até o final.
7. `fprintf(arquivo, "%s %d %s %d %d %d\n", ...);`
   - Escreve dados do paciente no arquivo.
8. `atual = atual->proximo;`
   - Avança para próximo nó.
9. `fclose(arquivo);`
   - Fecha o arquivo.
10. `printf("Lista salva com sucesso no arquivo %s!\n", nomeArquivo);`
    - Exibe mensagem de sucesso.

### void carregarLista(Lista* lista, const char* nomeArquivo)
Carrega dados de um arquivo para a lista.
- **Parâmetros:**
  - lista: ponteiro para a lista
  - nomeArquivo: nome do arquivo para carregar
- **Retorno:** void

#### Funcionamento linha a linha:
1. `FILE* arquivo = fopen(nomeArquivo, "r");`
   - Abre arquivo para leitura.
2. `if (arquivo == NULL) { ... }`
   - Verifica se conseguiu abrir o arquivo.
3. `printf("Erro ao abrir o arquivo para leitura!\n");`
   - Se erro, exibe mensagem.
4. `return;`
   - Retorna após exibir erro.
5. `while (lista->inicio != NULL) { ... }`
   - Limpa a lista atual.
6. `Elista* temp = lista->inicio;`
   - Salva ponteiro para nó atual.
7. `lista->inicio = lista->inicio->proximo;`
   - Avança início da lista.
8. `free(temp->dados->entrada);`
   - Libera memória da data.
9. `free(temp->dados);`
   - Libera memória do registro.
10. `free(temp);`
    - Libera memória do nó.
11. `lista->qntd = 0;`
    - Zera contador de pacientes.
12. `char nome[50];`
    - Declara variáveis para leitura.
13. `int idade;`
    - Declara variável para idade.
14. `char rg[9];`
    - Declara variável para RG.
15. `int dia, mes, ano;`
    - Declara variáveis para data.
16. `while (fscanf(arquivo, "%s %d %s %d %d %d", ...) == 6) { ... }`
    - Lê cada linha do arquivo.
17. `Registro* novoRegistro = malloc(sizeof(Registro));`
    - Aloca memória para novo registro.
18. `novoRegistro->entrada = malloc(sizeof(Data));`
    - Aloca memória para data.
19. `strcpy(novoRegistro->nome, nome);`
    - Copia nome lido.
20. `novoRegistro->idade = idade;`
    - Copia idade lida.
21. `strcpy(novoRegistro->rg, rg);`
    - Copia RG lido.
22. `novoRegistro->entrada->dia = dia;`
    - Copia dia lido.
23. `novoRegistro->entrada->mes = mes;`
    - Copia mês lido.
24. `novoRegistro->entrada->ano = ano;`
    - Copia ano lido.
25. `cadastrar_paciente(lista, novoRegistro);`
    - Insere paciente na lista.
26. `fclose(arquivo);`
    - Fecha o arquivo.
27. `printf("Lista carregada com sucesso do arquivo %s!\n", nomeArquivo);`
    - Exibe mensagem de sucesso. 