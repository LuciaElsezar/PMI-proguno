#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

//--- Struct Cliente -----------------
typedef struct{
    long int dni;
    char nombre[26];
    char apellido[26];
    int cant_tratamientos;
    int nivel;
}Cliente;

//--- Init y Set ---------------------
void init_cliente(Cliente* c){
    c-> dni = 0;
};

void Set_dni(Cliente* c, int dni){
    c-> dni = dni;
};

void Set_nombre_cliente(Cliente* c, char nom[]){
    strcpy(c->nombre, nom);
};

void Set_apellido_cliente(Cliente* c, char ap[]){
    strcpy(c->apellido, ap);
};

void Set_cant_tratamientos(Cliente* c, int t){
    c->cant_tratamientos=t;
};

void Set_nivel(Cliente* c, int n){
	c->nivel = n;
};

//--- Get ---------------------------
int Get_dni(Cliente c){
    return c.dni;
};

char* Get_nombre_cliente(Turno t){
char* p;
p = (char*)malloc(sizeof(char)*TAM_NOMBRE);
if(p==NULL){
    exit(1);
}
else{
    return p;
};
};

char* Get_apellido_cliente(Turno t){
char* p;
p = (char*)malloc(sizeof(char)*TAM_NOMBRE);
if(p==NULL){
    exit(1);
}
else{
    return p;
};
};

int Get_cant_tratamientos(Cliente c){
    return c.cant_tratamientos;
};

int Get_nivel(Cliente c){
	return c.nivel;
};
#endif // CLIENTE_H_INCLUDED
