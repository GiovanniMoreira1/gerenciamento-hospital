#ifndef FILA_H
#define FILA_H

#include "estruturas.h"

void enqueue_paciente(Fila *queue, Registro *dados);
void dequeue_paciente(Fila *queue);
void mostrar_queue(Fila *q);

#endif 