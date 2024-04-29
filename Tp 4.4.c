#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Datos {
    char nombre[50];
    char apellido[50];
    int dni;
};

int buscarDNI(int dni) {
    FILE *archivo;
    struct Datos datos;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0; 
    }

    while (fscanf(archivo, "%s %s %d", datos.nombre, datos.apellido, &datos.dni) != EOF) {
        if (datos.dni == dni) {
            fclose(archivo);
            return 1; 
        }
    }

    fclose(archivo);
    return 0; 
}

void ingresarDatos(struct Datos *datos) {
    int dni_existente;
    do {
        printf("Ingrese nombre: ");
        scanf("%s", (*datos).nombre);
        printf("Ingrese apellido: ");
        scanf("%s", (*datos).apellido);
        printf("Ingrese DNI: ");
        scanf("%d", &(*datos).dni);

        dni_existente = buscarDNI((*datos).dni);

        if (dni_existente) {
            printf("El DNI ingresado ya existe. Por favor, ingrese otro.\n");
            system("pause");
            system("cls");
        }

    } while (dni_existente); 
}

void buscarPorDNI(int dni) {
    FILE *archivo;
    struct Datos datos;
    int encontrado = 0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        system("pause");
        system("cls");
        return;
    }

    while (fscanf(archivo, "%s %s %d", datos.nombre, datos.apellido, &datos.dni) != EOF) {
        if (datos.dni == dni) {
            printf("Nombre: %s\nApellido: %s\nDNI: %d\n", datos.nombre, datos.apellido, datos.dni);
            encontrado = 1;
            break;
        }
    }
    system("pause");
    system("cls");
    if (!encontrado) {
        printf("No se encontraron datos con ese DNI.\n");
        system("pause");
        system("cls");
    }

    fclose(archivo);
}

void buscarPorNombreyApellido(char *nombre, char *apellido) {
    FILE *archivo;
    struct Datos datos;
    int encontrado = 0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fscanf(archivo, "%s %s %d", datos.nombre, datos.apellido, &datos.dni) != EOF) {
        if (strcmp(datos.nombre, nombre) == 0 && strcmp(datos.apellido, apellido) == 0) {
            printf("Nombre: %s\nApellido: %s\nDNI: %d\n", datos.nombre, datos.apellido, datos.dni);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos con ese nombre y apellido.\n");
        system("pause");
        system("cls");
    }

    fclose(archivo);
}


int compararDNI(const void *a, const void *b) {
    const struct Datos *dato1 = (const struct Datos *)a;
    const struct Datos *dato2 = (const struct Datos *)b;
    return ((*dato1).dni - (*dato2).dni);
}


void mostrarRegistrosOrdenados() {
    FILE *archivo;
    struct Datos datos[100];
    int num_registros = 0,x;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    
    while (fscanf(archivo, "%s %s %d", datos[num_registros].nombre, datos[num_registros].apellido, &datos[num_registros].dni) != EOF) {
        num_registros++;
    }

    fclose(archivo);

   
    qsort(datos, num_registros, sizeof(struct Datos), compararDNI);

    
    printf("Registros ordenados por DNI de menor a mayor:\n");
    for (x = 0; x < num_registros; x++) {
        printf("Nombre: %s\nApellido: %s\nDNI: %d\n", datos[x].nombre, datos[x].apellido, datos[x].dni);
    }

    system("pause");
    system("cls");
}

int main() {
    int opcion, dni, salir = 0;
    struct Datos datos;
    char nombre[50];
    char apellido[50];
    
    while (salir == 0) {
        printf("Gestion de archivo\n");
        printf("1. Ingresar nombre, apellido y DNI.\n");
        printf("2. Buscar datos por DNI.\n");
        printf("3. Buscar datos por nombre y apellido.\n");
        printf("4. Mostrar todos los registros ordenados por DNI.\n");
        printf("5. Salir.\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        system("cls");
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
                    system("pause");
                    system("cls");
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
                printf("Ha seleccionado la opcion de buscar por nombre y apellido.\n");
                system("pause");
                system("cls");
                printf("Ingrese el nombre a buscar: ");
                scanf("%s", nombre);
                fflush(stdin);
                printf("Ingrese el apellido a buscar: ");
                scanf("%s", apellido);
                buscarPorNombreyApellido(nombre, apellido);
                break;
            case 4:
                printf("Ha seleccionado la opcion de mostrar todos los registros ordenados por DNI.\n");
                mostrarRegistrosOrdenados();
                break;
            case 5:
                printf("Ha seleccionado la opcion de salir.\n");
                system("pause");
                system("cls");
                salir = 1;
                break;
        }
    }

    return 0;
}

