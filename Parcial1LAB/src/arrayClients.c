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
		list[freeIndex].cantidadDeAnuncios=0;
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
	int bufferIndex=findClientById(list,len,id);
	if(list != NULL && len > 0 && id > 0)
	{
		if(bufferIndex>-1 && list[bufferIndex].isEmpty==0)
		{
			list[bufferIndex].isEmpty=1;
			retornar = 0;
			printf("Hecho!\n");
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

void altaForzadaCliente(Client* list)
{
	list[0].id=1;
	strcpy(list[0].name,"Julian");
	strcpy(list[0].lastName,"Vallejos");
	strcpy(list[0].cuit,"20418932520");
	list[0].isEmpty=0;
	list[0].cantidadDeAnuncios=0;

	list[1].id=2;
	strcpy(list[1].name,"Jose");
	strcpy(list[1].lastName,"Garcia");
	strcpy(list[1].cuit,"201234567890");
	list[1].isEmpty=0;
	list[1].cantidadDeAnuncios=0;

	list[2].id=3;
	strcpy(list[2].name,"Pepe");
	strcpy(list[2].lastName,"Sech");
	strcpy(list[2].cuit,"148562365412");
	list[2].isEmpty=0;
	list[2].cantidadDeAnuncios=0;

	list[3].id=4;
	strcpy(list[3].name,"Miriam");
	strcpy(list[3].lastName,"Rodriguez");
	strcpy(list[3].cuit,"891236549875");
	list[3].isEmpty=0;
	list[3].cantidadDeAnuncios=0;

	list[4].id=5;
	strcpy(list[4].name,"Julio");
	strcpy(list[4].lastName,"Davides");
	strcpy(list[4].cuit,"521236859452");
	list[4].isEmpty=0;
	list[4].cantidadDeAnuncios=0;

}
