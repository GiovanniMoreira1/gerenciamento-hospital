# Relatório Técnico de Progresso  
**Projeto:** Gerenciador de Atendimento Médico  
**Disciplina:** Estrutura de Dados – 1º Semestre de 2025  
**Curso:** Ciência da Computação – Centro Universitário FEI  
**Docente Responsável:** Prof. Luciano Rossi

---

## 1. Introdução

O presente projeto visa implementar um sistema completo de gerenciamento de atendimento médico, baseado nos principais conceitos de Estrutura de Dados, como listas encadeadas, filas, pilhas, árvores binárias e heaps. A aplicação deve contemplar o cadastro e gerenciamento de pacientes, controle de atendimentos (normais e prioritários), funcionalidades de pesquisa ordenada, sistema de desfazer ações e persistência de dados.

---

## 2. Estruturas e Funcionalidades Implementadas

### 2.1. Lista Encadeada para Cadastro de Pacientes
Foi implementada uma **lista encadeada simples**, com inserção no início, para armazenar os pacientes do sistema. A estrutura garante:
- Alocação dinâmica dos dados com ponteiros;
- Inserção de pacientes com estrutura `Registro`;
- Consulta ao último paciente cadastrado;
- Listagem de todos os registros;
- Atualização e remoção de pacientes via RG;
- Gerenciamento correto de memória com `free()`.

### 2.2. Fila de Atendimento (FIFO)
Foi desenvolvida uma **fila dinâmica** baseada em ponteiros, para representar a fila de atendimento padrão. As funcionalidades incluem:
- Enfileiramento de pacientes cadastrados;
- Desenfileiramento de pacientes;
- Visualização da fila com ordenação de chegada;
- Correta manipulação dos ponteiros `head` e `tail`.

### 2.3. Menu Principal
Foi construído um menu com navegação funcional, incluindo chamadas diretas para os módulos implementados, além de uma tela "Sobre" com os dados dos desenvolvedores e do projeto.

---

## 3. Funcionalidades Pendentes

### 3.1. Atendimento Prioritário (Heap de Máximo)
- **Estrutura:** Heap de máximo com vetor de ponteiros para `Registro`;
- **Critério de ordenação:** prioridade por **idade**;
- **Limitação:** **20 pacientes** no heap por dia;
- **Operações:** enfileirar, desenfileirar e exibir a fila prioritária.

### 3.2. Pesquisa (Árvore Binária de Busca)
- **Estrutura:** Árvore binária contendo ponteiros para `Registro`;
- **Critérios de ordenação:** ano, mês, dia de registro e idade;
- **Operações:** inserção ordenada e visualização em diferentes ordens.

### 3.3. Pilha de Operações (Desfazer)
- **Estrutura:** Pilha de strings ou estruturas contendo tipo e dados da operação;
- **Funcionalidade:** desfazer a última operação realizada sobre a fila de atendimento;
- **Operações:** `push`, `pop`, exibição de log e confirmação de desfazer.

### 3.4. Persistência (Carregar e Salvar)
- **Funcionalidade:** leitura e gravação de dados em arquivo;
- **Requisito:** preservar a ordem de inserção dos pacientes;
- **Formato sugerido:** `.txt` ou `.csv`, de fácil leitura e parse.

---

## 4. Considerações Técnicas

Todas as estruturas dinâmicas são implementadas utilizando **alocação via `malloc()`**, e a liberação é devidamente tratada via `free()` para evitar vazamentos de memória. A aplicação segue o princípio de **centralização dos dados na lista de pacientes**, de modo que as outras estruturas operam com **referências (ponteiros)** para os mesmos dados, garantindo integridade e sincronização.

---

## 5. Próximos Passos

| Etapa | Tarefa Técnica                                | Prioridade |
|-------|-----------------------------------------------|------------|
| 1     | Implementar heap de prioridade por idade      | Alta       |
| 2     | Criar árvore binária de pesquisa e ordenação  | Alta       |
| 3     | Desenvolver estrutura de pilha para log       | Média      |
| 4     | Adicionar funcionalidade de persistência      | Média      |
| 5     | Realizar testes unitários e integração        | Alta       |
| 6     | Documentar código e preparar apresentação     | Alta       |

---

## 6. Conclusão

O projeto está em fase intermediária de desenvolvimento, com os módulos principais de cadastro e atendimento básico concluídos. As estruturas de dados fundamentais estão sendo aplicadas conforme o proposto, com atenção à integridade dos dados, modularização e boas práticas de programação em C. O cronograma de implementação segue viável e as próximas etapas envolvem a finalização das estruturas restantes e integração dos recursos pendentes.
