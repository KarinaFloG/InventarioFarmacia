/**
@file ADT_Medicamento.c
@brief Archivo que contiene los setters y getters para el objeto medicamento
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/

#include "ADT_Medicamento.h"


Medicamento* Medicamento_Create(){

  Medicamento* n= (Medicamento *)malloc(sizeof(Medicamento));
  if(n){
    strcpy(n->nombre, "N/A");
    n->control=FALSE;
    n->precio=0.0;
    n->lote1=NULL;
    n->lote2=NULL;
  }
  return n;
}

Medicamento *Medicamento_CreateWithData(Medicamento * this){

  Medicamento* n= (Medicamento *)malloc(sizeof(Medicamento));
  if(n){
    Medicamento_Assign(n,this);
  }

  return n;
}

void Medicamento_Destroy(Medicamento * this){
    if(this){free(this);}
}

void Medicamento_Print(Medicamento* this ){

  printf("\n\nNombre: %s  Precio: %.2f ",this->nombre, this->precio);
  if(this->control){
    printf("Medicamento controlado \n");
  }
  else{
    printf("Medicamento no controlado\n");
  }
  Lote_Print(this->lote1,this->lote2);

}

void Medicamento_PrintLine(Medicamento* this ){

  printf(" %s  Precio: %.2f ",this->nombre, this->precio);
  if(this->control){
    printf("Medicamento controlado  ");
  }
  else{
    printf("Medicamento no controlado  ");
  }
  Lote_PrintLine(this->lote1,this->lote2);

}

Bool Medicamento_PrintFile(Medicamento * this,FILE * fpt){

  if(!this || !fpt){return FALSE;}

  char control[16];
  if(Medicamento_GetControl(this)){
    strcpy (control, "CONTROLADO");
  }
  else{
    strcpy (control, "NO_CONTROLADA");
  }


  fprintf(fpt,"%s,%.2f,%s,",this->nombre,this->precio,control);
  if(this->lote1){
    fprintf(fpt,"%d,%s,%s,",this->lote1->cantidad,this->lote1->caducidad, this->lote1->codigo);
    if(this->lote2){
      fprintf(fpt,"%d,%s,%s",this->lote2->cantidad,this->lote2->caducidad, this->lote2->codigo);
    }
  }
  fprintf(fpt,"\n");
  return TRUE;
}

void Medicamento_SetNombre(Medicamento* this,char *  nombre ){
  strcpy(this->nombre,nombre);
}

void Medicamento_SetControl(Medicamento* this,Bool control ){
  this->control=control;
}

void Medicamento_SetPrecio(Medicamento* this,float precio ){
  this->precio=precio;
}

Bool Medicamento_SetLote(Medicamento* this, Lote * lote){
  if(!lote){return FALSE;}
  if(!this->lote1){
    this->lote1=Lote_Create();
    Lote_Assign(this->lote1,lote);
    return TRUE;
  }
  else if(!this->lote2){
    this->lote2=Lote_Create();
    Lote_Assign(this->lote2,lote);
    return TRUE;
  }
  return FALSE;
}

char *Medicamento_GetNombre(Medicamento *this){

  return this->nombre;
}

Bool Medicamento_GetControl(Medicamento *this){
  return this->control;
}

float Medicamento_GetPrecio(Medicamento *this){

  return this->precio;
}

Lote * Medicamento_GetLote1(Medicamento *this){

  return this->lote1;
}

Lote * Medicamento_GetLote2(Medicamento *this){
  return this->lote2;
}

void Medicamento_Assign(Medicamento* this, Medicamento* other){

  Medicamento_SetNombre(this,Medicamento_GetNombre(other));
  Medicamento_SetControl(this,Medicamento_GetControl(other));
  Medicamento_SetPrecio(this,Medicamento_GetPrecio(other));
  if(other->lote1){
    this->lote1=Lote_Create();
    Lote_Assign(this->lote1,other->lote1);
    if(other->lote2){
      this->lote2=Lote_Create();
      Lote_Assign(this->lote2,other->lote2);
    }
  }
}
