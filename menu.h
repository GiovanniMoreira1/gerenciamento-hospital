#ifndef MENU_H
#define MENU_H

#include "estruturas.h"
#include "lista.h"
#include "fila.h"
#include "pilha.h"

void limpar_buffer();
void confirma();
void cadastro(Lista *lista, Contexto *c);
void atendimento(Fila *fila, Lista *lista);
void menu();

#endif 