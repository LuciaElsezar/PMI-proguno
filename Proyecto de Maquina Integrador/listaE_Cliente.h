#ifndef LISTAE_CLIENTE_H_INCLUDED
#define LISTAE_CLIENTE_H_INCLUDED
#include "cliente.h"
//---------------LISTA ESTÁTICA DE CLIENTES--------

typedef struct{
    Cliente VIPD[MAX_SIZE];
    int cursor;
    int ultimo; //cantidad del arreglo ocupado
}listad_clientes;

//---Funciones de lista :p------------------
void init(listad_clientes* L){
    L->cursor=-1;
    L->tamaño=-1;
};

Cliente Insert(listad_clientes* L, Cliente elem){
    if(L->cursor==L->ultimo){//si el arreglo esta lleno retorna -1
        return -1;
    }
    else (L->cursor>L->ultimo) return -2;//si L esta fuera de la estructura retorna -2
    for(int i=L->ultimo;i>=L->cursor; i--){
            L->VIPD[i+1]=L->VIPD[i];
    }
    L->VIPD[L.cursor]=elem;
    L->ultimo++;
};

void supress(listad_clientes* L){//acomodar el cursor antes de llamar
    if(L->cursor>L->ultimo)//si el cursor se sale del arreglo
        return -1;
    else {
        for(int i=L->cursor;i<L->ultimo;i++)
        L->VIPD[i]=L->VIPD[i+1];
    }
    L->ultimo--;
};

int isEmpty(listad_clientes L){
    if(L->cursor==-1){
        return 0;
    }
    else return 1;
};

int isFull(listad_clientes L){
    if(L->cursor==MAX_SIZE){
        return 0;
    }
    else return 1;
};

void forwards(listad_clientes* L){//
    if(L.cursor<=L->tamaño)
        L->cursor++;
};

void reset(listad_clientes* L){
    L->cursor=0;
};
int isOos(listad_clientes L){
        return (L.cursor > L.tamaño)
}
Cliente Copy(listad_clientes L){
    return L.VIPD[L.cursor];
}

#endif // LISTAE_CLIENTE_H_INCLUDED
