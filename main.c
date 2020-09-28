#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxLargo 50

struct Producto {
    char *nombre;
    int cantidad;
    int donado; //1 = donado, 0 = comprado
};

//Necesito 1 arreglo estatico, compacto con pLibre y compacto sin pLibre
struct PuntoEncuentro {
    //Evento
    int idEvento;
    char *horaEvento;
    char *nombreEvento;
    char *locacionEvento;
    char *nombreOrganizador;
    //Donaciones
    char *donacionesCuenta;
    char *donacionesDireccion;
    //Productos
    struct Producto **productosQueHay;
    struct Producto **productosQueNecesitan;
};

struct Comuna {
    char *nombre;
    struct PuntoEncuentro **eventos;
};

int calcularPLibre(int id, struct Producto **productosQueHay);

void ordenarProductos(struct PuntoEncuentro **eventos, int idEvento, int idProducto);

void anadirProducto(struct PuntoEncuentro **eventos, int idEvento) {
    int  largo, cantidad;
    char buffer[maxLargo];
    int i = calcularPLibre(idEvento, eventos[idEvento]->productosQueHay);

    puts("Agregar un producto");
    
    puts("Ingrese el nombre del producto");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idEvento]->productosQueHay[i]->nombre = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idEvento]->productosQueHay[i]->nombre, buffer);
    puts("Ingrese la cantidad a registrar");
    scanf("%i", &cantidad);
    eventos[idEvento]->productosQueHay[i]->cantidad = cantidad;
}

void quitarProducto(struct PuntoEncuentro **eventos, int idEvento, int idProducto) {
    eventos[idEvento]->productosQueHay[idProducto] = NULL;
    ordenarProductos(eventos, idEvento, idProducto);
}

void mostrarEventos(struct PuntoEncuentro **eventos){
    int = 0;

    if(eventos[i] == NULL) return 0;

    while(eventos[i] != NULL){
        printf("%d %s \n", eventos[i]->idEvento, eventos[i]->nombreEvento);
        i++;
    }
}

int seleccionarEvento(struct PuntoEncuentro **eventos) {
    int i = 0;
    int idEvento;

    if(eventos[i] == NULL) return 0;

    puts("Seleccione un evento (Numero)");

    while(eventos[i] != NULL){
        printf("%d %s \n", eventos[i]->idEvento, eventos[i]->nombreEvento);
        i++;
    }

    scanf("%d", &idEvento);

    return idEvento;
}

void anadirEvento(struct PuntoEncuentro **eventos, int idUltimoEvento){
    int  largo;
    char buffer[maxLargo];
    
    eventos[idUltimoEvento+1]->idEvento = idUltimoEvento+1;
    puts("Agregar un evento");
    
    puts("Ingrese el nombre del evento");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idUltimoEvento+1]->nombreEvento = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idUltimoEvento]->nombreEvento, buffer);

    puts("Ingrese la hora del evento");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idUltimoEvento+1]->horaEvento = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idUltimoEvento]->horaEvento, buffer);

    puts("Ingrese la locacion del evento");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idUltimoEvento+1]->locacionEvento = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idUltimoEvento]->locacionEvento, buffer);

}

void editarEvento(struct PuntoEncuentro **eventos, int idEvento) {
    int  largo;
    char buffer[maxLargo];
    system("cls");
    puts("Editar evento");
    
    puts("Ingrese el nombre del evento");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idEvento]->nombreEvento = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idEvento]->nombreEvento, buffer);

    puts("Ingrese la hora del evento");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idEvento]->horaEvento = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idEvento]->horaEvento, buffer);

    puts("Ingrese la locacion del evento");
    scanf(" %[^\n]", buffer);
    largo = strlen(buffer);
    eventos[idEvento]->locacionEvento = (char *)malloc(largo*sizeof(char));
    strcpy(eventos[idEvento]->locacionEvento, buffer);
}

void ordenarEventos(struct PuntoEncuentro **eventos, int idEvento);

void quitarEvento(struct PuntoEncuentro **eventos, int idEvento) {
    eventos[idEvento] = NULL;
    ordenarEventos(eventos, idEvento);
}

int main() {
    int opcion = 0;
    int idEvento;

    puts("Bienvenidos a Yo te invito \v");
    puts("Seleccione una opcion");
    puts("1. Mostrar eventos");
    puts("2. Registrar un evento");
    puts("3. Editar un evento");
    puts("4. Eliminar un evento");
    puts("5. Salir");

    switch (opcion){
        case 1: 
                system("cls");
                mostrarEventos(eventos);
                break;
        case 2: 
                system("cls");
                anadirEvento(eventos);
                break;
        case 3: 
                system("cls");
                idEvento = seleccionarEvento(eventos);
                editarEvento(eventos, idEvento);
                break;
        case 4: 
                system("cls");
                idEvento = seleccionarEvento(eventos);
                anadirEvento(eventos, idEvento);
                break;
        case 5:
                system("cls");
            break;
        default:
            printf("La opcion ingresada no es valida\n");
            break;
    }

    return 0;
}