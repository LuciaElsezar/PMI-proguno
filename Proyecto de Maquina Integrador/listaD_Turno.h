#ifndef LISTAD_TURNO_H_INCLUDED
#define LISTAD_TURNO_H_INCLUDED
#include "turno.h"
#include <stdlib.h>

//--Struct nodo
struct nodo{
    Turno vipd;
    struct nodo* next;
};

//--Define tipos Nodo y lista
typedef struct nodo Nodo;
typedef struct{
    Nodo* acc;
    Nodo* cur;
    Nodo* aux;
}Lista_Turno;

//--Init
int init_lista_turno(Lista_Turno* l){ //Inicializa
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
    return 1;
};

//--isEmpty / isOos
int isEmpty_turno(Lista_Turno l){
    return l.acc == NULL; //1 si la lista esta vacia
};

int isOos_turno(Lista_Turno l){
    return l.cur == NULL; //1 si el cursor apunta a NULL -> no apunta a un elemento de la lista
};

//--Insert
int insert_turno(Lista_Turno* l, Turno T){
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo)); //Reserva memoria
    if(nuevo == NULL) return 0; //Si no hay espacio termina
    nuevo->vipd = T;

    if(l->cur == l->aux){ //Si cur y aux apuntan al primero o null
        nuevo->next = l->cur; //El siguiente del nuevo va a ser igual al primero
        l->cur=nuevo;
        l->aux=nuevo; //El aux
        l->acc=nuevo; //El acceso ahora apuntan al nuevo elemento
    }
    else{ //El cursor apunta al siguiente del auxiliar
        nuevo->next = l->cur; //El sigueinte del nuevo es el cursor
        l->cur = nuevo; //El cursor apunta al nuevo
        l->aux->next = nuevo; //El siguiente apunta al nuevo
    };
return 1;
};

//--Reset
void reset_turno(Lista_Turno* L){
    L->cur=L->acc;
    L->aux=L->acc;
};

//---Copy
Turno copy_turno(Lista_Turno L){
    return L.cur->vipd;
};

//--Supress
int supress_turno(Lista_Turno* l){
            if(l->aux==l->cur){ //Apuntan al primero o a null
                l->acc = l->cur->next; //Acc apunta al siguiente
                free((void*)l->cur); //Se libera a lo que apunta el cur
                l->cur = l->acc; //Cursor apunta al aux
                l->aux = l->acc; //Acc apunta al aux
            }
            else{ //El aux apunta al anterior de cur
                l->aux->next=l->cur->next; //El next del aux ahora apunta al siguiente del que se va a borrar
                free((void*)l->cur); //Se libera lo que apunta el cur
                l->cur = l->aux->next; //El cursor se posiciona en el siguiente
                };
    return 1; //operacion exitosa
};

//--Forward
int forward_turno(Lista_Turno *l){
    if(l->cur != l->aux){ //Si aux apunta al anterior del apuntado por el cursor
        l->aux = l->aux->next; //aux avanza al siguiente
    };
    l->cur = l->cur->next; //Cursor avanza al siguiente
    return 1; //operacion exitosa
};
#endif // LISTAD_TURNO_H_INCLUDED
