#include <stdio.h>
#include <stdlib.h>
#include "listaD_turno.h"
#include "listaE_Cliente.h"
#include <conio.h>

//---Se definen Tratamientos ------------------
typedef struct{
    char nombre[26];
    float precio;
}Tratamiento;

//---Funciones-------------------------------------------
//a)---Carga un turno por teclado
void carga_turno(){
	printf("Se cargo un turno\n");
};

//b)---Funcion auxiliar que busca los turnos no realizados
void buscar_turno(){
	printf("Se busco un turno\n");
}

//c)---Funcion que muestra los turnos de todo un mes ordenado por fecha
void mostrar_turno_fecha(){
	printf("Se mostraron los turnos por fecha\n");
}

//d)---Funcion que muestra los turno por nombre de cliente
void mostrar_turno_nombre(){
	printf("Se mostraros los turnos por nombre de cliente\n");
}

//e)---Mostrar los turnos solicitados en el mes por idCliente. Mostrar fecha total y idTurno(recursiva)
void mostrar_turno_idCliente(){
	printf("Se mostraron los turnos solicidatos en el mes por idCliente\n");
}

//f)---Calcula la ganancia mensual considerando los turnos ya realizados(recursiva)
void ganancia_mensual(){
	printf("Se calculo la ganancia mensual de forma recursiva\n");
}

//g)---Muestra los turnos de la lista de turnos
void mostrar_lista_turnos(){
	printf("Se muestran todos los turnos\n");
}

//h)---Funcion que modifica la cantidad de tratamientos de un cliente registrado
void modifica_tratamiento(){
	printf("Modifica la cantidad de tratamientos\n");
}

//i)---Modifica la forma de pago de un turno segun idCliente(solo turnos no realizados)
void modifica_formapago(){
	printf("Modifica la forma de pago de un turno\n");
}

//j)---Cancelar turno por Id cliente. Detalles en el practico
void cancelar_turno(){
	printf("Cancela un turno\n");
};

//k)---Almacenar datos de los turnos pagados con alguna forma de pago
void almacenar_turnos_formapago(){
	printf("Se almacenaron los turnos con cierta forma de pago");
};

//l)---funcion que permite registrar un cliente
void registar_cliente(){
	printf("Se registro un cliente\n");
}

//m)---Muestra los turnos por tratamiento
void mostrar_turno_tratamiento(){
	printf("Se Mostraron los turnos por tratamiento\n");
}

//n)---Realizar una precarga automática al iniciar el programa de los clientes a la lista de Clientes. Debe contener al menos 10 clientes.
void precarga_clientes(){
	printf("Se precargaron los turnos\n");
}

//ñ)---Muestra los clientes almacenados en lista clientes
void mostrar_lista_clientes(){
	printf("Se mostraron los clientes almacenados en clientes.txt\n");
}

//o)---Elimina un cliente (los turnos no quedan afectados)
void eliminar_cliente(){
	printf("Se elimino un cliente\n");
}

//p)---Funcion que modifica un turno confirmado (si asiste se modifica realizado, can tratamientos y el nivel)
void modifica_turno_cliente(){
	printf("Se modifico un turno y los datos relacionados\n");
}

//q)---Muestra los turnos no realizados
void mostrar_turno_norealizado(){
	printf("Se mostraron los turnos no realizados\n");
}

//---Main------------------------------------------------
int main()
{

//--Inicializa Variables------------------------------
	//--Listas
    Lista_Turno lista_turno;
    init_lista_turno(&lista_turno);
    Turno turno_aux;
    init_turno(&turno_aux);

    Lista_Cliente lista_cliente;
    init_lista_cliente(&lista_cliente);
    Cliente cliente_aux;
    init_cliente(&cliente_aux);

    Tratamiento tratamientos[10];

    //--Variables simples
    char aux[500], tecla;
    int opc = 1, i;

    //--Abre archivos
    FILE *fp_clientes, *fp_turnos, *fp_menu, *fp_tratamientos;
    fp_clientes= fopen("clientes.txt", "w+");
    fp_turnos = fopen("turnos.txt", "w+");
    fp_tratamientos = fopen("tratamientos.txt", "r");
    fp_menu = fopen("menu.txt", "r");
//-----------------------------------------------------
	for(i = 0; i < 10; i++){ //Lee tratamientos
	fscanf(fp_tratamientos," %[^\n]s", tratamientos[i].nombre);
	fscanf(fp_tratamientos, " %f", &tratamientos[i].precio);
	};
//--Menu----------------------------------------------
do{
	opc = 1;
    do{
    	//Limpia consola
    	rewind(fp_menu);
		system("cls");
		i = 0;
		//Texto mostrado en consola para bienvenida
        while(!feof(fp_menu)){
			fscanf(fp_menu, "\n%[^\n]s", aux);
        	if(opc + 2 == i){
				aux[55] = '<';
				aux[56] = '<';
				aux[57] = '-';
        	};
			printf("%s\n", aux);
			++i;
		};

		tecla = getch();
			switch(tecla){
			case 72:
				if(opc > 1)opc--;
				break; //sube
			case 80:
				if(opc < 16)opc++;
				break; //baja
			default: break;
    	};
    }while(tecla != '\r');
    system("cls");
    switch(opc){
	case 1:
			carga_turno();
	break;
		case 2:
			mostrar_turno_fecha();
	break;
		case 3:
			mostrar_turno_nombre();
	break;
		case 4:
			mostrar_turno_idCliente();
	break;
		case 5:
			ganancia_mensual();
	break;
		case 6:
			mostrar_lista_turnos();
	break;
		case 7:
			modifica_formapago();
	break;
		case 8:
			cancelar_turno();
	break;
		case 9:
			almacenar_turnos_formapago();
	break;
		case 10:
			registar_cliente();
	break;
		case 11:
			mostrar_turno_tratamiento();
	break;
		case 12:
			mostrar_lista_clientes();
	break;
		case 13:
			eliminar_cliente();
	break;
		case 14:
			modifica_turno_cliente();
	break;
		case 15:
			mostrar_turno_norealizado();
	break;
		case 16:

	break;
	default:
		printf("Como elegiste esta opcion??");
		return 666;
    };
    system("pause");
}while(opc != 16);
//------------------------------------------------------

//--Libera memoria y cierra archivos--------------------
    reset_turno(&lista_turno);
    while(lista_turno.acc != NULL){
        supress_turno(&lista_turno);
    };
    fclose(fp_clientes);
    fclose(fp_turnos);
    fclose(fp_menu);
    fclose(fp_tratamientos);
    return 0;
};
