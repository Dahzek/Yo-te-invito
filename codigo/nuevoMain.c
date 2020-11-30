#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Sirve para poder limitar el maximo del string en el scanf
#define XSTR(A) STR(A)
#define STR(A) #A
//---------------------------------------------------------
#define maxLargo 50
#define maxParrafo 100
#define bajoStock 5

//Guardar en fichero
//Cargar en archivos planos
//Funciones extra

// ----------------------Structs----------------------
//Donaciones
struct CuentaDonaciones {
    char *nombre;
    char *banco;
    char *tipoCuenta;
    char *numeroCuenta;
    char *rut;
};

struct Donacion {
    struct CuentaDonaciones *donacionesCuenta; //Cuenta bancaria a la que donar
    char *donacionesDireccion; //Direccion fisica donde donar
};

//Productos
struct Producto {
    char *nombre;
    int  stock; //If stock < 5 cambiar a productos que se necesitan
    int  necesitamos; //1 = Se necesita
};

struct NodoProducto {
    struct Producto producto;
	struct NodoProducto *sig;
};

//Eventos
struct PuntoEncuentro {
    //Evento
    int diaEvento;  //Valor numerico dia dentro del mes (1..31)
    int mesEvento;  //Valor numerico (1..12)
    int horaEvento; //Formato 24 horas
	int reportes;
	
    char *nombreEvento;
    char *locacionEvento;
    char *nombreOrganizador;
    char *descripcionEvento;
    //Donaciones
    struct Donacion *donaciones;
    //Productos
    struct NodoProducto *inventario;
};

//Arbol
struct NodoPuntoEncuentro {
    int idEvento;
    struct PuntoEncuentro *datosEvento;
    struct NodoPuntoEncuentro *izq, *der;
};

struct Comuna {
    char *nombre;
    struct NodoPuntoEncuentro *eventos;
};

// ----------------------Funciones----------------------
//Comuna ----------------------------------------------------------------------------
struct Comuna rellenarComuna();
//-----------------------------------------------------------------------------------
//Eventos ---------------------------------------------------------------------------
struct NodoPuntoEncuentro *agregarEvento(int id);
struct PuntoEncuentro *rellenarDatosEventoInput();
struct Donacion *rellenarDonacionesInput();
struct CuentaDonaciones *rellenarCuentaDonacionesInput();
void enlazarEvento(struct NodoPuntoEncuentro **eventos, struct NodoPuntoEncuentro *nuevoEvento);
void imprimirDatosEvento(struct NodoPuntoEncuentro *eventos);
void mostrarEventos(struct NodoPuntoEncuentro **eventos);
void mostrarEvento(struct NodoPuntoEncuentro ***eventos, int id);
void editarEvento (struct NodoPuntoEncuentro **evento);
void editarDonacion(struct Donacion **donaciones);
void eliminarEvento(struct NodoPuntoEncuentro **evento);
//------------------------------------------------------------------------------------
//Productos --------------------------------------------------------------------------
void mostrarInventario(struct NodoProducto **);
void enlazarProducto(struct NodoProducto ***inventario, struct NodoProducto *nuevoEvento);
struct NodoProducto *agregarProducto();
void mostrarProductos(struct NodoProducto *productos);
void editarProducto (struct NodoProducto **inventario, char *nombre);
void quitarProducto();
void ordenarProductos();
//------------------------------------------------------------------------------------
/*
struct CuentaDonaciones *rellenarCuentaDonacionesArchivo() {
	struct CuentaDonaciones *cuenta = (struct CuentaDonaciones *)malloc(sizeof(struct CuentaDonaciones));
	char buffer[maxLargo];
	
	cuenta->nombre = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->nombre, buffer);

	cuenta->banco = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->banco, buffer);

	cuenta->tipoCuenta = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->tipoCuenta, buffer);
	
	cuenta->numeroCuenta = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->numeroCuenta, buffer);

	cuenta->rut = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->rut, buffer);
	
	return cuenta;
}


struct Donacion *rellenarDonacionesArchivo() {
	struct Donacion *donacion = (struct Donacion *)malloc(sizeof(struct Donacion));
	char buffer[maxParrafo];
	
	puts("Cuenta donaciones");
	donacion->donacionesCuenta = rellenarCuentaDonacionesArchivo();

	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	donacion->donacionesDireccion = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(donacion->donacionesDireccion, buffer);
	
	return donacion;
}

struct PuntoEncuentro *rellenarDatosEventoArchivo() {
	struct PuntoEncuentro *datos = (struct PuntoEncuentro *)malloc(sizeof(struct PuntoEncuentro));
	FILE * fichero;
	fichero = fopen("datos/datosEvento.dat", "r");
	
	fscanf(fichero, "%d %d %d", &(*datos).diaEvento, &(*datos).mesEvento, &(*datos).horaEvento);

	(*datos).nombreEvento = "NombreTest";
	(*datos).locacionEvento = "Parque Test #312";
	(*datos).nombreOrganizador = "El tio Emilio";
	(*datos).descripcionEvento = "El evento test";
	datos->donaciones = rellenarDonacionesArchivo();
	(*datos).inventario = NULL;
	
	return datos;
}


struct NodoPuntoEncuentro *agregarEventoArchivo(int id) {
	struct NodoPuntoEncuentro *nuevoEvento;
	
	nuevoEvento = (struct NodoPuntoEncuentro*)malloc(sizeof(struct NodoPuntoEncuentro));
	
	nuevoEvento->idEvento = id;
	nuevoEvento->datosEvento = rellenarDatosEventoArchivo();
	
	if(!nuevoEvento->datosEvento) return NULL;
	
	nuevoEvento->der = nuevoEvento->izq = NULL;
	
	return nuevoEvento;	
}
*/

void escribirArchivo (struct Comuna valpo) {
	FILE * fichero;
	fichero = fopen("datosComuna.dat", "ab");
	
	fprintf(fichero, "%s", valpo.nombre);
}

int main() {
	int opcion, i = 1;
	struct Comuna valpo = rellenarComuna();
	valpo.eventos = NULL;
	
	do {
		//MENU -------------------------
		printf("\vBienvenidos a Yo te Invito - %s\n", valpo.nombre);
		puts("Seleccione una opcion");
		puts("1. Mostrar eventos");
		puts("2. Agregar un evento");
		puts("0. Salir");
		
		if(scanf("%d", &opcion) != 1) return EXIT_FAILURE;
		switch(opcion) {
			case 1: 
				mostrarEventos(&valpo.eventos);
				break;
					
			case 2:
				enlazarEvento(&valpo.eventos, agregarEvento(i));
				i++;
				break;
			
			/*case 3: 
				enlazarEvento(&valpo.eventos, agregarEventoArchivo(i));
				i++;
				break;
			*/
			
			case 0:
				break;
				
			default:
				puts("Ingrese una opcion valida");
				break;
		}
	} while(opcion != 0);
    
    return EXIT_SUCCESS;
}

//Comuna
struct Comuna rellenarComuna() {
	struct Comuna comuna;
	char buffer[maxLargo];
	FILE * fichero;
	fichero = fopen("datos/datosComuna.dat", "r");
	
	fgets(buffer, maxLargo, fichero);
	comuna.nombre = (char*)malloc(sizeof(char)*strlen(buffer));
	strcpy(comuna.nombre, buffer);
	
	return comuna;
}

//Crear evento
struct NodoPuntoEncuentro *agregarEvento(int id) {
	struct NodoPuntoEncuentro *nuevoEvento;
	
	nuevoEvento = (struct NodoPuntoEncuentro*)malloc(sizeof(struct NodoPuntoEncuentro));
	
	nuevoEvento->idEvento = id;
	nuevoEvento->datosEvento = rellenarDatosEventoInput();
	
	if(!nuevoEvento->datosEvento) return NULL;
	
	nuevoEvento->der = nuevoEvento->izq = NULL;
	
	return nuevoEvento;	
}

struct PuntoEncuentro *rellenarDatosEventoInput() {
	struct PuntoEncuentro *datos = (struct PuntoEncuentro *)malloc(sizeof(struct PuntoEncuentro));
	char buffer[maxParrafo];
	
	printf("Dia del evento(1..31): ");
	if(scanf("%d", &datos->diaEvento) != 1) return NULL;
	puts("");
	
	printf("Mes del evento (1..12): ");
	if(scanf("%d", &datos->mesEvento) != 1) return NULL;
	puts("");
	
	printf("Hora del evento (0..24): ");
	if(scanf("%d", &datos->horaEvento) != 1) return NULL;
	puts("");
	
	datos->reportes = 0;
	
	printf("Nombre del evento: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	datos->nombreEvento = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(datos->nombreEvento, buffer);
	puts("");
	
	printf("Locacion del evento: ");
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	datos->locacionEvento = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(datos->locacionEvento, buffer);
	puts("");
	
	printf("Nombre del organizador del evento: ");
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	datos->nombreOrganizador = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(datos->nombreOrganizador, buffer);
	puts("");
	
	printf("Descripcion del evento: ");
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	datos->descripcionEvento = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(datos->descripcionEvento, buffer);
	puts("");
	
	datos->donaciones = rellenarDonacionesInput();
	(*datos).inventario = NULL;
	
	return datos;
}

struct Donacion *rellenarDonacionesInput() {
	struct Donacion *donacion = (struct Donacion *)malloc(sizeof(struct Donacion));
	char buffer[maxParrafo];
	
	puts("Cuenta donaciones");
	donacion->donacionesCuenta = rellenarCuentaDonacionesInput();

	printf("Donde enviar las donaciones fisicas?: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	donacion->donacionesDireccion = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(donacion->donacionesDireccion, buffer);
	puts("");
	
	return donacion;
}

struct CuentaDonaciones *rellenarCuentaDonacionesInput() {
	struct CuentaDonaciones *cuenta = (struct CuentaDonaciones *)malloc(sizeof(struct CuentaDonaciones));
	char buffer[maxLargo];
	
	puts("Datos cuenta donaciones");
	printf("Nombre: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	cuenta->nombre = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->nombre, buffer);
	puts("");
	
	printf("Banco: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	cuenta->banco = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->banco, buffer);
	puts("");
	
	printf("Tipo de cuenta: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	cuenta->tipoCuenta = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->tipoCuenta, buffer);
	puts("");
	
	printf("Numero de cuenta: ");
	scanf(" %[^\n]s", buffer);
	cuenta->numeroCuenta = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->numeroCuenta, buffer);
	puts("");
	
	printf("Rut: ");
	scanf(" %9s", buffer);
	cuenta->rut = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(cuenta->rut, buffer);
	puts("");
	
	return cuenta;
}

void enlazarEvento(struct NodoPuntoEncuentro **eventos, struct NodoPuntoEncuentro *nuevoEvento) {
	struct NodoPuntoEncuentro *recorrido = *eventos;
	
	if(!nuevoEvento) {
		puts("La operacion fallo debido a un error en los datos ingresados, por favor asegurese de que el tipo de dato que ingresa sea correcto");
		return;
	}
	
	if( ! *eventos ) {
		(*eventos) = nuevoEvento;
	} else {
		do {
			if(nuevoEvento->idEvento < recorrido->idEvento) {
				if( !recorrido->izq ) {
					recorrido->izq = nuevoEvento;
					recorrido = recorrido->izq;
				}
				else {
					recorrido = recorrido->izq;
					
				}
			}
			else {
				if( !recorrido->der ) {
					recorrido->der = nuevoEvento;
					recorrido = recorrido->der;
				}
				else {
					recorrido = recorrido->der;
				}
			}
			
		} while(recorrido != nuevoEvento);
	}
}

//Mostrar evento
void imprimirDatosEvento(struct NodoPuntoEncuentro *eventos) {
	
	if(eventos){
		printf("%d // %s // %s // %s\n", eventos->idEvento, eventos->datosEvento->nombreEvento,
			eventos->datosEvento->locacionEvento, eventos->datosEvento->descripcionEvento);
		imprimirDatosEvento(eventos->izq);
		imprimirDatosEvento(eventos->der);
	}
}

void mostrarEventos(struct NodoPuntoEncuentro **eventos) {
	int opcion, idEvento;
	 
	if(! *eventos) printf("No hay eventos en esta comuna\n");
	
	else {
		do {
			printf("\vId // Nombre // Locacion // Descripcion\n");
			imprimirDatosEvento(*eventos);
			puts("\vSeleccione un evento para ver sus detalles o agregue su propio evento!");
			puts("1. Seleccionar un evento");
			puts("0. Salir");
			
			if(scanf("%d", &opcion) != 1) return;
			
			switch(opcion) {
				case 1:
					puts("Ingrese el id del evento que desea ver");
					scanf("%d", &idEvento);
					mostrarEvento(&eventos, idEvento);
					break;
				
				case 0:
					break;
					
				default:
					puts("Ingrese una opcion valida!");
					break;
			}
		} while(opcion != 0);
	}
}

void reportarEvento (struct PuntoEncuentro **datosEvento){
	
	if(!(*datosEvento)->reportes) (*datosEvento)->reportes = 0;
	(*datosEvento)->reportes = (*datosEvento)->reportes+1;
}

void mostrarEvento(struct NodoPuntoEncuentro ***eventos, int id) {
	int opcion;
	
	struct NodoPuntoEncuentro *recorrido = **eventos;
	
	if(!recorrido) {
		puts("Ingrese una opcion valida");
		return;
	}
	
	while(recorrido->idEvento != id) {
		if(recorrido->der == NULL && recorrido->idEvento != id){
			puts("Ingrese una opcion valida");
			return;
		}
		recorrido = recorrido->der;
	}
	
	do {
		printf("\vEste evento se llevara a cabo el %d/%d a las %d horas\n", recorrido->datosEvento->diaEvento, recorrido->datosEvento->mesEvento, recorrido->datosEvento->horaEvento);
		printf("Nombre del evento: %s\n", recorrido->datosEvento->nombreEvento);
		printf("Nombre del organizador: %s\n", recorrido->datosEvento->nombreOrganizador);
		printf("Locacion del evento: %s\n", recorrido->datosEvento->locacionEvento);
		printf("Descripcion del evento: %s\n", recorrido->datosEvento->descripcionEvento);
		printf("\vDatos cuenta donaciones\n");
		printf("Nombre: %s\n", recorrido->datosEvento->donaciones->donacionesCuenta->nombre);
		printf("Banco: %s\n", recorrido->datosEvento->donaciones->donacionesCuenta->banco);
		printf("Tipo de cuenta: %s\n", recorrido->datosEvento->donaciones->donacionesCuenta->tipoCuenta);
		printf("Numero de cuenta: %s\n", recorrido->datosEvento->donaciones->donacionesCuenta->numeroCuenta);
		printf("Rut: %s\n", recorrido->datosEvento->donaciones->donacionesCuenta->rut);
		printf("Este evento ha sido reportado %d veces", recorrido->datosEvento->reportes);
		
		printf("\vOpciones\n");
		printf("1. Ver inventario\n");
		printf("2. Editar evento\n");
		printf("3. Eliminar evento\n");
		printf("4. Eliminar evento\n");
		printf("0. Salir\n");
		if(scanf(" %d", &opcion) != 1) return;
		switch(opcion) {
			case 1:
				mostrarInventario(&recorrido->datosEvento->inventario);
				break;
			
			case 2:
				editarEvento(&recorrido);
				break;
			
			case 3:
				eliminarEvento(&recorrido);
				break;
			
			case 4:
				reportarEvento(&recorrido->datosEvento);
				break;
			
			case 0:
				break;
				
			default:
				puts("Ingrese una opcion valida!");
				break;
		}
	} while(opcion != 0 && opcion != 3);
}

//Editar evento -------------------------------------------------------
void editarEvento (struct NodoPuntoEncuentro **evento) {
	char buffer[maxParrafo], opcion;
	
	puts("\vEditando evento");
	//Dia del evento
	printf("Dia actual del evento: %d\n", (*evento)->datosEvento->diaEvento);
	printf("Nuevo dia del evento(1..31): ");
	do{
		if((*evento)->datosEvento->diaEvento > 31 || (*evento)->datosEvento->diaEvento < 1)
			puts("Ingrese una opcion valida");
		if(scanf(" %d", &(*evento)->datosEvento->diaEvento) != 1) return;
	} while((*evento)->datosEvento->diaEvento > 31 || (*evento)->datosEvento->diaEvento < 1);
	puts("");
	
	//Mes del evento
	printf("Mes actual del evento: %d\n", (*evento)->datosEvento->mesEvento);
	printf("Nuevo mes del evento(1..12): ");
	do{
		if((*evento)->datosEvento->mesEvento > 12 || (*evento)->datosEvento->mesEvento < 1)
			puts("Ingrese una opcion valida");
		if(scanf(" %d", &(*evento)->datosEvento->mesEvento) != 1) return;
	} while((*evento)->datosEvento->mesEvento > 12 || (*evento)->datosEvento->mesEvento < 1);
	puts("");
	
	//Hora del evento
	printf("Hora actual del evento: %d\n", (*evento)->datosEvento->diaEvento);
	printf("Nueva hora del evento(0..24): ");
	do{
		if((*evento)->datosEvento->horaEvento > 24 || (*evento)->datosEvento->horaEvento < 0)
			puts("Ingrese una opcion valida");
		if(scanf(" %d", &(*evento)->datosEvento->horaEvento) != 1) return;
	} while((*evento)->datosEvento->horaEvento > 24 || (*evento)->datosEvento->horaEvento < 0);
	puts("");
	
	//Nombre del evento
	printf("Nombre actual del evento: %s\n", (*evento)->datosEvento->nombreEvento);
	printf("Nuevo nombre del evento: ");
	
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	(*evento)->datosEvento->nombreEvento = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*evento)->datosEvento->nombreEvento, buffer);
	puts("");
	
	//Locacion del evento
	printf("Locacion actual del evento: %s\n", (*evento)->datosEvento->locacionEvento);
	printf("Nueva locacion del evento: ");
	
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	(*evento)->datosEvento->locacionEvento = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*evento)->datosEvento->locacionEvento, buffer);
	puts("");
	
	//Nombre del organizador del evento
	printf("Nombre actual del organizador del evento: %s\n", (*evento)->datosEvento->nombreOrganizador);
	printf("Nuevo nombre del organizador del evento: ");
	
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	(*evento)->datosEvento->nombreOrganizador = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*evento)->datosEvento->nombreOrganizador, buffer);
	puts("");
	
	//Descripcion del evento
	printf("Descripcion actual del evento: %s\n", (*evento)->datosEvento->descripcionEvento);
	printf("Nueva descripcion del evento: ");
	
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	(*evento)->datosEvento->descripcionEvento = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*evento)->datosEvento->descripcionEvento, buffer);
	puts("");
	
	printf("\vDesea editar los datos de las donaciones?\n1.Si\n0. Salir\n");
	do {
		scanf(" %c", &opcion);
		if(opcion == '1') editarDonacion(&(*evento)->datosEvento->donaciones);
		if(opcion != '1' && opcion != '0') printf("Seleccione una opcion valida\n");
	} while(opcion != '1' && opcion != '0');
}

void editarDonacion(struct Donacion **donaciones) {
	char buffer[maxParrafo];
	
	puts("\vEditando datos sobre donaciones");
	
	printf("Direccion para donaciones actual: %s\n", (*donaciones)->donacionesDireccion);
	printf("Nueva direccion para donaciones: ");
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	(*donaciones)->donacionesDireccion = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*donaciones)->donacionesDireccion, buffer);
	puts("");
	
	puts("Cuenta para donaciones");
	printf("Nombre: %s\n", (*donaciones)->donacionesCuenta->nombre);
	printf("Nuevo nombre: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	(*donaciones)->donacionesCuenta->nombre = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*donaciones)->donacionesCuenta->nombre, buffer);
	puts("");
	
	printf("Banco para donaciones actual: %s\n", (*donaciones)->donacionesCuenta->banco);
	printf("Nuevo banco: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	(*donaciones)->donacionesCuenta->banco = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*donaciones)->donacionesCuenta->banco, buffer);
	puts("");
	
	printf("Tipo de cuenta actual: %s\n", (*donaciones)->donacionesCuenta->tipoCuenta);
	printf("Nuevo tipo de cuenta: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	(*donaciones)->donacionesCuenta->tipoCuenta = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*donaciones)->donacionesCuenta->tipoCuenta, buffer);
	puts("");
	
	printf("Numero de cuenta actual: %s\n", (*donaciones)->donacionesCuenta->numeroCuenta);
	printf("Nuevo numero de cuenta: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	(*donaciones)->donacionesCuenta->numeroCuenta = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*donaciones)->donacionesCuenta->numeroCuenta, buffer);
	puts("");
	
	printf("Rut actual: %s\n", (*donaciones)->donacionesCuenta->rut);
	printf("Nuevo rut: ");
	scanf(" %"XSTR(maxLargo)"[^\n]", buffer);
	(*donaciones)->donacionesCuenta->rut = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy((*donaciones)->donacionesCuenta->rut, buffer);
	puts("");
}
//---------------------------------------------------------------------

//Inventario ----------------------------------------------------------

void mostrarProductos(struct NodoProducto *productos) {
	if(productos){
		printf("%s // %d ", productos->producto.nombre, productos->producto.stock);
		
		if(productos->producto.stock < bajoStock || productos->producto.necesitamos == 1) {
			printf("-> Necesitamos de este producto, cualquier aporte es bienvenido!\n");
		} else puts("");
		mostrarProductos(productos->sig);
	}
}

void mostrarInventario(struct NodoProducto **inventario) {
	char opcion;
	char nombre[maxParrafo];
	struct NodoProducto *aux = *inventario; 
	
	do{
		printf("\vInventario\n");
		if(! (*inventario)) printf("Este evento aun no tiene productos en su inventario\n");
		else printf("Nombre // Stock\n");
		mostrarProductos(*inventario);
		puts("\vOpciones\n1. Agregar producto\n2. Editar producto\n3. Eliminar producto\n0. Salir");
		
		do {
		scanf(" %c", &opcion);
		
		if(opcion != '1' && opcion != '2' && opcion != '3' && opcion != '0') 
			puts("Ingrese una opcion valida");
		} while (opcion != '1' && opcion != '2' && opcion != '3' && opcion != '0');
			
		switch(opcion) {
			case '1':
				puts("\vAgregar producto\v");
				enlazarProducto(&inventario, agregarProducto());
				break;
				
			case '2':
				printf("\v Escriba el nombre del producto que desea editar: ");
				scanf(" %"XSTR(maxParrafo)"[^\n]", nombre);
				editarProducto(&aux, nombre);
				break;
				
			case '3':
				puts("Eliminar producto");
				puts("\vEN DESARROLLO\v");
				break;
			case '0':
				break;
		}
		
	} while(opcion != '0');
}

void enlazarProducto(struct NodoProducto ***inventario, struct NodoProducto *nuevoProducto) {
	struct NodoProducto **recorrido = *inventario;
	struct NodoProducto *aux = *recorrido;
	
	if(!nuevoProducto) {
		puts("Se ingreso un dato invalido, por lo cual se cancelo la creacion del producto");
		return;
	}
	
	if(! **inventario) **inventario = nuevoProducto;
	else {
		do {
			if( !aux->sig ) {
				aux->sig = nuevoProducto;
				aux = aux->sig;
			}
			else {
				aux = aux->sig;
			}
		} while(aux != nuevoProducto);
	}	
}

struct NodoProducto *agregarProducto() {
	char buffer[maxParrafo];
	struct NodoProducto *nuevo = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
	
	printf("Nombre del producto: ");
	scanf(" %"XSTR(maxParrafo)"[^\n]", buffer);
	puts("");
	nuevo->producto.nombre = (char *)malloc(sizeof(char)*strlen(buffer));
	strcpy(nuevo->producto.nombre, buffer);
	
	printf("Stock del producto (Valor numerico): ");
	do {
		if(nuevo->producto.stock < 0) printf("\nIngrese un valor valido");	
		if(scanf(" %d", &nuevo->producto.stock) != 1) return NULL;
	} while(nuevo->producto.stock < 0);
	puts("");
	nuevo->sig = NULL;
	return nuevo;
}

void editarProducto (struct NodoProducto **inventario, char *nombre) {
	puts("\vEN DESARROLLO\v");
}
//---------------------------------------------------------------------
void eliminarProducto(struct NodoProducto **inventario, char *nombre) {
	puts("\vEN DESARROLLO\v");
}
//ESTA PARTE ES LA DEL ELIMINAR EL NODO DEL ARBOL
void eliminarEvento(struct NodoPuntoEncuentro **evento) {
	//ELIMINAR NODO PUNTO ENCUENTRO
	puts("\vEN DESARROLLO\v");
}
