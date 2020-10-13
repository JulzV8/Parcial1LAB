/*
 * arrayEmployees.c
 *
 *  Created on: 30 sep. 2020
 *      Author: Juli
 */

#include "arrayPublicaciones.h"
#include "informes.h"

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

/**
 *  \brief inicializa todas las publicaciones
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \return 0 exito -1 error
 */
int initPublicaciones(Publicaciones* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = 1;
			list[i].id = 0;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief encuentra el index libre mas bajo
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \return 0 exito -1 error
 */
int findEmptyIndexPublicaciones(Publicaciones* list, int len, int *pIndex)
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
 *  \brief busca una publicacion por ID y devuelve su index
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \return 0 devuelve el index
 */
int findPublicacionById(Publicaciones* list, int len, int id)
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
  *  \brief Añade una publicacion nueva
  *  \param lista de publicaciones
  *  \param longitud de la lista
  *  \param ID del cliente
  *  \param numero de rubro
  *  \param texto del aviso
  *  \return 0 exito -1 error
  */int addPublicacion(Publicaciones* list,int len, int clientId, int numDeRubro,char* textoDelAviso )
{
	int retorno = -1;
	if(list 	!= NULL &&
	   len 		>	0 	&&
	   clientId > 	0	&&
	   numDeRubro > 0	&&
	   strlen(textoDelAviso)!= 0)
	{
		int freeIndex;
		int newId = generateNewIdPublicaciones();
		findEmptyIndexPublicaciones(list,len,&freeIndex);
		list[freeIndex].id=newId;
		list[freeIndex].clientId=clientId;
		list[freeIndex].numDeRubro=numDeRubro;
		strcpy(list[freeIndex].textoDelAviso,textoDelAviso);
		list[freeIndex].isEmpty=0;
		list[freeIndex].estaPausada=0;
		printf("Publicacion añadida con exito, con un ID asignado de %d.\n",newId);
		retorno = 0;
	}
	return retorno;
}



  /**
   *  \brief Pausa una publicacion buscandola por ID y devuelve el id del cliente
   *  \param lista de publicaciones
   *  \param longitud de la lista
   *  \param id de la publicacion
   * \param puntero donde enviar el id del cliente
   *  \return 0 exito -1 error
   */
  int pausarPublicacion(Publicaciones* list, int len, int id, int* pClientId)
{
	int retornar = -1;
	int bufferConfirm;
	int bufferIndex=findPublicacionById(list,len,id);
	if(list != NULL && len > 0 && id > 0)
	{
		if(bufferIndex>-1 && list[bufferIndex].isEmpty==0 && list[bufferIndex].estaPausada==0)
		{
			printf("Este es la publicacion seleccionada:\n");
			printSinglePublicacion(list,bufferIndex);
			utn_getNumero(&bufferConfirm,"Estas seguro que deseas Pausarla?\nIngrese: 1=SI//0=NO","ERROR. Ingrese 0 o 1.",0,1,3);
			if(bufferConfirm==1)
			{
				list[bufferIndex].estaPausada=1;
				*pClientId = list[bufferIndex].clientId;
				retornar = 0;
				printf("Hecho!\n");
			}
		}
		else
		{
			printf("Esta publicacion ya esta pausada.\n");
		}
	}
	return retornar;
}

  /**
   *  \brief Reanuda una publicacion buscandola por ID y devuelve el id del cliente
   *  \param lista de publicaciones
   *  \param longitud de la lista
   *  \param id de la publicacion
   * \param puntero donde enviar el id del cliente
   *  \return 0 exito -1 error
   */
int reanudarPublicacion(Publicaciones* list, int len, int id, int* pClientId)
{
	int retornar = -1;
	int bufferConfirm;
	int bufferIndex=findPublicacionById(list,len,id);
	if(list != NULL && len > 0 && id > 0)
	{
		if(bufferIndex>-1 && list[bufferIndex].isEmpty==0 && list[bufferIndex].estaPausada==1)
		{
			printf("Este es la publicacion seleccionada:\n");
			printSinglePublicacion(list,bufferIndex);
			utn_getNumero(&bufferConfirm,"Estas seguro que deseas Reanudarla?\nIngrese: 1=SI//0=NO","ERROR. Ingrese 0 o 1.",0,1,3);
			if(bufferConfirm==1)
			{
				list[bufferIndex].estaPausada=0;
				*pClientId =list[bufferIndex].clientId;
				retornar = 0;
				printf("Hecho!\n");
			}
		}
		else
		{
			printf("Esta publicacion no esta pausada.\n");
		}
	}
	return retornar;
}

/**
 *  \brief Genera un id nuevo
 */
int generateNewIdPublicaciones(void)
{
    static int id=0;
    id = id+1;
    return id;
}

/**
 *  \brief Borra todas las publicaciones de un cliente
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \param id del cliente
 *  \return 0 exito -1 error
 */
int erasePublicaciones(Publicaciones* list, int len, int clientId)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0 && list[i].clientId == clientId)
			{
				list[i].isEmpty = 1;
				list[i].clientId= 0;
			}
		}
	}
	return retorno;
}


