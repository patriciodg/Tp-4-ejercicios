#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Datos {
    char nombre[50];
    int puntaje;
};

int buscarNombre(char *nombre) {
    FILE *archivo;
    struct Datos datos;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0; 
    }

    while (fscanf(archivo, "%s %d", datos.nombre, &datos.puntaje) != EOF) {
        if (strcmp(datos.nombre, nombre) == 0) {
            fclose(archivo);
            return 1; 
        }
    }

    fclose(archivo);
    return 0; 
}

void ingresarDatos(struct Datos *datos) {
    int nombre_existente;
    do {
        printf("Ingrese nombre: ");
        scanf("%s", (*datos).nombre);
        printf("Ingrese puntaje: ");
        scanf("%d", &(*datos).puntaje);

        nombre_existente = buscarNombre(datos->nombre);

        if (nombre_existente) {
            printf("El nombre ingresado ya existe. Por favor, ingrese otro.\n");
            system("pause");
            system("cls");
        }

    } while (nombre_existente); 
}

void buscarPorNombre(char *nombre) {
    FILE *archivo;
    struct Datos datos;
    int encontrado = 0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fscanf(archivo, "%s %d", datos.nombre, &datos.puntaje) != EOF) {
        if (strcmp(datos.nombre, nombre) == 0) {
            printf("Nombre: %s\nPuntaje: %d\n", datos.nombre, datos.puntaje);
            encontrado = 1;
            system("pause");
            system("cls");
			break;
        }
    }
    fclose(archivo);

    if (!encontrado) {
        printf("No se encontraron datos con ese nombre.\n");
        system("pause");
        system("cls");
    }
}

int compararPuntajes(const void *a, const void *b) {
    const struct Datos *dato1 = (const struct Datos *)a;
    const struct Datos *dato2 = (const struct Datos *)b;
    return (dato2->puntaje - dato1->puntaje);
}

void mostrarRegistrosOrdenados() {
    FILE *archivo;
    struct Datos datos[100];
    int num_registros = 0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fscanf(archivo, "%s %d", datos[num_registros].nombre, &datos[num_registros].puntaje) != EOF) {
        num_registros++;
    }

    fclose(archivo);

    qsort(datos, num_registros, sizeof(struct Datos), compararPuntajes);

    printf("Los 10 mejores jugadores de mayor a menor puntaje:\n");
    int i;
    for (i = 0; i < num_registros && i < 10; i++) {
        printf("%d. Nombre: %s, Puntaje: %d\n", i + 1, datos[i].nombre, datos[i].puntaje);
    }
	system("pause");
    system("cls");
}

int main() {
    int opcion, salir = 0;
    struct Datos datos;

    while (salir == 0) {
    	do{
        printf("Gestion de archivo\n");
        printf("1. Ingresar nombre y puntaje.\n");
        printf("2. Mostrar los 10 mejores jugadores de mayor a menor puntaje.\n");
        printf("3. Buscar puntaje por nombre.\n");
        printf("4. Para salir del programa.\n");
        printf("Ingrese una opcion: ");
    	scanf("%d", &opcion);
        system("cls");
        } while (opcion < 1 || opcion > 4);

        switch (opcion) {
            case 1:
                printf("Ha seleccionado la opcion de ingresar datos.\n");
                system("pause");
				system("cls");
                ingresarDatos(&datos);
                FILE *archivo;
                archivo = fopen("datos.txt", "a");
                if (archivo == NULL) {
                    printf("Error al abrir el archivo.\n");
                    return 1;
                }
                fprintf(archivo, "%s %d\n", datos.nombre, datos.puntaje);
                fclose(archivo);
                system("pause");
                system("cls");
                break;
            case 2:
                printf("Ha seleccionado la opcion de mostrar los 10 mejores jugadores.\n");
                system("pause");
    			system("cls");
                mostrarRegistrosOrdenados();
                system("pause");
                system("cls");
                break;
            case 3:
                printf("Ha seleccionado la opcion de buscar por nombre.\n");
                system("pause");
    			system("cls");
                printf("Ingrese nombre a buscar: ");
                char nombre_busqueda[50];
                scanf("%s", nombre_busqueda);
                buscarPorNombre(nombre_busqueda);
                system("pause");
                system("cls");
                break;
            case 4:
                printf("Ha seleccionado la opcion de salir.\n");
                salir = 1;
                system("pause");
                system("cls");
                break;
        }
    }

    return 0;
}

