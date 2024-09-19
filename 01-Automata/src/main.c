#include <stdlib.h>
#include <stdio.h>

#define CANT_ESTADOS 7
#define CANT_SIMBOLOS 6
#define MAX_NUM_LENGTH 10

typedef enum
{
    Q0,
    Q1,
    Q2,
    Q4,
    Q5,
    Q6,
    RR
} t_estado;

typedef enum
{
    CERO,
    UNOaSIETE,
    OCHOoNUEVE,
    Xx,
    AFaf,
    OTRO
} t_caracter;

#define ESTADO_INICIAL Q0

#define ES_ESTADO_FINAL_OCTAL(estado) (estado == Q4 || estado == Q1)
#define ES_ESTADO_FINAL_DECIMAL(estado) (estado == Q5)
#define ES_ESTADO_FINAL_HEXADECIMAL(estado) (estado == Q6)

#define CENTINELA ','

int tabla_transiciones[CANT_ESTADOS][CANT_SIMBOLOS] = {
    {Q1, Q5, Q5, RR, RR, RR}, // q0
    {Q4, Q4, RR, Q2, RR, RR}, // q1
    {Q6, Q6, Q6, RR, Q6, RR}, // q2
    {Q4, Q4, RR, RR, RR, RR}, // q4
    {Q5, Q5, Q5, RR, RR, RR}, // q5
    {Q6, Q6, Q6, RR, Q6, RR}, // q6
    {RR, RR, RR, RR, RR, RR}  // r
};

t_estado char_to_enum(char c);
void lexer(FILE *input, FILE *output);
void escribirEnArchivoSegunEstado(FILE *output, t_estado estado, char numLength);

int main(int argc, char *argv[])
{
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    if (inputFile == NULL)
    {
        printf("\nError al intentar abrir el archivo %s.\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (outputFile == NULL)
    {
        lexer(inputFile, stdout);
    }
    else
    {
        lexer(inputFile, outputFile);
    };

    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}

t_estado char_to_enum(char c)
{
    if (c == '0')
    {
        return CERO;
    }

    if (c >= '1' && c <= '7')
    {
        return UNOaSIETE;
    }

    if (c == '8' || c == '9')
    {
        return OCHOoNUEVE;
    }

    if (c == 'x' || c == 'X')
    {
        return Xx;
    }

    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
    {
        return AFaf;
    }

    return OTRO;
};

void lexer(FILE *input, FILE *output)
{
    char c;
    int estado = ESTADO_INICIAL;
    char numLength = 0;
    while ((c = fgetc(input)) != EOF)
    {
        if (c != CENTINELA)
        {
            fputc(c, output);
            estado = tabla_transiciones[estado][char_to_enum(c)];
            numLength++;
        }
        else
        {
            escribirEnArchivoSegunEstado(output, estado, numLength);
            estado = ESTADO_INICIAL;
            numLength = 0;
        };
    };
    escribirEnArchivoSegunEstado(output, estado, numLength);
};

void escribirEnArchivoSegunEstado(FILE *output, t_estado estado, char numLength)
{
    fputc(' ', output);
    for (int i = 0; i < MAX_NUM_LENGTH - numLength; i++)
    {
        fputc(' ', output);
    }

    if (ES_ESTADO_FINAL_DECIMAL(estado))
    {
        fputs("DECIMAL\n", output);
    }
    else if (ES_ESTADO_FINAL_HEXADECIMAL(estado))
    {
        fputs("HEXADECIMAL\n", output);
    }
    else if (ES_ESTADO_FINAL_OCTAL(estado))
    {
        fputs("OCTAL\n", output);
    }
    else
    {
        fputs("NO RECONOCIDA\n", output);
    };
}
