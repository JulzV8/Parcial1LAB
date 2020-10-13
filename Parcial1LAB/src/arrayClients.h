/*
 * arrayEmployees.h
 *
 *  Created on: 30 sep. 2020
 *      Author: Juli
 */

#ifndef ARRAYCLIENTS_H_
#define ARRAYCLIENTS_H_
#define CLIENT_QTY 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

typedef struct
{
	int id;
	char name[51];
	char lastName[51];
	char cuit[12];
	int isEmpty;
	int cantidadDeAnuncios;
}Client;

int initClients(Client* list, int len);

int findEmptyIndexClients(Client* list, int len, int *pIndex);
int addClient(Client* list,int len, char* name, char* lastName,char* cuit );
int findClientById(Client* list, int len, int id);
int EncontrarClienteConMasPublicaciones(Client* list, int len, int* pIndex);
int removeClient(Client* list, int len, int id);
int generateNewIdClients(void);
int orderClientsByLastName(Client* list,int len);


#endif /* ARRAYCLIENTS_H_ */
