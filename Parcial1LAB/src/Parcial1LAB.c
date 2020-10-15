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

	//altaForzadaCliente(arrayClientes);

	int selection = 0;
	char bufferName[51];
	char bufferLastName[51];
	char bufferCuit[13];
	char bufferTextoDelAviso[65];
	int bufferNumDeRubro;
	int bufferIdCliente;
	int bufferIdPublicaciones;
	int bufferIndex;
	int bufferIndex2;
	int idClienteMasPublicaciones;
	int numMaximoPublicaciones;
	int bufferContadorPublicaciones;
	int contadorMaxRubro;
	int bufferContadorRubro;
	int maxRubro;
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
					if(utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente a modificar.","ERROR: Ingrese un numero entero.",1,INT_MAX,3) == 0)
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
											utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente a modificar.","ERROR: Ingrese un numero entero.",1,INT_MAX,3);
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
					if(utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente a borrar:","ERROR. Ingrese un id valido.",1,INT_MAX,3) == 0 && findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)!=-1)
					{
						printf("Este es el Cliente a borrar:\n");
						printSingleClient(arrayClientes,findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente));
						printPublicacionesById(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdCliente);
						utn_getNumero(&selection,"Seguro desea borrarlo? Ingrese: 1 = SI// 0 = NO","ERROR: Ingrese 0 o 1.",0,1,3);
						if(selection==1)
						{
							erasePublicaciones(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdCliente);
							removeClient(arrayClientes,CLIENT_QTY,bufferIdCliente);
						}
						else
						{
							printf("El cliente no se borró.\n");
						}
					}
					break;
				//SUBIR PUBLICACION
				case 4:
						if(findEmptyIndexPublicaciones(arrayPublicaciones,PUBLICACIONES_QTY,&bufferIndex)!=-1)
						{
							if ((utn_getNumero(&bufferIdCliente,"Ingrese el ID del cliente","ERROR: Ingrese un ID valido.",1,CLIENT_QTY,3)) != -1 &&
								(findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)) != -1 &&
								(utn_getNumero(&bufferNumDeRubro,"Ingrese el numero de rubro","ERROR: Ingrese un numero valido.",1,INT_MAX,3)) != -1 &&
								(utn_getString(bufferTextoDelAviso,sizeof(bufferTextoDelAviso),"Ingrese el texto del aviso.","ERROR: Ingrese un Texto de hasta 64 caracteres.",3))!= -1)
							{
								 addPublicacion(arrayPublicaciones,PUBLICACIONES_QTY, bufferIdCliente,bufferNumDeRubro,bufferTextoDelAviso);
								 arrayClientes[findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)].cantidadDeAnunciosActivos++;

							}
							else
							{
								printf("La Publicacion no pudo subirse.\n");
							}
						}
					break;
				//PAUSAR PUBLICACION
				case 5:
						if(utn_getNumero(&bufferIdPublicaciones,"Ingrese el ID de la publicacion a pausar","ERROR: Ingrese un numero entero valido.",1,INT_MAX,3) == 0)
						{
							if(pausarPublicacion(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdPublicaciones,&bufferIdCliente)==0)
							{
								arrayClientes[findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)].cantidadDeAnunciosActivos--;
							}
						}
					break;
				//REANUDAR PUBLICACION
				case 6:
					if(utn_getNumero(&bufferIdPublicaciones,"Ingrese el ID de la publicacion a renaudar","ERROR: Ingrese un numero entero valido.",1,INT_MAX,3) == 0)
						{
							if(reanudarPublicacion(arrayPublicaciones,PUBLICACIONES_QTY,bufferIdPublicaciones,&bufferIdCliente)==0)
							{
								arrayClientes[findClientById(arrayClientes,CLIENT_QTY,bufferIdCliente)].cantidadDeAnunciosActivos++;
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
									"4. Cliente con mas avisos activos.\n"
									"5. Cliente con mas avisos pausados.\n"
									"6. Volver al menu principal","ERROR: Ingrese un numero del 1 al 4.",1,6,3)==0)
						{
							switch(selection)
							{
							//INFORMAR CLIENTE CON MAS AVISOS
								case 1:
									for(int i = 0; i < CLIENT_QTY; i++)
									{
										if(i==0 ||(arrayClientes[i].isEmpty == 0 && arrayClientes[i].id != 0))
										{
											bufferIdCliente = arrayClientes[i].id;
											bufferContadorPublicaciones =contarPublicacionesById(arrayPublicaciones,PUBLICACIONES_QTY,arrayClientes[i].id);
											if(i ==0 ||numMaximoPublicaciones < bufferContadorPublicaciones)
											{
												numMaximoPublicaciones=bufferContadorPublicaciones;
												idClienteMasPublicaciones = arrayClientes[i].id;
											}
										}
									}
									if(numMaximoPublicaciones != 0)
									{
										printf("El cliente con mas publicaciones es:\n");
										printSingleClient(arrayClientes,findClientById(arrayClientes,CLIENT_QTY,idClienteMasPublicaciones));
									}
									else
									{
										printf("No hay publicaciones.\n");
									}
									break;
								//INFORMAR CANTIDAD DE AVISOS PAUSADOS
								case 2:
									cantidadAvisosPausados(arrayPublicaciones,PUBLICACIONES_QTY);
									break;
								//INFORMAR CANTIDAD DE PUBLICACIONES DEL RUBRO MAS USADO
								case 3:
										for(int i = 0; i < PUBLICACIONES_QTY; i++)
										{
											if(i== 0 || arrayPublicaciones[i].isEmpty == 0)
											{
												bufferContadorRubro =contarPublicacionesByRubro(arrayPublicaciones,PUBLICACIONES_QTY,arrayPublicaciones[i].numDeRubro);
												if(i==0 ||contadorMaxRubro < bufferContadorRubro)
												{
													contadorMaxRubro=bufferContadorRubro;
													maxRubro = arrayPublicaciones[i].numDeRubro;
												}
											}
										}
										if(contadorMaxRubro==0)
										{
											printf("No hay publicaciones.\n");
										}
										else
										{
											printf("El rubro con mas publicaciones es: %d\n",maxRubro);
										}
									break;

								case 4:
									clienteConMasPublicacionesActivas(arrayClientes,CLIENT_QTY);
									break;
								case 5:
									for(int i = 0; i < CLIENT_QTY; i++)
									{
										if(i==0 ||(arrayClientes[i].isEmpty == 0 && arrayClientes[i].id != 0))
										{
											bufferIdCliente = arrayClientes[i].id;
											bufferContadorPublicaciones =contarPublicacionesPausadasById(arrayPublicaciones,PUBLICACIONES_QTY,arrayClientes[i].id);
											if(i ==0 ||numMaximoPublicaciones < bufferContadorPublicaciones)
											{
											numMaximoPublicaciones=bufferContadorPublicaciones;
											idClienteMasPublicaciones = arrayClientes[i].id;
											}
										}
									}
									if(numMaximoPublicaciones != 0)
									{
											printf("El cliente con mas publicaciones pausadas es el siguiente (Con %d publicaciones):\n",numMaximoPublicaciones);
											printSingleClient(arrayClientes,findClientById(arrayClientes,CLIENT_QTY,idClienteMasPublicaciones));

									}
									else
									{
											printf("No hay publicaciones.\n");
									}
									break;

									//VOLVER AL MENU PRINCIPAL
								case 6:
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
