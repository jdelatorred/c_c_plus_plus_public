/*Programa para Efectuar Operaciones con Polinomios
By Jorge de la Torre Dávalos Programacion I F.U.S.M.
Docentes Ing. Lyda Soto  -  Ing. Andres Gaitan*/

//Codigo Definitivo

//Declaracion de Librerias - Cabeceras
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>

//constantes para vectores
 #define SIZE_ONE 50
 #define SIZE_TWO 100

//Prototipos de Funciones en Orden Alfabetico
void ayuda(); //Guia de Ingreso de Polinomios al Programa
void dividir(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit_a, int limit_b, int limit); // Divide dos polinomios utilizando division Larga
void dividir_factorizacion(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int exp_fac_uno[2], int factor_uno[2], int exp_fac_dos[2], int factor_dos[2], int limit_a, int limit_b); // Divide los polinomios del resultado de teorema de Residuo
void encabezado(); //Imprime lineas de division
void espera(); //Pausa despues de ejecucion
void factorizar(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit_a, int limit_b); // Factoriza dos Polinomios Utilizando el Teorema del Factor
void imprimir_factorizacion(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int exp_tot[SIZE_ONE], float pol_tot[SIZE_ONE], int exp_fac_uno[2], int factor_uno[2], int exp_fac_dos[2], int factor_dos[2], int pol_uno_dividendo_aux[SIZE_ONE], int pol_dos_dividendo_aux[SIZE_ONE], int limit); // Imprime los polinomios Originales y su factorizacion
void imprimir_polinomios(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int exp_tot[SIZE_ONE], float pol_tot[SIZE_ONE], int limit); // Imprime los polinomios Originales y su resultado
void menu(); //Menu de Opciones
void multiplica(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit); //Realiza la Multiplicacion los Polinomios
void pedir_polinomio(int x); //Funcion para pedir los datos de los polinomios
void resta(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit); //Realiza la resta de los Polinomios
void suma(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit); //Realiza las Sumas de los Polinomios

//funcion Principal
void main(void)
{
	menu();
}
//Despliega el Encabezado del Programa y el menu de opciones
void menu()
{
	int i, opc, x;
	char *selec;
	do
	{
		clrscr();
		encabezado();
		gotoxy(10, 2);
		printf("FUNDACION UNIVERSITARIA SAN MARTIN - FACULTAD ABIERTA Y A DISTANCIA");
		gotoxy(28, 3);
		printf("INGENIERIA DE SISTEMAS");
		gotoxy(26, 4);
		printf("PROGRAMACION I-MATEMATICAS I");
		gotoxy(33, 5);
		printf("PROYECTO FINAL");
		gotoxy(29, 6);
		printf("SOLUCION DE POLINOMIOS\n\n");
		encabezado();
		printf("\n\n1.Suma de 2 Polinomios.\n\n2.Resta de 2 Polinomios.\n\n3.Multiplicacion de 2 Polinomios.\n\n4.Division de 2 Polinomios.\n\n5.Factorizacion de 2 Polinomios.\n\n6.Ayuda.\n\n7.Salir\n\n");
		printf("\nIngrese Su Opcion:[ ]\b\b");
		fflush(stdin);
		gets(selec);
		opc = atoi(selec);

		//evalua la eleccion del usuario
		switch (opc)
		{
			case 1:
				x = 1;
				pedir_polinomio(x);
				break;

			case 2:
				x = 2;
				pedir_polinomio(x);
				break;

			case 3:
				x = 3;
				pedir_polinomio(x);
				break;

			case 4:
				x = 4;
				pedir_polinomio(x);
				break;

			case 5:
				x = 5;
				pedir_polinomio(x);
				break;

			case 6:
				ayuda();
				break;

			default:
				if (opc == 7)
				{
					printf("\nSaliendo.");
					for (i = 1; i <= 11; i++)
					{
						delay(90);
						printf(".");
					}
				}
				break;
		}
	} while (opc != 7);
}
/*-------------------------------------------------------------------- Funcion Ayuda--------------------------------------------------------------------------------------*/
void ayuda()
{
	printf("\n\t\tGUIA PARA INGRESAR POLINOMIOS AL PROGRAMA\n\n");
	printf("\nEjemplo:\n");
	printf("\n\t\tPolinomio: 	2x^3  +x^2  -13x  +6\n\n");
	printf("\n\t\tTerminos: 	1er    2do   3er  4to");
      printf("\n\n1. El programa le pedira el Numero de Terminos del Polinomio: Terminos: 4\n");
	printf("2. El programa le pedira el Exponente del 1er Termino:   Exponente: 3\n");
	printf("3. El programa le pedira el Coeficiente del 1er Termino:   Coeficiente: 2\n");
	printf("4. El programa le pedira el Exponente del 2do Termino:   Exponente: 2\n");
	printf("6. El programa le pedira el Coeficiente del  2do Termino:   Coeficiente: 1\n");
	printf("6. El programa le pedira el Exponente del 3er Termino:   Exponente: 1\n");
	printf("7. El programa le pedira el Coeficiente del  3er Termino:   Coeficiente: -13\n");
	printf("8. El programa le pedira el Exponente del 4to Termino:   Exponente: 0\n");
	printf("9. El programa le pedira el Coeficiente del   4to Termino:   Coeficiente: 6\n");
	printf("\nIgual Para el Segundo Polinomio o Resto de las Operaciones");
	espera();
}
/*-------------------------------------------------------------------- fin de Funcion Ayuda-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------- Funcion dividir--------------------------------------------------------------------------------------*/
void dividir(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit_a, int limit_b, int limit)
{

	int a_aux, i, j, exp_cociente[SIZE_ONE], exp_uno_aux[SIZE_ONE];
	float b_aux, pol_cociente[SIZE_ONE], pol_residuo[SIZE_ONE], pol_uno_aux[SIZE_ONE];
	//Vectores inicializados a Ceros
	for (i = 0; i < SIZE_ONE; i++)
	{
		exp_cociente[i] = 0;
		pol_cociente[i] = 0;
		exp_uno_aux[i] = 0;
		pol_uno_aux[i] = 0;
	}

	//Duplicacion de Vector Uno
	for (i = 0; i <= limit_a; i++)
	{
		pol_uno_aux[i] = pol_uno[i];
		exp_uno_aux[i] = exp_uno[i];
	}

	for (i = limit_a; i >= 0; i--)
	{
		//Condicional para Dividir los terminos del primero polinomio entre el Primer termino del segundo
		if ((pol_uno_aux[i] != 0 && pol_dos[limit_b] != 0) && (exp_uno_aux[i] >= exp_dos[limit_b]))
		{
			exp_cociente[i] = (exp_uno_aux[i] - exp_dos[limit_b]);
			pol_cociente[i] = (pol_uno_aux[i] / pol_dos[limit_b]);
			//Ciclo y Condicional para multiplicar el cociente x el Polinomio Divisor
			for (j = limit_b; j >= 0; j--)
			{
				if (pol_dos[j] != 0)
				{
					a_aux = (exp_cociente[i] + exp_dos[j]);
					exp_uno_aux[a_aux] = a_aux;
					b_aux = ((pol_cociente[i] * pol_dos[j]) * -1);
					pol_uno_aux[a_aux] = pol_uno_aux[a_aux] + b_aux;
				}
			}
		}
	}

	//Impresion de Polinomios Originales y Resultado
	printf("\n\tPolinomio Uno: \n");
	printf("\t");
	for (i = limit; i >= 0; i--)
	{
		if (pol_uno[i] > 0)
		{
			printf("+%.1fx^%d ", pol_uno[i], exp_uno[i]);
		}
		else if (pol_uno[i] < 0)
		{
			printf("%.1fx^%d ", pol_uno[i], exp_uno[i]);

		}
	}
	printf("\n\n\tPolinomio Dos: \n");
	printf("\t");
	for (i = limit; i >= 0; i--)
	{
		if (pol_dos[i] > 0)
		{
			printf("+%.1fx^%d ", pol_dos[i], exp_dos[i]);
		}
		else if (pol_dos[i] < 0)
		{

			printf("%.1fx^%d ", pol_dos[i], exp_dos[i]);
		}
	}
	printf("\n\n\tPolinomio Resultado: \n");
	printf("\t");
	for (i = limit; i >= 0; i--)
	{
		if (pol_cociente[i] > 0)
		{
			printf("+%.1fx^%d ", pol_cociente[i], exp_cociente[i]);
		}
		else if (pol_cociente[i] < 0)
		{
			printf("%.1fx^%d ", pol_cociente[i], exp_cociente[i]);
		}
	}
	printf(" ; ");
	for (i = limit; i >= 0; i--)
	{
		if (pol_uno_aux[i] > 0)
		{
			printf("+%.1fx^%d ", pol_uno_aux[i], exp_uno_aux[i]);
		}
		else if (pol_uno_aux[i] < 0)
		{
			printf("%.1fx^%d ", pol_uno_aux[i], exp_uno_aux[i]);
		}
	}
	espera();
}

/*----------------------------------------------------------------------------------------------------------------------- Funcion dividir_factorizacion-----------------------------------------------------------------------------------------------------------------------------------*/
void dividir_factorizacion(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int exp_fac_uno[2], int factor_uno[2], int exp_fac_dos[2], int factor_dos[2], int limit_a, int limit_b)
{
	int a_aux, i, j, exp_cociente[SIZE_ONE], exp_uno_aux[SIZE_ONE], exp_cociente_dos[SIZE_ONE], exp_dos_aux[SIZE_ONE];
	float b_aux, pol_cociente[SIZE_ONE], pol_residuo[SIZE_ONE], pol_uno_aux[SIZE_ONE], pol_cociente_dos[SIZE_ONE], pol_residuo_dos[SIZE_ONE], pol_dos_aux[SIZE_ONE];
	//Vectores a inicializados a Ceros
	for (i = 0; i < SIZE_ONE; i++)
	{
		exp_cociente[i] = 0;
		pol_cociente[i] = 0;
		exp_uno_aux[i] = 0;
		pol_uno_aux[i] = 0;
		exp_cociente_dos[i] = 0;
		pol_cociente_dos[i] = 0;
		exp_dos_aux[i] = 0;
		pol_dos_aux[i] = 0;
	}
	//Duplicacion de Vectores
	for (i = 0; i <= limit_a; i++)
	{
		exp_uno_aux[i] = exp_uno[i];
		pol_uno_aux[i] = pol_uno[i];
	}
	for (i = 0; i <= limit_b; i++)
	{
		pol_dos_aux[i] = pol_dos[i];
		exp_dos_aux[i] = exp_dos[i];
	}

	for (i = limit_a; i >= 0; i--)
	{
		//Condicional para Dividir los terminos del primero polinomio entre el Primer termino del segundo
		if ((pol_uno_aux[i] != 0 && factor_uno[1] != 0) && (exp_uno_aux[i] >= exp_fac_uno[1]))
		{
			exp_cociente[i] = (exp_uno_aux[i] - exp_fac_uno[1]);
			pol_cociente[i] = (pol_uno_aux[i] / factor_uno[1]);
		}
		//Ciclo y Condicional para multiplicar el cociente x el Polinomio Divisor
		for (j = 1; j >= 0; j--)
		{
			a_aux = (exp_cociente[i] + exp_fac_uno[j]);
			exp_uno_aux[a_aux] = a_aux;
			b_aux = ((pol_cociente[i] * factor_uno[j]) * -1);
			pol_uno_aux[a_aux] = pol_uno_aux[a_aux] + b_aux;
		}
	}
	for (i = limit_b; i >= 0; i--)
	{
		//Condicional para Dividir los terminos del primero polinomio entre el Primer termino del segundo
		if ((pol_dos_aux[i] != 0 && factor_dos[1] != 0) && (exp_dos_aux[i] >= exp_fac_dos[1]))
		{
			exp_cociente_dos[i] = (exp_dos_aux[i] - exp_fac_dos[1]);
			pol_cociente_dos[i] = (pol_dos_aux[i] / factor_dos[1]);
		}
		//Ciclo y Condicional para multiplicar el cociente x el Polinomio Divisor
		for (j = 1; j >= 0; j--)
		{
			a_aux = (exp_cociente_dos[i] + exp_fac_dos[j]);
			exp_dos_aux[a_aux] = a_aux;
			b_aux = ((pol_cociente_dos[i] * factor_dos[j]) * -1);
			pol_dos_aux[a_aux] = pol_dos_aux[a_aux] + b_aux;
		}
	}
	//Impresion de Polinomios
	printf("\n\tPolinomio Uno: \n");
	printf("\t");
	for (i = limit_a; i >= 0; i--)
	{
		if (pol_uno[i] > 0)
		{
			printf("+%.1fx^%d ", pol_uno[i], exp_uno[i]);
		}
		else if (pol_uno[i] < 0)
		{
			printf("%.1fx^%d ", pol_uno[i], exp_uno[i]);

		}
	}
	printf("\n\n\tPolinomio Dos: \n");
	printf("\t");
	for (i = limit_b; i >= 0; i--)
	{
		if (pol_dos[i] > 0)
		{
			printf("+%.1fx^%d ", pol_dos[i], exp_dos[i]);
		}
		else if (pol_dos[i] < 0)
		{

			printf("%.1fx^%d ", pol_dos[i], exp_dos[i]);
		}
	}
	printf("\n\n\tPolinomio Uno Factorizado: \n");
	printf("\t(");
	for (i = limit_a; i >= 0; i--)
	{
		if (pol_cociente[i] > 0)
		{
			printf("+%.1fx^%d ", pol_cociente[i], exp_cociente[i]);
		}
		else if (pol_cociente[i] < 0)
		{
			printf("%.1fx^%d ", pol_cociente[i], exp_cociente[i]);
		}
	}
	printf(")");
	printf("(");
	for (i = 1; i >= 0; i--)
	{
		if (factor_uno[i] > 0)
		{
			printf("+%dx^%d ", factor_uno[i], exp_fac_uno[i]);
		}
		else if (factor_uno[i] < 0)
		{
			printf("%dx^%d ", factor_uno[i], exp_fac_uno[i]);
		}
	}
	printf(")");

	printf("\n\n\tPolinomio Dos Factorizado: \n");
	printf("\t(");
	for (i = limit_b; i >= 0; i--)
	{
		if (pol_cociente_dos[i] > 0)
		{
			printf("+%.1fx^%d ", pol_cociente_dos[i], exp_cociente_dos[i]);
		}
		else if (pol_cociente_dos[i] < 0)
		{
			printf("%.1fx^%d ", pol_cociente_dos[i], exp_cociente_dos[i]);
		}
	}
	printf(")");
	printf("(");
	for (i = 1; i >= 0; i--)
	{
		if (factor_dos[i] > 0)
		{
			printf("+%dx^%d ", factor_dos[i], exp_fac_dos[i]);
		}
		else if (factor_dos[i] < 0)
		{
			printf("%dx^%d ", factor_dos[i], exp_fac_dos[i]);
		}
	}
	printf(")");
	espera();

}
/*---------------------------------------fin de Funcion dividir_factorizacion----------------------------------------------------------------------------------------------------------------*/
//imprime lineas de encabezado
void encabezado()
{
	int j;
	for (j = 1; j <= 80; j++)
	{
		printf("=");

	}
}
// Espera una tecla para continuar
void espera()
{
	printf("\n\nPresione cualquier tecla para continuar. ;-)");
	while (!kbhit());
}
/*-------------------------------------------------------------------Funcion factorizar---------------------------------------------------------------------------------------------------------*/
void factorizar(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit_a, int limit_b)
{
	int i, j, k, l, m, n, o, p, base, pot;
	int p_multiplos_pol_uno[SIZE_ONE], q_multiplos_pol_uno[SIZE_ONE], p_multiplos_pol_dos[SIZE_ONE], q_multiplos_pol_dos[SIZE_ONE];
	int div_aux_uno, div_aux_dos, pol_uno_divisor, pol_uno_dividendo, pol_dos_divisor, pol_dos_dividendo;
	double si_es_cero, pq_multiplos_pol_uno[SIZE_ONE], pq_multiplos_pol_dos[SIZE_ONE], pol_uno_dividendo_aux[SIZE_ONE], pol_dos_dividendo_aux[SIZE_ONE];

	//polinomios factores
	int exp_fac_uno[2] = {0, 1};
	int factor_uno[2] = {0, 1};
	int exp_fac_dos[2] = {0, 1};
	int factor_dos[2] = {0, 1};

	//Asignacion de Dividendo y Divisor de los dos polinomios
	pol_uno_dividendo = abs(pol_uno[limit_a]);
	pol_uno_divisor = abs(pol_uno[0]);
	pol_dos_dividendo = abs(pol_dos[limit_b]);
	pol_dos_divisor = abs(pol_dos[0]);

	//Inicializacion de Vectores de Multiplos y Dividendos
	for (i = 0; i < SIZE_ONE; i++)
	{
		p_multiplos_pol_uno[i] = 0;
		q_multiplos_pol_uno[i] = 0;
		pq_multiplos_pol_uno[i] = 0;
		p_multiplos_pol_dos[i] = 0;
		q_multiplos_pol_dos[i] = 0;
		pq_multiplos_pol_dos[i] = 0;
		pol_uno_dividendo_aux[i] = 0;
		pol_dos_dividendo_aux[i] = 0;
	}
	//Duplicacion del Polinomio Dividendo
	for (i = 0; i <= limit_a; i++)
	{
		pol_uno_dividendo_aux[i] = pol_uno[i];
	}
	for (i = 0; i <= limit_b; i++)
	{
		pol_dos_dividendo_aux[i] = pol_dos[i];
	}
	//variables auxiliares para limite de division de multiplos
	k = 0;
	l = 0;
	m = 0;
	n = 0;
	o = 0;
	p = 0;
	//Multiplos de p y q para polinomio uno
	for (i = 1; i <= pol_uno_divisor; i++)
	{
		if (pol_uno_divisor % i == 0)
		{
			p_multiplos_pol_uno[k] = i;
			k++;
		}
	}
	for (j = 1; j <= pol_uno_dividendo; j++)
	{
		if (pol_uno_dividendo % j == 0)
		{
			q_multiplos_pol_uno[l] = j;
			l++;
		}
	}
	//Multiplos de p y q para polinomio dos
	for (i = 1; i <= pol_dos_divisor; i++)
	{
		if (pol_dos_divisor % i == 0)
		{
			p_multiplos_pol_dos[m] = i;
			m++;
		}
	}
	for (j = 1; j <= pol_dos_dividendo; j++)
	{
		if (pol_dos_dividendo % j == 0)
		{
			q_multiplos_pol_dos[n] = j;
			n++;
		}
	}

	//division de factores p/q para Polinomio uno
	for (i = 0; i < l; i++)
	{
		for (j = 0; j < k; j++)
		{
			div_aux_uno = p_multiplos_pol_uno[j] / q_multiplos_pol_uno[i];
			pq_multiplos_pol_uno[div_aux_uno] = div_aux_uno;
			if (div_aux_uno > o)
			{
				o = div_aux_uno;
			}
		}
	}
	//division de factores p/q para polinomio dos
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			div_aux_dos = p_multiplos_pol_dos[j] / q_multiplos_pol_dos[i];
			pq_multiplos_pol_dos[div_aux_dos] = div_aux_dos;
			if (div_aux_dos > p)
			{
				p = div_aux_dos;
			}
		}
	}
	//Reemplazo de Ceros en Polinomio uno
	for (i = 0; i <= o; i++)
	{
		if ((pq_multiplos_pol_uno[i] != 0) && (factor_uno[0] == 0))
		{
			si_es_cero = poly(pq_multiplos_pol_uno[i], limit_a, pol_uno_dividendo_aux);
			if (si_es_cero == 0)
			{
				factor_uno[0] = pq_multiplos_pol_uno[i] * -1;
			}
			else
			{
				si_es_cero = poly((pq_multiplos_pol_uno[i] * -1), limit_a, pol_uno_dividendo_aux);
				if (si_es_cero == 0)
					factor_uno[0] = pq_multiplos_pol_uno[i];
			}
		}
	}
	//Reemplazo de Ceros en Polinomio dos
	for (i = div_aux_dos; i <= p; i++)
	{
		if ((pq_multiplos_pol_dos[i] != 0) && (factor_dos[0] == 0))
		{
			si_es_cero = poly(pq_multiplos_pol_dos[i], limit_b, pol_dos_dividendo_aux);
			if (si_es_cero == 0)
			{
				factor_dos[0] = pq_multiplos_pol_dos[i] * -1;
			}
			else
			{
				si_es_cero = poly((pq_multiplos_pol_dos[i] * -1), limit_b, pol_dos_dividendo_aux);
				if (si_es_cero == 0)
					factor_dos[0] = pq_multiplos_pol_dos[i];
			}
		}
	}
	dividir_factorizacion(exp_uno, pol_uno, exp_dos, pol_dos, exp_fac_uno, factor_uno, exp_fac_dos, factor_dos, limit_a, limit_b);
}
/*--------------------------------------------------------------fin de Funcion factorizar-------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------Funcion imprimir_Polinomios-----------------------------------------------------------------------------------------------------------------------------*/
void imprimir_polinomios(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int exp_tot[SIZE_ONE], float pol_tot[SIZE_ONE], int limit)
{

	int i;
	printf("\n\tPolinomio Uno: \n");
	printf("\t");
	for (i = limit; i >= 0; i--)
	{
		if (pol_uno[i] > 0)
		{
			printf("+%.1fx^%d ", pol_uno[i], exp_uno[i]);
		}
		else if (pol_uno[i] < 0)
		{
			printf("%.1fx^%d ", pol_uno[i], exp_uno[i]);

		}
	}
	printf("\n\n\tPolinomio Dos: \n");
	printf("\t");
	for (i = limit; i >= 0; i--)
	{
		if (pol_dos[i] > 0)
		{
			printf("+%.1fx^%d ", pol_dos[i], exp_dos[i]);
		}
		else if (pol_dos[i] < 0)
		{
			printf("%.1fx^%d ", pol_dos[i], exp_dos[i]);
		}
	}
	printf("\n\n\tPolinomio Resultado: \n");
	printf("\t");
	for (i = limit; i >= 0; i--)
	{
		if (pol_tot[i] > 0)
		{
			printf("+%.1fx^%d ", pol_tot[i], exp_tot[i]);
		}
		else if (pol_tot[i] < 0)
		{
			printf("%.1fx^%d ", pol_tot[i], exp_tot[i]);
		}
	}
	espera();
}
/*------------------------------------Fin de Funcion imprimir_Polinomios--------------------------------------------------------------------------*/

/*------------------------------------Funcion Multiplica  para los Polinomios---------------------------------------------------------------------*/
//Multiplica los Polinomios
void multiplica(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit)
{

	int i, j, k;
	int exp_tot[SIZE_TWO];
	float pol_tot[SIZE_TWO];

	//inicializa polinomio y exponente total a ceros.
	for (i = 0; i < SIZE_TWO; i++)
	{
		pol_tot[i] = 0;
		exp_tot[i] = 0;
	}
	//Variable Auxiliar
	k = 0;
	for (i = 0; i <= limit; i++)
	{
		for (j = 0; j <= limit; j++)
		{
			if ((exp_uno[i] != 0 && exp_dos[j] != 0) || ((exp_uno[i] == 0 && pol_uno[i] != 0) || (exp_dos[j] == 0 && pol_dos[j] != 0)))
			{
				k = (exp_uno[i] + exp_dos[j]);
				exp_tot[k] = k;
				pol_tot[k] = pol_tot[k] + (pol_uno[i] * pol_dos[j]);
			}
		}
	}
	//se duplica el valor del limite x multiplicacion
	limit = limit * limit;
	//llamado a funcion
	imprimir_polinomios(exp_uno, pol_uno, exp_dos, pol_dos, exp_tot, pol_tot, limit);
}

/*----------------------------------------------------Fin de Funcion Multiplica  para los Polinomios---------------------------------------------------*/

/*---------------------------------------------------------Funcion pedir_ Polinomios--------------------------------------------------------------------*/

//Pide los datos de los Polinomios - Evalua el valor de seleccion del usuario
void pedir_polinomio(int x)
{

	int sel, limit_a, limit, limit_b, a_aux;
	int i, n, m, exp_uno[SIZE_ONE], exp_dos[SIZE_ONE];
	float b_aux, pol_uno[SIZE_ONE], pol_dos[SIZE_ONE];

	sel = x;
	//inicia Polinomios en ceros
	for (i = 0; i < SIZE_ONE; i++)
	{

		exp_uno[i] = 0;
		exp_dos[i] = 0;
		pol_uno[i] = 0;
		pol_dos[i] = 0;
	}
	//Solicitud de Datos Exponentes y  Coeficientes
	printf("\nPrimer Polinomio\n");

	printf("Ingrese el Numero de Terminos: ");
	scanf("%d", &n);
	fflush(stdin);
	printf("Ingrese el Exponente del 1er termino: ");
	scanf("%d", &limit_a);
	fflush(stdin);
	exp_uno[limit_a] = limit_a;
	printf("Ingrese el Coeficiente del  1er termino: ");
	scanf("%f", &b_aux);
	fflush(stdin);
	pol_uno[limit_a] = b_aux;

	for (i = 1; i < n; i++)
	{

		printf("Ingrese el Exponente del %døo termino: ", i + 1);
		scanf("%d", &a_aux);
		fflush(stdin);
		exp_uno[a_aux] = a_aux;
		printf("Ingrese el Coeficiente del %døo termino: ", i + 1);
		scanf("%f", &b_aux);
		fflush(stdin);
		pol_uno[a_aux] = b_aux;

	}
	printf("\nSegundo Polinomio\n");

	printf("Ingrese el Numero de Terminos: ");
	scanf("%d", &m);
	fflush(stdin);
	printf("Ingrese el Exponente del 1er termino: ");
	scanf("%d", &limit_b);
	fflush(stdin);
	exp_dos[limit_b] = limit_b;
	printf("Ingrese el Coeficiente del  1er termino: ");
	scanf("%f", &b_aux);
	fflush(stdin);
	pol_dos[limit_b] = b_aux;

	for (i = 1; i < m; i++)
	{

		printf("Ingrese el Exponente del %døo termino: ", i + 1);
		scanf("%d", &a_aux);
		fflush(stdin);
		exp_dos[a_aux] = a_aux;
		printf("Ingrese el Coeficiente del %døo termino: ", i + 1);
		scanf("%f", &b_aux);

		fflush(stdin);
		pol_dos[a_aux] = b_aux;

	}
	//Condicional para asignar un limite a los ciclos de la funciones
	if (limit_a > limit_b)
	{
		limit = limit_a;
	}
	else
	{
		limit = limit_b;
	}
	//Llama la Funcion segun lo requerido por el usuario
	if (sel == 1)
	{

		printf("\n\tSuma:\n");
		//Llamado a funcion Suma
		suma(exp_uno, pol_uno, exp_dos, pol_dos, limit);

	}
	else if (sel == 2)
	{

		printf("\n\n\tResta:\n");
		//llamado a funcion Resta
		resta(exp_uno, pol_uno, exp_dos, pol_dos, limit);

	}
	else if (sel == 3)
	{

		printf("\n\n\tMultiplicacion\n");
		//llamado a funcion Multiplica
		multiplica(exp_uno, pol_uno, exp_dos, pol_dos, limit);
	}
	else if (sel == 4)
	{
		//llamado a funcion Division
		printf("\n\nDivision\n");
		dividir(exp_uno, pol_uno, exp_dos, pol_dos, limit_a, limit_b, limit);
	}
	else if (sel == 5)
	{
		//llamado a funcion factorizacion
		printf("\n\nFactorizacion\n");
		factorizar(exp_uno, pol_uno, exp_dos, pol_dos, limit_a, limit_b);

	}
}

/*------------------------------------Fin de Funcion pedir_polinomio--------------------------------------------------------------------------*/

/*------------------------------------Funcion Resta para los Polinomios----------------------------------------------------------------------*/

//Resta dos Polinomios
void resta(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit)
{

	int i, exp_tot[SIZE_ONE];

	//Cambia de Signo al Polinomio Sustraendo.
	for (i = 0; i <= limit; i++)
	{
		pol_dos[i] = (pol_dos[i] * (-1));
	}
	//Llamado a funcion Suma
	suma(exp_uno, pol_uno, exp_dos, pol_dos, limit);
}
/*------------------------------------Fin de Funcion Resta--------------------------------------------------------------------------------------*/

/*------------------------------------Funcion Suma para los Polinomios------------------------------------------------------------------------*/
//Suma los polinomios
void suma(int exp_uno[SIZE_ONE], float pol_uno[SIZE_ONE], int exp_dos[SIZE_ONE], float pol_dos[SIZE_ONE], int limit)
{

	int i, exp_tot[SIZE_ONE];
	float pol_tot[SIZE_ONE];

	//inicializa polinomios totales a ceros.
	for (i = 0; i < SIZE_ONE; i++)
	{
		pol_tot[i] = 0;
		exp_tot[i] = 0;
	}
	//suma sus coeficientes y exponentes segun su Exponente (indice)
	for (i = 0; i <= limit; i++)
	{

		pol_tot[i] = (pol_uno[i] + pol_dos[i]);
		if (exp_uno[i] == 0)
		{
			exp_tot[i] = exp_dos[i];
		}
		else if (exp_dos[i] == 0)
		{
			exp_tot[i] = exp_uno[i];
		}
		else if ((exp_uno[i] != 0) && (exp_dos[i] != 0))
		{
			exp_tot[i] = (exp_uno[i] + exp_dos[i]) / 2;
		}
	}
	//Llamado a Funcion imprimir_polinomios
	imprimir_polinomios(exp_uno, pol_uno, exp_dos, pol_dos, exp_tot, pol_tot, limit);
}
/*------------------------------------Fin de Funcion Suma------------------------------------------*/
