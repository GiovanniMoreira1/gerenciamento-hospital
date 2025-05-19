#ifndef FILA_H
#define FILA_H

#include "estruturas.h"

void enqueue_paciente(Fila *queue, Registro *dados);
void dequeue_paciente(Fila *queue);
void mostrar_queue(Fila *q);
void desfazer_enqueue(Fila *queue);
void desfazer_dequeue(Fila *queue, Registro *dados);

#endif 