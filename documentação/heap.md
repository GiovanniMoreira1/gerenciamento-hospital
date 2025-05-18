# Heap Máximo (Atendimento Prioritário)

## Estrutura
- **HeapMaximo**: Estrutura com vetor de ponteiros para pacientes, tamanho atual e capacidade máxima.

## Funções

### HeapMaximo* criarHeap()
Cria e inicializa um heap máximo.
- **Retorno:** ponteiro para HeapMaximo

#### Funcionamento linha a linha:
1. `HeapMaximo* heap = (HeapMaximo*)malloc(sizeof(HeapMaximo));`
   - Aloca memória para a estrutura do heap.
2. `if (heap == NULL) { ... }`
   - Verifica se a alocação foi bem-sucedida. Se não, exibe erro e retorna NULL.
3. `heap->pacientes = (Registro**)malloc(20 * sizeof(Registro*));`
   - Aloca memória para o vetor de ponteiros para pacientes (capacidade inicial 20).
4. `if (heap->pacientes == NULL) { ... }`
   - Verifica se a alocação do vetor foi bem-sucedida. Se não, libera o heap e retorna NULL.
5. `heap->tamanho = 0;`
   - Inicializa o tamanho do heap como 0.
6. `heap->capacidade = 20;`
   - Define a capacidade máxima inicial como 20.
7. `return heap;`
   - Retorna o ponteiro para o heap criado.

### void destruirHeap(HeapMaximo* heap)
Libera toda a memória do heap.
- **Parâmetro:** heap
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (heap == NULL) { ... }`
   - Verifica se o heap existe. Se não, exibe mensagem e retorna.
2. `free(heap->pacientes);`
   - Libera o vetor de ponteiros para pacientes.
3. `free(heap);`
   - Libera a estrutura do heap.

### int inserirPaciente(HeapMaximo* heap, Registro* paciente)
Insere um paciente no heap, mantendo a propriedade de heap máximo (maior idade no topo).
- **Parâmetros:**
  - heap: ponteiro para o heap
  - paciente: ponteiro para o registro
- **Retorno:** 1 se sucesso, 0 se cheio

#### Funcionamento linha a linha:
1. `if(heapCheio(heap)) { ... }`
   - Verifica se o heap está cheio. Se sim, exibe erro e retorna 0.
2. `heap->pacientes[heap->tamanho] = paciente;`
   - Insere o paciente no final do vetor.
3. `subir(heap, heap->tamanho);`
   - Ajusta o heap para cima para manter a propriedade de heap máximo.
4. `heap->tamanho++;`
   - Incrementa o tamanho do heap.
5. `return 1;`
   - Retorna 1 indicando sucesso.

### Registro* removerPaciente(HeapMaximo* heap)
Remove e retorna o paciente de maior prioridade (maior idade).
- **Parâmetro:** heap
- **Retorno:** ponteiro para Registro removido

#### Funcionamento linha a linha:
1. `if(heapVazio(heap)) { ... }`
   - Verifica se o heap está vazio. Se sim, exibe erro e retorna NULL.
2. `Registro* paciente = heap->pacientes[0];`
   - Salva o paciente da raiz (maior prioridade).
3. `heap->pacientes[0] = heap->pacientes[heap->tamanho - 1];`
   - Move o último elemento para a raiz.
4. `heap->tamanho--;`
   - Decrementa o tamanho do heap.
5. `if(heap->tamanho > 0) { descer(heap, 0); }`
   - Se ainda houver elementos, ajusta o heap para baixo.
6. `return paciente;`
   - Retorna o paciente removido.

### int heapVazio(HeapMaximo* heap)
Verifica se o heap está vazio.
- **Parâmetro:** heap
- **Retorno:** 1 se vazio, 0 caso contrário

#### Funcionamento linha a linha:
1. `if(heap->tamanho == 0) { return 1; }`
   - Retorna 1 se o tamanho for 0.
2. `return 0;`
   - Caso contrário, retorna 0.

### int heapCheio(HeapMaximo* heap)
Verifica se o heap está cheio.
- **Parâmetro:** heap
- **Retorno:** 1 se cheio, 0 caso contrário

#### Funcionamento linha a linha:
1. `if(heap->tamanho == heap->capacidade) { return 1; }`
   - Retorna 1 se o tamanho for igual à capacidade.
2. `return 0;`
   - Caso contrário, retorna 0.

### void subir(HeapMaximo* heap, int indice)
Ajusta o heap para cima a partir do índice, mantendo a propriedade de heap máximo.
- **Parâmetros:**
  - heap: ponteiro para o heap
  - indice: índice do elemento a ser ajustado
- **Retorno:** void

#### Funcionamento linha a linha:
1. `int pai = (indice - 1) / 2;`
   - Calcula o índice do pai.
2. `if(indice > 0 && heap->pacientes[indice]->idade > heap->pacientes[pai]->idade) { ... }`
   - Se não é a raiz e o filho é maior que o pai, troca os dois.
3. `trocar(&heap->pacientes[indice], &heap->pacientes[pai]);`
   - Troca os ponteiros dos pacientes.
4. `subir(heap, pai);`
   - Continua subindo recursivamente.

### void descer(HeapMaximo* heap, int indice)
Ajusta o heap para baixo a partir do índice, mantendo a propriedade de heap máximo.
- **Parâmetros:**
  - heap: ponteiro para o heap
  - indice: índice do elemento a ser ajustado
- **Retorno:** void

#### Funcionamento linha a linha:
1. `int esquerda = 2 * indice + 1;`
   - Calcula o índice do filho esquerdo.
2. `int direita = 2 * indice + 2;`
   - Calcula o índice do filho direito.
3. `int maior = indice;`
   - Assume que o pai é o maior.
4. `if(esquerda < heap->tamanho && heap->pacientes[esquerda]->idade > heap->pacientes[maior]->idade) { maior = esquerda; }`
   - Se o filho esquerdo existe e é maior, atualiza o maior.
5. `if(direita < heap->tamanho && heap->pacientes[direita]->idade > heap->pacientes[maior]->idade) { maior = direita; }`
   - Se o filho direito existe e é maior, atualiza o maior.
6. `if(maior != indice) { ... }`
   - Se o maior não é o pai, troca e continua descendo.
7. `trocar(&heap->pacientes[indice], &heap->pacientes[maior]);`
   - Troca os ponteiros dos pacientes.
8. `descer(heap, maior);`
   - Continua descendo recursivamente.

### void trocar(Registro** a, Registro** b)
Troca dois ponteiros de pacientes.
- **Parâmetros:**
  - a: ponteiro para ponteiro de paciente
  - b: ponteiro para ponteiro de paciente
- **Retorno:** void

#### Funcionamento linha a linha:
1. `Registro* temp = *a;`
   - Guarda o valor do primeiro ponteiro.
2. `*a = *b;`
   - Primeiro ponteiro recebe o valor do segundo.
3. `*b = temp;`
   - Segundo ponteiro recebe o valor guardado.

### void imprimirHeap(HeapMaximo* heap)
Exibe todos os pacientes do heap.
- **Parâmetro:** heap
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if(heapVazio(heap)) { ... }`
   - Verifica se o heap está vazio. Se sim, exibe mensagem e retorna.
2. `for(int i = 0; i < heap->tamanho; i++) { ... }`
   - Percorre todos os pacientes do heap.
3. `printf("Nome: %s\n", heap->pacientes[i]->nome);`
   - Imprime o nome do paciente.
4. `printf("Idade: %d\n", heap->pacientes[i]->idade);`
   - Imprime a idade.
5. `printf("RG: %s\n", heap->pacientes[i]->rg);`
   - Imprime o RG.
6. `printf("Data: %d/%d/%d\n", ...);`
   - Imprime a data de entrada.
7. `printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
   - Imprime separador visual.

### void imprimirProximoAtendimento(HeapMaximo* heap)
Exibe o paciente de maior prioridade (raiz do heap).
- **Parâmetro:** heap
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if(heapVazio(heap)) { ... }`
   - Verifica se o heap está vazio. Se sim, exibe mensagem e retorna.
2. `printf("\nPróximo paciente a ser atendido:\n");`
   - Imprime cabeçalho.
3. `printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
   - Imprime separador visual.
4. `printf("Nome: %s\n", heap->pacientes[0]->nome);`
   - Imprime o nome do paciente da raiz.
5. `printf("Idade: %d\n", heap->pacientes[0]->idade);`
   - Imprime a idade.
6. `printf("RG: %s\n", heap->pacientes[0]->rg);`
   - Imprime o RG.
7. `printf("Data de entrada: %d/%d/%d\n", ...);`
   - Imprime a data de entrada.
8. `printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");`
   - Imprime separador visual.

### desenfileirarPaciente(HeapMaximo* heap, const char* rg)
Remove um paciente específico do heap pelo RG.
- **Parâmetros:**
  - heap: ponteiro para o heap
  - rg: RG do paciente
- **Retorno:** void

### enfileirarPaciente(HeapMaximo* heap, Lista* lista, const char* rg)
Adiciona um paciente da lista ao heap pelo RG.
- **Parâmetros:**
  - heap: ponteiro para o heap
  - lista: ponteiro para a lista de pacientes
  - rg: RG do paciente
- **Retorno:** void 