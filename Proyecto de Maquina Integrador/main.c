#include <stdio.h>
#include <stdlib.h>
#include "listaD_turno.h"
#include "listaE_Cliente.h"
#include <conio.h>
#include <math.h>

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

//d)---Funcion que muestra los turno por nombre de cliente de a 3
void mostrar_turno_nombre(char nom_base[], Lista_Turno* l, Tratamiento ts[]){
	system("cls");
	int pag = 0, i,j,k, cant_elems = 0, cant_pags, e, semejantes;
	char tecla = 0, *nom_cur, nom_aux[TAM_NOMBRE], min_aux[TAM_NOMBRE], *p, cabecera[] = ">>=================== x / y ====================<<";
	reset_turno(l);
	// Cuenta Cuantos elementos coinciden con la busqueda
	while(!isOos_turno(*l)){
		nom_cur = Get_nombre_turno(l->cur->vipd);
		semejantes = 1;
		for(i = 0; i < strlen(nom_base); i++){
			if(nom_base[i] != nom_cur[i]){
					semejantes = 0;
					i = strlen(nom_base);
			};
		};
		if(semejantes) cant_elems ++;
		forward_turno(l);
	};
	cant_pags = (int)ceil(cant_elems/3);
	//Se ejecuta hasta que se sale
	while(tecla != 27){
		i = 0;
		cabecera[22] = 48 + pag + 1;
		cabecera[26] = 48 + cant_pags + 1;
		if(pag >= 1){
			cabecera[9] = ' ';
			cabecera[10] = '<';
			cabecera[11] = '-';
			cabecera[12] = '-';
			cabecera[13] = ' ';
		}
		else{
			cabecera[9] = '=';
			cabecera[10] = '=';
			cabecera[11] = '=';
			cabecera[12] = '=';
			cabecera[13] = '=';
		};
		if(pag <= cant_pags - 1){
			cabecera[strlen(cabecera)-14] = ' ';
			cabecera[strlen(cabecera)-13] = '-';
			cabecera[strlen(cabecera)-12] = '-';
			cabecera[strlen(cabecera)-11] = '>';
			cabecera[strlen(cabecera)-10] = ' ';
		}
		else{
			cabecera[strlen(cabecera)-10] = '=';
			cabecera[strlen(cabecera)-11] = '=';
			cabecera[strlen(cabecera)-12] = '=';
			cabecera[strlen(cabecera)-13] = '=';
			cabecera[strlen(cabecera)-14] = '=';
		};
		printf("%s\n",cabecera);
		strcpy(min_aux, nom_base); //El minimo ahora es el nombre base
		reset_turno(l); //Cur apunta al primero
		do{
			e = 0;
			//Busca las primeras n veces k se menciona el actual nombre mas pequeño
			while(!isOos_turno(*l) && !e){
				nom_cur = Get_nombre_turno(l->cur->vipd);
				if(!strcmp(nom_cur, min_aux)){e = 1; i++;}
				else forward_turno(l);
			};
			//Si ya no hay turnos a nombre de la misma persona
				//Para buscar el sig nombre mas cercano
			if(isOos_turno(*l)){
				reset_turno(l);
				strcpy(nom_aux,"zzzzzzzzzzzzzzz");
				while(!isOos_turno(*l)){
					nom_cur = Get_nombre_turno(l->cur->vipd);
					semejantes = 1;
					for(j = 0; j < strlen(nom_base); j++){ //Compara que el nombre empieze con lo buscado
						if(nom_base[j] != nom_cur[j]){
							semejantes = 0;
							j = strlen(nom_base);
						};
					};
					if((strcmp(nom_aux,nom_cur))>0 && strcmp(min_aux, nom_cur)<0 && semejantes){ //Si el nombre apuntado es tq min_aux<nom_cur<nom_aux, nom_cur empieza con lo buscado
						strcpy(nom_aux, nom_cur); //Ahora aux es el nuevo nombre mas cercano
					};
					forward_turno(l);
				};

				//Ahora el nuevo min es el encontrado
				strcpy(min_aux, nom_aux);
				reset_turno(l);

			};
			if(i > 3*pag  && e){ //va a mostrar si es de los ult 3 y encontro uno que corresponda
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
					if(Get_tratamiento(l->cur->vipd,k)){
						printf("   >>%s\n", ts[k].nombre);
					};
				};
				printf(">>Se realizo el turno: ");
				if(Get_realizado(l->cur->vipd)){printf("Si.\n");}
				else {printf("No.\n");};
			};
			if(e) forward_turno(l);
		}while(i < 3*(pag+1) && strcmp(nom_aux,"zzzzzzzzzzzzzzz"));
	printf(">>=====> Use las flechas. Escape para salir. <=====<<\n");
	tecla = getch();
	switch(tecla){
	case 75:
		if(pag > 0) pag--;
	break;
	case 77:
		if(pag < cant_pags) pag++;
	break;
	default: break;
	};
	system("cls");
	};
free((void*)nom_cur);
free((void*)p);
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
		fscanf(f, " %d\n", &cliente_aux.nivel);
		insert_cliente(l,cliente_aux);
		++n;
	};
	if(!feof(f)) printf("Se alcanzo el limite de clientes antes de finalizar la precarga.\n");
	else
		if(n == 0)printf("No hay clientes para precargar.\n");
		else printf("Se precargaron %d clientes exitosamente.\n", n);
	system("pause");
};


//---Precarga de los turnos
void precarga_turnos(Lista_Turno* l, FILE* f){
	Turno turno_aux;
	int n = 0, i;
	while(!feof(f)){
		fscanf(f, " %s", turno_aux.id_turno);
		fscanf(f, " %s", turno_aux.nombre_cliente_turno);
		fscanf(f, " %ld", &turno_aux.id_cliente);
		for(i = 0; i < 10; i++){
			fscanf(f, " %d", &turno_aux.tratamientos[i]);
		};
		fscanf(f, " %d", &turno_aux.forma_pago);
		fscanf(f, " %f", &turno_aux.total);
		fscanf(f, "%d-%d-%d %dhs", &turno_aux.fecha_turno.dia,&turno_aux.fecha_turno.mes, &turno_aux.fecha_turno.anio, &turno_aux.fecha_turno.hora);
		fscanf(f, " %d\n", &turno_aux.realizado);
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
<<<<<<< Updated upstream
    char arr_aux[500], tecla;
    int opc = 1, i, mes, forma_pago, res;
=======
    char arr_aux[500], tecla, nom_min[TAM_NOMBRE];
    int opc = 1, i, mes, forma_pago, res, tratamiento;
>>>>>>> Stashed changes
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
			ingresar_mes(&mes);
			mostrar_turno_fecha(&lista_turnos,mes,tratamientos);
	break;
		case 3:
			printf("Escriba el nombre que busca:\n");
			scanf("%s", nom_min);
			mostrar_turno_nombre(nom_min,&lista_turnos,tratamientos);
	break;
		case 4:
			mostrar_turno_idCliente();
	break;
		case 5:
			reset_turno(&lista_turnos);
			ingresar_mes(&mes);
			monto = ganancia_mensual(&lista_turnos,tratamientos,mes,0);
			if(monto){
				printf(">>La ganancia total de ");
				if(mes == 11) printf("noviembre");
				else printf("diciembre");
				printf(" fue de $%.2f.\n", monto);
			}
			else printf(">>No hubieron ganancias en el mes dado.\n");
			system("pause");
	break;
		case 6:
			mostrar_lista_turnos();
	break;
		case 7:
			printf(">>Ingrese el Id de cliente a buscar:\n");
			scanf("%ld", &dni);
			printf("Ingrese el nuevo tipo de pago:\n");
			scanf("%d", &forma_pago);
			res=modifica_formapago(&lista_turnos,dni,forma_pago);
			switch(res){
			case 1: printf(">>Se modifico exitosamente el pago.\n"); break;
			case 0: printf(">>El ultimo turno del cliente ya fue realizado. No se cambio la forma de pago.\n"); break;
			case -1: printf(">>No se encontraron turnos correspondientes al cliente.\n"); break;
			};
			system("pause");
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
<<<<<<< Updated upstream
			mostrar_turno_tratamiento();
=======
			printf("Ingrese el tratamiento:\n1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n7. %s\n8. %s\n9. %s\n10. %s\n", tratamientos[0].nombre, tratamientos[1].nombre, tratamientos[2].nombre, tratamientos[3].nombre, tratamientos[4].nombre, tratamientos[5].nombre, tratamientos[6].nombre, tratamientos[7].nombre, tratamientos[8].nombre, tratamientos[9].nombre);
			system("pause");
			ingresar_int(&tratamiento,1,10,"Tratamiento a buscar","Error. El tratamiento no existe. Reintente.");
			mostrar_turno_tratamiento(&lista_turnos, tratamiento-1, tratamientos);
			system("pause");
>>>>>>> Stashed changes
	break;
		case 12:
			mostrar_lista_clientes();
	break;
		case 13:
			eliminar_cliente();
	break;
		case 14:
<<<<<<< Updated upstream
			modifica_turno_cliente();
=======
			printf(">>Ingrese el Id de cliente a buscar:\n");
			scanf("%ld", &dni);
			res = modifica_turno_cliente(&lista_clientes, &lista_turnos, dni);
			switch(res){
			case 1: printf("Turno modificado exitosamente.\n"); break;
			case 0: printf("No tiene ningun turno sin realizar.\n"); break;
			case -1: printf("No existe un cliente con ese Id.\n"); break;
			};
			system("pause");
>>>>>>> Stashed changes
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
