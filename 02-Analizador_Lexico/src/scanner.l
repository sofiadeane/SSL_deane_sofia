
/* Inicio de la sección de definiciones. Aquí: */
/* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
/* De esas formas podemos poner declaraciones y definiciones de C y directivas del preprocesador */
/* 2. Los comentarios (sólo hay de múltiples líneas) sin sangría también se copian tal cual al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */

%{

#include <stdio.h>
#include <string.h>
#include "reportes.h"

Reporte reporte_constantes_reales;
Reporte reporte_literales_cadena;
Reporte reporte_palabras_reservadas_tipo;
Reporte reporte_palabras_reservadas_estructura;
Reporte reporte_palabras_reservadas_otro;
Reporte reporte_caracteres_puntuacion_operadores;
Reporte reporte_cadenas_no_reconocidas;
Reporte reporte_constantes_enteras_decimales;
Reporte reporte_constantes_enteras_octales;
Reporte reporte_constantes_enteras_hexadecimales;
Reporte reporte_constantes_caracter;
Reporte reporte_identificadores;

#define INICIO_CONTEO_LINEA 1
#define INICIO_CONTEO_COLUMNA 1

int linea_actual = INICIO_CONTEO_LINEA, columna_actual = INICIO_CONTEO_COLUMNA;
Posicion *lista_tipos_datos =NULL;
Posicion *lista_estructuras_control=NULL;
Posicion *lista_otros=NULL;
Posicion *lista_no_reconocidos=NULL;

%}

/* La siguiente línea define explícitamente a yytext como un puntero a un caracter ( char* yytext; ). Ésta es la opción por defecto si no se pone nada. */
%pointer
/* Con la siguiente opción la función de análisis int yylex(void); se comporta como si en la sección de usuario existiera la función int yywrap(void) return 1; la cual devuelve verdadero (no-cero), haciendo que una vez que la función de análisis int yylex(void) reciba una indicación de EOF desde YY_INPUT, asuma que no hay nada más para analizar de yyin y finalice (haciendo un return 0;) */
%option noyywrap

/* Estados*/
%x tokenNoReconocido
/* Condiciones de arranque inclusivas */
/* %s */
/* Condiciones de arranque exclusivas */
/* %x */

/* Declaraciones con cada nombre y su definición; se utilizan para simplificar las reglas */
/* digito [0-9] */
DIGITO                          [0-9] 
DIGITO_OCTAL                    [0-7]
DIGITO_HEX                      [0-9A-Fa-f]

SECUENCIA_UNICODE               u{DIGITO_HEX}{4}|U{DIGITO_HEX}{8}
SECUENCIA_ESCAPE                ["'\\abfnrtv]|{CONSTANTE_OCTAL}|{CONSTANTE_HEXADECIMAL}|{SECUENCIA_UNICODE}
CARACTER_ESCAPADO               \\{SECUENCIA_ESCAPE}
PARTE_EXPONENTE                 [eE][+-]?{DIGITO}+
SUFIJO_REAL                     [dDfFlL]
CARACTER_NORMAL_CADENA          [^"\\]
CARACTER_NORMAL_CARACTER        [^'\\]

IDENTIFICADORES                 [A-Za-z_][0-9A-Za-z_]*
CONSTANTE_DECIMAL               {DIGITO}+
CONSTANTE_OCTAL                 0{DIGITO_OCTAL}*
CONSTANTE_HEXADECIMAL           0[xX]{DIGITO_HEX}+
LITERAL_CADENA                  \"({CARACTER_NORMAL_CADENA}|{CARACTER_ESCAPADO})*\"
CONSTANTE_CARACTER              \'({CARACTER_NORMAL_CARACTER}|{CARACTER_ESCAPADO})\'
CONSTANTE_FRACCIONARIA          {DIGITO}*\.{DIGITO}+ 
PALABRA_RESERVADA_TIPO_DATO     (int|short|long\ long|long|float|double|long\ double|char|unsigned\ char|signed\ char|void|bool|unsigned|signed)
/* Definiciones para palabras reservadas de estructuras de control */
PALABRA_RESERVADA_CONTROL       (if|else|switch|case|default|while|do|for|break|continue|return)
/* Definiciones para palabras reservadas otras */
PALABRA_RESERVADA_OTRO          (auto|extern|register|static|typedef|inline|struct|union|enum|sizeof)

/* Fin de la sección de definiciones */
/* Inicio de la sección de reglas. Aquí: */
/* 1. Cualquier texto sangrado o encerrado entre '%{' y '%}' (estos últimos dos sin sangrar en líneas ocupadas únicamente por ellos) se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
/* Esto podría utilizarse para declarar variables que son locales a la rutina de análisis léxico y (después de las declaraciones) al código que debe ejecutarse siempre que se entra a la rutina de análisis léxico */
/* 2. NO pueden hacerse comentarios sin sangría, ya que estos no se copian literalmente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */
%%

({LITERAL_CADENA}) { agregar_elemento_ordenado(&reporte_literales_cadena, yytext); columna_actual += yyleng; }

({CONSTANTE_CARACTER}) { agregar_elemento(&reporte_constantes_caracter, yytext); columna_actual += yyleng; }

({CONSTANTE_OCTAL}) { agregar_elemento(&reporte_constantes_enteras_octales, yytext); columna_actual += yyleng; } 

({CONSTANTE_DECIMAL}) { agregar_elemento(&reporte_constantes_enteras_decimales, yytext); columna_actual += yyleng; }

({CONSTANTE_HEXADECIMAL}) { agregar_elemento(&reporte_constantes_enteras_hexadecimales, yytext); columna_actual += yyleng; }

[+\-*/%=!&|>\<?:\(\)\{\}\[\];,] { agregar_elemento(&reporte_caracteres_puntuacion_operadores, yytext); columna_actual += yyleng; }

({CONSTANTE_FRACCIONARIA}{PARTE_EXPONENTE}?{SUFIJO_REAL}?)|({DIGITO}+{PARTE_EXPONENTE}{SUFIJO_REAL}?) { agregar_elemento(&reporte_constantes_reales, yytext); columna_actual += yyleng; } 

{PALABRA_RESERVADA_TIPO_DATO} { agregar_elemento(&reporte_palabras_reservadas_tipo, yytext); insertar_lista(&lista_tipos_datos, linea_actual, columna_actual); columna_actual += yyleng; }

{PALABRA_RESERVADA_CONTROL} { agregar_elemento(&reporte_palabras_reservadas_estructura, yytext); insertar_lista(&lista_estructuras_control, linea_actual, columna_actual); columna_actual += yyleng; }

{PALABRA_RESERVADA_OTRO} { agregar_elemento(&reporte_palabras_reservadas_otro, yytext); insertar_lista(&lista_otros, linea_actual, columna_actual); columna_actual += yyleng; }

{IDENTIFICADORES} {agregar_elemento(&reporte_identificadores, yytext); columna_actual += yyleng;}

[ \t]+ { columna_actual += yyleng; }

\n+ { linea_actual += yyleng; columna_actual = INICIO_CONTEO_COLUMNA; }

[^ \t\n] {
    insertar_lista(&lista_no_reconocidos, linea_actual, columna_actual);
    agregar_elemento(&reporte_cadenas_no_reconocidas, yytext);
    BEGIN(tokenNoReconocido);
    columna_actual += yyleng;
  }



<tokenNoReconocido>{
    /* Manejar el final del archivo */
    <<EOF>> {
        fprintf(stderr, "\n");
        BEGIN(INITIAL);
    }
    /* Manejar espacios, tabuladores y nuevas líneas para finalizar el token no reconocido*/
    " "|\t|\n {
        yyless(0); // Devuelve el espacio al flujo de entrada
        fprintf(stderr, "\n");
        BEGIN(INITIAL); // Regresa al estado inicial
    }
    /* Continuar capturando el token no reconocido*/
    [^ \t\n]+ {
        concatenar_ultimo_elemento(&reporte_cadenas_no_reconocidas,yytext);
        columna_actual += yyleng;
        BEGIN(INITIAL); // Regresa al estado inicial
    }
}
    /* Reglas por defecto de Flex: */
        /* <*>.|\n { ECHO; } */
            /* (ECHO; escribe yytext en la salida del escáner: FILE* yyout (variable global a la cual por defecto se le asigna stdout)) */
        /* <<EOF>> { yyterminate(); } */
            /* (yyterminate(); hace que la función yylex finalice retornando un 0, indicando un fin-de-entrada (EOF)) */

%%
/* Fin de la sección de reglas */ 

/* Inicio de la sección de código de usuario, la cual: */
	/* 1. Se utiliza para rutinas de complemento que llaman al analizador léxico o son llamadas por este; la presencia de esta sección es opcional */
    /* 2. Toda esta sección simplemente se copia íntegramente al archivo de salida del analizador léxico (scanner) generado (*.lex.yy.c) */

int main(int argc, char *argv[])
{
    FILE *inputFile = NULL;
    char *fileName = NULL;
    int debugFlag = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            debugFlag = 1;
        }
        else
        {
            fileName = argv[i];
            inputFile = fopen(fileName, "r");
        }
    }

    if (debugFlag == 0)
    {
        if (inputFile == NULL)
        {
            if (fileName)
            {
                printf("Error al abrir el archivo %s\n", fileName);
            }
            else
            {
                printf("No se proporciono un archivo de entrada.\n");
            }
            return EXIT_FAILURE;
        }
        else
        {
            yyin = inputFile;
        }
    } else {
        printf("Modo debug activado. La entrada sera manual por consola\n");
    }


    inicializar_reporte(&reporte_literales_cadena);
    inicializar_reporte(&reporte_palabras_reservadas_tipo);
    inicializar_reporte(&reporte_palabras_reservadas_estructura);
    inicializar_reporte(&reporte_palabras_reservadas_otro);
    inicializar_reporte(&reporte_constantes_reales);
    inicializar_reporte(&reporte_caracteres_puntuacion_operadores);
    inicializar_reporte(&reporte_cadenas_no_reconocidas);
    inicializar_reporte(&reporte_constantes_enteras_decimales);
    inicializar_reporte(&reporte_constantes_enteras_octales);
    inicializar_reporte(&reporte_constantes_enteras_hexadecimales);
    inicializar_reporte(&reporte_constantes_caracter);
    inicializar_reporte(&reporte_identificadores);

    yylex();

    imprimir_reporte_identificadores(&reporte_identificadores);
    imprimir_reporte_literal_cadena(&reporte_literales_cadena);
    imprimir_reporte_palabras_reservadas(&reporte_palabras_reservadas_tipo, "tipos de dato", lista_tipos_datos);
    imprimir_reporte_palabras_reservadas(&reporte_palabras_reservadas_estructura, "estructuras de control",lista_estructuras_control);
    imprimir_reporte_palabras_reservadas(&reporte_palabras_reservadas_otro, "otros",lista_otros);
    imprimir_reporte_constantes_enteras(&reporte_constantes_enteras_decimales, "decimales");
    imprimir_reporte_constantes_enteras(&reporte_constantes_enteras_hexadecimales, "hexadecimales");
    imprimir_reporte_constantes_enteras(&reporte_constantes_enteras_octales, "octales");
    imprimir_reporte_constantes_reales(&reporte_constantes_reales);
    imprimir_reporte_constantes_caracter(&reporte_constantes_caracter);
    imprimir_reporte_caracteres_puntuacion_operadores(&reporte_caracteres_puntuacion_operadores);
    imprimir_reporte_cadenas_no_reconocidas(&reporte_cadenas_no_reconocidas,lista_no_reconocidos);

    liberar_reporte(&reporte_constantes_reales);
    liberar_reporte(&reporte_palabras_reservadas_tipo);
    liberar_reporte(&reporte_palabras_reservadas_estructura);
    liberar_reporte(&reporte_palabras_reservadas_otro);
    liberar_reporte(&reporte_literales_cadena);
    liberar_reporte(&reporte_caracteres_puntuacion_operadores);
    liberar_reporte(&reporte_cadenas_no_reconocidas);
    liberar_reporte(&reporte_constantes_enteras_decimales);
    liberar_reporte(&reporte_constantes_enteras_octales);
    liberar_reporte(&reporte_constantes_enteras_hexadecimales);
    liberar_reporte(&reporte_constantes_caracter);
    liberar_reporte(&reporte_identificadores);

    eliminar_lista(lista_tipos_datos);
    eliminar_lista(lista_estructuras_control);
    eliminar_lista(lista_otros);
    eliminar_lista(lista_no_reconocidos);

    fclose(inputFile);
    return EXIT_SUCCESS;
}

/* Fin de la sección de código de usuario */