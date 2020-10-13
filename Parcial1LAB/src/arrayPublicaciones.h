/*
 * arrayEmployees.h
 *
 *  Created on: 30 sep. 2020
 *      Author: Juli
 */

#ifndef ARRAYPUBLICACIONES_H_
#define ARRAYPUBLICACIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#define PUBLICACIONES_QTY 1000

typedef struct
{
	int id;
	int clientId;
	int numDeRubro;
	char textoDelAviso[65];
	int estaPausada;
	int isEmpty;
}Publicaciones;

int initPublicaciones(Publicaciones* list, int len);

int findEmptyIndexPublicaciones(Publicaciones* list, int len, int *pIndex);
int addPublicacion(Publicaciones* list,int len, int clientId, int numDeRubro,char* textoDelAviso );
int findPublicacionById(Publicaciones* list, int len, int id);
int removePublicacion(Publicaciones* list, int len, int id);
int generateNewIdPublicaciones(void);
int pausarPublicacion(Publicaciones* list, int len, int id ,int* pClientId);
int reanudarPublicacion(Publicaciones* list, int len, int id, int* pClientId);
int erasePublicaciones(Publicaciones* list, int len, int clientId);

#endif /* ARRAYCLIENTS_H_ */
