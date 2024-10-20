#ifndef LISTAE_CLIENTE_H_INCLUDED
#define LISTAE_CLIENTE_H_INCLUDED
#define MAX_C 10
//---Define nodo-------------------------
typedef struct {
    int VIPD[MAX_C];
    int cur;
    int ultimo;
}Lista_Cliente;

//---Funciones de la lista---------------

//---Inicializador-----------------------
void init(Lista_Cliente *L){
    L->cur=0;
    L->ultimo=0
}
//isoOs-----------------------------
int isOos(Lista_Cliente L){
    if(L->cur > L->ultimo  || L->cur<0){
        return 1;//fuera de lugar
    }else{
    return 0;
    }
}
//isEmpty---------------------------
int isEmpty(Lista_Cliente L){
  if(L.ultimo=-1){
    return 1;
  }else{
  return 0;
  }
    };
//isFull----------------------------
int isFull(Lista_Cliente L){
    if(L.ultimo = (MAX_C-1)){
        return 1;
    }else{
    return 0;
    }
};

//---insert en el que cursor y auxiliar sean iguales

void insert_caso(Lista_Cliente* L,int dato){
    if(!isFull(L) && !isOos(L)){
      for(int i=L->ultimo;i> L->cur;i--){
        L->VIPD[i];=L->VIPD[i-1];
      }
      L->VIPD[L->cur]=dato;
      L->ultimo++;
    }
}

//---supress-------------------------
void supress(Lista_Cliente* L){
    if(!isEmpty(L) && !isOos(L)){
        for (int i = L->cursor; i < L->tamaño - 1; i++) {
        L->datos[i] = L->datos[i + 1];
    }
    L->tamaño--;
    }
};
#endif // LISTAE_CLIENTE_H_INCLUDED
