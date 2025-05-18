# Pilha de Operações (Desfazer)

## Estrutura
- **Pilha**: Estrutura com ponteiro para o topo e tamanho.
- **E_pilha**: Nó da pilha, armazena uma operação e ponteiro para o próximo nó.
- **Operacao**: Estrutura que armazena o tipo da operação e uma cópia do registro envolvido.

## Funções

### Registro* clonar_registro(const Registro* original)
Cria uma cópia profunda de um registro de paciente.
- **Parâmetro:** original
- **Retorno:** ponteiro para novo Registro

#### Funcionamento linha a linha:
1. `Registro* novo = malloc(sizeof(Registro));`
   - Aloca memória para o novo registro.
2. `strcpy(novo->nome, original->nome);`
   - Copia o nome do paciente.
3. `strcpy(novo->rg, original->rg);`
   - Copia o RG.
4. `novo->idade = original->idade;`
   - Copia a idade.
5. `novo->entrada = malloc(sizeof(Data));`
   - Aloca memória para a data de entrada.
6. `*(novo->entrada) = *(original->entrada);`
   - Copia os valores da data de entrada.
7. `return novo;`
   - Retorna o ponteiro para o novo registro.

### Pilha* criar_pilha()
Cria e inicializa uma pilha vazia.
- **Retorno:** ponteiro para Pilha

#### Funcionamento linha a linha:
1. `Pilha* p = malloc(sizeof(Pilha));`
   - Aloca memória para a estrutura da pilha.
2. `p->topo = NULL;`
   - Inicializa o topo como NULL (pilha vazia).
3. `p->tamanho = 0;`
   - Inicializa o tamanho como 0.
4. `return p;`
   - Retorna o ponteiro para a pilha criada.

### void empilhar(Pilha* pilha, Operacao op)
Adiciona uma operação ao topo da pilha.
- **Parâmetros:**
  - pilha: ponteiro para a pilha
  - op: operação a ser empilhada
- **Retorno:** void

#### Funcionamento linha a linha:
1. `E_pilha* nova = malloc(sizeof(E_pilha));`
   - Aloca memória para um novo nó da pilha.
2. `nova->operacao = op;`
   - Armazena a operação no novo nó.
3. `nova->proximo = pilha->topo;`
   - O novo nó aponta para o antigo topo.
4. `pilha->topo = nova;`
   - O novo nó vira o topo da pilha.
5. `pilha->tamanho++;`
   - Incrementa o tamanho da pilha.

### int esta_vazia(Pilha* pilha)
Verifica se a pilha está vazia.
- **Parâmetro:** pilha
- **Retorno:** 1 se vazia, 0 caso contrário

#### Funcionamento linha a linha:
1. `return pilha->topo == NULL;`
   - Retorna 1 se o topo é NULL, indicando pilha vazia; caso contrário, retorna 0.

### Operacao desempilhar(Pilha* pilha)
Remove e retorna a operação do topo da pilha.
- **Parâmetro:** pilha
- **Retorno:** Operacao removida

#### Funcionamento linha a linha:
1. `Operacao op_vazia = {0};`
   - Cria uma operação "vazia" para retorno em caso de pilha vazia.
2. `if (esta_vazia(pilha)) return op_vazia;`
   - Se a pilha está vazia, retorna a operação vazia.
3. `E_pilha* temp = pilha->topo;`
   - Salva o ponteiro do topo.
4. `Operacao op = temp->operacao;`
   - Copia a operação do topo.
5. `pilha->topo = temp->proximo;`
   - Move o topo para o próximo nó.
6. `free(temp);`
   - Libera a memória do nó removido.
7. `pilha->tamanho--;`
   - Decrementa o tamanho da pilha.
8. `return op;`
   - Retorna a operação removida.

### void desfazer_ultima_operacao(Contexto *c)
Desfaz a última operação realizada (cadastro, remoção ou enfileiramento).
- **Parâmetro:** c (contexto do sistema)
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Pilha* pilha = c->pilha_operacoes;`
   - Obtém a pilha de operações do contexto.
2. `Lista* lista = c->lista_pacientes;`
   - Obtém a lista de pacientes do contexto.
3. `Fila* fila = c->fila_pacientes;`
   - Obtém a fila de pacientes do contexto.
4. `if (esta_vazia(pilha)) { ... }`
   - Se a pilha está vazia, exibe mensagem e retorna.
5. `Operacao op = desempilhar(pilha);`
   - Desempilha a última operação.
6. `printf("Deseja desfazer a operação? (S/N): ");`
   - Solicita confirmação do usuário.
7. `char resposta; scanf(" %c", &resposta); limpar_buffer();`
   - Lê a resposta do usuário e limpa o buffer.
8. `if (resposta != 'S' && resposta != 's') { ... }`
   - Se a resposta não for S/s, cancela a operação e retorna.
9. `switch (op.tipo) { ... }`
   - Verifica o tipo da operação para desfazer:
   - `OP_CADASTRO`: desfaz cadastro removendo o paciente da lista.
   - `OP_REMOCAO`: desfaz remoção cadastrando novamente o paciente.
   - `OP_ENFILEIRAR`: informa que não é possível desfazer totalmente o enfileiramento. 