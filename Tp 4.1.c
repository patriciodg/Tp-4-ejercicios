#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Datos {
    char nombre[50];
    char apellido[50];
    int dni;
};

void ingresarDatos(struct Datos *datos) {
    printf("Ingrese nombre: ");
    scanf("%s", datos->nombre);
    printf("Ingrese apellido: ");
    scanf("%s", datos->apellido);
    printf("Ingrese DNI: ");
    scanf("%d", &datos->dni);
}

void buscarPorDNI(int dni) {
    FILE *archivo;
    struct Datos datos;
    int encontrado = 0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fscanf(archivo, "%s %s %d", datos.nombre, datos.apellido, &datos.dni) != EOF) {
        if (datos.dni == dni) {
            printf("Nombre: %s\nApellido: %s\nDNI: %d\n", datos.nombre, datos.apellido, datos.dni);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos con ese DNI.\n");
    }

    fclose(archivo);
}

int main() {
    int opcion, dni, salir = 0;
    struct Datos datos;

    while (salir == 0) {
        printf("Gestion de archivo\n");
        printf("1. Ingresar nombre, apellido y DNI.\n");
        printf("2. Buscar datos por DNI.\n");
        printf("3. Salir.\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

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
                fprintf(archivo, "%s %s %d\n", datos.nombre, datos.apellido, datos.dni);
                fclose(archivo);
                break;
            case 2:
            	printf("Ha seleccionado la opcion de buscar por dni.\n");
                system("pause");
                system("cls");
                printf("Ingrese DNI a buscar: ");
                scanf("%d", &dni);
                buscarPorDNI(dni);
                break;
            case 3:
                printf("Ha seleccionado la opcion de salir.\n");
                system("pause");
                system("cls");
                salir = 1;
                break;
     
        }
    }

    return 0;
}

