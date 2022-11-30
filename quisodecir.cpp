#include <string.h>
#include <stdio.h>
#define TAMTOKEN 50


void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{

	
	iNumElementos = 1;
	strcpy(szPalabras[0], "AquiVaElDiccionario");
	iEstadisticas[0] = 1; 

	FILE* archivo;

	fopen_s(&archivo, szNombre, "r");
	if (archivo != NULL)
	{
		char textoEnBruto[700];

		
		while (!feof(archivo))
		{
			for (int i = 0; i != NUMPALABRAS; i++)
			{
				
				fscanf(archivo, "%s", textoEnBruto[i]);
				
			}
			fclose(archivo);
		}

		int caracterszNombre, numpalabra = 0, j = 0;
		char szpalabrasinorden[][TAMTOKEN]{ 'hola','pepe','C' };
		char arrayAxiliar[TAMTOKEN];
		struct PALABRA_CON_FREC
		{
			char laPalabra[TAMTOKEN];
			int frecuencia = 1;
		}unaPalabra;

		
		while (szNombre[caracterszNombre] != '\0')
		{
			caracterszNombre = 0;
			
			while (caracterszNombre != ' ' && caracterszNombre != '\0' && caracterszNombre != '	' && caracterszNombre != ',' && caracterszNombre != '.' && caracterszNombre != '(' && caracterszNombre != ')' && caracterszNombre != '¿' && caracterszNombre != '?' && caracterszNombre != '!' && caracterszNombre != '¡')
			{
				
				szpalabrasinorden[numpalabra][caracterszNombre++] = szNombre[caracterszNombre];
			}
			
			caracterszNombre = '\0';
			numpalabra++;
			if (szNombre[caracterszNombre] != '\0')
			{
				
				caracterszNombre++;
			}
		}
		
		for (int i = 0; i < caracterszNombre; i++)
		{
			for (int posicionDelantera = 1; posicionDelantera < caracterszNombre; posicionDelantera++)
			{
				if (strcmp(szpalabrasinorden[i], szpalabrasinorden[posicionDelantera]) == 0)
					
				{
					szpalabrasinorden[posicionDelantera][0] = '\0';
					unaPalabra.frecuencia++;
				}
				else if (strcmp(szpalabrasinorden[i], szpalabrasinorden[posicionDelantera]) > 0)
				{
					strcpy(arrayAxiliar, szpalabrasinorden[i]);
					strcpy(szpalabrasinorden[i], szpalabrasinorden[posicionDelantera]);
					strcpy(szpalabrasinorden[posicionDelantera], arrayAxiliar);
				}
			}
		}

	}
	else
	{
		printf("No fue posible leer el archivo, verifique que este en la capeta mecionada o que no este vacío ni corrupto.");
	}
}

int numero1;
int numero2;

void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy(szListaFinal[0], szPalabrasSugeridas[0]); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata

	iNumLista = 1;							//Una sola palabra candidata
}

void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}







/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) Ernesto Peñaloza Romero 2015-2020

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

******************************************************************************************************************/
// quisodecir.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <string.h>
#include "corrector.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char	szNombre[50];
	char	szPalabras[NUMPALABRAS][TAMTOKEN];
	int		iEstadisticas[NUMPALABRAS];
	int		i;
	int		iNumElementos;
	int		iNumSugeridas;
	char	szPalabraLeida[TAMTOKEN];
	char	szPalabrasSugeridas[3300][TAMTOKEN];
	char	szListaFinal[3300][TAMTOKEN];
	int		iPeso[3300]; //son 66 combinaciones por letra, mas o menos 3300 para 50 letras
	int		iNumLista;

	//Inicia el arreglo de estadisticas
	for (i = 0; i < NUMPALABRAS; i++)
		iEstadisticas[i] = 0;

	//strcpy_s(szNombre, "anita.txt");
	printf("Archivo para el diccionario: ");
	scanf_s("%s", szNombre, 50);

	Diccionario(szNombre, szPalabras, iEstadisticas, iNumElementos);

	for (int j = 0; j < iNumElementos; j++)
		printf("%-12s %i\n", szPalabras[j], iEstadisticas[j]);

	printf("Numero de elementos en la lista: %i\n", iNumElementos);
	strcpy_s(szPalabraLeida, "");
	while (strcmp(szPalabraLeida, "fin"))
	{
		printf("\nDigite una palabra o 'fin' para terminar: ");
		scanf_s("%s", szPalabraLeida, TAMTOKEN);
		_strlwr_s(szPalabraLeida);
		ClonaPalabras(szPalabraLeida, szPalabrasSugeridas, iNumSugeridas);

		for (int j = 0; j < iNumSugeridas - 1; j++)
			printf("%s\n", szPalabrasSugeridas[j]);
		printf("Numero de elementos en la lista de clonacion: %i\n", iNumSugeridas);

		ListaCandidatas(szPalabrasSugeridas, iNumSugeridas, szPalabras, iEstadisticas, iNumElementos,
			szListaFinal, iPeso, iNumLista);
		printf("\n\nTal vez ud quiso decir:\npalabra\t frecuencia\n");
		printf("=======\t ==========\n");
		if (iNumLista > 0)
		{

			for (int j = 0; j < iNumLista; j++)
				printf("%s\t%i\n", szListaFinal[j], iPeso[j]);
			printf("Numero de elementos en la lista de opciones: %i\n", iNumLista);
		}
		else
			printf("\n\nSin opciones que mostrar\n");
	}

	return 0;
}

//






