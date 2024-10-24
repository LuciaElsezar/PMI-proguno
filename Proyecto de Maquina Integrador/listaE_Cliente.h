#ifndef LISTACLIENTE_H_INCLUDED
#define LISTACLIENTE_H_INCLUDED
#include "clientexd.h"
#define MAX_C 10
//---Define nodo-------------------------
typedef struct {
    Cliente VIPD[MAX_C];
    int cur;
    int ultimo;
}Lista_Cliente;

//---Funciones de la lista---------------
//---fordward----------------------------
void fordward_cliente(Lista_Cliente* L){
	L->cur = (L->cur+1);
}
//---reset
void reset_cliente(Lista_Cliente* L){
    L->cur=-1;
}
//---Inicializador-----------------------
void init_lista_cliente(Lista_Cliente *L){
    L->cur=-1;
    L->ultimo=-1;
}
//isEmpty---------------------------
int isEmpty_cliente(Lista_Cliente L){
  return L.ultimo == -1;
}
//isFull----------------------------

int isFull_cliente(Lista_Cliente L){
    return L.ultimo == (MAX_C-1);
}

//---insert en el que cursor y auxiliar sean iguales

int insert_cliente(Lista_Cliente* L, Cliente dato){
    if(isEmpty(*L)){
      L->ultimo++;
      L->cur++;
	}
	else{
		int i = L->ultimo;
		for (; i >= L->cur; i--) {
			L->VIPD[i + 1] = L->VIPD[i]; // Desplaza a la derecha
		};
	};
	L->VIPD[L->cur] = dato;
return 1;
};

//---supress-------------------------
void supress_cliente(Lista_Cliente* L){
	int i;
	for (i = L->cur; i < L->ultimo - 1; i++) {
        L->VIPD[i] = L->VIPD[i + 1];
    }
    L->ultimo--;
    if (L->cur > L->ultimo) {
            L->cur = L->ultimo; // Ajusta el cursor si es necesario
        };
};

//---copy---------------------------
Cliente copy_Lista(Lista_Cliente *L){
    return L->VIPD[L->cur];
};
#endif // LISTACLIENTE_H_INCLUDED
