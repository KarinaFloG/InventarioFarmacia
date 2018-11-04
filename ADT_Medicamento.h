/**
@file ADT_Medicamento.h
@brief Archivo de cabecera para las funciones de ADT_Medicamento.h
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/

#ifndef ADT_MEDICAMENTO_INC
#define ADT_MEDICAMENTO_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADT_Lote.h"
#include "Bool.h"

struct Medicamento_Type{
  char nombre[50]; //Nombre del medicamento
	float precio; //Precio de venta
  Bool control; //Tipo: Controlado o no
  Lote * lote1;
  Lote * lote2;
}; typedef struct Medicamento_Type Medicamento;

Medicamento* Medicamento_Create();
/**
@brief Crea una estructura medicamento
@param
@return la direccion de memoria de medicamento
*/
Medicamento *Medicamento_CreateWithData(Medicamento * this);
/**
@brief Crea una estructura medicamento inicializandola con datos
@param this->la direccion de memoria de una estructura medicamento
@return la direccion de memoria de medicamento
*/

void Medicamento_Destroy(Medicamento * this);
/**
@brief Devuelve la memoria de medicamento
@param this-> la direccion de memoria de medicamento
@return
*/

void Medicamento_Print(Medicamento* this );
/**
@brief Imprime en pantalla una estructura medicamento
@param this-> la direccio de memoria de una estructura medicamento
@return
*/

void Medicamento_PrintLine(Medicamento* this );
/**
@brief Imprime la estructura medicamento de corrido
@param this-> la direccion de estructura  medicamento
@return
*/

Bool Medicamento_PrintFile(Medicamento * this,FILE * fpt);
/**
@brief  Imprime en el archivo la estructura medicamento
@param this-> la direccion de memoria de una estructura medicamento, fpt-> la direccion al archivo
@return el estado de exito al Imprimir
*/

void Medicamento_SetNombre(Medicamento* this,char *  nombre );
/**
@brief Asigna nombre a un medicamento
@param this-> la direccion de medicamento, nombre-> la direccion del nombre a poner
@return
*/

void Medicamento_SetControl(Medicamento* this,Bool control );
/**
@brief Asigna el control a medicamento
@param this-> la direccion de memoria de medicamento, control-> el estado de control de medicamento
@return
*/

void Medicamento_SetPrecio(Medicamento* this,float precio );
/**
@brief Asigna el precio a un medicamento
@param this->la direccion de memoria de medicamento, precio-> el precio de medicamento
@return
*/

Bool Medicamento_SetLote(Medicamento* this, Lote * lote);
/**
@brief Asigna los datos de un lote a medicamento
@param this-> la direccion de medicamento, lote->la direccion de un lote
@return si se pudo asignar lote a medicamento
*/

char *Medicamento_GetNombre(Medicamento *this);
/**
@brief Extrae el nombre a medicamento
@param this-> la direccion de memoria a medicamento
@return la direccion de un tipo char con el nombre
*/

Bool Medicamento_GetControl(Medicamento *this);
/**
@brief Extrae el estado de control de medicamento
@param  this-> la direccion de memoria a medicamento
@return el estado de control de medicamento
*/

float Medicamento_GetPrecio(Medicamento *this);
/**
@brief Extrae el precio de medicamento
@param  this-> la direccion de memoria a medicamento
@return el precio de medicamento
*/

Lote * Medicamento_GetLote1(Medicamento *this);
/**
@brief Extrae el lote1 del medicamento
@param  this-> la direccion de memoria a medicamento
@return la direccion de lote1 de medicamento
*/

Lote * Medicamento_GetLote2(Medicamento *this);
/**
@brief Extrae el lote2 del medicamento
@param  this-> la direccion de memoria a medicamento
@return la direccion de memoria de lote2 de medicamento
*/

void Medicamento_Assign(Medicamento* this, Medicamento* other);
/**
@brief Asigan los datos de medicamento a otro medicamento
@param this-> la direccion de memoria a medicamento, other-> la direccion de otro medicamento
@return los datos de oher en this
*/



#endif
