/**
@file ADT_Lote.c
@brief Archivo que contiene los setters y getters para la estructura lote
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/

#include "ADT_Lote.h"


Lote* Lote_Create(){

  Lote* n= (Lote *)malloc(sizeof(Lote));
  if(n){
    strcpy(n->caducidad, "N/A");
    strcpy(n->codigo, "N/A");
    n->bloqueo=FALSE;
    n->cantidad=0;
  }
  return n;
}

Lote *Lote_CreateWithData(Lote * this){

  Lote* n= (Lote *)malloc(sizeof(Lote));
  if(n){
    Lote_Assign(n,this);
  }
  return n;
}

void Lote_Destroy(Lote * this){

  if(this){free(this);}
}

void Lote_Print(Lote* this, Lote * other ){

  if(this){
    printf("\nLote 1: Cantidad: %d  Caducidad: %s  Codigo  %s ",this->cantidad, this->caducidad, this->codigo );
    if(this->bloqueo){
      printf(" Bloqueado" );
    }

  }
  else{
    printf(" Medicamento agotado " );
  }
  if(other){
    printf("\nLote 2: Cantidad: %d  Caducidad: %s  Codigo  %s ",other->cantidad, other->caducidad, other->codigo );
    if(other->bloqueo){
      printf(" Bloqueado" );
    }
  }
}

void Lote_PrintLine(Lote* this, Lote * other ){

  if(this){
    printf("Lote 1: Cantidad: %d  %s  %s  ",this->cantidad, this->caducidad, this->codigo );

  }
  else{
    printf(" Medicamento agotado " );

  }
  if(other){
    printf("Lote 2: Cantidad: %d  %s  %s",other->cantidad, other->caducidad, other->codigo );

  }
}

Bool Lote_PrintFile(Lote * this, FILE * fpt){

  if(!this || !fpt){return FALSE;}
  fprintf(fpt,"%d,%s,%s,",this->cantidad,this->caducidad, this->codigo);
  return TRUE;
}

void Lote_SetCaducidad(Lote* this, char* caducidad){

    strcpy(this->caducidad, caducidad);

}

void Lote_SetCantidad(Lote* this, int cantidad){

  this->cantidad=cantidad;
}

void Lote_SetCodigo(Lote* this,char * codigo){

  strcpy(this->codigo, codigo);
}

void Lote_SetBloqueo(Lote* this, Bool bloqueo){

  this->bloqueo=bloqueo;
}

char* Lote_GetCaducidad(Lote *this){
  return this->caducidad;
}

char * Lote_GetCodigo(Lote *this){
  return this->codigo;
}

int Lote_GetCantidad(Lote *this){
  return this->cantidad;

}

Bool Lote_GetBloqueo(Lote *this){
  return this->bloqueo;

}

void Lote_Assign(Lote* this, Lote* other){

  Lote_SetCaducidad(this,Lote_GetCaducidad(other));
  Lote_SetCantidad(this, Lote_GetCantidad(other));
  Lote_SetCodigo(this, Lote_GetCodigo(other));
  Lote_SetBloqueo(this,Lote_GetBloqueo(other));
}
