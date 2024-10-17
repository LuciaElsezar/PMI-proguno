#ifndef LISTAD_TURNO_H_INCLUDED
#define LISTAD_TURNO_H_INCLUDED
#include "turno.h"

//---Define nodo-------------------------
struct nodo{
    Turno VIPD;
    struct nodo *next;
};
typedef struct nodo Nodo;

//--- Define lista de turnos ------------------
typedef struct{
    Nodo* acc; //Acceso
    Nodo* cur; //Cursor
    Nodo* aux; //Auxiliar
}Lista_Turno;

//---Funciones de lista :p------------------
void init(Lista_Turno* L){
    L->acc = NULL;
    L->cur = NULL;
    L->aux = NULL;
};

//--- Caso 1: aux y cur apuntan al mismo -----------
void insert_caso_1(Lista_Turno* L, nodo* n){
    L->acc = n;
    n->next = L.cur;
    L->cur = n;
    L->aux = n;
};
//--- Caso 2: aux y cur NO apuntan al mismo---------
void insert_caso_2(Lista_Turno* L, nodo* n){
    n->next = L.cur;
    L->cur = n;
    aux->next=cur;
};

//---Suprimir
void supress(Lista_Turno* L){
    L.aux -> next = L.cur.next;
    free((void)L.cur);
    L -> cur = L.aux;
};

int isEmpty(Lista_Turno L){
    if(L.acc.next==NULL){
        return 1;
    }
    else{
        return 0;
    };
};

int isOos(Lista_Turno L){
    if(L.cur==NULL){
        return 1};
    else {
        return 0};
};

void forwards(Lista_Turno* L){
    L->aux=L->cur;
    L->cur=L->cur.next;
};

void reset(Lista_Turno* L){
    L->cur=L.acc;
    L->aux=L.acc;
};

Turno Copy(Lista_Turno L){
    return L.cur->VIPD;
};


#endif // LISTAD_TURNO_H_INCLUDED
