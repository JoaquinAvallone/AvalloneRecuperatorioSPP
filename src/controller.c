/*
 * controller.c
 *
 *  Created on: 14 dic. 2022
 *      Author: mac2020
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

int pedirPath(char* path)
{
	int todoOk = 0;
	char pathAux [30];
	if(path)
	{
	 path[0]='\0';
	 printf("Ingrese el Path: ");
	 fflush(stdin);
	 gets(pathAux);
	 fflush(stdin);
	 while(strlen(pathAux) <= 0 || strlen(pathAux) >= 20)
	 {
		 printf("Ingrese un Path mas corto/largo: ");
		 fflush(stdin);
		 gets(pathAux);
		 fflush(stdin);
	 }
	 strcat(path,pathAux);
	 todoOk = 1;
	}
	 return todoOk;
}


int parser_VacunadosFromText(FILE* pFile , LinkedList* pLista)
{
	int retorno = 0;
	char buffer[5][100];
	eVacunado* auxUser = NULL;

	if(pFile!=NULL && pLista!=NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
			auxUser = vacunado_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

			if(auxUser != NULL)
			{
				ll_add(pLista, auxUser);
			}
		}
		retorno = 1;
	}
    return retorno;
}

/** \brief Carga los datos de los paises desde el archivo vacunas.csv (modo texto).
 *
 * \param path char*
 * \param pLista LinkedList*
 * \return int
 *
 */
int controller_cargarVacunadosDesdeTexto(char* path , LinkedList* pLista)
{
	int retorno=0;
	FILE* file = NULL;

	if(pLista!=NULL && path!=NULL)
	{
		file=fopen(path,"r");

		if(file!=NULL)
		{
			parser_VacunadosFromText(file, pLista);
			retorno=1;
		}
		fclose(file);
	}
    return retorno;
}


int controller_listarVacunado(eVacunado* unVacunado)
{
	int retorno = 0;
	int id;
	char pais[100];
	int vac1dosis;
	int vac2dosis;
	int sinVacunar;

	if(unVacunado!=NULL)
	{
		if(vacunado_getId(unVacunado, &id) && vacunado_getPais(unVacunado, pais) && vacunado_getVac1(unVacunado, &vac1dosis) &&
		   vacunado_getVac2(unVacunado, &vac2dosis) && vacunado_getSinVacunar(unVacunado, &sinVacunar))
		{
			printf("| %-3d |  %-26s  |   %-5d  |    %-5d   |    %-5d   |\n", id, pais, vac1dosis, vac2dosis, sinVacunar);
		}
	}


	return retorno;
}


/** \brief Listar vacunados
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_listarVacunados(LinkedList* pLista)
{
	int retorno = 0;
	int largo = ll_len(pLista);

	if(pLista != NULL && largo > 0)
	{
		limpiarConsola();
		printf( "===========================================================================\n"
				"|                            ***LISTA PAISES***                           |\n"
				"===========================================================================\n"
				"| ID  |            PAIS              | VAC1DOSIS | VAC2DOSIS | SINVACUNAR |\n"
			    "---------------------------------------------------------------------------\n");

		for(int i=0; i < largo; i++)
		{
			controller_listarVacunado((eVacunado*) ll_get(pLista, i));
		}
		printf( "===========================================================================\n");
		retorno=1;
	}
    return retorno;
}

int asignarUnaDosis(LinkedList* listaPaises)
{
	int retorno = 0;
	if(listaPaises!=NULL)
	{
		ll_map(listaPaises, asignarVacAleatorio);
		retorno = 1;
	}
	return retorno;
}

void* asignarVacAleatorio(void* elemento)
{
	int vac1Dosis;
	eVacunado* auxVacunado = NULL;

	if(elemento!=NULL)
	{
		auxVacunado = (eVacunado*)elemento;
		vac1Dosis= ((rand() % (60 - 1 + 1)));
		vacunado_setVac1(auxVacunado, vac1Dosis);
	}

	return auxVacunado;
}

int asignarDosDosis(LinkedList* listaPaises)
{
	int retorno = 0;
	if(listaPaises!=NULL)
	{
		ll_map(listaPaises, asignarVac2Aleatorio);
		retorno = 1;
	}
	return retorno;
}

void* asignarVac2Aleatorio(void* elemento)
{
	int vac2Dosis;
	eVacunado* auxVacunado = NULL;

	if(elemento!=NULL)
	{
		auxVacunado = (eVacunado*)elemento;
		vac2Dosis= ((rand() % (40 - 1 + 1)));
		vacunado_setVac2(auxVacunado, vac2Dosis);
	}

	return auxVacunado;
}

int asignarNoVacunados(LinkedList* listaPaises)
{
	int retorno = 0;
	if(listaPaises!=NULL)
	{
		ll_map(listaPaises, asignarNoVacAleatorio);
		retorno = 1;
	}
	return retorno;
}

void* asignarNoVacAleatorio(void* elemento)
{
	int noVacunados;
	eVacunado* auxVacunado = NULL;
	int dosis1;
	int dosis2;

	if(elemento!=NULL)
	{
		auxVacunado = (eVacunado*)elemento;
		vacunado_getVac1(auxVacunado, &dosis1);
		vacunado_getVac2(auxVacunado, &dosis2);
		noVacunados = 100 - (dosis1 + dosis2);
		vacunado_setSinVacunar(auxVacunado, noVacunados);
	}

	return auxVacunado;
}

int filtrarExitosos(void* unVacunado)
{

	int retorno=0;
	eVacunado* auxVacunado;
	int segundaDosis;

	if(unVacunado!=NULL)
	{
		auxVacunado=(eVacunado*)unVacunado;
		vacunado_getVac2(auxVacunado,&segundaDosis);

		if(segundaDosis > 30)
		{
			retorno=1;
		}
	}
return retorno;
}

int filtrarAlHorno(void* unVacunado)
{

	int retorno=0;
	eVacunado* auxVacunado;
	int noVacunado;
	int unaDosis;
	int dosDosis;

	if(unVacunado!=NULL)
	{
		auxVacunado=(eVacunado*)unVacunado;
		vacunado_getSinVacunar(auxVacunado,&noVacunado);
		vacunado_getVac1(unVacunado, &unaDosis);
		vacunado_getVac2(unVacunado, &dosDosis);

		if(noVacunado > unaDosis && noVacunado>dosDosis)
		{
			retorno=1;
		}
	}
return retorno;
}


int controller_guardarVacunadosTexto(char* path , LinkedList* listaPaises)
{
	int retorno = 0;
	eVacunado* auxVacunado = NULL;
	int id;
	char pais[100];
	int vac1;
	int vac2;
	int sinVacunar;
	int tam;
	FILE* f=fopen(path,"w");

	tam=ll_len(listaPaises);

	if(path!=NULL && listaPaises!=NULL && f!=NULL)
	{
		fprintf(f,"id,pais,vac1dosis,vac2dosis,sinVacunar\n");

		for(int i=0;i<tam;i++)
		{
			auxVacunado=(eVacunado*)ll_get(listaPaises, i);
			vacunado_getId(auxVacunado, &id);
			vacunado_getPais(auxVacunado, pais);
			vacunado_getVac1(auxVacunado, &vac1);
			vacunado_getVac2(auxVacunado, &vac2);
			vacunado_getSinVacunar(auxVacunado, &sinVacunar);
			fprintf(f,"%d,%s,%d,%d,%d\n",id,pais,vac1,vac2,sinVacunar);
			retorno = 1;
		}
	}
	fclose(f);

    return retorno;
}

int ordenarVacunados(void* paisI, void* paisJ)
{
    int returnAux=0;
    eVacunado* vacunadoIndiceI;
    eVacunado* vacunadoIndicej;
    int auxVacunadoI;
    int auxVacunadoJ;

    if(paisI != NULL && paisJ != NULL)
    {
    	vacunadoIndiceI = (eVacunado*)paisI;
    	vacunadoIndicej = (eVacunado*)paisJ;

    	vacunado_getVac1(vacunadoIndiceI,&auxVacunadoI);
    	vacunado_getVac1(vacunadoIndicej,&auxVacunadoJ);

        if(auxVacunadoI < auxVacunadoJ)
        {
            returnAux=1;
        }

    }
    return returnAux;
}

int masCastigados(LinkedList* masCastigados)
{
	int retorno = 0;
	int tam;

	if(masCastigados != NULL)
	{
		limpiarConsola();
		tam = ll_len(masCastigados);
		printf( "===========================================================================\n"
				"|                          ***PAIS MAS CASTIGADO***                       |\n"
				"===========================================================================\n"
				"| ID  |            PAIS              | VAC1DOSIS | VAC2DOSIS | SINVACUNAR |\n"
				"---------------------------------------------------------------------------\n");
		for(int i=0; i<tam; i++)
		{
			controller_listarVacunado((eVacunado*)ll_get(masCastigados, 0));
			break;
		}
		printf("===========================================================================\n");
		retorno = 1;
	}

	return retorno;
}
