/*
 * informes.h
 *
 *  Created on: 12 oct. 2020
 *      Author: Juli
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include "arrayPublicaciones.h"
#include "arrayClients.h"
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

int printPublicaciones(Publicaciones* list, int len);
void printSinglePublicacion(Publicaciones* list,int index);
int printClients(Client* list, int len);
void printSingleClient(Client* list,int index);
int printPublicacionesById(Publicaciones* list, int len, int clientId);
int cantidadAvisosPausados(Publicaciones* list, int len);
int contarPublicacionesById(Publicaciones* list, int len, int clientId, int* pContador);
int contarPublicacionesByRubro(Publicaciones* list, int len, int rubro, int* pContador);
int contarCantidadClientes(Client* list, int len);

#endif /* INFORMES_H_ */
