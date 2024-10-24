#include <stdio.h>
#include <stdlib.h>
#include "turno.h"
#include "cliente.h"
#include "lista_turnoD_Turno.h"
#include "lista_turnoE_Cliente.h"

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
    Lista lista_turno;
    Turno turno_aux;
    init_turno(&lista_turno);
    int opc, x, op_exitosa, valor_econtrado;
    do{
        printf("----Bienvenido----\n");
        printf("Opciones\n");
        printf("1.Aniadir\n");
        printf("2.Mostrar\n");
        printf("3.Modificar\n");
        printf("4.Eliminar\n");
        printf("5.Avanzar al siguiente con el cursor\n");
        printf("0.Salir\n");
        scanf("%d",&opc);
        switch(opc){
            case 1:
                printf("Escriba un entero: \n");
                scanf("%d", &x);
                op_exitosa = insert_turno(&lista_turno, x);
                if(!op_exitosa){
                    printf("No hay espacio suficiente. Reintente.\n");
                };
                break;
            case 2:
                if(!isEmpty_turno(lista_turno)){
                    printf("Lista: \n");
                    reset_turno(&lista_turno);
                    do{
                        turno_aux = copy_turno(lista_turno); //Acá hay que hacer que el turno turno_aux sea el turno apuntado por cur. No se si está bien xd
                        printf("Valores: ..."); //Tiene que mostrar cada campo de turno_aux
                        forward_turno(&lista_turno); //avanza al siguiente
                    }while(!isOos_turno(lista_turno)); //Cur va a terminar apuntando a null
                    printf("\n");
                }
                else{
                    printf("Lista vacia.\n");
                };
                break;
            case 3:
                reset_turno(&lista_turno);
                printf("Elemento a buscar: \n");
                scanf("%d",&x);
                valor_econtrado = 0;
                while(!isOos_turno(lista_turno)&&!valor_econtrado){
                    if(lista_turno.cur->vipd == x) valor_econtrado = 1;
                    else forward_turno(&lista_turno);
                };
                if(isOos_turno(lista_turno)) printf("El elemento no existe.\n");
                else{
                supress_turno(&lista_turno);
                printf("Escriba un entero: \n");
                scanf(" %d", &x);
                insert_turno(&lista_turno, x);
                };
                break;
            case 4:
                if(!isEmpty_turno(lista_turno)&&!isOos_turno(lista_turno)){
                    supress_turno(&lista_turno);
                    printf("Elemento a eliminar: %d\n", lista_turno.cur->vipd);
                }
                else printf("Elemento no encontrado.\n");
                break;
            case 5:
                if(!isOos_turno(lista_turno)) forward_turno(&lista_turno);
                else printf("Error. No hay elemento siguiente. Aniada otro elemento xfis :3\n");
                break;
            case 0:
                break;
            default:
                printf("Input no valido. Reintente.\n");
        };
    }while(opc);
    reset_turno(&lista_turno);
    while(lista_turno.acc != NULL){
        supress_turno(&lista_turno);
    };
    return 0;
};
