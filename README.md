# Gerenciador de Atendimento Hospitalar

Este projeto é um sistema completo de gerenciamento de atendimentos médicos, desenvolvido em C, que utiliza diversas estruturas de dados clássicas para simular o funcionamento de um hospital. O sistema permite o cadastro, busca, atendimento e gerenciamento de pacientes, com suporte a operações de desfazer e persistência em arquivo.

## Estruturas de Dados Utilizadas

- **Lista Encadeada**: Armazena todos os pacientes cadastrados, permitindo inserção, remoção, atualização e listagem.
- **Fila (FIFO)**: Gerencia a ordem de atendimento padrão dos pacientes.
- **Heap Máximo**: Implementa a fila de atendimento prioritário, ordenando pacientes por idade (maior idade = maior prioridade).
- **Pilha**: Armazena operações realizadas para permitir desfazer ações (cadastro, remoção, enfileiramento).
- **Árvore Binária de Busca (ABB)**: Permite buscas e exibições ordenadas de pacientes por ano, mês, dia de registro ou idade, sem alterar a lista principal.

## Funcionalidades Principais

- **Cadastro de Pacientes**: Adiciona pacientes com nome, idade, RG e data de entrada.
- **Consulta e Listagem**: Permite consultar o último paciente cadastrado e listar todos os pacientes.
- **Atualização e Remoção**: Atualiza dados ou remove pacientes pelo RG.
- **Atendimento Padrão**: Gerencia uma fila FIFO para atendimento sequencial.
- **Atendimento Prioritário**: Gerencia uma fila de prioridade (heap) para pacientes mais velhos, com limite de 20 por dia.
- **Pesquisa Ordenada**: Permite inserir pacientes em uma ABB e exibir ordenado por ano, mês, dia ou idade, sem alterar a lista principal.
- **Desfazer Operações**: Permite desfazer as últimas operações de cadastro, remoção e enfileiramento.
- **Persistência**: Salva e carrega a lista de pacientes em arquivo texto (`pacientes.txt`).

## Fluxo do Sistema

1. **Menu Principal**: O usuário pode acessar as opções de cadastro, atendimento, atendimento prioritário, pesquisa, desfazer, carregar/salvar e sobre.
2. **Cadastro**: Permite adicionar, consultar, listar, atualizar e remover pacientes.
3. **Atendimento**: Adiciona pacientes à fila padrão e realiza atendimentos sequenciais.
4. **Atendimento Prioritário**: Adiciona pacientes à fila prioritária (heap) e realiza atendimentos por prioridade de idade.
5. **Pesquisa**: Insere pacientes já cadastrados em uma ABB e permite exibir ordenado por ano, mês, dia ou idade.
6. **Desfazer**: Permite desfazer a última operação realizada.
7. **Persistência**: Salva ou carrega a lista de pacientes de/para um arquivo texto.

## Estrutura dos Arquivos

- `main.c`: Ponto de entrada do sistema.
- `menu.c/h`: Implementação do menu e fluxo principal.
- `lista.c/h`: Implementação da lista encadeada de pacientes.
- `fila.c/h`: Implementação da fila de atendimento padrão.
- `heap.c/h`: Implementação do heap de prioridade para atendimento prioritário.
- `pilha.c/h`: Implementação da pilha de operações para desfazer.
- `arvore.c/h`: Implementação da árvore binária de busca para pesquisa ordenada.
- `estruturas.h`: Definições das estruturas de dados utilizadas.
- `pacientes.txt`: Arquivo de persistência dos pacientes (nome, idade, RG, dia, mês, ano).

## Formato do Arquivo de Pacientes

Cada linha do arquivo `pacientes.txt` segue o formato:
```
Nome Idade RG Dia Mês Ano
```
Exemplo:
```
Joao 45 123 15 3 2024
Maria 32 456 10 2 2023
```

## Como Usar

1. Compile todos os arquivos `.c` juntos:
   ```
   gcc -o hospital main.c menu.c lista.c fila.c heap.c pilha.c arvore.c
   ```
2. Execute o programa:
   ```
   ./hospital
   ```
3. Navegue pelo menu para cadastrar pacientes, realizar atendimentos, pesquisar, desfazer operações e salvar/carregar dados.

## Observações
- O sistema foi desenvolvido para fins didáticos, aplicando conceitos de Estrutura de Dados.
- O código é modular e pode ser expandido para novas funcionalidades.
- O arquivo de pacientes pode ser editado manualmente para testes.

---
Desenvolvido para a disciplina de Estrutura de Dados - Ciência da Computação - FEI
Alunos:
   Artur Chaves Paiva - 22.223.023-7
   Giovanni Antonio Moreira - 22.223.010-4
