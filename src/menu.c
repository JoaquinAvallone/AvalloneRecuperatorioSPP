/*
 * menu.c
 *
 *  Created on: 14 dic. 2022
 *      Author: mac2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"
#include "menu.h"


int menuPrincipal()
{
	int opcion;

	printf("                 ***MENU PRINCIPAL***\n\n"
			   "1.CARGAR ARCHIVO\n"
			   "2.IMPRIMIR LISTA\n"
			   "3.ASIGNAR ESTADISTICAS\n"
			   "4.FILTRAR POR PAISES EXITOSOS\n"
			   "5.FILTRAR POR PAISES EN EL HORNO\n"
			   "6.ORDENAR POR NIVEL DE VACUNACION\n"
			   "7.MOSTRAR MAS CASTIGADO\n"
			   "8.SALIR\n");

	utn_getNumeroInt(&opcion, "Ingrese opcion: ", "Error\n", 1, 8 , 4);

	return opcion;
}
