/*
 * informes.c
 *
 *  Created on: 12 oct. 2020
 *      Author: Juli
 */

#include "arrayPublicaciones.h"
#include "arrayClients.h"
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

/**
 *  \brief imprime todas las publicaciones
 *  \param lista de publicaciones a imprimir
 *  \param longitud de la lista
 *  \return 0 exito -1 error
 */
int printPublicaciones(Publicaciones* list, int len)
{
	int retorno = -1;
	int allEmpty = 1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0)
			{
				printf("ID: %d\nID del cliente: %d\nNumero de Rubro: %d\nTexto del aviso: %s\nEsta Pausada?: ",list[i].id,list[i].clientId,list[i].numDeRubro,list[i].textoDelAviso);
				if(list[i].estaPausada == 1)
				{
					printf("SI.\n\n");
				}
				else
				{
					printf("NO.\n\n");
				}
				allEmpty=0;
			}
		}
		if(allEmpty ==1)
		{
			printf("No hay publicaciones en el sistema.\n");
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief imprime una sola publicacion
 *  \param lista de publicaciones
 *  \param index de la publicacion a imprimir
 */
void printSinglePublicacion(Publicaciones* list, int index)
{
	printf("ID: %d\nID del cliente: %d\nNumero de Rubro: %d\nTexto del aviso: %s\nEsta Pausada?: ",list[index].id,list[index].clientId,list[index].numDeRubro,list[index].textoDelAviso);
	if(list[index].estaPausada == 1)
	{
		printf("SI.\n\n");
	}
	else
	{
		printf("NO.\n\n");
	}
}

/**
 *  \brief Imprime la lista completa de clientes
 *  \param lista de cliente
 *  \param longitud del array de clientes
 *  \return 0 exito -1 error
 */
int printClients(Client* list, int len)
{
	int retorno = -1;
	int allEmpty = 1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0)
			{
				printf("ID: %d\nNombre: %s\nApellido: %s\nCuit: %s\nCantidad de publicaciones activas: %d\n\n",list[i].id,list[i].name,list[i].lastName,list[i].cuit,list[i].cantidadDeAnuncios);
				allEmpty=0;
			}
		}
		if(allEmpty ==1)
		{
			printf("No hay clientes en el sistema.\n");
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief imprime un solo cliente
 *  \param lista de clientes
 *  \param index del cliente a imprimir
 */
void printSingleClient(Client* list, int index)
{
	printf("ID: %d\nNombre: %s\nApellido: %s\nCuit: %s\nCantidad de publicaciones activas: %d\n",list[index].id,list[index].name,list[index].lastName,list[index].cuit,list[index].cantidadDeAnuncios);

}

/**
 *  \brief imprime todas las publicaciones que tienen un Id de cliente especifico
 *  \param lista de publicaciones
 *  /param longitud de la lista
 *  \param ID del cliente
 *  \return 0 exito -1 error
 */
int printPublicacionesById(Publicaciones* list, int len, int clientId)
{
	int retorno = -1;
	int allEmpty = 1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0 && list[i].clientId == clientId)
			{
				allEmpty=0;
				break;
			}
		}

		if(allEmpty == 0)
		{
			printf("Estas son las publicaciones del cliente:\n");
			for(int i=0;i<len;i++)
				{
					if(list[i].isEmpty == 0 && list[i].clientId == clientId)
					{
						printf("ID: %d\nID del cliente: %d\nNumero de Rubro: %d\nTexto del aviso: %s\nEsta Pausada?: ",list[i].id,list[i].clientId,list[i].numDeRubro,list[i].textoDelAviso);
						if(list[i].estaPausada == 1)
						{
							printf("SI.\n\n");
						}
						else
						{
							printf("NO.\n\n");
						}
					}
				}
		}
		else
		{
			printf("Este cliente no tenia publicaciones.\n");
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief Cuenta cuantos avisos pausados hay
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \return 0 exito -1 error
 */
int cantidadAvisosPausados(Publicaciones* list, int len)
{
	int retornar = -1;
	int contadorAvisosPausados =0;
	if(list != NULL && len>0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].estaPausada == 1)
			{
				contadorAvisosPausados++;
				retornar = 0;

			}
		}
	}
	if(retornar == -1)
	{
		printf("No hay ningun anuncio pausado!\n");
	}
	else
	{
		printf("Hay un total de %d avisos pausados.\n",contadorAvisosPausados);
	}
	return retornar;
}

/**
 *  \brief cuenta cuantas publicaciones tiene un id especifico
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \param id del cliente a buscar
 *  \param puntero a una direccion INT donde enviar el resultado
 *  \return 0 exito -1 error
 */
int contarPublicacionesById(Publicaciones* list, int len, int clientId, int* pContador)
{
	int retorno = -1;
	int contadorPublicaciones = 0;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0 && list[i].clientId == clientId)
			{
				contadorPublicaciones++;
			}
		}
		*pContador = contadorPublicaciones;
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief cuenta cuantas publicaciones tiene un rubro especifico
 *  \param lista de publicaciones
 *  \param longitud de la lista
 *  \param rubro a buscar
 *  \param puntero donde dejar el resultado
 *  \return 0 exito -1 error
 */
int contarPublicacionesByRubro(Publicaciones* list, int len, int rubro, int* pContador)
{
	int retorno = -1;
	int contadorRubro = 0;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0 && list[i].numDeRubro == rubro)
			{
				contadorRubro++;
			}
		}
		*pContador = contadorRubro;
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief cuenta cuantoss clientes hay en total (por id)
 *  \param lista de clientes
 *  \param longitud de la lista
 *  \return devuelve el resultado
 */
int contarCantidadClientes(Client* list, int len)
{
	int cantidadClientes = 0;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == 0 && list[i].id != 0)
			{
				cantidadClientes++;
			}
		}
	}
	return cantidadClientes;
}
