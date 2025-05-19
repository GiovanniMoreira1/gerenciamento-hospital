# Árvore Binária de Busca (ABB) para Pesquisa

## Estrutura
- **ABB**: Estrutura principal com ponteiro para a raiz e quantidade de nós.
- **EABB**: Nó da árvore, armazena ponteiro para Registro e para os filhos esquerdo e direito.

## Funções

### ABB* criar_abb()
Cria e inicializa uma árvore binária de busca vazia.
- **Retorno:** ponteiro para ABB

#### Funcionamento linha a linha:
1. `ABB *arvore = (ABB*)malloc(sizeof(ABB));`
   - Aloca memória para a estrutura da árvore.
2. `arvore->raiz = NULL;`
   - Inicializa a raiz como NULL (árvore vazia).
3. `arvore->qtde = 0;`
   - Inicializa a quantidade de nós como 0.
4. `return arvore;`
   - Retorna o ponteiro para a árvore criada.

### void inserir_abb(ABB *arvore, Registro *paciente)
Insere um paciente já cadastrado na árvore (sem ordenação, sempre à esquerda).
- **Parâmetros:**
  - arvore: ponteiro para a ABB
  - paciente: ponteiro para o registro
- **Retorno:** void

#### Funcionamento linha a linha:
1. `EABB *novo = criar_no(paciente);`
   - Cria um novo nó para o paciente.
2. `if (arvore->raiz == NULL) { ... }`
   - Se a árvore está vazia, o novo nó vira a raiz.
3. `else { ... }`
   - Caso contrário, percorre sempre para a esquerda até encontrar o último nó.
4. `atual->filhoEsq = novo;`
   - Insere o novo nó como filho esquerdo do último nó.
5. `arvore->qtde++;`
   - Incrementa a quantidade de nós na árvore.

### void liberar_abb(ABB *arvore)
Libera toda a memória da árvore, incluindo todos os nós.
- **Parâmetro:** arvore
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (arvore == NULL) return;`
   - Se a árvore é nula, não faz nada.
2. `liberar_eabb(arvore->raiz);`
   - Libera todos os nós a partir da raiz.
3. `free(arvore);`
   - Libera a estrutura da árvore.

### void mostrar_por_ano(EABB *raiz, int *count)
Exibe os pacientes ordenados por ano de registro.
- **Parâmetros:**
  - raiz: ponteiro para o nó raiz da árvore
  - count: ponteiro para contador de exibição
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (raiz == NULL) return;`
   - Se o nó é nulo, retorna.
2. `mostrar_por_ano(raiz->filhoEsq, count);`
   - Percorre recursivamente o filho esquerdo.
3. `printf(...);`
   - Imprime os dados do paciente atual, incrementando o contador.
4. `mostrar_por_ano(raiz->filhoDir, count);`
   - Percorre recursivamente o filho direito.

### void mostrar_por_mes(EABB *raiz, int *count)
Exibe os pacientes ordenados por mês de registro.
- **Parâmetros:**
  - raiz: ponteiro para o nó raiz da árvore
  - count: ponteiro para contador de exibição
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (raiz == NULL) return;`
   - Se o nó é nulo, retorna.
2. `mostrar_por_mes(raiz->filhoEsq, count);`
   - Percorre recursivamente o filho esquerdo.
3. `printf(...);`
   - Imprime os dados do paciente atual, incrementando o contador.
4. `mostrar_por_mes(raiz->filhoDir, count);`
   - Percorre recursivamente o filho direito.

### void mostrar_por_dia(EABB *raiz, int *count)
Exibe os pacientes ordenados por dia de registro.
- **Parâmetros:**
  - raiz: ponteiro para o nó raiz da árvore
  - count: ponteiro para contador de exibição
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (raiz == NULL) return;`
   - Se o nó é nulo, retorna.
2. `mostrar_por_dia(raiz->filhoEsq, count);`
   - Percorre recursivamente o filho esquerdo.
3. `printf(...);`
   - Imprime os dados do paciente atual, incrementando o contador.
4. `mostrar_por_dia(raiz->filhoDir, count);`
   - Percorre recursivamente o filho direito.

### void mostrar_por_idade(EABB *raiz, int *count)
Exibe os pacientes ordenados por idade.
- **Parâmetros:**
  - raiz: ponteiro para o nó raiz da árvore
  - count: ponteiro para contador de exibição
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (raiz == NULL) return;`
   - Se o nó é nulo, retorna.
2. `mostrar_por_idade(raiz->filhoEsq, count);`
   - Percorre recursivamente o filho esquerdo.
3. `printf(...);`
   - Imprime os dados do paciente atual, incrementando o contador.
4. `mostrar_por_idade(raiz->filhoDir, count);`
   - Percorre recursivamente o filho direito.

### void inserir_todos_ano(EABB* no, ABB* temp)
Insere todos os pacientes da árvore em uma nova ABB ordenada por ano.
- **Parâmetros:**
  - no: nó atual da árvore original
  - temp: ABB temporária
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (no == NULL) return;`
   - Se o nó é nulo, retorna.
2. `inserir_ordenado_ano(&temp->raiz, no->dados);`
   - Insere o paciente na árvore temporária ordenada por ano.
3. `inserir_todos_ano(no->filhoEsq, temp);`
   - Repete para o filho esquerdo.
4. `inserir_todos_ano(no->filhoDir, temp);`
   - Repete para o filho direito.

### void inserir_todos_mes(EABB* no, ABB* temp)
Insere todos os pacientes da árvore em uma nova ABB ordenada por mês.
- **Parâmetros:**
  - no: nó atual da árvore original
  - temp: ABB temporária
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (no == NULL) return;`
   - Se o nó é nulo, retorna.
2. `inserir_ordenado_mes(&temp->raiz, no->dados);`
   - Insere o paciente na árvore temporária ordenada por mês.
3. `inserir_todos_mes(no->filhoEsq, temp);`
   - Repete para o filho esquerdo.
4. `inserir_todos_mes(no->filhoDir, temp);`
   - Repete para o filho direito.

### void inserir_todos_dia(EABB* no, ABB* temp)
Insere todos os pacientes da árvore em uma nova ABB ordenada por dia.
- **Parâmetros:**
  - no: nó atual da árvore original
  - temp: ABB temporária
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (no == NULL) return;`
   - Se o nó é nulo, retorna.
2. `inserir_ordenado_dia(&temp->raiz, no->dados);`
   - Insere o paciente na árvore temporária ordenada por dia.
3. `inserir_todos_dia(no->filhoEsq, temp);`
   - Repete para o filho esquerdo.
4. `inserir_todos_dia(no->filhoDir, temp);`
   - Repete para o filho direito.

### void inserir_todos_idade(EABB* no, ABB* temp)
Insere todos os pacientes da árvore em uma nova ABB ordenada por idade.
- **Parâmetros:**
  - no: nó atual da árvore original
  - temp: ABB temporária
- **Retorno:** void

#### Funcionamento linha a linha:
1. `if (no == NULL) return;`
   - Se o nó é nulo, retorna.
2. `inserir_ordenado_idade(&temp->raiz, no->dados);`
   - Insere o paciente na árvore temporária ordenada por idade.
3. `inserir_todos_idade(no->filhoEsq, temp);`
   - Repete para o filho esquerdo.
4. `inserir_todos_idade(no->filhoDir, temp);`
   - Repete para o filho direito. 