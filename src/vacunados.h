/*
 * vacunados.h
 *
 *  Created on: 14 dic. 2022
 *      Author: mac2020
 */

#ifndef VACUNADOS_H_
#define VACUNADOS_H_


typedef struct
{
	int dosis;
	char pais[100];
	int vac1dosis;
	int vac2dosis;
	int sinVacunar;
}eVacunado;

#endif /* VACUNADOS_H_ */

eVacunado* vacunado_new();

eVacunado* vacunado_newParametros(char* idStr,char* pais,char* vac1Str, char* vac2Str, char* sinVacunarStr);

int vacunado_setId(eVacunado* this,int id);

int vacunado_getId(eVacunado* this,int* pId);

int vacunado_setPais(eVacunado* this, char* pais);

int vacunado_getPais(eVacunado* this,char* pais);

int vacunado_setVac1(eVacunado* this,int dosis);

int vacunado_getVac1(eVacunado* this,int* pDosis);

int vacunado_setVac2(eVacunado* this,int dosis);

int vacunado_getVac2(eVacunado* this,int* pDosis);

int vacunado_setSinVacunar(eVacunado* this,int dosis);

int vacunado_getSinVacunar(eVacunado* this,int* pDosis);

