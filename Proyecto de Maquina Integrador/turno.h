#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED
#include <string.h>
#define TAM_NOMBRE 26
#define TAM_ID_TURNO 9

//--- Definir Struct Fecha -------------------
typedef struct{
    int dia;
    int mes;
    int anio;
    int hora; //Formato 24hs.
}Fecha;

//Tratamientos
/*
*/

//--- Definir Struct Turno ------------------
typedef struct{
    char id_turno[TAM_ID_TURNO];
    char nombre[TAM_NOMBRE];
    int id_cliente;
    int tratamientos[10];
    int forma_pago;
    //Formas de pago:
    /*
    */
    float total;
    Fecha fecha_turno;
    int realizado;
    //Realizado: SI => 1; NO => 0
}Turno; //------------------------------------

//---Init y Set ---------------------------

void init_turno(Turno* t){
    strcpy(t->id_turno, "a0");
};

void Set_id_turno(Turno* t, char id[]){
    strcpy(t->id_turno, id);
};

void Set_nombre_turno(Turno* t, char nom[]){
    strcpy(t->nombre, nom);
};

void Set_id_cliente(Turno* t, int dni){
    t->id_cliente = dni;
};

void Set_tratamiento(Turno* t, int x, int i){
    t->tratamientos[i]=x;
};

void Set_forma_pago(Turno* t, int f){
    t->forma_pago=f;
};

void Set_dia(Turno* t, int d){
    t -> fecha_turno.dia = d;
};
void Set_mes(Turno* t, int m){
    t -> fecha_turno.mes = m;
};
void Set_anio(Turno* t, int a){
    t -> fecha_turno.anio = a;
};
void Set_hora(Turno* t, int h){
    t -> fecha_turno.hora = h;
};

void Set_realizado(Turno* t, int r){
    t -> realizado = r;
};

//--- Get ------------------------------
char* Get_id_turno(Turno t){
char* p;
p = (char*)malloc(sizeof(char)*TAM_ID_TURNO);
if(p==NULL){
    exit(1);
}
else{
    return p;
};
};

char* Get_nombre_turno(Turno t){
char* p;
p = (char*)malloc(sizeof(char)*TAM_NOMBRE);
if(p==NULL){
    exit(1);
}
else{
    return p;
};
};

//Hacer un if en main para verificar si se salió de la funcion :p

int Get_id_cliente(Turno t){
    return t.id_cliente;
};

int Get_tratamiento(Turno t, int i){
    return t.tratamientos[i];
};

int Get_forma_pago(Turno t){
    return t.forma_pago;
};

int Get_dia(Turno t){
    return t.fecha_turno.dia;
}
int Get_mes(Turno t){
    return t.fecha_turno.mes;
}
int Get_anio(Turno t){
    return t.fecha_turno.anio;
}
int Get_hora(Turno t){
    return t.fecha_turno.hora;
}

int Get_realizado(Turno t){
    return t.realizado;
};
#endif // TURNO_H_INCLUDED
