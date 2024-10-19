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
void carga_turno(Lista t);
//b)---Funcion auxiliar que busca los turnos no realizados
void buscar_turno(Lista t);
//c)---Funcion que muestra los turnos de todo un mes ordenado por fecha
void mostrar_turno_fecha(Lista t);
//d)---Funcion que muestra los turno por nombre de cliente
void mostrar_turno_nombre(Lista t);
//e)---Mostrar los turnos solicitados en el mes por idCliente. Mostrar fecha total y idTurno(recursiva)
void mostrar_turno_idCliente(Lista t);
//f)---Calcula la ganancia mensual considerando los turnos ya realizados(recursiva)
float ganancia_mensual(Lista t);
//g)---Muestra los turnos de la lista de turnos
void mostrar_lista_turnos(Lista t);
//h)---Funcion que modifica la cantidad de tratamientos de un cliente registrado
void modifica_tratamiento();
//i)---Modifica la forma de pago de un turno segun idCliente(solo turnos no realizados)
void modifica_formapago(Lista t);
//j)---Cancelar turno por Id cliente. Detalles en el practico
void cancelar_turno(Lista t);
//l)---funcion que permite registrar un cliente
void registar_cliente();
//m)---Muestra los turnos por tratamiento
void mostrar_turno_tratamiento(Lista t);
//n)---¿¿??

//ñ)---Muestra los clientes almacenados en lista clientes
void mostrar_lista_clientes();
//o)---Elimina un cliente (los turnos no quedan afectados)
void eliminar_cliente();
//p)---Funcion que modifica un turno confirmado (si asiste se modifica realizado, can tratamientos y el nivel)
void modifica_cliente();
//q)---Muestra los turnos no realizados
void mostrar_turno_norealizado(Lista t);

//---Main------------------------------------------------
int main()
{
    printf("Hello world!\n");
    return 0;
}
