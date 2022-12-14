/*
 * vacunados.c
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

eVacunado* vacunado_new()
{
	eVacunado* v = (eVacunado*) malloc(sizeof(eVacunado));
	    if(v != NULL)
	    {
	        v->dosis = 0;
	        *(v->pais) = '\0';;
	        v->vac1dosis = 0;
	        v->vac2dosis = 0;
	        v->sinVacunar = 0;
	    }

	    return v;
}


eVacunado* vacunado_newParametros(char* idStr,char* pais,char* vac1Str, char* vac2Str, char* sinVacunarStr)
{
	eVacunado* v = vacunado_new();
	    if(v != NULL)
	    {
	        if(!(vacunado_setId(v, atoi(idStr)) &&
	        vacunado_setPais(v, pais) &&
			vacunado_setVac1(v,atoi(vac1Str)) &&
			vacunado_setVac2(v,atoi(vac2Str)) &&
			vacunado_setSinVacunar(v, atoi(sinVacunarStr))))
	        {
	            free(v);
	            v = NULL;
	        }
	    }

	return v;
}

int vacunado_setId(eVacunado* this,int dosis)
{
	int retorno = 0;

	if(this!=NULL && dosis>=1)
	{
		this->dosis = dosis;
		retorno = 1;
	}

	return retorno;
}
int vacunado_getId(eVacunado* this,int* pDosis)
{
	int retorno = 0;

	if(this!=NULL && pDosis!=NULL)
	{
		*pDosis = this->dosis;
		retorno = 1;
	}
	return retorno;
}

int vacunado_setPais(eVacunado* this, char* pais)
{
	int retorno=0;
	int largoCad;
	char auxCad[200];

	largoCad = strlen(pais);

	if(this !=NULL && pais!=NULL && largoCad<100)
	{
		strcpy(auxCad, pais);
		//strlwr(auxCad);
		auxCad[0]=toupper(auxCad[0]);
		strcpy(this->pais, auxCad);
		retorno = 1;
	}

	return retorno;
}

int vacunado_getPais(eVacunado* this,char* pais)
{
	int retorno=0;

	if(this!=NULL && pais!=NULL)
	{
		strcpy(pais, this-> pais);
		retorno=1;
	}

	return retorno;
}

int vacunado_setVac1(eVacunado* this,int dosis)
{
	int retorno = 0;

	if(this!=NULL)
	{
		this->vac1dosis = dosis;
		retorno = 1;
	}

	return retorno;
}
int vacunado_getVac1(eVacunado* this,int* pDosis)
{
	int retorno = 0;

	if(this!=NULL && pDosis!=NULL)
	{
		*pDosis = this->vac1dosis;
		retorno = 1;
	}
	return retorno;
}

int vacunado_setVac2(eVacunado* this,int dosis)
{
	int retorno = 0;

	if(this!=NULL)
	{
		this->vac2dosis = dosis;
		retorno = 1;
	}

	return retorno;
}
int vacunado_getVac2(eVacunado* this,int* pDosis)
{
	int retorno = 0;

	if(this!=NULL && pDosis!=NULL)
	{
		*pDosis = this->vac2dosis;
		retorno = 1;
	}
	return retorno;
}

int vacunado_setSinVacunar(eVacunado* this,int dosis)
{
	int retorno = 0;

	if(this!=NULL)
	{
		this->sinVacunar = dosis;
		retorno = 1;
	}

	return retorno;
}
int vacunado_getSinVacunar(eVacunado* this,int* pDosis)
{
	int retorno = 0;

	if(this!=NULL && pDosis!=NULL)
	{
		*pDosis = this->sinVacunar;
		retorno = 1;
	}
	return retorno;
}
