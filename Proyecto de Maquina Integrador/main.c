#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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

//---Adicionales ---------------------------------------
//---Funcion para ingresar un int valido:
int ingresar_int(int* x, int min, int max, char msg[], char err[]){
	*x = 0;
	do{
		printf(">>%s\n", msg);
		scanf(" %d", x);
		if(*x < min || *x > max){
			printf("%s\n", err);
			system("pause");
		};
		system("cls");
	}while(*x < min || *x > max);
	return *x;
};

//---Funcion para mostrar un turno
void muestra_turno(Turno t, int id_t, int nombre, int id_c, int fecha, int hora, int forma_pago, int tratamiento, int realizado, Tratamiento ts[]){
char* p; int i;
if(id_t){
	if((p = Get_id_turno(t))) printf(">>Turno: %s\n", p);
else printf(">>Error al obtener el turno.\n");
if(nombre){
	if((p = Get_nombre_turno(t))) printf(">>Nombre del Cliente: %s\n", p);
}
else printf(">>Error al obtener el nombre del cliente.\n");
};
if(p != NULL)free((void*)p);
if(id_c) printf(">>Id del Cliente: %ld\n", Get_id_cliente(t));
if(fecha) printf(">>Fecha del turno: %d-%d-%d\n", Get_dia(t), Get_mes(t), Get_anio(t));
if(hora) printf(">>Hora del turno: %dhs.\n", Get_hora(t));
if(tratamiento){
	printf(">>Tratamientos del turno:\n");
	for(i=0;i<10;i++){
		if(Get_tratamiento(t,i)) printf("   >>%s\n", ts[i].nombre);
	};
}
if(realizado){
	printf(">>Se realizo el turno: ");
	if(Get_realizado(t))printf("Si.\n");
	else {printf("No.\n");
};
};
};


//a)---Carga un turno por teclado
void carga_turno(Lista_Turno* l_t, Lista_Cliente* l_c, FILE *tratamientos){//verificar si es nuevo cliente o no
	Turno nuevo_turno, aux_turno;
	Cliente nuevo_cliente, aux_cliente;
	long int id;
	char nom[26],id_tur[26];
	int t,c, d, dia, mes, anio, hora;

	printf("Ingrese la id a buscar\n");scanf("%ld", &id);
	reset_cliente(l_c);
	while(!isOos_cliente(*l_c)){
		aux_cliente=copy_cliente(*l_c);
		if(Get_dni(aux_cliente)== id){  //verificar si el id ingresado esta registrado o no
		printf("EL id pertenece a un cliente registrado");
	    printf("----------------------------------------");
	    printf("Ingrese los datos del turno\n");
	    printf("Generando id_turno.......\n");//utilizar la funcion para generar un turno
	    //funcion
	    printf("Nombre del turno\n");
	    scanf("%[^\n]s",nom);
		printf("tratamientos\n Ingresa la cantidad de tratamientos a realizar(no mayor a 3):");
		scanf("%d", &t);
		printf("Elija una opcion\n");
			do{
				for(c=0; c<t; c++){
					printf("<1>unas \n <2> Limpieza facial \n <3>Masajes \n <4>Manicura\n <5>Pedicura\n <6>Depilacion \n <7>Pestañas \n <8>Peeling \n <9>Ondas Galvanicas\n <10>Botox\n"); scanf("%d", &d);
					d--;//posicion en el arreglo
					Set_tratamiento(&aux_turno, 1, d);
				}
			}while(t!=3 && t<0);//verifica que la cantidad de tratamientos sea correcta

			while(Get_dia(aux_turno)<01 && Get_dia(aux_turno)>31 && Get_mes(aux_turno)>13 &&
			  	Get_mes(aux_turno)<10 && Get_anio(aux_turno)!= 2024
			  	&& Get_hora(aux_turno)<9 && Get_hora(aux_turno)>20){//verifica que las fechas no esten fuera de lugar
				printf("Fecha(tiene que ser a partir del dia 01/11/2024 a las 9hs):");
				printf("dia: \n");scanf("%d",&dia);
				printf("mes: \n"); scanf("%d",&mes);
				printf("anio: \n"); scanf("%d",&anio);
				printf("Hora: \n"); scanf("%d",&hora);
			}
			printf("El total a pagar es");
			Set_nombre_turno(&aux_turno, nom);
			Set_dia(&aux_turno, dia);
			Set_mes(&aux_turno, mes);
			Set_anio(&aux_turno, anio);
			Set_hora(&aux_turno, hora);
			insert_turno(l_t,aux_turno);
	}

	else{fordward_cliente(l_c);}

	printf("Registrar clienten\n");
	registar_cliente();//colocar parametros de la funcion
	FILE *fp1=fopen("clientes.txt","a+");
	fprintf(fp1,"%d\n",dni);
	fprintf(fp1,"%s\n",nombre);
	fprintf(fp1,"%s\n",apellido);
	fprintf(fp1,"%d\n",cantidad_tratamientos);
	fprintf(fp1,"%d\n",nivel);
	//colocar en la funcion de mari---
	fclose(fp1);
	 printf("Ingrese los datos del turno\n");
	    printf("Generando id_turno.......\n");//utilizar la funcion para generar un turno
	    //funcion
	    printf("Nombre del turno\n");
	    scanf("%[^\n]s",nom);
		printf("tratamientos\n Ingresa la cantidad de tratamientos a realizar(no mayor a 3):");
		scanf("%d", &t);
		printf("Elija una opcion\n");
			do{
				for(c=0; c<t; c++){
					printf("<1>unas \n <2> Limpieza facial \n <3>Masajes \n <4>Manicura\n <5>Pedicura\n <6>Depilacion \n <7>Pestañas \n <8>Peeling \n <9>Ondas Galvanicas\n <10>Botox\n"); scanf("%d", &d);
					d--;//posicion en el arreglo
					Set_tratamiento(&aux_turno, 1, d);
				}
			}while(t!=3 && t<0);//verifica que la cantidad de tratamientos sea correcta

			while(Get_dia(aux_turno)<01 && Get_dia(aux_turno)>31 && Get_mes(aux_turno)>13 &&
			  	Get_mes(aux_turno)<10 && Get_anio(aux_turno)!= 2024
			  	&& Get_hora(aux_turno)<9 && Get_hora(aux_turno)>20){//verifica que las fechas no esten fuera de lugar
				printf("Fecha(tiene que ser a partir del dia 01/11/2024 a las 9hs):");
				printf("dia: \n");scanf("%d",&dia);
				printf("mes: \n"); scanf("%d",&mes);
				printf("anio: \n"); scanf("%d",&anio);
				printf("Hora: \n"); scanf("%d",&hora);
			}
			printf("El total a pagar es");
			Set_nombre_turno(&aux_turno, nom);
			Set_dia(&aux_turno, dia);
			Set_mes(&aux_turno, mes);
			Set_anio(&aux_turno, anio);
			Set_hora(&aux_cliente, hora);
			insert_turno(l_t, aux_turno);

	}
}

//b)---Funcion auxiliar que busca los turnos no realizados
void buscar_turno(){
	printf("Se busco un turno\n");
}

//c)---Funcion que muestra los turnos de todo un mes ordenado por fecha
void mostrar_turno_fecha(Lista_Turno *l, int m, Tratamiento ts[]){
	int d=1,h,cant_dias, n=0, o= 0, dia_mostrado;
	Turno t;
	if(m==11){ //Noviembre 30 d
		cant_dias = 30;
	}
	else{ //Diciembre 31 d
		cant_dias = 31;
	};
	for(;d<cant_dias; d++){ //Recorre por los 30 o 31 dias
		dia_mostrado = 0;
		for(h=9;h<20;h++){ //Recore por las horas
			reset_turno(l);
			while(!isOos_turno(*l)){
				t = copy_turno(*l);
				if(Get_mes(t)==m){
					if(Get_dia(t)==d){
						if(Get_hora(t)==h){ //Turno coincide en fecha y hora
							if(!dia_mostrado){
								printf(">>- - - - - -| %d / %d / %d |- - - - - -<<\n", Get_dia(t), Get_mes(t), Get_anio(t));
								dia_mostrado = 1;
							}
							printf(">>- - - - - - - - - - -\n");
							if(Get_realizado(t)) n++;
							else o++;
							muestra_turno(t,1,1,1,0,1,1,1,1,ts);
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
	Turno t;
	system("cls");
	int pag = 0, i,j, cant_elems = 0, cant_pags, e, semejantes;
	char tecla = 0, nom_aux[TAM_NOMBRE], min_aux[TAM_NOMBRE], cabecera[] = ">>=================== x / y ====================<<";
	reset_turno(l);
	// Cuenta Cuantos elementos coinciden con la busqueda
	while(!isOos_turno(*l)){
		t = copy_turno(*l);
		semejantes = 1;
		for(i = 0; i < strlen(nom_base); i++){
			if(nom_base[i] != Get_nombre_turno(t)[i]){
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
			//Busca las primeras n veces k se menciona el actual nombre mas peque�o
			while(!isOos_turno(*l) && !e){
				t = copy_turno(*l);
				if(!strcmp(Get_nombre_turno(t), min_aux)){e = 1; i++;}
				else forward_turno(l);
			};
			//Si ya no hay turnos a nombre de la misma persona
				//Para buscar el sig nombre mas cercano
			if(isOos_turno(*l)){
				reset_turno(l);
				strcpy(nom_aux,"zzzzzzzzzzzzzzz");
				while(!isOos_turno(*l)){
					t = copy_turno(*l);
					semejantes = 1;
					for(j = 0; j < strlen(nom_base); j++){ //Compara que el nombre empieze con lo buscado
						if(nom_base[j] != Get_nombre_turno(t)[j]){
							semejantes = 0;
							j = strlen(nom_base);
						};
					};
					if((strcmp(nom_aux,Get_nombre_turno(t)))>0 && strcmp(min_aux, Get_nombre_turno(t))<0 && semejantes){ //Si el nombre apuntado es tq min_aux<nom_t<nom_aux
						strcpy(nom_aux, Get_nombre_turno(t)); //Ahora aux es el nuevo nombre mas cercano
					};
					forward_turno(l);
				};

				//Ahora el nuevo min es el encontrado
				strcpy(min_aux, nom_aux);
				reset_turno(l);

			};
			if(i > 3*pag  && e){ //va a mostrar si es de los ult 3 y encontro uno que corresponda
				printf(">>- - - - - - - - - - -\n");
				muestra_turno(t,1,1,1,1,1,1,1,1,ts);
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
}

//e)---Mostrar los turnos solicitados en el mes por idCliente. Mostrar fecha total y idTurno(recursiva)
void mostrar_turno_idCliente(){
	printf("Se mostraron los turnos solicidatos en el mes por idCliente\n");
}

//f)---Calcula la ganancia mensual considerando los turnos ya realizados(recursiva)
float ganancia_mensual(Lista_Turno* l, int m){
	Turno t; float g;
	if((isOos_turno(*l))){
		return 0;
	}
	else{
		t = copy_turno(*l);
		if(Get_realizado(t) && Get_mes(t) == m){
			g = Get_total(t);
		};
		forward_turno(l);
		return g + ganancia_mensual(l,m);
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
	reset_turno(l);
	int e = 0;
	Turno t;
	while(!isOos_turno(*l)){
		t = copy_turno(*l);
		if(Get_id_cliente(t)==id){
			e = 1; //Se encontro un turno correspondiente al cliente
			if(!(Get_realizado(t))){
				Set_forma_pago(&(t), p);
				supress_turno(l);
				insert_turno(l,t);
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
void mostrar_turno_tratamiento(Lista_Turno* l, int id, Tratamiento ts[]){
	int n = 0, o = 0; Turno t;
	reset_turno(l);
	while(!isOos_turno(*l)){
		t = copy_turno(*l);
		if(Get_tratamiento(t,id)){
					printf(">>- - - - - - - - - - -\n");
					muestra_turno(t,1,1,1,1,1,1,1,1,ts);
					if(Get_realizado(t))n++;
					else o++;
		};
	forward_turno(l);
	};
	if(!n)printf("No se realizo ese tratamiento en ningun turno.\n");
	else printf("Se realizao un total de %d veces.\n",n);
	if(!o)printf("No quedan turnos sin realizar que incluyan ese tratamiento.\n");
	else printf("Quedan %d turnos por realizar con ese tratamiento.\n", o);
}

//n)---Realizar una precarga autom�tica al iniciar el programa de los clientes a la lista de Clientes. Debe contener al menos 10 clientes.
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

//�)---Muestra los clientes almacenados en lista clientes
void mostrar_lista_clientes(){
	printf("Se mostraron los clientes almacenados en clientes.txt\n");
}

//o)---Elimina un cliente (los turnos no quedan afectados)
void eliminar_cliente(){
	printf("Se elimino un cliente\n");
}

//p)---Funcion que modifica un turno confirmado (si asiste se modifica realizado, can tratamientos y el nivel)
int modifica_turno_cliente(Lista_Cliente* l_c, Lista_Turno* l_t, long int id){
	int c_encontrado = 0, t_encontrado = 0, i, cant_aux = 0; Turno t; Cliente c;
	reset_cliente(l_c); reset_turno(l_t);
	while(l_c->cur!=l_c->ultimo && !c_encontrado){
		c = copy_cliente(*l_c);
		if(Get_dni(c) == id) c_encontrado = 1; //El cliente existe
		else fordward_cliente(l_c);
	};
	if(!c_encontrado) return -1; //-1 -> El cliente no existe
	while(!isOos_turno(*l_t)&&!t_encontrado){
		t = copy_turno(*l_t);
		if(!Get_realizado(t) && id == Get_id_cliente(t)) t_encontrado = 1; //El turno existe
		else forward_turno(l_t);
	};
	if(!t_encontrado) return 0; //0 -> El turno no existe
	Set_realizado(&t,1);
	for(i = 0; i < 9; i++){
		cant_aux += Get_tratamiento(t, i);
	};
	cant_aux += Get_cant_tratamientos(c);
	Set_cant_tratamientos(&c, cant_aux); //cambia cant trats
	if(cant_aux > 11) cant_aux = 11;
	switch(cant_aux){ //modifica nivel
	case 1 ... 4: Set_nivel(&c,1); break;
	case 5 ... 10: Set_nivel(&c,2); break;
	case 11: Set_nivel(&c,3); break;
	};
	supress_turno(l_t);
	insert_turno(l_t,t);
	return 1; //Se modifico
}

//q)---Muestra los turnos no realizados
void mostrar_turno_norealizado(){
	printf("Se mostraron los turnos no realizados\n");
}

//---Main------------------------------------------------
int main(){

//--Inicializa Variables------------------------------

    //--Variables simples
    char arr_aux[500], tecla, nom_min[TAM_NOMBRE];
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
			system("pause");
	break;
		case 3:
			printf("Escriba el nombre que busca:\n");
			scanf("%s", nom_min);
			mostrar_turno_nombre(nom_min,&lista_turnos,tratamientos);
			system("pause");
	break;
		case 4:
			mostrar_turno_idCliente();
	break;
		case 5:
			reset_turno(&lista_turnos);
			ingresar_int(&mes,11,12,"Ingrese el mes de los turnos:\n>>11: Noviembre\n>>12: Diciembre", "Error, mes no valido. Reintente.");
			monto = ganancia_mensual(&lista_turnos,mes);
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
			ingresar_int(&forma_pago,1,4,"Ingrese el nuevo tipo de pago:\n1: Debito\n2:credito\n3: Codigo QR\n4: Efectivo","Error. El metodo no existe.");
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
			printf("Ingrese el tratamiento:\n1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n7. %s\n8. %s\n9. %s\n10. %s\n", tratamientos[0].nombre, tratamientos[1].nombre, tratamientos[2].nombre, tratamientos[3].nombre, tratamientos[4].nombre, tratamientos[5].nombre, tratamientos[6].nombre, tratamientos[7].nombre, tratamientos[8].nombre, tratamientos[9].nombre);
			ingresar_int(&tratamiento,1,10,"Tratamiento a buscar","Error. El tratamiento no existe. Reintente.");
			mostrar_turno_tratamiento(&lista_turnos, tratamiento-1, tratamientos);
			system("pause");
	break;
		case 12:
			mostrar_lista_clientes();
	break;
		case 13:
			eliminar_cliente();
	break;
		case 14:
			printf("Ingrese el dni:\n");
			scanf("%ld", &dni);
			res = modifica_turno_cliente(&lista_clientes, &lista_turnos, dni);
			switch(res){
			case 1: printf("Turno modificado exitosamente.\n"); break;
			case 0: printf("No tiene ningun turno sin realizar.\n"); break;
			case -1: printf("No existe un cliente con ese Id.\n"); break;
			};
			system("pause");
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
