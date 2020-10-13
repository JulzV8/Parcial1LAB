/*
 ============================================================================
 Name        : Parcial1LAB.c
 Author      : Julian Vallejos
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "arrayClients.h"
#include "arrayPublicaciones.h"
#include "informes.h"
#include "utn.h"

int main(void) {
	//INICIALIZO VARIABLES Y ARRAYS
	Client arrayClientes[CLIENT_QTY];
	initClients(arrayClientes,CLIENT_QTY);
	Publicaciones arrayPublicaciones[PUBLICACIONES_QTY];
	initPublicaciones(arrayPublicaciones,PUBLICACIONES_QTY);

	int selection = 0;
	char bufferName[51];
	char bufferLastName[51];
	char bufferCuit[51];
	char bufferTextoDelAviso[70];
	int bufferNumDeRubro;
	int bufferIdCliente;
	int bufferIdPublicaciones;
	int bufferIndex;
	int bufferIndex2;
	int bufferClienteConMasPublicaciones;
	int bufferContadorPublicaciones = 0;
	int bufferContadorPublicaciones2;
	int cantidadDeClientes = 0;
	int bufferRubro;
	int contadorRubro = 0;
	int contadorRubro2;
	int bufferRubroConMasPublicaciones;
	printf("Bienvenido!\n");

	//MENU PRINCIPAL
	while(selection != -1)
	{
		if(utn_getNumero(&selection,"Escriba un numero correspondiente a la accion deseada.\n"
				"1. Subir un cliente.\n"
				"2. Modificar un cliente.\n"
				"3. Borrar un cliente.\n"
				"4. Publicar.\n"
				"5. Pausar Publicacion.\n"
				"6. Reanudar Publicacion.\n"
				"7. Imprimir Clientes.\n"
				"8. Informar...\n"
				"9. Salir.","ERROR: Type a valid number from 1 to 5.\n",1,9,3)==0)
		{
			switch(selection)
			{
			//SUBA DE CLIENTES
				case 1:
					if(findEmptyIndexClients(arrayClientes,CLIENT_QTY,&bufferIndex)!=-1)
					{
						if ((utn_getStringAlfabetico(bufferName,sizeof(bufferName),"Ingrese el nombre del cliente","ERROR: Ingrese solo letras.",3)) == 0 &&
						(utn_getStringAlfabetico(bufferLastName,sizeof(bufferLastName),"Ingrese el apellido del cliente","ERROR: Ingrese solo letras.",3)) == 0 &&
						(utn_getStringCuit(bufferCuit,sizeof(bufferCuit),"Ingrese el cuit del cliente.","ERROR: Ingrese un Cuit valido (11 numeros).",3)) == 0 &&
						(addClient(arrayClientes,CLIENT_QTY,bufferName,bufferLastName,bufferCuit)!=0))
						{
							printf("No se pudo subir al cliente. Verifique los datos e intente denuevo.\n");
						}

					}
					break;
			//MODIFICAR CLIENTE
				case 2:
					if(utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente a modificar.","ERROR: Ingrese un numero entero.",0,INT_MAX,3) == 0)
					{
						bufferIndex = findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente);
						if(bufferIndex!=-1)
						{
							printf("Este es el cliente seleccionado:\n");
							printSingleClient(arrayClientes,bufferIndex);

							//SUBMENU 1
							while(selection !=-2)
							{
								if(utn_getNumero(&selection,"Que le gustaria modificar?.\n"
										"1. Nombre.\n"
										"2. Apellido.\n"
										"3. Cuit.\n"
										"4. Cambiar cliente seleccionado.\n"
										"5. Volver al menu principal.","ERROR: Ingrese un numero del 1 al 5.\n",1,5,3)==0)
								{
									switch(selection)
									{
									//MODIFICAR NOMBRE
										case 1:
											if(utn_getStringAlfabetico(bufferName,sizeof(bufferName),"Ingrese el nuevo nombre del cliente","ERROR: Ingrese solo letras.",3)==0)
											{
												strncpy(arrayClientes[bufferIndex].name,bufferName,sizeof(arrayClientes[bufferIndex].name));
												printf("Hecho!\n");
											}
											break;
										//MODIFICAR APELLIDO
										case 2:
											if(utn_getString(bufferLastName,sizeof(bufferLastName),"Ingrese el nuevo apellido del cliente","ERROR: Ingrese solo letras.",3)==0)
											{
												strncpy(arrayClientes[bufferIndex].lastName,bufferLastName,sizeof(arrayClientes[bufferIndex].lastName));
												printf("Hecho!\n");
											}
											break;
										//MODIFICAR CUIT
										case 3:
											if(utn_getStringCuit(bufferCuit,sizeof(bufferCuit),"Ingrese el nuevo cuit del cliente","ERROR: Ingrese un Cuit valido (11 numeros).",3)==0)
											{
												strncpy(arrayClientes[bufferIndex].cuit,bufferCuit,sizeof(arrayClientes[bufferIndex].cuit));
												printf("Hecho!\n");
											}
											break;
										//MODIFICAR CLIENTE SELECCIONADO
										case 4:
											utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente a modificar.","ERROR: Ingrese un numero entero.",0,INT_MAX,3);
											bufferIndex2 = findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente);
											if(bufferIndex2==-1)
											{
												printf("El ID seleccionado no ha cambiado.\n");
											}
											else
											{
												bufferIndex = bufferIndex2;
												printf("Este es el nuevo cliente seleccionado:\n");
												printSingleClient(arrayClientes,bufferIndex);
											}
											break;
										//VOLVER AL MENU PRINCIPAL
										case 5:
											selection = -2;
											break;

									}
								}
							}

						}
					}
					break;

				//VUELTA AL MENU PRINCIPAL
				//BORRAR CLIENTE
				case 3:
					if(utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente a borrar","ERROR: Type an integer number.",0,INT_MAX,3) == 0 && findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)!=-1)
					{
						printPublicacionesById(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdCliente);
						if(removeClient(arrayClientes,CLIENT_QTY,bufferIdCliente)==0)
						{
							erasePublicaciones(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdCliente);
						}
					}
					break;
				//SUBIR PUBLICACION
				case 4:
						if(findEmptyIndexPublicaciones(arrayPublicaciones,PUBLICACIONES_QTY,&bufferIndex)!=-1)
						{
							if ((utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente","ERROR: Ingrese un ID valido.",0,CLIENT_QTY,3)) != -1 &&
								(findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)) != -1 &&
								(utn_getNumero(&bufferNumDeRubro,"Ingrese el numero de rubro","ERROR: Ingrese un numero valido.",1,INT_MAX,3)) != -1 &&
								(utn_getString(bufferTextoDelAviso,sizeof(bufferTextoDelAviso),"Ingrese el texto del aviso.","ERROR: Ingrese un Texto de hasta 64 caracteres.",3))!= -1)
							{
								 addPublicacion(arrayPublicaciones,PUBLICACIONES_QTY, bufferIdCliente,bufferNumDeRubro,bufferTextoDelAviso);
								 arrayClientes[findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)].cantidadDeAnuncios++;

							}
							else
							{
								printf("La Publicacion no pudo subirse.\n");
							}
						}
					break;
				//PAUSAR PUBLICACION
				case 5:
						if(utn_getNumero(&bufferIdPublicaciones,"Ingrese el ID de la publicacion a pausar","ERROR: Ingrese un numero entero valido.",0,INT_MAX,3) == 0)
						{
							if(pausarPublicacion(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdPublicaciones,&bufferIdCliente)==0)
							{
								arrayClientes[findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)].cantidadDeAnuncios--;
							}
						}
					break;
				//REANUDAR PUBLICACION
				case 6:
					if(utn_getNumero(&bufferIdPublicaciones,"Ingrese el ID de la publicacion a renaudar","ERROR: Ingrese un numero entero valido.",0,INT_MAX,3) == 0)
						{
							if(reanudarPublicacion(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdPublicaciones,&bufferIdCliente)==0)
							{
								arrayClientes[findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)].cantidadDeAnuncios++;
							}
						}
					break;

				//IMPRIMIR CLIENTES
				case 7:
					printClients(arrayClientes,CLIENT_QTY);
					break;
				//INFORMAR
				//SUBMENU 2
				case 8:
					while(selection != -3)
					{
						if(utn_getNumero(&selection,"Que te gustaria saber?.\n"
									"1. Cliente con mas avisos.\n"
									"2. Cantidad de avisos pausados.\n"
									"3. Rubro con mas avisos.\n"
									"4. Volver al menu principal","ERROR: Ingrese un numero del 1 al 4.",1,4,3)==0)
						{
							switch(selection)
							{
							//INFORMAR CLIENTE CON MAS AVISOS
								case 1:
									bufferIndex2 =contarCantidadClientes(arrayClientes,CLIENT_QTY);
									while(cantidadDeClientes < bufferIndex2)
									{
										for(int i = 0; i < CLIENT_QTY; i++)
										{
											if(arrayClientes[i].isEmpty == 0 && arrayClientes[i].id != 0)
											{
												bufferIdCliente = arrayClientes[i].id;
												contarPublicacionesById(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdCliente,&bufferContadorPublicaciones2);
												if(bufferContadorPublicaciones < bufferContadorPublicaciones2)
												{
													bufferContadorPublicaciones=bufferContadorPublicaciones2;
													bufferClienteConMasPublicaciones = bufferIdCliente;
												}
												cantidadDeClientes++;
											}
										}
									}
									if(bufferContadorPublicaciones != 0)
									{
										printf("El cliente con mas publicaciones es:\n");
										printSingleClient(arrayClientes,findClientById(arrayClientes,CLIENT_QTY,bufferClienteConMasPublicaciones));
									}
									else
									{
										printf("No hay publicaciones.\n");
									}
									cantidadDeClientes =0;
									bufferContadorPublicaciones =0;
									break;
								//INFORMAR CANTIDAD DE AVISOS PAUSADOS
								case 2:
									cantidadAvisosPausados(arrayPublicaciones,PUBLICACIONES_QTY);
									break;
								//INFORMAR CANTIDAD DE PUBLICACIONES DEL RUBRO MAS USADO
								case 3:
										for(int i = 0; i < PUBLICACIONES_QTY; i++)
										{
											if(arrayPublicaciones[i].isEmpty == 0)
											{
												bufferRubro =arrayPublicaciones[i].numDeRubro;
												contarPublicacionesByRubro(arrayPublicaciones,PUBLICACIONES_QTY,bufferRubro,&contadorRubro2);
												if(contadorRubro < contadorRubro2)
												{
													contadorRubro=contadorRubro2;
													bufferRubroConMasPublicaciones = bufferRubro;
												}
											}
										}
										if(contadorRubro==0)
										{
											printf("No hay publicaciones.\n");
										}
										else
										{
											printf("El rubro con mas publicaciones es: %d\n",bufferRubroConMasPublicaciones);
										}
									contadorRubro2 =0;
									bufferRubroConMasPublicaciones =0;
									break;
								//VOLVER AL MENU PRINCIPAL
								case 4:
									selection = -3;
									break;
							}
						}

					}

					break;


				//VUELTA AL MENU PRINCIPAL
				//SALIR/
				case 9:
					if(utn_getNumero(&selection,"Estas seguro que deseas salir?\n"
							"Escribe: 1=SI//0=NO","ERROR. Escribe 1 o 2.",0,1,3) ==0 && selection == 1)
					{
						printf("Gracias por usarme!");
						selection = -1;
					}
					break;
			}
		}
		else
		{
			return EXIT_FAILURE;
		}
	}


	return EXIT_SUCCESS;
}
