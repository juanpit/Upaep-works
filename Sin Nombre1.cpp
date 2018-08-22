/* 

24500568 | Rodriguez Montenegro Garcia, Erick
24500566 | Velazquez Caballero, Juan Pablo 
30/11/2017
Proyecto

*/

/*

Como parte de los requerimientos, se tiene que hacer uso de estas formas de funciones:
1) Se le pasa un argumento y devuelve un valor:        bool inicializaMatriz( struct contenedorMatriz* sContenedor );
2) Se le pasan argumentos y NO devuelve un valor:      void preguntaRenglonYColumna( int* iColumna, int* iRenglon );
3) No se le pasa ningun argumento y devuelve un valor: int seleccionaDelMenu( void ); 
4) No se le pasa ningun argumento y NO devuelve nada:  void adios(void);

*/


// Archivos de cabecera, para las funciones de la biblioteca de C, usadas en el programa
//#include "stdafx.h"    // ! Comentar para compilar en C, dejar sin comentario para C++
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>   // Permite manipular los atributos de la ventana de salida (consola)
#include <math.h>
#include <time.h>


// En C no está definido el tipo de datos bool, como en C++ o C#, asi que vamos a definir unas constantes, para que 
// este código compile correctamente en C (quita los comentarios para C, dejalos para C++):
// !

#define bool int
#define true 1 
#define false 0

// Como vamos a trabajar con un arreglo bidimensional (matriz), con tamaño fijo, definamos los valores 
// que servirán como dimensiones de dicho arreglo...
#define MaximoColumnas 5
#define MaximoRenglones 5


// Dado que el lenguaje C no permite pasar un arreglo directamente a una función, lo vamos a almacenar dentro 
// de una estructura, la cual si podemos pasarla a una función...
struct contenedorMatriz
{
	float matrizDatos[MaximoRenglones][MaximoColumnas];
};


// Declara los prototipos de las funciones que vamos a usar para manipular el contenedor con nuestra matriz...
bool inicializaMatriz(struct contenedorMatriz* sContenedor);            // Usamos el operador * para indicar que vamos a pasar la variable por referencia.
void muestraMatriz(struct contenedorMatriz sContenedor, bool lPausa);   // Aqui solo pasamos el valor de la variable, pero no una referencia.
void muestraCelda(struct contenedorMatriz sContenedor);
void modificaCelda(struct contenedorMatriz* nOriginal);
void ordenaMatriz(struct contenedorMatriz* Original);

// Declara los prototipos de las funciones accesorias...
int seleccionaDelMenu( void );                                             // Muestra las opciones para este programa y le permite al usuario elegir una.
void preguntaRenglonYColumna( int* iColumna, int* iRenglon);        // Para no repetir el codigo al preguntar por Columna y Renglon.
void adios(void);


// Ciclo principal...
int main()
{
	struct contenedorMatriz sMatrizDeVentas;  // Declara una variable de tipo "contenedorMatriz" esto es la estructura que definimos al inicio.
	bool lYaTieneDatos = false;            // Controla que ya se hayan cargado los datos en la matriz.
	bool lMostrarMatriz = false;           // Para saber si debemos mostrar o no la matriz en la pantalla.
	int iOpcion = 0;                        // Opcion que elije el usuario de acuerdo al menu que se le muestra.  

	do {
		system("@cls");   // Limpia la pantalla...

		// Si la matriz ya tiene valores y si el usuario ya eligio la opcion dos, entonces muestra el contenido de 
		// la matriz por lo que resta del programa...
		if (lYaTieneDatos && lMostrarMatriz)
		{
			muestraMatriz(sMatrizDeVentas, false);  // Le pasamos "false" para que no haga pausa...
		}

		iOpcion = seleccionaDelMenu();

		if ( (iOpcion == 1 || iOpcion == 6) || ((iOpcion > 1) && lYaTieneDatos))
		{
			switch (iOpcion)
			{
			case 1:
				// Carga los datos en el arreglo, nota que la variable la estamos pasando por referencia a la funcion...
				lYaTieneDatos = inicializaMatriz( &sMatrizDeVentas );
				break;

			case 2:
				// Muestra el contenido de la matriz, siempre y cuando ya se hayan cargado los valores...
				muestraMatriz( sMatrizDeVentas, true );  // le pasamos "true" para que haga una pausa después de mostrar los valores...
				lMostrarMatriz = true;
				break;

			case 3:
				// Muestra el valor de la celda ( renglon, columna ) que elija el usuario...
				muestraCelda( sMatrizDeVentas );
				break;

			case 4:
				// Permite al usuario cambiar el valor de la celda que elija...
				modificaCelda( &sMatrizDeVentas );
				break;

			case 5:
				// Ordena la matriz en forma descendente de acuerdo al valor de una columna...
				ordenaMatriz( &sMatrizDeVentas );
				break;

			case 6:
				adios();
				break;

			default:
				printf("Por favor elija un valor entre 1 y 6...\n");
				system("PAUSE");
				break;
			}
		}
		else
		{
			printf("Por favor, primero llene el arreglo con los valores (iOpcion 1)...\n");
			system("PAUSE");
		}
	} while (iOpcion != 6);
	system("PAUSE");
}


bool inicializaMatriz(struct contenedorMatriz* nResultado)
{
	int iColumna = 0, iRenglon = 0;

	struct contenedorMatriz sContenedor;

	// Inicializa el generador de numeros aleatoreos...
	// Nota: usamos una conversión de tipos de datos, en este caso de time a int, usando un "cast" en tiempo de compilacion...
	// C++ srand( static_cast<int>( time(NULL) ) );
	srand(time(NULL));

	// Inicializa los valores de la matriz, de acuerdo a lo siguiente:
	// 1.- La primera columna (0) de la matriz con numeración ascendente inciando en 1 
	// 2.- Las columnas 1 y 2 con valores aleatorios y 
	// 3.- La columna 3 contine el resultado de multiplicar la columna 1 por la dos, del mismo renglon
	// 4.- La columna 4 contendra el resultado de multiplcar la columna 3 por 1.15, para sumarle el 15%, esto en el mismo renglon
	for (iRenglon = 0; iRenglon < MaximoRenglones; iRenglon++) {
		for (iColumna = 0; iColumna < MaximoColumnas; iColumna++) {
			switch (iColumna)
			{
			case 0:
				// Clave del vendedor:
				// C++  sContenedor.matrizDatos[iColumna][iRenglon] = (float)( iRenglon + 1 );  
				sContenedor.matrizDatos[iColumna][iRenglon] = (iRenglon + 1);
				break;

			case 1:
				// Cantidad en almacén (se genera al azar):
				sContenedor.matrizDatos[iColumna][iRenglon] = (rand() % 100 );
				break;

			case 2:
				// Precio unitario del producto (se genera al azar):
				sContenedor.matrizDatos[iColumna][iRenglon] = ( rand() % 10000 + 1 );
				break;

			case 3:
				// Importe (cantidad por precio unitario) del producto:
				sContenedor.matrizDatos[iColumna][iRenglon] = ( sContenedor.matrizDatos[1][iRenglon] * sContenedor.matrizDatos[2][iRenglon] );
				break;

			case 4:
				// Total con ¿impuesto? (importe * 1.15):
				sContenedor.matrizDatos[iColumna][iRenglon] = ( (sContenedor.matrizDatos[3][iRenglon] * 0.15) );
				break;

			default:
				sContenedor.matrizDatos[iColumna][iRenglon] = 0;
			}
		}
	}
	printf("\n¡Listo!  Se han cargado los valores...\n");
	system("PAUSE");

	// Asigna la matriz al apuntador que te pasaron como argumento por referencia, 
	// con lo cual cargas los valores al resultado y los podras tener de vuelta en main()...
	*nResultado = sContenedor;

	return (true);
}


void muestraMatriz( struct contenedorMatriz sContenedor, bool lPausa )
{
	int iColumna = 0, iRenglon = 0;
	bool lResaltado = false;
	float nValor = 0.00;


	HANDLE hVentanaConsola;  // Contenedor a una referencia o "handle"
	hVentanaConsola = GetStdHandle(STD_OUTPUT_HANDLE); // Obten la referencia a la ventana de salida de este programa (consola)
	
	for (iRenglon = 0; iRenglon < MaximoRenglones; iRenglon++) 
	{
		// Detalle estetico: resalta de forma alternada cada renglon de la matriz (estilo "caramelo" o "cebra")...
		if (lResaltado)
		{
			// Cambia el color del texto y el fondo en la ventana donde esta trabajando el programa (esta consola)...
			SetConsoleTextAttribute( hVentanaConsola, 63 );
		}
		else
		{
			// Color alterno...
			SetConsoleTextAttribute( hVentanaConsola, 11 );
		}

		for (iColumna = 0; iColumna < MaximoColumnas; iColumna++) 
		{
			nValor = sContenedor.matrizDatos[iColumna][iRenglon];
			if (iColumna == 0)
			{
				printf(" %4.0f  |", nValor);
			}
			else
			{
				printf(" %10.2f ", nValor);
			}			
		}
		printf("\n");

		// Indica que debes cambiar el color del renglon...
		lResaltado = !lResaltado;
	}
	
	// Deja el color de texto en blanco, fondo negro...
	SetConsoleTextAttribute(hVentanaConsola, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	if (lPausa)
	{
		printf("\n");
		system("PAUSE");
	}
	else
	{
		printf("-------------------------\n");
	}
	return;
}


void muestraCelda(struct contenedorMatriz sContenedor)
{
	int iColumna = 0, iRenglon = 0;
	float nValor = 0.00;

	printf("Muestra una celda: \n");
	preguntaRenglonYColumna( &iColumna, &iRenglon );

	nValor = sContenedor.matrizDatos[iColumna][iRenglon];
	iColumna++;
	iRenglon++;

	printf(" El valor en la matriz columna[%1d], renglon[%1d] es %10.2f ", iColumna, iRenglon, nValor);
	printf("\n");

	system("PAUSE");
}


void modificaCelda(struct contenedorMatriz* nOriginal)
{
	int iColumna = 0, iRenglon = 0;
	float nNuevoValor = 0.00;
	float nValor = 0.00;
	struct contenedorMatriz sContenedor;

	// Toma los valores de la variable original para trabajar con ellos...
	sContenedor = *nOriginal;

	printf("Modifica una celda entre las columnas 1 a 3: \n");
	preguntaRenglonYColumna(&iColumna, &iRenglon);

	if (iColumna >= 0 && iColumna <= 2)
	{
		nValor = sContenedor.matrizDatos[iColumna][iRenglon];
		// En la salida a consola, le estamos sumando un uno a la columna y al renglon, para que sea entendible al usuario"...
		printf("  El valor actual en la matriz columna[%1d], renglon[%1d] es %10.2f\n", iColumna + 1, iRenglon + 1, nValor);

		printf("  Cual es el nuevo valor que deseas darle? ");
		scanf("%f", &nNuevoValor);

		sContenedor.matrizDatos[iColumna][iRenglon] = nNuevoValor;
		nValor = sContenedor.matrizDatos[iColumna][iRenglon];
		printf("  El nuevo valor a [%1d][%1d] ha sido asignado! %10.2f\n", iColumna + 1, iRenglon + 1, nValor);
		if (iColumna > 0)
		{
			// Si cambiaron el valor de cantidad o precio entonces vuelve a calcular el importe y el total...
			sContenedor.matrizDatos[3][iRenglon] = (sContenedor.matrizDatos[1][iRenglon] * sContenedor.matrizDatos[2][iRenglon]);
			// sContenedor.matrizDatos[4][iRenglon] = (float)((sContenedor.matrizDatos[3][iRenglon] * 0.15));
			sContenedor.matrizDatos[4][iRenglon] = ( (sContenedor.matrizDatos[3][iRenglon] * 0.15) );
			printf("  Se re calcularon los valores de las columnas 4 y 5 de este mismo renglon...\n");
		}

		// Copia los valores de vuelta a la variable original para que esten disponibles en main()...
		*nOriginal = sContenedor;
	}
	else
	{
		printf("  Puedes elegir cualquier renglon, pero solo de las primeras tres columnas\n");
	}
	printf("\n");
	system("PAUSE");
}


void ordenaMatriz(struct contenedorMatriz* Original )
{
	int iColumnaElegida = 0;
	int iRenActual = 0;
	int iSigRenglon = 0;
	int iEstaCol = 0;
	float nPaso = 0;

	struct contenedorMatriz sContenedor;

	// Toma los valores de la variable original para trabajar con ellos...
	sContenedor = *Original;

	printf("Ordena la matriz de menor a mayor en base a una columna.\n");

	printf("Elije una columna para ordenar: ");
	while (scanf("%1d", &iColumnaElegida) != 1)
	{
		while (getchar() != '\n');
		printf("Por favor ingresa un numero...");
	}

	// Recuerda que el usuario emplea columnas del 1 al 5, internamente C las maneja del 0 al 4...
	iColumnaElegida--;

	// Si el valor que proporciono el usuario está dentro del rango...
	if (iColumnaElegida >= 0 && iColumnaElegida <= MaximoColumnas)
	{
		// Procede a ordenar el arreglo en base al número de columna elegida...
		for (iRenActual = 0; iRenActual < MaximoRenglones; iRenActual++) 
		{
			for (iSigRenglon = iRenActual + 1; iSigRenglon < MaximoRenglones; iSigRenglon++)
			{
				// Si el elemento en la posición iRenActual de la columna seleccionada es mayor al del siguiente renglon...
				if (sContenedor.matrizDatos[iColumnaElegida][iRenActual] > sContenedor.matrizDatos[iColumnaElegida][iSigRenglon])
				{
					// Intercambia los valores de todas las columnas en los renglones actual y siguiente...
					for (iEstaCol = 0; iEstaCol < MaximoColumnas; iEstaCol++)
					{
						// Haz el intercambio los elementos de los renglones Actual y Siguiente, columna por columna...
						nPaso = sContenedor.matrizDatos[iEstaCol][iRenActual];
						sContenedor.matrizDatos[iEstaCol][iRenActual] = sContenedor.matrizDatos[iEstaCol][iSigRenglon];
						sContenedor.matrizDatos[iEstaCol][iSigRenglon] = nPaso;
					}
				}
			}
		}
		// Copia los valores de vuelta a la variable original para que esten disponibles en main()...
		*Original = sContenedor;

		printf("  Listo!  La matriz fue ordenada en base a la columna %d\n", iColumnaElegida + 1);
	}
	else
	{
		printf("  Por favor, elije un valor entre 1 y 5...\n");
	}
	printf("\n");
	system("PAUSE");

}


int seleccionaDelMenu(void)
{
	int iOpcion = 0;
	HANDLE hVentanaConsola;  // Contenedor a una referencia o "handle"
	hVentanaConsola = GetStdHandle(STD_OUTPUT_HANDLE); // Obten la referencia a la ventana de salida de este programa (consola)

	printf("MENU para Vendedores :D\n\n");
	printf("1)  Llenar datos de las columnas 2 y 3 con valores al azar\n");
	printf("2)  Desplegar todos los datos en la matriz\n");
	printf("3)  Imprimir un dato solicitado\n");
	printf("4)  Cambiar un dato\n");
	printf("5)  Ordenar datos en base a alguna columna\n");
	printf("6)  Salir\n\n");

	// Cambia el color del texto y el fondo en la ventana donde esta trabajando el programa (esta consola)...
	SetConsoleTextAttribute(hVentanaConsola, FOREGROUND_GREEN);
	printf(" Que opcion eliges? ");
	SetConsoleTextAttribute(hVentanaConsola, 7);

	// Trata de que solo te den un número...
	while (scanf("%1d", &iOpcion) != 1)
	{
		while (getchar() != '\n');
		SetConsoleTextAttribute(hVentanaConsola, 79);
		printf("Por favor ingresa un numero...");
		SetConsoleTextAttribute(hVentanaConsola, 7);
	}

	return iOpcion;
}


void preguntaRenglonYColumna(int* iColumna, int* iRenglon)
{
	int iEsteRenglon = 0, iEstaColumna = 0;

	printf("Indica un valor para la columna: ");

	// Trata de que solo te den un número...
	while (scanf("%1d", &iEstaColumna) != 1)
	{
		while (getchar() != '\n');
		printf("Por favor ingresa un numero...");
	}

	printf("Indica un valor para el renglon: ");

	// Trata de que solo te den un número...
	while (scanf("%1d", &iEsteRenglon) != 1)
	{
		while (getchar() != '\n');
		printf("Por favor ingresa un numero...");
	}
	// Recuerda que los índices de un arreglo en C comienzan en cero, asi que, restales uno, para que 
	// realmente apunten a la columna y renglón que corresponde a la imagen en memoria del arreglo...
	iEstaColumna--; 
	iEsteRenglon--;

	// Asigna los valores a los apuntadores, para que se modifiquen el contenido de las variables que nos pasaron por referencia...
	*iColumna = iEstaColumna;
	*iRenglon = iEsteRenglon;
}


void adios(void)
{
	printf("\nHasta luego!\n\n");
}

// EoF: proyecto.c

