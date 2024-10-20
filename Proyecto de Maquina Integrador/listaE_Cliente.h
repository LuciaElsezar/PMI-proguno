#ifndef LISTAE_CLIENTE_H_INCLUDED
#define LISTAE_CLIENTE_H_INCLUDED
#define MAX_C 10
//---Define nodo-------------------------
typedef struct {
    Cliente VIPD[MAX_C];
    int cur;
    int ultimo;
}Lista_Cliente;

//---Funciones de la lista---------------

//---Inicializador-----------------------
void init(Lista_Cliente *L){
    L->cur=0;
    L->ultimo=-1;
}
//isoOs-----------------------------
int isOos(Lista_Cliente L){
    return(L.cur > L.ultimo  || L.cur<0);//retorna 1 verdadero o 0 caso contrario
}
//isEmpty---------------------------
int isEmpty(Lista_Cliente L){
  return(L.ultimo == -1);//retorna 1 verdadero o 0 caso contrario
}
//isFull----------------------------
int isFull(Lista_Cliente L){
    return (L.ultimo == (MAX_C-1));//retorna 1 verdadero o 0 caso contrario
    }


//---insert en el que cursor y auxiliar sean iguales

void insert_caso(Lista_Cliente* L,Cliente dato){
    if(!isFull(L) && !isOos(L)){
      for(int i=L->ultimo;i> L->cur;i--){
        L->VIPD[i];=L->VIPD[i-1];//desplaza los elementos hacia la izquierda
      }
      L->VIPD[L->cur]=dato;
      L->ultimo++;
    }
}

//---supress-------------------------
void supress(Lista_Cliente* L){
    if(!isEmpty(L) && !isOos(L)){
        for (int i = L.cur; i < L.ultimo - 1; i++) {
        L->datos[i] = L->datos[i + 1];
    }
    L->ultimo--;
    }
}
#endif // LISTAE_CLIENTE_H_INCLUDED
