#ifndef MENU_H
#define MENU_H

#include "estruturas.h"
#include "lista.h"
#include "fila.h"

void limpar_buffer();
void confirma();
void cadastro(Lista *lista);
void atendimento(Fila *fila, Lista *lista);
void menu();

#endif 