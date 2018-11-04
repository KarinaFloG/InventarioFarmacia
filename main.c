/**
@file main.c
@brief Archivo que contiene Driver Program-Menu
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "ADT_Lote.h"
#include "ADT_Medicamento.h"
#include "DLL_Medicamento.h"
#include "Inventario.h"
#include "Bool.h"

int menu();
void Nuevo_Lote(DLL * inventario);
void Nuevo_Medicamento(DLL * inventario);
void Mayusculas(char * cadena);
void Eliminar_Medicamento(DLL * inventario);
void Ventas(DLL * inventario);
void Informacion_Medicamento(DLL * inventario);
void Medicamento_Alerta(DLL * inventario);

int main(){

  system("clear");
  printf ( "\t----------------------\n"
        "\t|     INVENTARIO     |\n"
        "\t ---------------------\n");
  DLL * inventario=DLL_Create();
  if(!Extraccion(inventario)){
    printf("\n\nERROR FATAL\n" );
    DLL_Destroy(inventario);
    assert(0);
  }

  if(Caducidad(inventario)){
    char aler;
    printf("Lotes en alerta  (Codigo del lote,Nombre del medicamento,Dias para que caduque):\n\n" );
    system("more Alerta.csv");
    printf("\n\t¿Desea borrar los productos en alerta [S,N] ? : ");
    scanf("%c",&aler);
    Mayusculas(&aler);
    if(aler=='S'){
      if(!Remove_ProductoCaducado(inventario)){
        printf("\n\nERROR FATAL\n" );
        DLL_Destroy(inventario);
        assert(0);
      }

      if(!Modificar(inventario)){
        printf("\n\nERROR FATAL\n" );
        DLL_Destroy(inventario);
        assert(0);
      }
    }
  }

  while(1){
    system("clear");
    int opcion = menu ();
    switch (opcion) {
      case 1:
      printf ("\tSaliendo...\n");
        return 0;


      case 2:
        printf("Imprimir Inventario\n");
        Imprimir_Inventario(inventario);
        getchar();
        getchar();
        break;

      case 3:
        printf("\tNuevo Lote\n\n" );
        getchar();
        Nuevo_Lote(inventario);
        printf("\tOperacion terminada\n");
        printf("\tPresione enter para continuar.\n");
		    getchar();
        getchar();
        break;


      case 4:
        printf("\tNuevo medicamento\n\n" );
        getchar();
        Nuevo_Medicamento(inventario);
        printf("\tOperacion terminada\n");
        printf("\tPresione enter para continuar.\n");
		    getchar();
        getchar();

        break;

      case 5:
        printf("\tEliminar medicamento\n\n");
        getchar();
        Eliminar_Medicamento(inventario);
        printf("\tOperacion terminada\n");
        printf("\tPresione enter para continuar.\n");
		    getchar();
        getchar();

        break;

      case 6:
        printf("\tVentas\n");
        getchar();
        Ventas(inventario);
        printf("\tOperacion terminada\n");
        printf("\tPresione enter para continuar.\n");
        getchar();
        getchar();

        break;

      case 7:
        printf("\tInformacion de un medicamento\n\n");
        getchar();
        Informacion_Medicamento(inventario);
        getchar();
        getchar();
        break;

      case 8:
        printf("\tMedicamentos en alerta \n\n" );
        getchar();
        Medicamento_Alerta(inventario);
        printf("\tOperacion terminada\n");
        printf("\tPresione enter para continuar.\n");
        getchar();
        getchar();
        break;

      }

      if(!Modificar(inventario)){
      printf("\tERROR FATAL: NO SE PUDO MODIFICAR EL ARCHIVO\n");
      assert(0);
    }
  }
  return 0;
}

int menu(){
	char opcion;
  int res;

	do {
		printf ("\t----------------------\n"
					"\t|     INVENTARIO     |\n"
					"\t ---------------------\n"
					"\t¿Que desea hacer?\n"
					"\tOpciones:\n"
					"\t\t1 -- Salir\n"
					"\t\t2 -- Imprimir inventario\n"
					"\t\t3 -- Ingresar lote\n"
          "\t\t4 -- Nuevo medicamento\n"
          "\t\t5 -- Eliminar medicamento\n"
          "\t\t6 -- Ventas\n"
          "\t\t7 -- Información de un medicamento\n"
          "\t\t8 -- Eliminar medicamento en alerta\n"

					"\tSu opcion>  ");

		scanf ("%c", &opcion);
    res = atoi(&opcion);//para evitar errores de lectura de caracteres alfabeticos

    if(res < 0 || res > 8){
      printf("\n\nOpcion Invalida\n" );
    }
	} while (res < 0 || res > 8);
	printf ("\n");
	return res;

}

void Nuevo_Lote(DLL * inventario){

  char nombre[32];
  Node* aux= FALSE;
  if(!aux)
	{
    printf("\t>Ingrese el nombre del medicamento: " );
    scanf("%[^\n]",nombre);

    Mayusculas(nombre);
    aux=DLL_Search(inventario, nombre);
    if(!aux)
	{
		printf("\tERROR: El medicamento no existe\n\tIntente de nuevo\n");;
		return;
	}
  }

  if(Medicamento_GetLote2(aux->medicamento)){
    printf("\tERROR: Se alcanzo el maximo de lotes para este medicamento.\n");
	 return;
  }
  Lote * lote=Lote_Create();
  printf("\t>Ingrese la cantidad de productos del lote: ");
  scanf("%d",&lote->cantidad );
  printf("\t>Ingrese el codigo de barras: ");
  scanf("%s",lote->codigo);
  printf("\t>Ingrese la fecha de caducidad (dd/mm/aa): " );
  scanf("%s", lote->caducidad);

  if(!Insertar_Lote(aux,lote)){
    printf("\tERROR: No fue posible ingresar el lote al inventario.\n");
	  getchar();
  }

}

void Nuevo_Medicamento(DLL * inventario){
  char res;
	char nombre[15];
	float precio;

	printf("\t>Ingresa el nombre medicamento: ");
	scanf("%[^\n]", nombre);
  Mayusculas(nombre);
	Node *tmp = DLL_Search (inventario , nombre);
	if(!tmp)
	{
		Medicamento * aux = Medicamento_Create();
		Medicamento_SetNombre(aux,nombre );

		printf("\t>Ingresa el precio: ");
		scanf("%f",&precio);
		Medicamento_SetPrecio(aux,precio);

		printf("\t>Indique si el medicamento es controlado [S/N]:");
    getchar();
  	scanf("%c",&res);

  	if(res=='S'){ Medicamento_SetControl(aux, TRUE); }

		if(!Insertar_Medicamento(inventario,aux)){
    		printf("\tERROR: No fue posible ingresar el medicamento.\n" );
    		return;
  		}
	}
	else{
		printf("\tERROR: Ya existe el medicamento.\n");
	}
}

void Eliminar_Medicamento(DLL * inventario){

  char conf;
  char nombre[32];

  printf ("\t¿Que medicamento desea eliminar?: ");
  scanf ("%[^\n]", nombre);
  Mayusculas(nombre);
  getchar();

  Node * tmp=DLL_Search(inventario,nombre);

  if(tmp){

    if (Medicamento_GetLote1(tmp->medicamento)){
      printf ("\tSi se encontro el medicamento, puede que aun contenga lotes\n");
      printf ("\t¿Seguro desea eliminarlo [S/N]?\n\n\t");
      scanf ("%c", &conf);
      Mayusculas(&conf);

      if (conf == 'S'){
        Remover_Med(inventario,tmp);
      }
    }
    else{ Remover_Med(inventario,tmp); }
  }

}

void Ventas(DLL * inventario){


  int cantidad;
  char res;
  char nombre[32];

  do {
    printf("\n\t>Ingrese el nombre del medicamento: ");
    scanf("%[^\n]", nombre);
    Mayusculas(nombre);
    Node* tmp =  DLL_Search (inventario , nombre);
    if (!tmp){
      printf("\n\tNo existe medicamento\n");
    }
    else{
      printf("\t>Cantidad: ");
      scanf("%d", &cantidad);

      if (Remover_Productos(inventario, tmp->medicamento, cantidad)){
        printf("\n\tRegistro realizado\n");
      }
      else{
        printf("\n\tImposible realizar registro de ventas\n");
      }
    }

    getchar();
    printf("\t¿Hay mas ventas [S/N]?: ");
    scanf("%c",&res);
    Mayusculas(&res);
    getchar();

  } while ('S' == res);

}

void Informacion_Medicamento(DLL * inventario){

  char nombre[32];
  printf("\t>Ingrese el nombre del medicamento: ");
  scanf("%[^\n]", nombre);
  Mayusculas(nombre);
  Node* tmp =  DLL_Search (inventario , nombre);
  if (!tmp){
    printf("\n\tNo existe medicamento\n");
  }
  else{
    Medicamento_Print(tmp->medicamento);
  }
}

void Medicamento_Alerta(DLL * inventario){


  if(Caducidad(inventario)){
    char aler;
    printf("Lotes en alerta  (Codigo del lote,Nombre del medicamento,Dias para que caduque):\n\n" );
    system("more Alerta.csv");
    printf("\n\t¿Desea borrar los productos en alerta [S,N] ? : ");
    scanf("%c",&aler);
    Mayusculas(&aler);
    if(aler=='S'){
      if(!Remove_ProductoCaducado(inventario)){
        printf("\n\nERROR FATAL\n" );
        DLL_Destroy(inventario);
        assert(0);
      }

    }
  }
  else{printf("\n\t\tNo hay medicamentos en alerta\n");}

}
void Mayusculas(char * cadena){

  for(size_t i=0;i<strlen(cadena);i++){
    cadena[i]=toupper(cadena[i]);
  }
}
