/**
@file DLL_Medicamento.h
@brief Archivo de cabecera para las funciones de DLL_Medicamento.h
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/


#ifndef DLL_MEDICAMENTO_INC
#define DLL_MEDICAMENTO_INC

#include"Bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADT_Medicamento.h"

struct Node_Type{

  Medicamento * medicamento;
  struct Node_Type* next;
  struct Node_Type* prev;
};
typedef struct Node_Type Node;

struct DLL_Type{

    Node * first;
    Node * last;
    Bool empty;
};
typedef struct DLL_Type DLL;

Node * newNode(Medicamento* medicamento);
/**
@brief	Crea un nuevo Nodo
@param	medicamento-> la estructura del medicamento
@return	la direccion de memoria del Nodo creado
*/
void deleteNode(Node* n);
/**
@brief	Elimina un Nodo
@param	n-> direccion de momoria de un Nodo
@return
*/
DLL* DLL_Create();
/**
@brief	Crea memoria para una lista
@param
@return	Direccion de la lista enlazada
*/
Bool DLL_Insert(DLL * this, Medicamento * medicamento);
/**
@brief	Inserta un nuevo medicamento en la lista
@param	this->direccion de memoria de la lista, medicamento->estructura medicamento
@return	TRUE, si se pudo insertar; FALSE, sino se pudo
*/
Bool DLL_Remove(DLL* this,Medicamento * medicamento);
/**
@brief	Remueve un medicamento de la lista,
@param	this->la direccion de la lista, medicamento->estructura medicamento
@return	TRUE, si se pudo remover; FALSE, sino se pudo
*/
void DLL_Destroy(DLL * this);
/**
@brief	Destruye la lista
@param	 this->la direccion de la lista
@return
*/
Bool DLL_FindIf(DLL * this ,char * nombre);
/**
@brief	Busca si se encunetra un medicamento en especifico dentro de la lista
@param	this->direccion de la lista, nombre-> nombre del medicamento que se buscara
@return	TRUE, si se encuentra; FALSE, sino esta el medicamento en la lista
*/
Bool DLL_IsEmpty(DLL * this);
/**
@brief	Determina si la lista esta vacia o no
@param	this->direccion de la lista
@return	TRUE, si esta vacia; FALSE, si tiene algun elemento
*/

Node * DLL_Search(DLL * this ,char* nombre);
/**
@brief	Busca en toda la lista un nombre de medicina
@param	this->direccion de la lista, nombre->nombre de medica
@return	Direccion de memoria de la lista donde esta el medicamento
*/
Bool DLL_InsertBack(DLL * this,Medicamento * medicamento);
/**
@brief	Inserta un elemento del lado izquierdo de la lista
@param	this->ireccion de la lista, medicamento-> estructura medicamento
@return	TRUE, si se pudo insertar; FALSE, si no se pudo
*/
Bool DLL_InsertAt(DLL * this, Node * pos, Medicamento * medicamento);
/**
@brief	Inserta en una posicion especifica de la lista otro tipo de medicina
@param	this->direccion de la lista, pos-> direccion del Nodo anterior a la posicion que se quiere insertar, medicamento->estructura medicamento
@return	TRUE, si se pudo insertar; FALSE, no se insertó
*/
Bool DLL_RemoveBack(DLL * this,Medicamento * medicamento);
/**
@brief	Remueve un medicamento del lado derecho de la lista
@param	this->direccion de la lista, medicamento-> estrcutura medicamento.
@return	TRUE, si se removio; FALSE, no se pudo remover
*/
Bool DLL_RemoveAt(DLL * this, Node * pos, Medicamento * medicamento);
/**
@brief	Remueve en una posicion X de la lista
@param	this-> direccion de la lista, Medicamento->direccion del Nodo anterior a la posicion que se quiere remover, medicamento->estructura medicamento
@return	TRUE, si se removio; FALSE, si no se pudo.
*/


#endif
