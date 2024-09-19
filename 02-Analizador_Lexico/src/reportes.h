#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 50

typedef struct
{
    char **listado;
    size_t cantidad;
    size_t capacidad;
} Reporte;

typedef struct lista_identificadores
{
    char *identificador;
    int cantidad;
    struct lista_identificadores *siguiente;
} Nodo;

void insertar_en_lista(Nodo **lista, const char *identificador);

typedef struct Posicion
{
    int fila;
    int columna;
    struct Posicion *siguiente;
} Posicion;

// Funciones para manejo de reportes
void eliminar_lista(Posicion *lista)
{
    Posicion *actual = lista;
    Posicion *aux;

    while (actual != NULL)
    {
        aux = actual->siguiente;
        free(actual);
        actual = aux;
    }
}
void insertar_lista(Posicion **lista, int fila, int columna)
{
    Posicion *nuevo = (Posicion *)malloc(sizeof(Posicion));
    if (nuevo == NULL)
    {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    nuevo->fila = fila;
    nuevo->columna = columna;
    nuevo->siguiente = NULL;

    if (*lista == NULL)
    {
        *lista = nuevo;
    }
    else
    {
        Posicion *actual = *lista;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void inicializar_reporte(Reporte *reporte)
{
    reporte->cantidad = 0;
    reporte->capacidad = 1;
    reporte->listado = malloc(reporte->capacidad * sizeof(char*));
    if (reporte->listado == NULL) {
        printf("Error al inicializar el reporte\n");
        exit(EXIT_FAILURE);
    }
    // Inicializa la primera cadena
    reporte->listado[0] = malloc(MAX_STRING_LENGTH * sizeof(char));
    if (reporte->listado[0] == NULL)
    {
        printf("No se pudo asignar memoria para la cadena inicial\n");
        exit(EXIT_FAILURE);
    }
    // Inicializar el primer string a v acío
    reporte->listado[0][0] = '\0'; // Asegura que la cadena comienza vacía
}

void concatenar_ultimo_elemento(Reporte *reporte, const char *elemento)
{
    if (reporte->cantidad < 0)
        return; // Verificación básica de índice válido

    char *original = reporte->listado[reporte->cantidad - 1];
    size_t new_size = strlen(original) + strlen(elemento) + 1; // +1 para el carácter nulo
    // printf("La cadena original es %s, la cantidad original es %s.\n", original, reporte->listado[reporte->cantidad-1]);

    // Realiza el realloc y verifica si es exitoso
    char *new_string = realloc(original, new_size);
    if (new_string == NULL)
    {
        // Maneja el error de memoria
        fprintf(stderr, "Error de memoria al redimensionar la cadena.\n");
        exit(1);
    }

    // Asigna el puntero reallocado de vuelta al listado
    reporte->listado[reporte->cantidad - 1] = new_string;

    // Concatena el nuevo elemento
    strcat(reporte->listado[reporte->cantidad - 1], elemento);

    // printf("Cadena original después de concatenar: %s\n", reporte->listado[reporte->cantidad-1]);
}

void agregar_elemento_ordenado(Reporte *reporte, const char *elemento) {
    // Verificar y redimensionar la capacidad si es necesario
    if (reporte->cantidad >= reporte->capacidad) {
        size_t nueva_capacidad = reporte->capacidad * 2;
        char **nuevo_listado = realloc(reporte->listado, nueva_capacidad * sizeof(char *));
        if (nuevo_listado == NULL) {
            fprintf(stderr, "Error al redimensionar el listado\n");
            exit(EXIT_FAILURE);
        }
        for (size_t i = reporte->capacidad; i < nueva_capacidad; i++) {
            nuevo_listado[i] = NULL;
        }
        reporte->listado = nuevo_listado;
        reporte->capacidad = nueva_capacidad;
    }

    // Crear una copia de la cadena a agregar
    char *elemento_copiado = malloc(strlen(elemento) + 1);
    if (elemento_copiado == NULL) {
        fprintf(stderr, "No se pudo asignar memoria para la nueva cadena\n");
        exit(EXIT_FAILURE);
    }
    strcpy(elemento_copiado, elemento);

    // Encontrar la posición correcta para insertar el nuevo elemento
    int i;
    for (i = 0; i < reporte->cantidad; i++) {
        if (strlen(elemento_copiado) < strlen(reporte->listado[i])) {
            break;
        }
    }

    // Mover los elementos para hacer espacio para el nuevo elemento
    for (int j = reporte->cantidad; j > i; j--) {
        reporte->listado[j] = reporte->listado[j - 1];
    }

    // Insertar el nuevo elemento en la posición correcta
    reporte->listado[i] = elemento_copiado;
    reporte->cantidad++;
}


void agregar_elemento(Reporte *reporte, const char *elemento)
{
    if (reporte->cantidad >= reporte->capacidad)
    {
        size_t nueva_capacidad = reporte->capacidad * 2;
        char **nuevo_listado = realloc(reporte->listado, nueva_capacidad * sizeof(char *));
        if (nuevo_listado == NULL)
        {
            printf("Error al redimensionar el listado\n");
            exit(EXIT_FAILURE);
        }
        for (size_t i = reporte->capacidad; i < nueva_capacidad; i++)
        {
            nuevo_listado[i] = malloc(MAX_STRING_LENGTH * sizeof(char));
            if (nuevo_listado[i] == NULL)
            {
                printf("No se pudo asignar memoria");
                exit(EXIT_FAILURE);
            }
        }
        reporte->listado = nuevo_listado;
        reporte->capacidad = nueva_capacidad;
    }
    strcpy(reporte->listado[reporte->cantidad], elemento);
    reporte->cantidad++;
}

void liberar_reporte(Reporte *reporte)
{
    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        free(reporte->listado[i]);
    }
    free(reporte->listado);
}

void insertar_en_lista(Nodo **lista, const char *identificador){
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->identificador = strdup(identificador);
    nuevo_nodo->cantidad = 1;
    nuevo_nodo->siguiente = NULL;

    if (*lista == NULL || strcmp((*lista)->identificador, identificador) > 0)
    {
        nuevo_nodo->siguiente = *lista;
        *lista = nuevo_nodo;
        return;
    }

    Nodo *actual = *lista;
    while (actual->siguiente != NULL && strcmp(actual->siguiente->identificador, identificador) < 0)
    {
        actual = actual->siguiente;
    }
    nuevo_nodo->siguiente = actual->siguiente;
    actual->siguiente = nuevo_nodo;
}

// Generación de reportes por tipo de token

void imprimir_reporte_identificadores(Reporte *reporte)
{
    Nodo *lista_identificadores_sin_repetir = NULL;

    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        char *identificador_actual = reporte->listado[i];
        int esta_en_lista = 0;

        
        Nodo *actual = lista_identificadores_sin_repetir;
        while (actual != NULL)
        {
            if (strcmp(actual->identificador, identificador_actual) == 0)
            {
                actual->cantidad++;
                esta_en_lista = 1;
                break;
            }
            actual = actual->siguiente;
        }

        if (!esta_en_lista)
        {
            // Insertar nuevo identificador en la lista ordenada
            insertar_en_lista(&lista_identificadores_sin_repetir, identificador_actual);
        }
    }

    
    printf("\n* Listado de identificadores encontrados:\n");
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }

    Nodo *aux = lista_identificadores_sin_repetir;
    while (aux != NULL)
    {
        printf("%s: aparece %d %s\n", aux->identificador, aux->cantidad, aux->cantidad > 1 ? "veces" : "vez");
        aux = aux->siguiente;
    }

    aux = lista_identificadores_sin_repetir;
    while (aux != NULL)
    {
        Nodo *siguiente = aux->siguiente;
        free(aux->identificador);
        free(aux);
        aux = siguiente;
    }
}

void imprimir_reporte_constantes_reales(Reporte *reporte)
{
    printf("\n* Listado de constantes reales:\n");
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        double valor = atof(reporte->listado[i]);
        int parte_entera = (int)valor;
        double mantisa = valor - parte_entera;
        printf("%s: parte entera %d.000000, mantisa %.6f\n", reporte->listado[i], parte_entera, mantisa);
    }
}

void imprimir_reporte_literal_cadena(Reporte *reporte)
{
    printf("\n* Listado de literales cadena encontrados:\n");
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        printf("%s: longitud %d\n", reporte->listado[i], strlen(reporte->listado[i]) - 2); // le rresto 2 por que toma como longitud a las comillas
    }
}

void imprimir_reporte_palabras_reservadas(Reporte *reporte, char *cual, Posicion *lista)
{
    Posicion *actual = lista;
    printf("\n* Listado de palabras reservadas (%s):\n", cual);
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        printf("%s: linea %d, columna %d\n", reporte->listado[i], actual->fila, actual->columna);
        if (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
    }
}

void imprimir_reporte_cadenas_no_reconocidas(Reporte *reporte, Posicion *lista)
{
    Posicion *actual = lista;
    printf("\n* Listado de cadenas no reconocidas:\n");
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        printf("%s: linea %d, columna %d\n", reporte->listado[i], actual->fila, actual->columna);
        if (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
    }
}

void imprimir_reporte_constantes_caracter(Reporte *reporte)
{
    printf("\n* Listado de constantes caracter enumerados:\n");
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    for (size_t i = 0; i < reporte->cantidad; i++)
    {
        printf("%d) %s \n", i + 1, reporte->listado[i]);
    }
}

/*
Listado de palabras reservadas en el orden en el que han aparecido en el archivo,
indicando el número de línea y columna de cada una de ellas. Se debe indicar todas
las apariciones de cada palabra reservada y separar el listado por tipos de datos, estructuras de control y otros.
 */
void imprimir_reporte_caracteres_puntuacion_operadores(Reporte *reporte)
{
    char *simbolos_unicos = NULL;
    int *cantidades = NULL;
    int num_simbolos_unicos = 0;

    for (int i = 0; i < reporte->cantidad; i++)
    {
        char *simbolo_actual = reporte->listado[i];
        int encontrado = 0;

        for (int j = 0; j < num_simbolos_unicos; j++)
        {
            if (simbolos_unicos[j] == *simbolo_actual)
            {
                cantidades[j]++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            num_simbolos_unicos++;
            simbolos_unicos = realloc(simbolos_unicos, num_simbolos_unicos * sizeof(char));
            cantidades = realloc(cantidades, num_simbolos_unicos * sizeof(int));
            simbolos_unicos[num_simbolos_unicos - 1] = *simbolo_actual;
            cantidades[num_simbolos_unicos - 1] = 1;
        }
    }
    printf("\n* Listado de operadores/caracteres de puntuación:\n");
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    for (size_t i = 0; i < num_simbolos_unicos; i++)
    {
        printf("%c: aparece %d %s\n", simbolos_unicos[i], cantidades[i], cantidades[i] > 1 ? "veces" : "vez");
    }

    free(simbolos_unicos);
    free(cantidades);
}

void imprimir_reporte_constantes_enteras(Reporte *reporte, char *cual)
{
    printf("\n* Listado de constantes enteras %s:\n", cual);
    int suma = 0;
    if (reporte->cantidad == 0)
    {
        printf("-\n");
    }
    if (strcmp("decimales", cual) == 0)
    {

        for (size_t i = 0; i < reporte->cantidad; i++)
        {
            int valor = atoi(reporte->listado[i]);
            suma += valor;
            printf("%s: valor %d\n", reporte->listado[i], valor);
        }
        if (suma > 0)
            printf("Total acumulado de sumar todas las constantes decimales: %d\n", suma);
    }
    else if (strcmp("octales", cual) == 0)
    {

        for (size_t i = 0; i < reporte->cantidad; i++)
        {
            int valor = strtol(reporte->listado[i], NULL, 8);
            printf("%s: valor entero decimal %d\n", reporte->listado[i], valor);
        }
    }
    else if (strcmp("hexadecimales", cual) == 0)
    {

        for (size_t i = 0; i < reporte->cantidad; i++)
        {
            int valor = strtol(reporte->listado[i], NULL, 16);
            printf("%s: valor entero decimal %d\n", reporte->listado[i], valor);
        }
    }
}