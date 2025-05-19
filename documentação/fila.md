# Fila de Atendimento (FIFO)

## Estrutura
- **Fila**: Estrutura principal com ponteiros para o início (head), fim (tail) e quantidade de elementos.
- **Efila**: Nó da fila, armazena ponteiro para Registro e para o próximo nó.

## Funções

### void enqueue_paciente(Fila *queue, Registro *dados)
Adiciona um paciente ao final da fila.

- **Parâmetros:**
  - `queue`: ponteiro para a fila
  - `dados`: ponteiro para o registro do paciente
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Efila *novo = malloc(sizeof(Efila));`
   - Aloca memória para um novo nó da fila.
2. `novo->dados = dados;`
   - Associa o ponteiro de dados do novo nó ao paciente recebido.
3. `novo->proximo = NULL;`
   - Inicializa o ponteiro para o próximo nó como NULL (será o último da fila).
4. `if(queue->head == NULL) {`
   - Verifica se a fila está vazia.
5. `queue->head = novo;`
   - Se vazia, o novo nó vira o início da fila.
6. `queue->tail = novo;`
   - E também o final da fila.
7. `} else {`
   - Se a fila não está vazia:
8. `queue->tail->proximo = novo;`
   - O último nó atual aponta para o novo nó.
9. `queue->tail = novo;`
   - O novo nó vira o novo final da fila.
10. `}`
11. `queue->qntd++;`
   - Incrementa a quantidade de elementos na fila.

### void dequeue_paciente(Fila *queue)
Remove o paciente do início da fila.

- **Parâmetro:** `queue`
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if(queue->head == NULL) {`
   - Verifica se a fila está vazia.
2. `printf("\nFila vazia!");`
   - Se vazia, exibe mensagem.
3. `return;`
   - Sai da função.
4. `}`
5. `Efila *temp = queue->head;`
   - Salva o ponteiro do primeiro nó.
6. `queue->head = queue->head->proximo;`
   - Move o início da fila para o próximo nó.
7. `free(temp);`
   - Libera a memória do nó removido.
8. `queue->qntd--;`
   - Decrementa a quantidade de elementos.
9. `if(queue->head == NULL) {`
   - Se a fila ficou vazia após a remoção:
10. `queue->tail = NULL;`
    - O final da fila também vira NULL.
11. `}`

### void mostrar_queue(Fila *q)
Exibe todos os pacientes na fila, na ordem de chegada.

- **Parâmetro:** `q`
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Efila *atual = q->head;`
   - Cria um ponteiro para percorrer a fila a partir do início.
2. `if(atual == NULL) {`
   - Verifica se a fila está vazia.
3. `printf("\nFila vazia!");`
   - Se vazia, exibe mensagem.
4. `return;`
   - Sai da função.
5. `}`
6. `while(atual != NULL) {`
   - Percorre a fila até o final.
7. `printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
   - Imprime separador visual.
8. `printf("Nome: %s \n", atual->dados->nome);`
   - Imprime o nome do paciente.
9. `printf("Idade: %d \n", atual->dados->idade);`
   - Imprime a idade.
10. `printf("RG: %s \n", atual->dados->rg);`
    - Imprime o RG.
11. `printf("Data: %d/%d/%d \n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);`
    - Imprime a data de entrada.
12. `atual = atual->proximo;`
    - Avança para o próximo nó.
13. `}` 