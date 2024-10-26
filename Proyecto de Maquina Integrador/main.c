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
void mostrar_turno_fecha(Lista_Turno *l, int m, Tratamiento t[]){
	int d=1,h,k, cant_dias, n=0, o= 0;
	char* p;
	if(m==11){ //Noviembre 30 d
		cant_dias = 30;
	}
	else{ //Diciembre 31 d
		cant_dias = 31;
	};
	for(;d<cant_dias; d++){ //Recorre por los 30 o 31 dias
		for(h=9;h<20;h++){ //Recore por las horas
			reset_turno(l);
			while(!isOos_turno(*l)){
				if(Get_mes(l->cur->vipd)==m){
					if(Get_dia(l->cur->vipd)==d){
						if(Get_hora(l->cur->vipd)==h){ //Turno coincide en fecha y hora

							printf(">>- - - - - - - - - - -\n");
							if((p = Get_id_turno(l->cur->vipd)))
								printf(">>Turno: %s\n", p);
							else
								printf(">>Error al obtener el turno.\n");
							free((void*)p);
							if((p = Get_nombre_turno(l->cur->vipd)))
								printf(">>Nombre del Cliente: %s\n", p);
							else
								printf(">>Error al obtener el nombre del cliente.\n");
							free((void*)p);
							printf(">>Id del Cliente: %ld\n", Get_id_cliente(l->cur->vipd));
							printf(">>Fecha del turno: %d-%d-%d, %dhs.\n", Get_dia(l->cur->vipd), Get_mes(l->cur->vipd), Get_anio(l->cur->vipd), Get_hora(l->cur->vipd));
							printf(">>Tratamientos del turno:\n");
							for(k=0;k<10;k++){
								if(Get_tratamiento(l->cur->vipd,k)){
									printf("   >>%s\n", t[k].nombre);
								};
							};
							printf(">>Se realizo el turno: ");
							if(Get_realizado(l->cur->vipd)){printf("Si.\n");n++;}
							else {printf("No.\n");o++;};
						};
					};
				};
			forward_turno(l);
			};
		};
	};
	if(!n)printf("No se realizaron turnos en el mes dado.\n");
	else printf("Se realizaron un total de %d turnos en el mes.\n",n);
	if(!o)printf("No quedan turnos sin realizar.\n");
	else printf("Quedan %d turnos por realizar.\n", o);
};

//d)---Funcion que muestra los turno por nombre de cliente
void mostrar_turno_nombre(){
	printf("Se mostraros los turnos por nombre de cliente\n");
}

//e)---Mostrar los turnos solicitados en el mes por idCliente. Mostrar fecha total y idTurno(recursiva)
void mostrar_turno_idCliente(){
	printf("Se mostraron los turnos solicidatos en el mes por idCliente\n");
}

//f)---Calcula la ganancia mensual considerando los turnos ya realizados(recursiva)
float ganancia_mensual(Lista_Turno* l, Tratamiento t[], int m, float g){
	if((isOos_turno(*l))){
		return 0;
	}
	else{
		if(Get_realizado(l->cur->vipd)){
			g+= Get_total(l->cur->vipd);
		};
		forward_turno(l);
		return g + ganancia_mensual(l,t,m,g);
	};
};

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
void precarga_clientes(Lista_Cliente* l, FILE* f){
	Cliente cliente_aux;
	int n = 0;
	while(!feof(f)&&!isFull_cliente(*l)){
		fscanf(f, " %ld", &cliente_aux.dni);
		fscanf(f, " %[^\n]s", cliente_aux.nombre);
		fscanf(f, " %[^\n]s", cliente_aux.apellido);
		fscanf(f, " %d", &cliente_aux.cant_tratamientos);
		fscanf(f, " %d", &cliente_aux.nivel);
		insert_cliente(l,cliente_aux);
		++n;
	};
	if(!feof(f)) printf("Se alcanzo el limite de clientes antes de finalizar la precarga.\n");
	else
		if(n == 0)printf("No hay clientes para precargar.\n");
		else printf("Se precargaron %d clientes exitosamente.\n", n);
	system("pause");
};

void precarga_turnos(Lista_Turno* l, FILE* f){
	Turno turno_aux;
	int n = 0, i;
	while(!feof(f)){
		fscanf(f, " %[^\n]s", turno_aux.id_turno);
		fscanf(f, " %[^\n]s", turno_aux.nombre_cliente_turno);
		fscanf(f, " %ld", &turno_aux.id_cliente);
		for(i = 0; i < 10; i++){
			fscanf(f, " %d", &turno_aux.tratamientos[i]);
		};
		fscanf(f, " %d", &turno_aux.forma_pago);
		fscanf(f, " %f", &turno_aux.total);
		fscanf(f, "%d-%d-%d %dhs", &turno_aux.fecha_turno.dia,&turno_aux.fecha_turno.mes, &turno_aux.fecha_turno.anio, &turno_aux.fecha_turno.hora);
		fscanf(f, " %d", &turno_aux.realizado);
		insert_turno(l,turno_aux);
		++n;
	};
	if(n == 0)printf("No hay clientes para precargar.\n");
	else printf("Se precargaron %d turnos exitosamente.\n", n);
	system("pause");
};

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

//---Adicionales ---------------------------------------
//---Funcion para ingresar un mes valido:
int ingresar_mes(int* m){
	*m = 0;
	do{
		system("cls");
		printf(">>Ingrese el mes cuyos turnos desee mostrar:\n");
		scanf(" %d", m);
		if(*m != 11 && *m != 12){
			printf("Ingreso un mes invalido. Reintente.\n");
			system("pause");
		};
	}while(*m != 11 && *m != 12);
	return *m;
};


//---Main------------------------------------------------
int main(){

//--Inicializa Variables------------------------------

    //--Variables simples
    char arr_aux[500], tecla;
    int opc = 1, i, mes, int_aux_1, int_aux_2;
    float float_aux_1;

    //--Abre archivos
    FILE *fp_clientes, *fp_turnos, *fp_menu, *fp_tratamientos;
    fp_clientes= fopen("clientes.txt", "r+");
    if(fp_clientes == NULL){
		printf("Error al abrir clientes.txt.");
		exit(1);
    };
    fp_turnos = fopen("turnos.txt", "r+");
    if(fp_turnos == NULL){
		printf("Error al abrir turnos.txt.");
		exit(1);
    };
    fp_tratamientos = fopen("tratamientos.txt", "r");
    if(fp_tratamientos == NULL){
		printf("Error al abrir tratamientos.txt.");
		exit(1);
    };
    fp_menu = fopen("menu.txt", "r");
    if(fp_menu == NULL){
		printf("Error al abrir menu.txt.");
		exit(1);
    };

	//--Listas
    Lista_Turno lista_turnos;
    init_lista_turno(&lista_turnos);

    Lista_Cliente lista_clientes;
    init_lista_cliente(&lista_clientes);

    Tratamiento tratamientos[10];
//-----------------------------------------------------
//---Carga datos de los archivos

	for(i = 0; i < 10; i++){ //Lee tratamientos
	fscanf(fp_tratamientos," %[^\n]s", tratamientos[i].nombre);
	fscanf(fp_tratamientos, " %f", &tratamientos[i].precio);
	};

	precarga_clientes(&lista_clientes,fp_clientes);
	precarga_turnos(&lista_turnos, fp_turnos);
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
			fscanf(fp_menu, "\n%[^\n]s", arr_aux);
        	if(opc + 2 == i){
				arr_aux[55] = '<';
				arr_aux[56] = '<';
				arr_aux[57] = '-';
        	};
			printf("%s\n", arr_aux);
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
			ingresar_mes(&mes);
			mostrar_turno_fecha(&lista_turnos,mes,tratamientos);
	break;
		case 3:
			mostrar_turno_nombre();
	break;
		case 4:
			mostrar_turno_idCliente();
	break;
		case 5:
			reset_turno(&lista_turnos);
			ingresar_mes(&mes);
			float_aux_1 = ganancia_mensual(&lista_turnos,tratamientos,mes,0);
			if(float_aux_1){
				printf(">>La ganancia total de ");
				if(mes == 11) printf("noviembre");
				else printf("diciembre");
				printf(" fue de $%.2f.\n", float_aux_1);
			}
			else printf(">>No hubieron ganancias en el mes dado.\n");
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
		printf("Como elegiste esta opcion??"); //No se puede elegir jaja
		return 666;
    };
    system("pause");
}while(opc != 16);
//------------------------------------------------------

//--Libera memoria y cierra archivos--------------------
    reset_turno(&lista_turnos);
    while(!isEmpty_turno(lista_turnos)){
        supress_turno(&lista_turnos);
    };
    fclose(fp_clientes);
    fclose(fp_turnos);
    fclose(fp_menu);
    fclose(fp_tratamientos);
    return 0;
};
