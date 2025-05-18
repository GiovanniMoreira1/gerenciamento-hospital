#ifndef PILHA_H
#define PILHA_H

#include "estruturas.h"
#include "lista.h"
#include "fila.h"

Pilha* criar_pilha();
void empilhar(Pilha* pilha, Operacao op);
Operacao desempilhar(Pilha* pilha);
int esta_vazia(Pilha* pilha);
void desfazer_ultima_operacao(Contexto* c);

#endif