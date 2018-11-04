/**
@file Inventario.c
@brief Archivo que contiene las funciones de control del inventario
@brief Archivo que contiene las funciones que controlan las operaciones realizadas a los productos del inventario
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/



#include "Inventario.h"

//////////////////////////////////////////////////////////////////////
///FUNCIONES ENCARGADAS A LA EXTRACCION Y MODIFICACION DE ARCHIVOS////
//////////////////////////////////////////////////////////////////////
Bool Extraccion(DLL * this){

  if(!this){return FALSE;}

  FILE * fpt_Inv=NULL;

  if(!(fpt_Inv=(fopen("Inventario.csv","r+")))){
    printf("Error al abrir el archivo\n" );
    return FALSE;
  }
  Medicamento * tmp;
  char buffer[128];

  fgets(buffer,128,fpt_Inv);
  while(!feof(fpt_Inv)){

    tmp=Medicamento_Read_Buffer(buffer);

    if(!DLL_Insert(this,tmp)){
        return FALSE;
    }
    fgets(buffer,128,fpt_Inv);

  }

  Medicamento_Destroy(tmp);
  fclose(fpt_Inv);
  return TRUE;

}

Bool Modificar (DLL *this){
  if(!this){return FALSE;}

  FILE * fpt_New=NULL;

    if(!(fpt_New=(fopen("Inventario_new.csv","w")))){
      printf("Error al abrir el archivo\n" );
      return FALSE;
    }

  Node *it = this->first;

  while(it){
    Medicamento_PrintFile(it->medicamento,fpt_New);
    fflush(fpt_New);
    it = it->next;
  }
  fclose(fpt_New);
  remove("Inventario.csv");
  rename("Inventario_new.csv","Inventario.csv");

  return TRUE;
}

Medicamento * Medicamento_Read_Buffer(char * buffer){

  int it=0;
  Medicamento * this=Medicamento_Create();
  for(size_t i=0;i<128;i++){
    if(buffer[i]==','){
      it++;
    }
    else if(buffer[i]=='\n'){
      break;
    }
  }

  Medicamento_SetNombre(this,strtok(buffer,","));
  Medicamento_SetPrecio(this,(float)(atof(strtok(NULL,","))));
  if(!strcmp(strtok(NULL,","),"CONTROLADO")){
    Medicamento_SetControl(this,TRUE);
  }
  else{
    Medicamento_SetControl(this,FALSE);
  }

  if(it>3){
    this->lote1=Lote_Create();
    Lote_SetCantidad(this->lote1,atoi(strtok(NULL,",")));
    Lote_SetCaducidad(this->lote1,strtok(NULL,","));
    Lote_SetCodigo(this->lote1,strtok(NULL,","));
    if(it>6){
      this->lote2=Lote_Create();
      Lote_SetCantidad(this->lote2,atoi(strtok(NULL,",")));
      Lote_SetCaducidad(this->lote2,strtok(NULL,","));
      Lote_SetCodigo(this->lote2,strtok(NULL,"\n"));
    }
  }
  return this;
}

//////////////////////////////////////////////////////////////////////
///FUNCIONES DEDICADAS AL CALCULO DE CADUCIDAD Y CONTROL /////////////
//////////////////////////////////////////////////////////////////////
Bool Caducidad(DLL* this){

  FILE *fpt_Ale=NULL;
  if(!(fpt_Ale=(fopen("Alerta.csv","w+")))){
    printf("Error al abrir el archivo\n" );
    return FALSE;
  }
  int dias1=0,dias2=0;
  Bool alerta=FALSE;
  time_t ta=Fecha_Local();
  Node * it=this->first;
  while(it){
    Comparar_Fechas(it->medicamento,ta,&dias1,&dias2);
    if(dias1>0 && dias1<90){//cantidad de dias definida por la empresa farmaceutica para una alerta
      fflush(fpt_Ale);
      fprintf(fpt_Ale,"%s,%s,%d",Lote_GetCodigo(it->medicamento->lote1),Medicamento_GetNombre(it->medicamento), dias1);
      fflush(fpt_Ale);
      fputs("\n",fpt_Ale);
      if(dias1<30){//cantidad de dias definida por la empresa farmaceutica para bloquear lote
        Lote_SetBloqueo(it->medicamento->lote1,TRUE);

      }
      alerta=TRUE;
    }
    if(dias2>0 && dias2<90){
      fflush(fpt_Ale);
      fprintf(fpt_Ale,"%s,%s,%d",Lote_GetCodigo(it->medicamento->lote2),Medicamento_GetNombre(it->medicamento), dias2);
      fflush(fpt_Ale);
      fputs("\n",fpt_Ale);

      if(dias2<30){
        Lote_SetBloqueo(it->medicamento->lote2,TRUE);
      }
    }
    it=it->next;
  }

  fclose(fpt_Ale);
  return alerta;
}

void Comparar_Fechas(Medicamento * this, time_t ta, int * dias1, int * dias2){

  if(this->lote1){
    time_t f_cad=Fecha(Lote_GetCaducidad(this->lote1));
    *dias1=(int)(difftime(f_cad,ta)/86400);
    if (this->lote2){
      f_cad=Fecha(Lote_GetCaducidad(this->lote2));
      *dias2=(int)(difftime(f_cad,ta)/86400);
    }
    else{
      *dias2=-1;
    }
  }
  else{
    *dias1=-1;
    *dias2=-1;
  }
}

time_t Fecha(char * cad_fecha){

  struct tm fecha;
  char buffer[10];
  strcpy(buffer,cad_fecha);
  fecha.tm_mday=atoi(strtok(buffer,"/"));
  fecha.tm_mon=atoi(strtok(NULL,"/"))-1;
  fecha.tm_year=atoi(strtok(NULL,","))+100;
  fecha.tm_sec = 0;
  fecha.tm_min = 0;
  fecha.tm_hour = 0;
  return mktime(&fecha);
}

time_t Fecha_Local(){
  time_t local=time(0);
  struct tm *tlocal = localtime(&local);
  tlocal->tm_sec=0;
  tlocal->tm_min=0;
  tlocal->tm_hour=0;

  return mktime(tlocal);
}

Bool Remove_ProductoCaducado(DLL * this){
  if (!this) { return FALSE; }

  char codigo[32];

  FILE* fpt_Ale = fopen("Alerta.csv","r");

  if (!fpt_Ale) {
    printf("No se pudo abrir el fpt_Ale\n");
    return FALSE;
  }

  Medicamento* caducado;

  char buffer[50];

  fgets (buffer, 50, fpt_Ale);

  while (!feof(fpt_Ale)) {

    strcpy(codigo,strtok(buffer, ","));
    caducado = Search_Medicamento (codigo , this);

    if (!strcmp(Lote_GetCodigo(caducado->lote1), codigo)){
      Lote_Destroy(caducado->lote1);
      caducado->lote1 = caducado->lote2;
      caducado->lote2=NULL;


    }
    else if (!strcmp(Lote_GetCodigo(caducado->lote2), codigo)){
      Lote_Destroy(caducado->lote2);
      caducado->lote2=NULL;
    }

    fgets (buffer, 50, fpt_Ale);
  }

  fclose (fpt_Ale);

  remove("Alerta.csv");

  return TRUE;
}

Medicamento* Search_Medicamento (char * codigo, DLL* this){
  Node* tmp = this->first;

  while (tmp) {
    if (tmp->medicamento->lote1){
      if (!strcmp(codigo , Lote_GetCodigo(tmp->medicamento->lote1))){
        return tmp->medicamento;
      }
    }
    if (tmp->medicamento->lote2){
      if (!strcmp(codigo ,  Lote_GetCodigo(tmp->medicamento->lote2))){
        return tmp->medicamento;
      }
    }
    tmp=tmp->next;
  }
  return NULL;
}

//////////////////////////////////////////////////////////////////////
////MENU 2: IMPRESIÓN DEL INVENTARIO//////////////////////////////////
//////////////////////////////////////////////////////////////////////

void Imprimir_Inventario(DLL* this) {
  Node* tmp = this->first;
  int i=1;
  while (tmp) {
    printf("%d.- ",i);
    Medicamento_PrintLine(tmp->medicamento);
    printf("\n");
    tmp = tmp->next;
    i++;
  }

}

//////////////////////////////////////////////////////////////////////
////MENU 3: NUEVO LOTE////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Insertar_Lote (Node* producto, Lote* datos){
  if (!producto || !datos){
    return FALSE;
  }


  if (!producto->medicamento->lote1){
    producto->medicamento->lote1 =Lote_Create ();
    Lote_Assign(producto->medicamento->lote1,datos);
    return TRUE;
  }
  else if (!producto->medicamento->lote2){
    producto->medicamento->lote2 =Lote_Create ();
    Lote_Assign(producto->medicamento->lote2,datos);
    return TRUE;
  }

  return FALSE;
}

//////////////////////////////////////////////////////////////////////
////MENU 4: NUEVO MEDICAMENTO/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Insertar_Medicamento(DLL  * this, Medicamento * medicamento){
  if(!this && !medicamento){return FALSE;}
  return DLL_Insert(this,medicamento);
}

//////////////////////////////////////////////////////////////////////
////MENU 5: ELIMINAR MEDICAMENTO//////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Remover_Med(DLL* this, Node * other){

		Medicamento *aux=Medicamento_Create();
		if (DLL_RemoveAt(this, other, aux))
		{
			Medicamento_Destroy(aux);
			return TRUE;
		}
		Medicamento_Destroy(aux);
		return FALSE;

}

//////////////////////////////////////////////////////////////////////
////MENU 6: VENTAS////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

Bool Remover_MedicamentoRecursivo (Medicamento * this, int acum){

  if (acum == 0){ return TRUE; }// CASO BASE

  if (!this || !this->lote1) { return FALSE; }

  if (acum == 0){ return TRUE; }// CASO BASE

  this->lote1->cantidad--;

  if (this->lote1->cantidad == 0){
    if (!this->lote2){ this->lote1 = NULL; }
    else {
      Lote_Destroy(this->lote1);
      this->lote1 = this->lote2;
      this->lote2 =NULL;
    }
  }
  return Remover_MedicamentoRecursivo (this, acum-1);// CASO RECURSIVO
}//FUNCION RECURSIVA

Bool Remover_Productos (DLL * this, Medicamento* other, int cantidad){
  if (!this || !other || cantidad<0){ return FALSE; }

  int acu=0;
  if (other->lote1 && !Lote_GetBloqueo(other->lote1)){
    acu+=Lote_GetCantidad(other->lote1);
  }
  if (other->lote2 && !Lote_GetBloqueo(other->lote2)){
    acu+=Lote_GetCantidad(other->lote2);
  }

  if (acu >= cantidad){
    return Remover_MedicamentoRecursivo(other, cantidad);
  }
  return FALSE;
} //FUNCION DE ACTIVACIÓN
