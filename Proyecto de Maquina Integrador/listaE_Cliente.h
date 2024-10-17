#ifndef LISTAE_CLIENTE_H_INCLUDED
#define LISTAE_CLIENTE_H_INCLUDED
//---Define nodo-------------------------
struct nodo{
    Cliente VIPD;
    struct nodo *next;
};
typedef struct nodo Nodo;


//---Define Lista del Cliente------------
typedef struct{
    Nodo* acc; //acceso
    Nodo* aux; //auxiliar
    Nodo* cur; //cursor
}Lista_Cliente;


//---Funciones de la lista---------------

//---Inicializador-----------------------
void init(Lista_Cliente *L){
    L->acc= NULL;
    L->aux= NULL;
    L->cur= NULL;
}
//---insert en el que cursor y auxiliar sean iguales

void insert_caso1(Lista_Cliente* L,Nodo* n){
    L->acc=n;
    n->next=L->cur;
    L->cur=n;
    L->aux=n;
}
//---insert caso comun en el que hayga mas de un elemento
void insert_case2(Lista_Cliente* L,Nodo* n){
    if(L->aux != NULL){
    n->next = L->cur;
    L->cur = n;
    L->aux->next=L->cur;
};
};

//---supress-------------------------
void supress(Lista_Cliente* L){

    if(L->cur != NULL){
        if(L->aux != NULL){
           L->aux->next=L->cur->next; //caso en el que auxiliar y cursor no sean nulos
        }else{
        L->acc=L->cur->next;//caso en el que auxiliar sea nulo y cursor no sea nulo (quiere decir que hay un unico elemento a eliminar)
    }
    free(L->cur);//elimina el elemento
    L->cur=L->aux;//cursor apunta a lo apuntado por auxiliar
}
}
//isEmpty---------------------------
int isEmpty(Lista_Cliente L){
    if(L.acc==NULL){
        return 1;
    }else{
    return 0;
    };
};
//isFull----------------------------
//int isFull(Lista_Cliente L){
//    if(L.)
//}

//isoOs-----------------------------
int isOos(Lista_Cliente L){
    if(L.cur == NULL){
        return 1;
    }else{
    return 0;
    }
}


#endif // LISTAE_CLIENTE_H_INCLUDED
