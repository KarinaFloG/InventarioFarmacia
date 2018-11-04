 #include <stdlib.h> 
#include <stdio.h> 
#include <assert.h> 
#include <string.h> 

enum {FALSE = 0, TRUE = !FALSE};
typedef unsigned int Bool;

//**-----------------------------------------------------------------------**//

struct Medicamento_Type
{
	char nombre[50]; //Nombre del medicamento
	char tipo[25]; //Tipo: Controlado o no
	float precio; //Precio de venta
	//Aqui falta la otra lista o cola
};
typedef struct Medicamento_Type Medicamento;
//**-------------------------------------------------------------------------**//
//	Estructura de los nodos en la lista
struct Node_Type
{
	Medicamento medicamento;

	struct Node_Type* next;
	struct Node_Type* prev;
};
typedef struct Node_Type Node;
//*--------------------------------------------------------------------------**//
//*----------------------------------------------------**//
//Crea la lista
struct DLL_Type
{
	Node* first;
	Node* last;
	Bool empty;
};
typedef struct DLL_Type DLL;
//**-------------------------------------------------------------------------**//
//Crea los nodos 
Node* newNode (Medicamento* medicamento)
{
	Node* n = (Node*) malloc (sizeof (Node));
	if(n){
		char* nombre = Medicamento_GetNombre (medicamento);
		char* tipo = Medicamento_GetTipo (medicamento);
		float* precio = Medicamento_GetPrecio (medicamento);

//Operaciones para insertar los campos a la estructura
//Deben ser creadas con estos nombres
		Alumno_SetNombre (&n->medicamento, nombre);
		Alumno_SetTipo (&n->medicamento, tipo);
		Alumno_SetPrecio (&n->medicamento, precio);

		n->next = n->prev = NULL;
		}
		return n;
}
//*----------------------------------------------------**//
//*----------------------------------------------------**//
//Destruye nodos
void deleteNode(Node* n)
{
	if (n) {free (n); }
}

//*----------------------------------------------------**//
//Cre la lista doble enlazada
DLL* DLL_Create()
{
	DLL* lista = (DLL*) malloc (sizeof (DLL));


	if (lista){
		lista->first = lista->last = NULL;
		lista->empty = TRUE;
	}
	return lista;
}
//**-----------------------------------------------------------**//
 //Destruye la lista doble enlazada
void DLL_Destroy (DLL* this)
{
	if (this){
			while(this->first){
					Node* tmp = this->first->next;
					deleteNode(this->first);
					this->first = tmp;
			}
			//BORA LA LISTA
			free(this);
	}
}
//**---------------------------------------------------------------------**//

