/*
 * controller.h
 *
 *  Created on: 14 dic. 2022
 *      Author: mac2020
 */
#include "vacunados.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_



#endif /* CONTROLLER_H_ */


int pedirPath(char* path);

int parser_VacunadosFromText(FILE* pFile , LinkedList* pLista);

int controller_cargarVacunadosDesdeTexto(char* path , LinkedList* pLista);

int controller_listarVacunado(eVacunado* unVacunado);

int controller_listarVacunados(LinkedList* pLista);

int asignarUnaDosis(LinkedList* listaPaises);

void* asignarVacAleatorio(void* elemento);

int asignarDosDosis(LinkedList* listaPaises);

void* asignarVac2Aleatorio(void* elemento);

int asignarNoVacunados(LinkedList* listaPaises);

void* asignarNoVacAleatorio(void* elemento);

int filtrarExitosos(void* unVacunado);

int controller_guardarVacunadosTexto(char* path , LinkedList* listaPaises);

int filtrarAlHorno(void* unVacunado);

int ordenarVacunados(void* paisI, void* paisJ);

int masCastigados(LinkedList* masCastigados);
