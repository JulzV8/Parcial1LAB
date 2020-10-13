/*
 * arrayEmployees.c
 *
 *  Created on: 30 sep. 2020
 *      Author: Juli
 */

#include "arrayClients.h"
#include "informes.h"
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

/**
 *  \brief Inicializa la lista de clientes
 *  \param Lista de clientes
 *  \param longitud de la lista
 *  \return 0 exito -1 error
 */
int initClients(Client* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = 1;
			list[i].cantidadDeAnuncios=0;
			list[i].id = 0;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief encuentra el index libre mas bajo
 *  \param lista de clientes
 *  \param longitud de la lista
 *  \return 0 exito -1 error
 */
int findEmptyIndexClients(Client* list, int len, int *pIndex)
{
	int retornar = -1;
	if(list != NULL && pIndex != NULL && len>0)
	{
		for(int i = 0; i < len; i++)
		{

			if(list[i].isEmpty == 1)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	if(retornar == -1)
	{
		printf("ERROR: No hay ningun espacio vacio!\n");
	}
	return retornar;
}

/**
 *  \brief busca un cliente por ID y devuelve su index
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \return devuelve el index
 */
int findClientById(Client* list, int len, int id)
{
	int retornar = -1;
	if(list != NULL && id > 0 && len>0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].id == id)
			{
				return i;
			}
		}
	}
	printf("Este ID esta vacio.\n");
	return retornar;
}

/**
 *  \brief Añade un cliente nuevo
 *  \param lista de clientes
 *  \param longitud de la lista
 *  \param nombre del cliente
 *  \param apellido del cliente
 *  \param numero de cuit
 *  \return 0 exito -1 error
 *  */
int addClient(Client* list,int len, char* name, char* lastName,char* cuit )
{
	int retorno = -1;
	if(list 	!= NULL &&
	   len 		>	0 	&&
	   strlen(name)!= 0 &&
	   strlen(lastName)!= 0 &&
	   strlen(cuit)!= 0)
	{
		int freeIndex;
		int newId = generateNewIdClients();
		findEmptyIndexClients(list,len,&freeIndex);
		list[freeIndex].id=newId;
		strcpy(list[freeIndex].name,name);
		strcpy(list[freeIndex].lastName,lastName);
		strcpy(list[freeIndex].cuit,cuit);
		list[freeIndex].isEmpty=0;
		printf("Cliente añadido con exito, con un ID asignado de %d.\n",newId);
		retorno = 0;
	}
	return retorno;
}


/**
   *  \brief Pone el estado isEmpty de un cliente en 1
   *  \param lista de clientes
   *  \param longitud de la lista
   *  \param id del cliente
   *  \return 0 exito -1 error
   */
int removeClient(Client* list, int len, int id)
{
	int retornar = -1;
	int bufferConfirm;
	int bufferIndex=findClientById(list,len,id);
	if(list != NULL && len > 0 && id > 0)
	{
		if(bufferIndex>-1 && list[bufferIndex].isEmpty==0)
		{
			printf("Este es el cliente seleccionado:\n");
			printSingleClient(list,bufferIndex);
			utn_getNumero(&bufferConfirm,"Estas seguro que deseas eliminarlo?\nIngrese: 1=SI//0=NO","ERROR. Ingrese 0 o 1.",0,1,3);
			if(bufferConfirm==1)
			{
				list[bufferIndex].isEmpty=1;
				retornar = 0;
				printf("Hecho!\n");
			}
		}
	}
	return retornar;
}

/**
 *  \brief genera un id nuevo
 *  \return devuelve el id creado
 */
int generateNewIdClients(void)
{
    static int id=0;
    id = id+1;
    return id;
}

