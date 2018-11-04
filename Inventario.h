/**
@file Inventario.h
@brief Archivo de cabecera para las funciones de Inventario.h
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/


#ifndef INVENTARIO_INC
#define INVENTARIO_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ADT_Lote.h"
#include "ADT_Medicamento.h"
#include "DLL_Medicamento.h"
#include "Bool.h"

//////////////////////////////////////////////////////////////////////
///FUNCIONES ENCARGADAS A LA EXTRACCION Y MODIFICACION DE ARCHIVOS////
//////////////////////////////////////////////////////////////////////
Bool Extraccion(DLL * this);
/**
@brief Extrae los datos de un archivo
@param this-> la direccion de una lista
@return el estado de exito de si se pudo extraer los datos
*/
Bool Modificar (DLL * this);
/**
@brief Actualiza al archivo los cambios de la  lista enlazada
@param this-> la direccion de la lista
@return el estado de exito de la actualizacion
*/
Medicamento * Medicamento_Read_Buffer(char * buffer);
/**
@brief Lee un cadena Buffer para almacenar los datos del Medicamento
@param buffer -> La cadena de caracteres del buffer
@return La direccion de tipo Medicamento donde se guardo
*/

//////////////////////////////////////////////////////////////////////
///FUNCIONES DEDICADAS AL CALCULO DE CADUCIDAD Y CONTROL /////////////
//////////////////////////////////////////////////////////////////////

Bool Caducidad(DLL* this);
/**
@brief  Determina de la lista los lotes que estan proximos a caducar
@param  this->la direccion de una lista
@return el estado de exito de las caducidades
*/
void Comparar_Fechas(Medicamento * this, time_t ta, int * dias1, int * dias2);
/**
@brief compara dos fechas
@param this-> la direccion de un medicamento, ta-> la fecha actual del sistema, dias1->la direccion de un entero, dia2->la direccion de otro entero
@return la cantidad de dias de diferencia de dia1 y dia2
*/
time_t Fecha(char * cad_fecha);
/**
@brief Transforma la fecha de tipo time_t
@param cad_fecha -> la direccion de la cadena
@return la fecha de tipo time_t
*/
time_t Fecha_Local();
/**
@brief Determina la fecha del sistema
@param
@return la fecha del sistema
*/
Bool Remove_ProductoCaducado(DLL * this);
/**
@brief Remueve un lote caducado
@param this->la direccion de una lista
@return el estado de exito para remover los lotes caducados
*/
Medicamento * Search_Medicamento (char * codigo, DLL * this);
/**
@brief Busca el medicamento a partir del codigo de barras de un lote
@param this-> la direccion de la lista enlazada, codigo->la direccion del codigo lote
@return la direccion de medicamento
*/

//////////////////////////////////////////////////////////////////////
////MENU 2: IMPRESIÓN DEL INVENTARIO//////////////////////////////////
//////////////////////////////////////////////////////////////////////

void Imprimir_Inventario(DLL* this);
/**
@brief Imprime em pantalla la lista
@param this->la direccion de memoria de una lista
@return
*/

//////////////////////////////////////////////////////////////////////
////MENU 3: NUEVO LOTE////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Insertar_Lote (Node* producto, Lote* datos);
/**
@brief Inserta los datos de un lote a un medicamento
@param producto->la direccion de memoria de un nodo, datos->la direccion de memoria de un lote
@return el estado de exito para insertar los datos de lote en medicamento
*/

//////////////////////////////////////////////////////////////////////
////MENU 4: NUEVO MEDICAMENTO/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Insertar_Medicamento(DLL  * this, Medicamento * medicamento);
/**
@brief Inserta un Medicamento a la lista
@param this -> La direccion a la lista enlazada, medicamento -> La direccion del medicamento a insertar
@return La confirmacion de exito al insertar
*/

//////////////////////////////////////////////////////////////////////
////MENU 5: ELIMINAR MEDICAMENTO//////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Remover_Med(DLL* this, Node * other);
/**
@brief Remueve el medicamento de la lista
@param this -> Direccion de la lista, other -> Direccion del Nodo a remover
@return Confirmacion de que se removio
*/

//////////////////////////////////////////////////////////////////////
////MENU 6: VENTAS////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Remover_MedicamentoRecursivo (Medicamento * this, int acum);
/**
@brief Funcion recursiva que remuve unitariamente los medicamentos hasta llegar al caso base
@param this -> la direccion de memoria al medicamento a Modificar, acum -> El valor que nos dira si llegamos al caso base que es 0
@return El exito del caso recursiva
*/
Bool Remover_Productos (DLL * this, Medicamento* other, int cantidad);
/**
@brief Remueve una cantidad de medicamento a los lotes
@param this -> La direccion de la lista enlazada, other -> La direccion del medicamento a Modificar, cantidad -> La cantidad a remover
@return Si hubo exito al remover los productos
*/

#endif
