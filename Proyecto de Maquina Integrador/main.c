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

//---Cuenta cantidad total de turnos
int contar_turnos(Lista_Turno* l){
int i = 0;
reset_turno(l);
while(!isOos_turno(*l)){
	i++;
	forward_turno(l);
};
return i;
};

//---Genera Hexadecimal
void generar_hex(char hex[]){ //Devuelve un puntero. Luego hay que liberar la memoria utilizada
int j = strlen(hex)-1, sig = 1;
	while(sig){
		switch(hex[j]){
		case '0' ... '8':
		case 'a' ... 'e':
			hex[j]++; sig = 0; break; //del 0 al 8 y de la a a la e slo hay que pasar al sig char
		case '9': hex[j] = 'a'; sig = 0; break; //Si vale nueve, pasa a ser una a
		case 'f': hex[j] = '0'; j--; break; //Si es una f, pasa a ser un 0, y revisa el valor del siguiente
		};
	};
};

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

//l)---funcion que permite registrar un cliente
int registar_cliente(Lista_Cliente *l){
	if(isFull_cliente(*l)){
		printf("Arreglo de clientes lleno. No se pueden agregar mas clinetes.");
		return 0;
	};
    long int DNI;
    char nombre[TAM_NOMBRE];
    char apellido[TAM_NOMBRE];
    Cliente c;//se guarda lo leido aca
	printf("Eligio registrar un cliente\n");
	printf("Ingresa el ID o DNI del cliente:\n ");
        scanf("%ld", &DNI);
        Set_dni(&c, DNI);
	printf("Ingrese el nombre del cliente \n");
        scanf(" %[^\n]s", nombre);
            Set_nombre_cliente(&c, nombre);
    printf("Ingrese el apellido\n");
        scanf(" %[^\n]s", apellido);
            Set_apellido_cliente(&c, apellido);
            Set_cant_tratamientos(&c, 0);
    Set_nivel(&c, 0);
    insert_cliente(l, c);
    return 1;
};


//a)---Carga un turno por teclado
int carga_turno(Lista_Turno* l_t, Lista_Cliente* l_c, Tratamiento ts[], int* cant_turnos){//verificar si es nuevo cliente o no
	Turno aux_turno;
	Cliente aux_cliente;
	long int id;
	char id_t[TAM_ID_TURNO], nom_t[TAM_NOMBRE*2-1], nom_c[TAM_NOMBRE], *p_n, *p_id;
	int c = 0, d, dia, mes, hora, e, i, j, cant_tratamientos;
	float monto = 0, descuento = 0;
	printf("Ingrese la id a buscar\n");scanf("%ld", &id);
	reset_turno(l_t);
	reset_cliente(l_c);
	for(i = 0; i < *cant_turnos; i++){
	forward_turno(l_t);
	};
	aux_turno = copy_turno(*l_t);
	p_id = Get_id_turno(aux_turno);
	strcpy(id_t,p_id); //Ahora se sabe el ultimo id_turno B)
	free((void*)p_id);
	reset_turno(l_t);
	while(!isOos_cliente(*l_c) && !e){
		aux_cliente=copy_cliente(*l_c);
		if(Get_dni(aux_cliente)== id){  //verificar si el id ingresado esta registrado o no
		e = 1;
		printf("EL id pertenece a un cliente registrado\n");
	    printf("----------------------------------------\n");
		}
	else forward_cliente(l_c);
	};
	if(isOos_cliente(*l_c)){
	ingresar_int(&i,0,1,"El cliente no existe. Desea registrar un cliente nuevo?\n1: si\n0:no","Error. Opcion no valida. Reintente.");
	if(i){
		if(!registar_cliente(l_c))return -1; //Devuelve -1 si el arr ya esta lleno. Sino sigue con normalidad
	}
	else return 0; //El cliente no existia y no se registro, por lo que no se registra ningun turno.
	};
	//---Genera un turno
	 generar_hex(id_t);
	    //---Genera el nombre del turno, sin espacios
	    i = 0; j = 0; p_n = Get_nombre_cliente(aux_cliente);
	    strcpy(nom_c, p_n);
	    while(nom_c[i]!='\0'){
		    if(nom_c[i]!=' '){
				nom_t[j] = nom_c[i];
				j++;
		    };
		    i++;
	    };
	    i = 0; p_n = Get_apellido_cliente(aux_cliente);
	    strcpy(nom_c, p_n);
	    while(nom_c[i]!='\0'){
		    if(nom_c[i]!=' '){
				nom_t[j] = nom_c[i];
				j++;
		    };
		    i++;
	    };
	    nom_t[j] = '\0';
		free((void*)p_n);
	    //---Ingresa datos turno
	    printf(">>--------Ingrese los datos del turno\n-----------");
	    //Tratamientos
		ingresar_int(&cant_tratamientos,1,3,"tratamientos\n Ingresa la cantidad de tratamientos a realizar(no mayor a 3):","Error. Cantidad de tratamientos invalida.");
		printf("Elija una opcion\n");
		for(i = 0; i < 10; i++){
			Set_tratamiento(&aux_turno,0,i);
		};
		do{
				ingresar_int(&d, 1,10,"<1>unas \n <2> Limpieza facial \n <3>Masajes \n <4>Manicura\n <5>Pedicura\n <6>Depilacion \n <7>Pestañas \n <8>Peeling \n <9>Ondas Galvanicas\n <10>Botox\n", "Error. Reintente nuevamente");
				Set_tratamiento(&aux_turno,1,d-1);
				descuento += ts[d-1].precio*0.05*Get_nivel(aux_cliente);
				monto += ts[d-1].precio;
				c++;
		}while(c < cant_tratamientos-1);//verifica que la cantidad de tratamientos sea correcta
		//Ingresa fecha
		printf("Ingreso de la fecha:\n");
		ingresar_int(&mes,11,12,"Ingrese el mes:\n11: noviembre\n12:diciembre","Error. Mes invalido");
		if(mes == 11)ingresar_int(&dia,1,30,"Ingrese el dia","Dia no valido. Reintente.");
		else ingresar_int(&dia,1,31,"Ingrese el dia","Dia no valido. Reintente.");
		ingresar_int(&hora,9,20,"Ingrese la hora del turno. Entre las 9 y 20 hs.","Error. Fuera de horario.");
		monto -= descuento;
		if(!descuento) printf("Hubo un descuento total de &%.2f\n", descuento);
		printf("El total a pagar es: $%.2f\n", monto);
		Set_nombre_turno(&aux_turno, nom_t);
		Set_id_turno(&aux_turno,id_t);
		Set_id_cliente(&aux_turno,Get_dni(aux_cliente));
		Set_dia(&aux_turno, dia);
		Set_mes(&aux_turno, mes);
		Set_anio(&aux_turno, 2024);
		Set_hora(&aux_turno, hora);
		Set_realizado(&aux_turno,0);
		if(insert_turno(l_t,aux_turno)){
				cant_turnos += 1;
			return 1; //Se registro un turno exitosamente
		}else return -1; //Error al generar el nodo
};


//b)---Funcion auxiliar que busca los turnos no realizados
int buscar_turno(Lista_Turno *l,long int idcliente){
	int e=0;
	reset_turno(l);
	while(!isOos_turno(*l)){
       Turno busca_turno = copy_turno(*l);
        if(Get_id_cliente(busca_turno) == idcliente){
                printf("Entro\n");
                e++;
            if(Get_realizado(busca_turno) == 0){
              return 1; //se encontro un turno no realizado
            }
        }
        forward_turno(l);
    };//end while
    if (e == 0){
        return 0;//no se encontro la id del cliente
	}
	else{
		return -1;//cliente encontrado
	}
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

//e)---Mostrar los turnos solicitados en el mes por idCliente. Mostrar fecha, total y idTurno(recursiva)
int mostrar_turno_idCliente(Lista_Turno *l, Turno* nuevo, long int id, int mes, int* cant){
        if(isOos_turno(*l)){
            printf("Se mostraron los turnos\n.");
            return *cant;
        }
        else{
			*nuevo=copy_turno(*l);
			if(Get_id_cliente(*nuevo) == id && Get_mes(*nuevo) == mes){
			printf(">>Fecha: %d/%d/%d \n", Get_dia(*nuevo), Get_mes(*nuevo),  Get_anio(*nuevo));
			printf(">>Hora: %d\n", Get_hora(*nuevo));
			printf(">>Total: %.2f\n", Get_total(*nuevo));
			printf(">>IdTurno: %s\n", Get_id_turno(*nuevo));
			*cant += 1;
            };
            forward_turno(l);//avanzar turno
            mostrar_turno_idCliente(l,nuevo, id, mes, cant);
        };
};

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
void mostrar_lista_turnos(Lista_Turno *l, Tratamiento tratamientos[]){
	reset_turno(l); Turno t_aux;
	while(!isOos_turno(*l)){
	t_aux = copy_turno(*l);
	muestra_turno(t_aux,1,1,1,1,1,1,1,1,tratamientos);
	forward_turno(l);
	};
};

//h)---Funcion que modifica la cantidad de tratamientos de un cliente registrado
int modifica_tratamiento(Lista_Cliente *l,int cant,long int id_modifico){
	printf("Modifica la cantidad de tratamientos\n");
	reset_cliente(l);
	while(!isOos_cliente(*l)){
        Cliente modificar;
        modificar= copy_cliente(*l);
        if(Get_dni(modificar) == id_modifico){
            int cant_total = Get_cant_tratamientos(modificar)+cant;
            Set_cant_tratamientos(&modificar, cant_total);
            supress_cliente(l);
            insert_cliente(l,modificar);
            return 1;//exito
        }else{
        forward_cliente(l);
        }
	}
	return -1;//turno no se encontro
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
int cancelar_turno(Lista_Turno *l, FILE *fp1,long int id_buscada){
    int i;
	reset_turno(l);
    while(!isOos_turno(*l)){
        Turno lista=copy_turno(*l);
        if(Get_id_cliente(lista) == id_buscada){
            printf("Turno encontrado.\n");
                printf(">>Desea confirmar la eliminacion del Turno.\n");
                while(i == 1){
                    printf("Para confirmar presione 1 para cancelar presione 0.\n");
                    scanf("%d",&i);
                    switch(i){
                    case 0:return 2;//cancelando la eliminacion del turno
                    case 1:fprintf(fp1,"%s\n",Get_id_turno(lista));//id turno
                    fprintf(fp1,"%s\n",Get_nombre_turno(lista)); //nombre cliente
                    fprintf(fp1,"%ld\n",Get_id_cliente(lista)); //id cliente
                    //fprintf(fp1,"%d\n",Get_tratamiento(lista,t)); //tratamientos
                    fprintf(fp1,"%d\n",Get_forma_pago(lista)); //forma de pago
                    fprintf(fp1,"%.2f\n",Get_total(lista)); //total
                    supress_turno(l);return 1;//se pudo guardar el turno cancelado
                    default:printf(">>ERROR no es una opcion valida.\n");break;
                    }
                }
        }else{
        forward_turno(l);
        }
    }return 0;//no se a podido eliminar el turno
};

//k)---Almacenar datos de los turnos pagados con alguna forma de pago
int almacenar_turnos_formapago(Lista_Turno *l,int forma_pago, FILE *fp1){
	printf("Se almacenaron los turnos con cierta forma de pago");
	int cont;
	reset_turno(l);
	while(!isOos_turno(*l)){
        Turno var_pago = copy_turno(*l);
        if(Get_forma_pago(var_pago) == forma_pago){
            if(Get_realizado(var_pago) == 1){
                fprintf(fp1,"%s\n",Get_id_turno(var_pago));//id turno
                fprintf(fp1,"%s\n",Get_nombre_turno(var_pago));//nombre turno
                fprintf(fp1,"%ld\n",Get_id_cliente(var_pago));//id cliente
                //fprintf(fp1,"%d",Get_tratamiento(var_pago,t));//tratamientos
                fprintf(fp1,"%.2f\n",Get_total(var_pago));//total a pagar
                fprintf(fp1,"%d/%d/%d\n",Get_dia(var_pago),Get_mes(var_pago),Get_anio(var_pago));//fecha
                fprintf(fp1,"%d\n",Get_hora(var_pago));//hora
                fprintf(fp1,"%d\n",Get_forma_pago(var_pago));
                cont++;
            }
        }else{
        forward_turno(l);
        }
    }//end while
    return cont;
};

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

//ñ)---Muestra los clientes almacenados en lista clientes
void mostrar_lista_clientes(Lista_Cliente *L){
	printf("Se mostraron los clientes almacenados en la lista de clientes\n");
	reset_cliente(L);
	Cliente actual;
        do{
            actual=copy_cliente(*L);
            printf("Id del cliente: %ld\n ", Get_dni(actual));
            printf("Nombre del cliente: %s\n", Get_nombre_cliente(actual));
            printf("Apellido del cliente: %s\n", Get_apellido_cliente(actual));
            printf("Cantidad de tratamientos del cliente: %d\n", Get_cant_tratamientos(actual));
            printf("Nivel del cliente: %d\n", Get_nivel(actual));
            printf("-------------------------------------------\n");
            forward_cliente(L);//avanzar al siguiente turno
        }while(!isOos_cliente(*L)); //la funcion sigue hasta que el cursor este en el ultimo
}


//o)---Elimina un cliente (los turnos no quedan afectados)
int eliminar_cliente(Lista_Cliente *l, long int id_cliente){
    int e=0 ;int i;
	reset_cliente(l);
	while(!isOos_cliente(*l)){
        Cliente elimina_cliente = copy_cliente(*l);
        if(Get_dni(elimina_cliente) == id_cliente){
            e++;
            while(i != 1){
                printf(">>Desea confirmar la eliminmacion\n");
                printf(">>Presione 1 para confirmar o 0 para cancelar\n");
                scanf("%d",&i);
                    switch(i){
                            case 1: supress_cliente(l);return 1;// se elimino correctamente
                            case 0: return 2;
                            default:printf(">>ERROR seleccione una opcion valida\n");
                            }
                }
        }else{
        forward_cliente(l);
        }
	}//end while
	if(e == 0){
        return -1;//cliente no existente
	}else{
	return 0;//cliente encontrado
	}
};

//p)---Funcion que modifica un turno confirmado (si asiste se modifica realizado, can tratamientos y el nivel)
int modifica_turno_cliente(Lista_Cliente* l_c, Lista_Turno* l_t, long int id){
	int c_encontrado = 0, t_encontrado = 0, i, cant_aux = 0; Turno t; Cliente c;
	reset_cliente(l_c); reset_turno(l_t);
	while(l_c->cur!=l_c->ultimo && !c_encontrado){
		c = copy_cliente(*l_c);
		if(Get_dni(c) == id) c_encontrado = 1; //El cliente existe
		else forward_cliente(l_c);
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
void mostrar_turno_norealizado(Lista_Turno *l, FILE *archivo){//usar reset antes de llamar a la funcion
    long int id_cliente;
    int FormaPago, contador, tratamiento_i; int n;
    char linea[100];
    reset_turno(l);
    Turno x;//almacena el turno actual
	printf("Se mostraran los turnos no realizados\n");
	do{
        forward_turno(l);
        x=copy_turno(*l);
        id_cliente=Get_id_cliente(x);
        n = buscar_turno(l, id_cliente);

        if(n==1) { //si el turno no fue realizado
        printf(">>Turno Id turno: %s \n", Get_id_turno(x));
        printf(">>Nombre del cliente: %s\n", Get_nombre_turno(x));
        printf(">>Turno Id cliente: %ld\n", Get_id_cliente(x));
        printf(">>Tratamientos:");
        //-----TRATAMIENTOS------------
        int i;
         for (i=0; i<10; i++){//recorre el arreglo
                tratamiento_i=Get_tratamiento(x, i);//Obtiene el valor en i del arrelgo
            if(tratamiento_i==1){//verifica si el tratamiento se hizo
                int m=i+1;//linea del archivo que corresponde al tratamiento actual


                //reinicia el puntero del archivo al inicio, tambien el contador
                rewind(archivo);
                contador=0;

                //busca la linea
                    while (fgets(linea, sizeof(linea), archivo)){//el bucle sigue hasta que devuelva NULL(fin archivo)
                    contador++;//linea del archivo
                        if (contador == m) { // Verifica si es la línea deseada
                        printf("%s", linea);
                            break; // Termina después de encontrar la línea, sigue el for
                        }
                    }
            }
         }
        }
	    printf(">>Turno forma de pago: ");
	    FormaPago=Get_forma_pago(x);
	    switch(FormaPago){
    case 1:
        printf(">>>Debito\n"); break;
    case 2:
        printf(">>>Credito\n"); break;
    case 3:
        printf(">>>QR\n"); break;
    case 4:
        printf(">>>Efectivo\n"); break;
}
	    printf(">>Turno total a pagar: %.2f", Get_total(x));
	}while(!isOos_turno(*l));
}


//---Main------------------------------------------------
int main(){

//--Inicializa Variables------------------------------

    //--Variables simples
//<<<<<<< Updated upstream
    char arr_aux[500], tecla, nom_min[TAM_NOMBRE];
    int opc = 1, i, mes, forma_pago, res, tratamiento, can, Mes, acum, cantidad_turnos;
//>>>>>>> Stashed changes
    float monto;
    long int dni;
    Turno nuevo;
    //--Abre archivos
    FILE *fp_clientes, *fp_turnos, *fp_menu, *fp_tratamientos, *fp_turnos_cancelados , *fp_turnos_formapago;

	fp_turnos_cancelados= fopen("turnos_cancelados.txt","r+");
    if(fp_turnos_cancelados == NULL){
        printf("Error al abrir turnos_cancelados.txt.");
		exit(1);
    };
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

	cantidad_turnos = contar_turnos(&lista_turnos);
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
			//carga_turno();
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
            reset_turno(&lista_turnos);
            printf("Ingresa el id del cliente\n");scanf("%ld", &dni);
            printf("ingresa el mes 11 o 12"); scanf("%d", &Mes);

			can=mostrar_turno_idCliente(&lista_turnos, &nuevo, dni, Mes, &acum);
			printf("acum es %d\n",can);
			if(can==0)
                printf("No se encontro un turno con ese Id\n");
                system("pause");
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
		if(!isEmpty_turno(lista_turnos)){
            mostrar_lista_turnos(&lista_turnos, tratamientos);
			}
			else
                printf(">>No hay turnos para mostrar, cargue los turnos y vuelva a intentar\n");
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
            printf("Ingrese la Id del cliente\n");
            scanf("%ld", &dni);
			res = cancelar_turno(&lista_turnos,fp_turnos_cancelados,dni);
			switch(res){
                case 0:printf(">>No se encontro el dni del cliente.\n");break;
                case 1:printf(">>Se elimino el turno con exito.\n");break;
                case 2:printf(">>Usted cancelo la eliminacion del cliente.\n");break;
               }
			 system("pause");
        break;
		case 9:
            printf("Ingrese el metodo de pago\n");
		    scanf("%d", &forma_pago);
			printf("La cantidad de clientes almacenados es: %d\n", (almacenar_turnos_formapago(&lista_turnos, forma_pago, fp_turnos)));
			system("pause");
	break;
		case 10:
			if(!isFull_cliente(lista_clientes)){
            registar_cliente(&lista_clientes);
		    }
		    else
                printf("No se pueden almacenar mas clientes. Refresque\n");
                system("pause");
	break;
		case 11:
			printf("Ingrese el tratamiento:\n1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n7. %s\n8. %s\n9. %s\n10. %s\n", tratamientos[0].nombre, tratamientos[1].nombre, tratamientos[2].nombre, tratamientos[3].nombre, tratamientos[4].nombre, tratamientos[5].nombre, tratamientos[6].nombre, tratamientos[7].nombre, tratamientos[8].nombre, tratamientos[9].nombre);
			ingresar_int(&tratamiento,1,10,"Tratamiento a buscar","Error. El tratamiento no existe. Reintente.");
			mostrar_turno_tratamiento(&lista_turnos, tratamiento-1, tratamientos);
			system("pause");
	break;
		case 12:
		    if(!isEmpty_cliente(lista_clientes)){
			mostrar_lista_clientes(&lista_clientes);
			}
			else {
                printf("No hay clientes cargados. Ingresa clientes\n");}
                system("pause");
	break;
		case 13:
			 printf("Ingrese el id del cliente\n");
		    scanf("%ld", &dni);
		    if(!isEmpty_cliente(lista_clientes)){
			res = eliminar_cliente(&lista_clientes,dni);
            switch(res){
            case 1:printf(">> Se elimino el cliente con exito.\n"); break;
            case 0:printf(">> No se logro eliminar al cliente.\n"); break;
            case -1:printf(">> El cliente no fue encontrado.\n"); break;
            case 2:printf(">>Usted cancelo la eliminacion del cliente.\n");break;
			}
		    }else printf(">>ERROR no hay clientes anotados.\n");
			system("pause");
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
		    if(!isEmpty_turno(lista_turnos)){
			mostrar_turno_norealizado(&lista_turnos,fp_turnos_cancelados);
		    }
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
    //actualiza clientes.txt
    rewind(fp_clientes);
    reset_cliente(&lista_clientes);
    Cliente cliente_txt;
    while(!isOos_cliente(lista_clientes)){
	cliente_txt = copy_cliente(lista_clientes);
	fprintf(fp_clientes,"%ld\n",Get_dni(cliente_txt));
	fprintf(fp_clientes,"%s\n",Get_nombre_cliente(cliente_txt));
	fprintf(fp_clientes,"%s\n",Get_apellido_cliente(cliente_txt));
	fprintf(fp_clientes,"%d\n",Get_cant_tratamientos(cliente_txt));
	fprintf(fp_clientes,"%d\n",Get_nivel(cliente_txt));
    forward_cliente(&lista_clientes);
    }
    reset_turno(&lista_turnos);
    while(!isEmpty_turno(lista_turnos)){
        supress_turno(&lista_turnos);
    };
    fclose(fp_clientes);
    fclose(fp_turnos);
    fclose(fp_menu);
    fclose(fp_tratamientos);
    fclose(fp_turnos_cancelados);
    return 0;
}
