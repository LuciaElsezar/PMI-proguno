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
    Lista lista;
    init_l(&lista);
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
                op_exitosa = insert_l(&lista, x);
                if(!op_exitosa){
                    printf("No hay espacio suficiente. Reintente.\n");
                };
                break;
            case 2:
                if(!isEmpty(lista)){
                    printf("Lista: \n");
                    reset_l(&lista);
                    do{
                        printf("%d\t", lista.cur->vipd);
                        forward_l(&lista);
                    }while(!isOos(lista));
                    reset_l(&lista);
                    printf("\n");
                }
                else{
                    printf("Lista vacia.\n");
                };
                break;
            case 3:
                reset_l(&lista);
                printf("Elemento a buscar: \n");
                scanf("%d",&x);
                valor_econtrado = 0;
                while(!isOos(lista)&&!valor_econtrado){
                    if(lista.cur->vipd == x) valor_econtrado = 1;
                    else forward_l(&lista);
                };
                if(isOos(lista)) printf("El elemento no existe.\n");
                else{
                pop_l(&lista);
                printf("Escriba un entero: \n");
                scanf(" %d", &x);
                insert_l(&lista, x);
                };
                break;
            case 4:
                if(!isEmpty(lista)&&!isOos(lista)){
                    pop_l(&lista);
                    printf("Elemento a eliminar: %d\n", lista.cur->vipd);
                }
                else printf("Elemento no encontrado.\n");
                break;
            case 5:
                if(!isOos(lista)) forward_l(&lista);
                else printf("Error. No hay elemento siguiente. Aniada otro elemento xfis :3\n");
                break;
            case 0:
                break;
            default:
                printf("Input no valido. Reintente.\n");
        };
    }while(opc);
    reset_l(&lista);
    while(lista.acc != NULL){
        pop_l(&lista);
    };
    return 0;
};
