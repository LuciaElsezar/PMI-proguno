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
	int d=1,h,k, cant_dias, n=0, o= 0, d_mostrado;
	char* p;
	if(m==11){ //Noviembre 30 d
		cant_dias = 30;
	}
	else{ //Diciembre 31 d
		cant_dias = 31;
	};
	for(;d<cant_dias; d++){ //Recorre por los 30 o 31 dias
		d_mostrado = 0;
		for(h=9;h<20;h++){ //Recore por las horas
			reset_turno(l);
			while(!isOos_turno(*l)){
				if(Get_mes(l->cur->vipd)==m){
					if(Get_dia(l->cur->vipd)==d){
						if(Get_hora(l->cur->vipd)==h){ //Turno coincide en fecha y hora
							if(!d_mostrado){
								printf(">>- - - - - - - - - - - - - - - -\n");
								printf("- ->> %d-%d-%d <<- -\n",Get_dia(l->cur->vipd), Get_mes(l->cur->vipd), Get_anio(l->cur->vipd));
								d_mostrado = 1;
							};
							printf(">>- - - - - - - - - - - - - - - -\n");
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
							printf(">>Hora del turno:%dhs.\n", Get_hora(l->cur->vipd));
							printf(">>Forma de pago: ");
							switch(Get_forma_pago(l->cur->vipd)){
							case DEBITO: printf("Debito."); break;
							case CREDITO: printf("Credito."); break;
							case QR: printf("Codigo QR."); break;
							case EFECTIVO: printf("Efectivo."); break;
							};
							printf("\n>>Tratamientos del turno:\n");
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
int modifica_formapago(Lista_Turno* l, int id, int p){
	reset_turno(l); int e = 0;
	while(!isOos_turno(*l)){
		if(Get_id_cliente(l->cur->vipd)==id){
			e = 1; //Se encontro un turno correspondiente al cliente
			if(!(Get_realizado(l->cur->vipd))){
				Set_forma_pago(&(l->cur->vipd), p);
				return 1; //1 -> exito
			};
		};
		forward_turno(l);
	};
	if(e) return 0;
	else return -1; //-1 -> turno no encontrado
};

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
void mostrar_turno_tratamiento(Lista_Turno* l, int t, Tratamiento ts[]){
	int k, r, n, o;
	char* p;
	reset_turno(l);
	while(!isOos_turno(*l)){
		if(Get_tratamiento(l->cur->vipd,t)){
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
					printf(">>Forma de pago: ");
					switch(Get_forma_pago(l->cur->vipd)){
					case DEBITO: printf("Debito."); break;
					case CREDITO: printf("Credito."); break;
					case QR: printf("Codigo QR."); break;
					case EFECTIVO: printf("Efectivo."); break;
					};
					printf("\n>>Otros tratamientos del turno:\n");
					for(k=0;k<10;k++){
						if(k != t){
							if(Get_tratamiento(l->cur->vipd,k)){
								printf("   >>%s\n", ts[k].nombre);
								r = 1;
							};
						};
					};
					if(!r) printf("   >>Ninguno\n");
					printf(">>Se realizo el turno: ");
					if(Get_realizado(l->cur->vipd)){printf("Si.\n");n++;}
					else {printf("No.\n");o++;};
			};
	forward_turno(l);
	};
	if(!n)printf("No se realizo ese tratamiento en ningun turno.\n");
	else printf("Se realizao un total de %d veces.\n",n);
	if(!o)printf("No quedan turnos sin realizar que incluyan ese tratamiento.\n");
	else printf("Quedan %d turnos por realizar con ese tratamiento.\n", o);
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
int modifica_turno_cliente(Lista_Cliente* l_c, Lista_Turno* l_t, long int id){
	int c_encontrado = 0, t_encontrado = 0, i, cant_aux = 0;
	reset_cliente(l_c); reset_turno(l_t);
	while(l_c->cur!=l_c->ultimo && !c_encontrado){
		if(Get_dni(l_c->VIPD[l_c->cur]) == id){c_encontrado = 1;} //El cliente existe
		else fordward_cliente(l_c);
	};
	if(!c_encontrado) return -1; //-1 -> El cliente no existe
	while(!isOos_turno(*l_t)&&!t_encontrado){
		if(!Get_realizado(l_t->cur->vipd)) t_encontrado = 1; //El turno existe
		else forward_turno(l_t);
	};
	if(!t_encontrado) return 0; //0 -> El turno no existe
	Set_realizado(&l_t->cur->vipd,1);
	for(i = 0; i < 9; i++){
		cant_aux += Get_tratamiento(l_t->cur->vipd, i);
	};
	cant_aux += Get_cant_tratamientos(l_c->VIPD[l_c->cur]);
	Set_cant_tratamientos(&l_c->VIPD[l_c->cur], cant_aux); //cambia cant trats
	if(cant_aux > 11) cant_aux = 11;
	switch(cant_aux){ //modifica nivel
	case 1 ... 4: Set_nivel(&l_c->VIPD[l_c->cur],1); break;
	case 5 ... 10: Set_nivel(&l_c->VIPD[l_c->cur],2); break;
	case 11: Set_nivel(&l_c->VIPD[l_c->cur],3); break;
	};
	return 1; //Se modifico
};

//q)---Muestra los turnos no realizados
void mostrar_turno_norealizado(){
	printf("Se mostraron los turnos no realizados\n");
}

//---Adicionales ---------------------------------------
//---Funcion para ingresar un mes valido:
int ingresar_int(int* x, int min, int max, char msg[],char err[]){
	do{
		system("cls");
		printf(">>%s:\n", msg);
		scanf(" %d", x);
		if(*x < min || *x > max){
			printf("%s\n", err);
			system("pause");
		};
	}while(*x < min || *x > max);
	return *x;
};


//---Main------------------------------------------------
int main(){

//--Inicializa Variables------------------------------

    //--Variables simples
    char arr_aux[500], tecla;
    int opc = 1, i, mes, forma_pago, res, tratamiento;
    float monto;
    long int dni;

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
			ingresar_int(&mes,11,12,"Ingrese el mes de los turnos:\n>>11: Noviembre\n>>12: Diciembre", "Error, mes no valido. Reintente.");
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
			ingresar_int(&mes,11,12,"Ingrese el mes de los turnos:\n>>11: Noviembre\n>>12: Diciembre", "Error, mes no valido. Reintente.");
			monto = ganancia_mensual(&lista_turnos,tratamientos,mes,0);
			if(monto){
				printf(">>La ganancia total de ");
				if(mes == 11) printf("noviembre");
				else printf("diciembre");
				printf(" fue de $%.2f.\n", monto);
			}
			else printf(">>No hubieron ganancias en el mes dado.\n");
	break;
		case 6:
			mostrar_lista_turnos();
	break;
		case 7:
			printf(">>Ingrese el Id de cliente a buscar:\n");
			scanf("%ld", &dni);
			printf("Ingrese el nuevo tipo de pago:\n");
			ingresar_int(&forma_pago,1,4,"Ingrese el nuevo tipo de pago:\n1: Debito\n2:credito\n3: Codigo QR\n4: Efectivo","Error. El metodo no existe.");
			res=modifica_formapago(&lista_turnos,dni,forma_pago);
			switch(res){
			case 1: printf(">>Se modifico exitosamente el pago.\n"); break;
			case 0: printf(">>El ultimo turno del cliente ya fue realizado. No se cambio la forma de pago.\n"); break;
			case -1: printf(">>No se encontraron turnos correspondientes al cliente.\n"); break;
			};
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
			printf("Ingrese el tratamiento:\n1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n7. %s\n8. %s\n9. %s\n10. %s\n", tratamientos[0].nombre, tratamientos[1].nombre, tratamientos[2].nombre, tratamientos[3].nombre, tratamientos[4].nombre, tratamientos[5].nombre, tratamientos[6].nombre, tratamientos[7].nombre, tratamientos[8].nombre, tratamientos[9].nombre);
			system("pause");
			ingresar_int(&tratamiento,1,10,"Tratamiento a buscar","Error. El tratamiento no existe. Reintente.");
			mostrar_turno_tratamiento(&lista_turnos, tratamiento-1, tratamientos);
	break;
		case 12:
			mostrar_lista_clientes();
	break;
		case 13:
			eliminar_cliente();
	break;
		case 14:
			printf(">>Ingrese el Id de cliente a buscar:\n");
			scanf("%ld", &dni);
			res = modifica_turno_cliente(&lista_clientes, &lista_turnos, dni);
			switch(res){
			case 1: printf("Turno modificado exitosamente.\n"); break;
			case 0: printf("No tiene ningun turno sin realizar.\n"); break;
			case -1: printf("No existe un cliente con ese Id.\n"); break;
			};
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
