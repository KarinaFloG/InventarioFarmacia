/**
@file DLL_Medicamento.c
@brief Archivo que contiene las operaciones realizadas sobre el objeto medicamento
@author Flores García Karina
@author Montoya Perez Hector
@author Ocaña Anaya Guillermo
@author Velasco Arciniega Ernesto
@author Vivanco Quintanar Diego Armanado
@date  02/06/2017
*/

#include "DLL_Medicamento.h"


Node * newNode(Medicamento* medicamento){

  Node* n=(Node *)malloc(sizeof(Node));
  if(n){
    n->medicamento=Medicamento_Create();
    Medicamento_Assign(n->medicamento, medicamento);
    n->next=n->prev=NULL;
  }
  return n;
}

void deleteNode(Node* n){
 if (n){
   free(n);
 }
}

DLL* DLL_Create(){

  DLL* n=(DLL*)malloc (sizeof(DLL));
  if(n){
    n->first=NULL;
    n->last=NULL;
    n->empty=TRUE;
  }

  return n;
}

Bool DLL_Insert(DLL * this, Medicamento *medicamento){

  Node* n=newNode(medicamento);
  if(!n){return FALSE;}
  if(this->empty){
    this->first=this->last=n;
    this->empty=FALSE;
  }
  else{
    this->last->next=n;
    n->prev=this->last;
    this->last=n;

  }
  return TRUE;
}

Bool DLL_Remove(DLL *this, Medicamento * medicamento){

  if(this->first!=this->last){

    Medicamento_Assign(medicamento,this->first->medicamento);
    Node *tmp=this->first->next;
    deleteNode(this->first);
    this->first=tmp;
    this->first->prev=NULL;
    return TRUE;
  }
  else  if(this->first){

    Medicamento_Assign(medicamento,this->last->medicamento);
    this->first=this->last=NULL;
    this->empty=TRUE;

    return TRUE;
  }
  else{ return FALSE;}
}

void DLL_Destroy(DLL * this){

  if(this){
      while(this->first){
        Node * tmp =this->first->next;
        deleteNode(this->first);
        this->first=tmp;
      }
    }
  free(this);
}

Bool DLL_FindIf(DLL * this ,char* nombre){

  Node* it = this->first;
  while(it){//it : iterador
    if (!strcmp(nombre, it->medicamento->nombre)){return TRUE;}
    it=it->next;
  }
  return FALSE;

}

Bool DLL_IsEmpty(DLL * this){

  return this->empty;
}

Node * DLL_Search(DLL * this ,char * nombre) {

  Node * it =this->first;
  while(it){
    if (!strcmp(nombre, it->medicamento->nombre)){return it;}
    it=it->next;
  }
  return NULL;
}

Bool DLL_InsertBack(DLL * this,Medicamento * medicamento){

  Node* n=newNode(medicamento);
  if(!n){return FALSE;}
  if(this->empty){
    this->first=this->last=n;
    this->empty=FALSE;
  }
  else{
    n->next=this->first;
    this->first->prev=n;
    this->first=n;
  }
  return TRUE;
}

Bool DLL_RemoveBack(DLL *this, Medicamento * medicamento){

  if(this->first!=this->last){
    Medicamento_Assign(medicamento,this->last->medicamento);
    Node *tmp=this->last->prev;
    deleteNode(this->last);
    this->last=tmp;
    this->last->next=NULL;
    return TRUE;
  }
  else  if(this->first){
    Medicamento_Assign(medicamento, this->last->medicamento );
    deleteNode(this->last);
    this->first=this->last=NULL;
    this->empty=TRUE;
    return TRUE;
  }
  else{ return FALSE;}
}

Bool DLL_RemoveAt(DLL *this, Node *pos,Medicamento *medicamento){

  if(pos==this->first){ return DLL_Remove(this,medicamento);}
  else if(pos==this->last){ return DLL_RemoveBack(this,medicamento);}
  else{
    Medicamento_Assign(medicamento, pos->medicamento);
    Node *left=pos->prev;
    Node *right=pos->next;
    deleteNode(pos);
    left->next=right;
    right->prev=left;
    return TRUE;
  }
}

Bool DLL_InsertAt(DLL *this, Node *pos, Medicamento *medicamento){ //inserta en pos->next

  if(pos==this->last){ return DLL_Insert(this,medicamento);}
  else{
    Node *n =newNode(medicamento);
    if(n){
      n->prev=pos;
      n->next=pos->next;
      pos->next->prev=n;
      pos->next=n;
    }
    return TRUE;
  }

}
