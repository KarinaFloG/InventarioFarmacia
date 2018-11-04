/**
@file ADT_Lote.h
@brief Archivo de cabecera para las funciones de ADT_Lote.h
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/

#ifndef ADT_LOTE_INC
#define ADT_LOTE_INC

#include"Bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lote_Type{

  int cantidad;
  char caducidad[16];
  char codigo[32];
  Bool bloqueo;
}; typedef struct Lote_Type Lote;

Lote* Lote_Create();
/**
@brief Crear un lote
@param
@return La direccion de un lote
*/
Lote *Lote_CreateWithData(Lote * this);
/**
@brief  Crea un lote inicializandola
@param  this -> Direccion de un lote
@return La direccion de un lote
*/
void Lote_Destroy(Lote * this);
/**
@brief  Devuelve memoria de tipo lote
@param this -> Direccion de un lote
@return
*/
void Lote_Print(Lote* this , Lote * other);
/**
@brief  Imprime en pantalla dos lotes
@param  this -> Direccion de un  lote, other la direccion de otro lote
@return
*/
void Lote_PrintLine(Lote* this, Lote * other );
/**
@brief  Imprime un lote en pantalla de corrido
@param  this -> Direccion de un  lote, other la direccion de otro lote
@return
*/
Bool Lote_PrintFile(Lote * this, FILE * fpt);
/**
@brief Imprime en el archivo un lote
@param this -> la direccion de un lote, fpt->la direccion de FILE a un archivo
@return si hubo un error al imorimir en el archivo
*/
void Lote_SetCaducidad(Lote* this, char* caducidad);
/**
@brief  Asigina la caducidad a lote
@param this -> direccion de un lote, caducidad -> direccion de la cadena
@return
*/
void Lote_SetCantidad(Lote* this, int cantidad);
/**
@brief  Asigina la cantidad a lote
@param  this -> la direccion de un lote , cantidad -> entero con la cantidad
@return
*/
void Lote_SetCodigo(Lote* this,char * codigo);
/**
@brief Asigna codigo a un lote
@param this -> La direccion de un lote, codigo -> La direccion de codigo
@return
*/
void Lote_SetBloqueo(Lote* this, Bool bloqueo);
/**
@brief Asigna si esta bloqueado un lote
@param  this -> la direccion de lote, bloqueo -> estado de bloqueo
@return
*/
char* Lote_GetCaducidad(Lote *this);
/**
@brief Extrae la caducidad de un lote
@param this -> la direccion del lote
@return la direccion de caducidad
*/
char * Lote_GetCodigo(Lote *this);
/**
@brief Extre codigo de un lote
@param this -> la direccion de un lote
@return la direccion de codigo
*/
int Lote_GetCantidad(Lote *this);
/**
@brief Extrae cantidad de un lote
@param this -> la direccion de un lote
@return la cantidad en entero
*/
Bool Lote_GetBloqueo(Lote *this);
/**
@brief Extrae el estado de bloqueo de lote
@param this -> la direccion de un lote
@return estado de bloqueo
*/
void Lote_Assign(Lote* this, Lote* other);
/**
@brief asigna lo que hay en other en this
@param this -> la direccion de un lote, other ->la direccion de otro
@return
*/


#endif
