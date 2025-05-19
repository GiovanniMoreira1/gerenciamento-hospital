#ifndef LISTA_H
#define LISTA_H

#include "estruturas.h"

void mostrarLista(Lista *lista);
Elista *criar_celula(Registro *registro);
void cadastrar_paciente(Lista *lista, Registro *registro);
void consultar_ultimo_paciente(Lista *lista);
void remover_paciente(Lista *lista, char rg[9]);
void atualizar_paciente(Lista *lista);
void salvarLista(Lista* lista, const char* nomeArquivo);
void carregarLista(Lista* lista, const char* nomeArquivo);

#endif 