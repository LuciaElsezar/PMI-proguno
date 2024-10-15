#include <stdio.h>
#include <stdlib.h>
#include "turno.h"
#include "cliente.h"
#include "listaD_Turno.h"
#include "listaE_Cliente.h"

//---Se definen Tratamientos ------------------
typedef struct{
    char nombre[26];
    float precio;
}Tratamiento;
//---Arreglo tratamientos -----------------------------
Tratamiento tratamientos[10]= {{"Unas", 7400},{"Limpieza Facial", 9400},
                                {"Masajes", 7500},{"Manicura", 10000},
                                {"Pedicura", 12000},{"Depilacion", 8000},
                                {"Pestanias", 123},{"Peeling", 22000},
                                {"Ondas Galvanicas", 123},{"Botox", 123}};

//---Funciones-------------------------------------------


//---Main------------------------------------------------
int main()
{
    printf("Hello world!\n");
    return 0;
}
