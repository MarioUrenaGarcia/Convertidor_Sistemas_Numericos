#include "alfaconv.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * Mario Ureña Garcpua
 *
 * Este programa permite al usuario convertir números entre sistemas numéricos decimal, binario, octal y hexadecimal.
 * Entradas:
 * - Número de entrada: El número a convertir.
 * - Base de salida: El sistema numérico deseado para la salida.
 * - Guardar resultado: si se guarda el resultado en un archivo.
 *
 * Salidas:
 * - Número convertido: El resultado de la conversión.
 * - Salida de archivo: si está habilitado, el programa guarda el resultado de la conversión en un archivo.
 *
 */

// Main ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  printf("\n\n\tEste código fue creado por Mario Ureña García\n\n");

  // Variables
  char entrada[256] = {0};
  char salida[256] = {0};
  char conversion[2] = {0};
  int proceso = 0;
  int entrada_int = 0;
  int salida_int = 0;
  int abrir = 0;
  int out = 0;

  FILE *fp;
  char archivo[256];

  // Procesos
  if (argc < 2)
  {
    printf("Ingrese un número:    ");
    scanf("%s", entrada);

    printf("\nIngrese la base de salida:    ");
    scanf("%s", conversion);

    printf("\n¿Desea guardar el resultado en un archivo? (1 = Sí, 0 = No):    ");
    scanf("%d", &abrir);

    if (abrir == 1)
    {
      printf("\nIngrese el nombre del archivo:    ");
      scanf("%s", archivo);
    }
  }
  else if (argc == 2)
  {
    strcpy(entrada, argv[1]);

    printf("\nIngrese la base de salida:    ");
    scanf("%s", conversion);

    printf("\n¿Desea guardar el resultado en un archivo? (1 = Sí, 0 = No):    ");
    scanf("%d", &abrir);

    if (abrir == 1)
    {
      printf("\nIngrese el nombre del archivo:    ");
      scanf("%s", archivo);
    }
  }
  else if (argc == 3)
  {
    strcpy(entrada, argv[1]);
    strcpy(conversion, argv[2]);

    printf("\n¿Desea guardar el resultado en un archivo? (1 = Sí, 0 = No):    ");
    scanf("%d", &abrir);

    if (abrir == 1)
    {
      printf("\nIngrese el nombre del archivo:    ");
      scanf("%s", archivo);
    }
  }
  else if (argc == 4 && strcmp(argv[3], "-f") == 0)
  {
    strcpy(entrada, argv[1]);
    strcpy(conversion, argv[2]);
    abrir = 1;
    if (abrir == 1)
    {
      printf("\nIngrese el nombre del archivo:    ");
      scanf("%s", archivo);
    }
  }
  else if (argc == 5)
  {
    strcpy(entrada, argv[1]);
    strcpy(conversion, argv[2]);
    strcpy(archivo, argv[4]);
    abrir = 1;
  }
  else
  {
    printf("\n\n\tEntrada no válida\n\n");
    return 1;
  }

  if (entrada[0] == '0' && entrada[1] != 'x')
  {
    proceso = 1; // La entrada es un octal

    for (int i = 0; i < strlen(entrada); i++) // borrar el 0 del inicio
    {
      entrada[i] = entrada[i + 1];
    }

    // Comprobar que todos los caracteres sean 0, 1, 2, 3, 4, 5, 6, 7
    for (int i = 0; i < strlen(entrada); i++)
    {
      if (entrada[i] != '0' && entrada[i] != '1' && entrada[i] != '2' && entrada[i] != '3' && entrada[i] != '4' && entrada[i] != '5' && entrada[i] != '6' && entrada[i] != '7')
      {
        printf("\n\n\tEntrada no válida\n\n");
        return 1;
      }
    }
  }
  else if (entrada[0] == '0' && entrada[1] == 'x' || entrada[1] == 'X')
  {
    proceso = 2; // La entrada es un hexadecimal

    for (int i = 0; i < strlen(entrada); i++) // borrar el 0x del inicio
    {
      entrada[i] = entrada[i + 2];
    }

    // Comprobar que todos los caracteres sean 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
    for (int i = 0; i < strlen(entrada); i++)
    {
      if (entrada[i] != '0' && entrada[i] != '1' && entrada[i] != '2' && entrada[i] != '3' && entrada[i] != '4' && entrada[i] != '5' && entrada[i] != '6' && entrada[i] != '7' && entrada[i] != '8' && entrada[i] != '9' && entrada[i] != 'A' && entrada[i] != 'B' && entrada[i] != 'C' && entrada[i] != 'D' && entrada[i] != 'E' && entrada[i] != 'F' && entrada[i] != 'a' && entrada[i] != 'b' && entrada[i] != 'c' && entrada[i] != 'd' && entrada[i] != 'e' && entrada[i] != 'f')
      {
        printf("\n\n\tEntrada no válida\n\n");
        return 1;
      }
    }
  }
  else if (entrada[0] == 'b')
  {
    proceso = 3; // La entrada es un binario

    for (int i = 0; i < strlen(entrada); i++) // borrar la b del inicio
    {
      entrada[i] = entrada[i + 1];
    }

    // Comprobar que todos los caracteres sean 0, 1
    for (int i = 0; i < strlen(entrada); i++)
    {
      if (entrada[i] != '0' && entrada[i] != '1')
      {
        printf("\n\n\tEntrada no válida\n\n");
        return 1;
      }
    }
  }
  else
  {
    // Comprobar que todos los caracteres sean 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    for (int i = 0; i < strlen(entrada); i++)
    {
      if (entrada[i] != '0' && entrada[i] != '1' && entrada[i] != '2' && entrada[i] != '3' && entrada[i] != '4' && entrada[i] != '5' && entrada[i] != '6' && entrada[i] != '7' && entrada[i] != '8' && entrada[i] != '9')
      {
        printf("\n\n\tEntrada no válida\n\n");
        return 1;
      }
    }
    proceso = 4; // La entrada es un decimal
  }

  if (proceso == 4 && strcmp(conversion, "b") == 0)
  {
    printf("\n\nDECIMAL A BINARIO");
    entrada_int = atoi(entrada);
    dec_to_bin(entrada_int, salida);
    out = 1;
  }

  else if (proceso == 4 && strcmp(conversion, "h") == 0)
  {
    printf("\n\nDECIMAL A HEXADECIMAL");
    entrada_int = atoi(entrada);
    dec_to_hex(entrada_int, salida);
    out = 1;
  }

  else if (proceso == 4 && strcmp(conversion, "0") == 0)
  {
    printf("\n\nDECIMAL A OCTAL");
    entrada_int = atoi(entrada);
    dec_to_oct(entrada_int, salida);
    out = 1;
  }

  else if (proceso == 3 && strcmp(conversion, "d") == 0)
  {
    printf("\n\nBINARIO A DECIMAL");
    salida_int = bin_to_dec(entrada);
    out = 2;
  }

  else if (proceso == 3 && strcmp(conversion, "h") == 0)
  {
    printf("\n\nBINARIO A HEXADECIMAL");
    bin_to_hex(entrada, salida);
    out = 1;
  }
  else if (proceso == 2 && strcmp(conversion, "d") == 0)
  {
    printf("\n\nHEXADECIMAL A DECIMAL");
    salida_int = hex_to_dec(entrada);
    out = 2;
  }

  else if (proceso == 2 && strcmp(conversion, "b") == 0)
  {
    printf("\n\nHEXADECIMAL A BINARIO");
    hex_to_bin(entrada, salida);
    out = 1;
  }

  else if (proceso == 1 && strcmp(conversion, "d") == 0)
  {
    printf("\n\nOCTAL A DECIMAL");
    salida_int = oct_to_dec(entrada);
    out = 2;
  }
  else
  {
    printf("\n\n\tNo Implementado");
    return 1;
  }

  if (abrir == 1)
  {
    if (out == 1)
    {
      fp = fopen(archivo, "a");
      fprintf(fp, "%s  ->  %s \n", entrada, salida);
      fclose(fp);
    }
    else if (out == 2)
    {
      fp = fopen(archivo, "a");
      if (proceso == 1)
      {
        fprintf(fp, "0");
      }
      else if (proceso == 2)
      {
        fprintf(fp, "0x");
      }
      else if (proceso == 3)
      {
        fprintf(fp, "b");
      }
      fprintf(fp, "%s  ->  %d \n", entrada, salida_int);
      fclose(fp);
    }
  }

  // FINALIZACIÓN DEL PROGRAMA
  printf("\n\n\tPrograma Finalizado con ÉXITO\n\n");
  return 0;
}
