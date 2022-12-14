/*
 ============================================================================
 Name        : 1A.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "validaciones.h"
#include "controller.h"
#include "menu.h"
#include "vacunados.h"
#include "time.h"

int main(void) {
	setbuf(stdout,NULL);
	char respuesta = 'n';
	int flagEstadisticas = 0;
	int flagAlHorno = 0;
	char path[30];
	srand(time(NULL));
	LinkedList* listaPaises = ll_newLinkedList();
	LinkedList* listaExitosos = ll_newLinkedList();
	LinkedList* listaAlHorno = ll_newLinkedList();

	do{
		switch(menuPrincipal())
		{
		case 1:
			pedirPath(path);
			if(strcmp(path, "vacunas.csv") == 0)
			{
				if(controller_cargarVacunadosDesdeTexto("vacunas.csv", listaPaises))
				{
					printf("El archivo se cargo con exito.\n");
				}
				else
				{
					printf("No pudo cargarse el archivo.\n");
				}
			}
			else
			{
				printf("Nombre de path invalido.Recomendacion path: vacunas.csv\n");
			}
			pausa();
			break;
		case 2:
			if(ll_isEmpty(listaPaises))
			{
				printf("No hay paises, ingrese al punto 1.\n");
			}
			else
			{
				controller_listarVacunados(listaPaises);
			}
			pausa();
			break;
		case 3:
			if(ll_isEmpty(listaPaises))
			{
				printf("No hay paises, ingrese al punto 1.\n");
			}
			else
			{
				if(asignarUnaDosis(listaPaises) && asignarDosDosis(listaPaises) && asignarNoVacunados(listaPaises))
				{
					flagEstadisticas = 1;
					printf("Estadisticas asignados con exito.\n");
					pausa();
					controller_listarVacunados(listaPaises);
				}
			}
			pausa();
			break;
		case 4:
			if(ll_isEmpty(listaPaises))
			{
				printf("No hay paises, ingrese al punto 1.\n");
			}
			else
			{
				if(!flagEstadisticas)
				{
					printf("Primero se deben asignar las estadisticas de los posteos en el punto 3.\n");
				}
				else
				{
					listaExitosos = ll_filter(listaPaises,filtrarExitosos);
					controller_listarVacunados(listaExitosos);
					controller_guardarVacunadosTexto("exitosos.csv", listaExitosos);
				}
			}
			pausa();
			break;
		case 5:
			if(ll_isEmpty(listaPaises))
			{
				printf("No hay paises, ingrese al punto 1.\n");
			}
			else
			{
				if(!flagEstadisticas)
				{
					printf("Primero se deben asignar las estadisticas de los posteos en el punto 3.\n");
				}
				else
				{
					listaAlHorno = ll_filter(listaPaises,filtrarAlHorno);
					if(controller_listarVacunados(listaAlHorno))
					{
						flagAlHorno = 1;
						controller_guardarVacunadosTexto("horno.csv", listaAlHorno);
					}
					else
					{
						printf("No hay paises al horno.\n");
					}
				}
			}
			pausa();
			break;
		case 6:
			if(ll_isEmpty(listaPaises))
			{
				printf("No hay paises, ingrese al punto 1.\n");
			}
			else
			{
				if(!flagEstadisticas)
				{
					printf("Primero se deben asignar las estadisticas de los posteos en el punto 3.\n");
				}
				else
				{
					ll_sort(listaPaises,ordenarVacunados,1);
					controller_listarVacunados(listaPaises);
				}
			}
			pausa();
			break;
		case 7:
			if(ll_isEmpty(listaPaises))
			{
				printf("No hay paises, ingrese al punto 1.\n");
			}
			else
			{
				if(!flagEstadisticas)
				{
					printf("Primero se deben asignar las estadisticas de los posteos en el punto 3.\n");
				}
				else
				{
					if(!flagAlHorno)
					{
						printf("Primero se debe ingresar al punto 5.\n");
					}
					else
					{
						masCastigados(listaAlHorno);
					}
				}
			}
			pausa();
			break;
		case 8:
			pausa();
			break;
		default:
			printf("La opcion elegida no existe.\n");
			pausa();
		}
		limpiarConsola();
	}while(respuesta == 'n');
	return 0;
}
