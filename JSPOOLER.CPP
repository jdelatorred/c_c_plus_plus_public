/*JSpooler By Jorge de la Torre Davalos F.U.S.M. 2005
ADMINISTRADOR DE IMPRESION UTILIZANDO COLAS DINAMICAS
PROF: ING ERLINGTON SALCEDO BENAVIDES
*/

//LIBRERIAS DE CABECERA
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <graphics.h>


//Constantes para Prioridad de Atencion de Colas
#define PRIOR1 3
#define PRIOR2 2
#define PRIOR3 1


//ESTRUCTURA PRINCIPAL DE NODOS
struct JOB
{
	int Code;
	char Nombre[20];
	char Contenido[100];
	int Size;
	int Priority;
	struct time t;
	struct JOB *SigPtr;
};
typedef JOB *Job; //Estructura para declarar Nodos
typedef JOB *COLAS; //Estructura para declarar punteros a Colas

//Estructura para el manejo de Clave de Administrador
struct Password
{
	int Pass;
};

//FUNCIONES
void Atender_Cola(COLAS *CabPtr, COLAS *ColaPtr);
void Borrar_Job(COLAS *lista, int n);
void Esperar();
int Generar_Size();
void Imprimir_Cola(COLAS *CabColaPrincipal, int n);
void Inicio_Grafico();
void Log_Impresion();
int Leer_Clave(char *pass);
void Manejo_Administrador();
void Menu();
void Nueva_Clave();
int Nuevo_Job(COLAS *CabColaPtr1, COLAS *ColaPtr1, COLAS *CabColaPtr2, COLAS *ColaPtr2, COLAS *CabColaPtr3, COLAS *ColaPtr3, int n);
void Pantalla_Administrador();
void Pasar_a_Principal(COLAS *CabColaPrincipal, COLAS *ColaPrincipal, COLAS *CabColaPtr, COLAS *ColaPtr);
void Procesar_Jobs(COLAS *CabColaPrincipal, COLAS *ColaPrincipal);
int maxX, maxY;

//Funcion principal
void main(void)
{
	Inicio_Grafico();

}
/*Carga el Modo grafico para las funciones de Libreria*/
void Inicio_Grafico()
{
	int gdriver = DETECT, gmode, errorcode;

	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("ERROR : %s Verifique la Ruta BGI", grapherrormsg(errorcode));
		getch();
		exit(1);
	}
	//Deteccion de Maximos Graficos de X y Y
	maxX = getmaxx();
	maxY = getmaxy();

	Menu();

	closegraph();
}
/*Funcion Menu con las opciones de usuario*/
void Menu()
{
	COLAS CabColaPrincipal = NULL, ColaPrincipal = NULL, CabColaPtr1 = NULL, ColaPtr1 = NULL, CabColaPtr2 = NULL, ColaPtr2 = NULL, CabColaPtr3 = NULL, ColaPtr3 = NULL;
	int St = 0, i, j, opc, NCode = 1;
	char *sel=NULL;
	do
	{

		cleardevice();
		setbkcolor(BLUE);
		textcolor(3);
		rectangle(2, 2, maxX - 2, maxY - 2);
		settextstyle(3, 0, 5);
		outtextxy(210, 15, "MyJobSPooler");
		settextstyle(2, 0, 4);
		outtextxy(450, 460, "By Jorge de la Torre Davalos");
		gotoxy(10, 8);
		printf("1.Ingresar Job al Spooler.");
		gotoxy(10, 10);
		printf("2.Procesar el Spooler.");
		gotoxy(10, 12);
		printf("3.Ver Estado del Spooler.");
		gotoxy(10, 14);
		printf("4.Administrador.");
		gotoxy(10, 16);
		printf("5.Salir.");
		gotoxy(10, 18);
		printf("Su Opcion: [ ]\b\b");
		fflush(stdin);
		gets(sel);
		fflush(stdin);
		opc = atoi(sel);

		//Validacion de las opciones de usuario
		switch (opc)
		{
			case 1:
				St = Nuevo_Job(&CabColaPtr1, &ColaPtr1, &CabColaPtr2, &ColaPtr2, &CabColaPtr3, &ColaPtr3, NCode);
				if (St == 1)
				{
					NCode++;
				}
				break;

			case 2:
				for (i = 0; i < NCode; i++)
				{
					j = 0;
					while (CabColaPtr3 && j < PRIOR1)
					{
						Pasar_a_Principal(&CabColaPrincipal, &ColaPrincipal, &CabColaPtr3, &ColaPtr3);
						i++;
						j++;
					}
					j = 0;
					while (CabColaPtr2 && j < PRIOR2)
					{
						Pasar_a_Principal(&CabColaPrincipal, &ColaPrincipal, &CabColaPtr2, &ColaPtr2);
						i++;
						j++;
					}
					j = 0;
					while (CabColaPtr1 && j < PRIOR3)
					{
						Pasar_a_Principal(&CabColaPrincipal, &ColaPrincipal, &CabColaPtr1, &ColaPtr1);
						i++;
						j++;
					}
				}

				Imprimir_Cola(&CabColaPrincipal, 2);
				Procesar_Jobs(&CabColaPrincipal, &ColaPrincipal);
				break;

			case 3:
				Imprimir_Cola(&CabColaPrincipal, 1);
				Procesar_Jobs(&CabColaPrincipal, &ColaPrincipal);
				Imprimir_Cola(&CabColaPrincipal, 2);
				break;

			case 4:
				Manejo_Administrador();
				break;


			default:

				break;
		}
	} while (opc != 5);
}
/*Insercion de un nuevo nodo en la Pila*/
int Nuevo_Job(COLAS *CabColaPtr1, COLAS *ColaPtr1, COLAS *CabColaPtr2, COLAS *ColaPtr2, COLAS *CabColaPtr3, COLAS *ColaPtr3, int n)
{
	int s = 0, x = 0;
	FILE *in = NULL;
	COLAS JobTmp;
	char path[15] = "a:\\";

	JobTmp = (Job)malloc(sizeof(JOB));
	JobTmp->SigPtr = NULL;
	JobTmp->Code = n;
	fflush(stdin);
	cleardevice();
	setbkcolor(BLUE);
	textcolor(4);
	rectangle(10, 10, maxX - 10, maxY - 10);
	gotoxy(28, 5);
	printf("[ DATOS DEL JOB ]");
	gotoxy(18, 10);
	fflush(stdin);
	printf("Nombre del Archivo con extension: ");
	gets(JobTmp->Nombre);
	fflush(stdin);
	gotoxy(18, 12);
	printf("Prioridad del Job 1<->3: ");
	scanf("%d", &JobTmp->Priority);
	fflush(stdin);
	gotoxy(18, 14);
	strcat(path, JobTmp->Nombre);
	printf("Coloque el Disco en la Unidad. Presione Cualquier Tecla.");
	getch();

	if ((in = fopen(path, "r")) == NULL)
	{
		gotoxy(18, 16);
		printf("Error Leyendo El Disco. ");
		delay(1000);
		free(JobTmp);
	}
	else
	{
		fscanf(in, "%s", &JobTmp->Contenido);
		fclose(in);

		while (x++ < 45)
		{
			gotoxy(17 + x, 17);
			printf("€");
			delay(40);
		}
		s = 1;
		JobTmp->Size = Generar_Size();
		gettime(&JobTmp->t);

		if (JobTmp->Priority == 1)
		{
			if (*ColaPtr1)
				(*ColaPtr1)->SigPtr = JobTmp;

			*ColaPtr1 = JobTmp;

			if (!*CabColaPtr1)
				*CabColaPtr1 = JobTmp;

		}
		else if (JobTmp->Priority == 2)
		{
			if (*ColaPtr2)
				(*ColaPtr2)->SigPtr = JobTmp;

			*ColaPtr2 = JobTmp;

			if (!*CabColaPtr2)
				*CabColaPtr2 = JobTmp;

		}
		else if (JobTmp->Priority == 3)
		{
			if (*ColaPtr3)
				(*ColaPtr3)->SigPtr = JobTmp;

			*ColaPtr3 = JobTmp;

			if (!*CabColaPtr3)
				*CabColaPtr3 = JobTmp;
		}
	}

	return s;
}

/*Pasa los Jobs(Nodos) de las 3 diferentes listas a la Principal*/
void Pasar_a_Principal(COLAS *CabColaPrincipal, COLAS *ColaPrincipal, COLAS *CabColaPtr, COLAS *ColaPtr)
{
	COLAS BkpPtr = NULL;

	BkpPtr = *CabColaPtr;

	*CabColaPtr = BkpPtr->SigPtr;

	if (!*CabColaPtr)
	{
		*ColaPtr = NULL;
	}

	BkpPtr->SigPtr = NULL;

	if (*ColaPrincipal)
		(*ColaPrincipal)->SigPtr = BkpPtr;

	*ColaPrincipal = BkpPtr;

	if (!*CabColaPrincipal)
		*CabColaPrincipal = BkpPtr;
}
/*Muestra una animacion de Impresion*/
void Impresion_Animado()
{
	int a = 0;
	do
	{
		gotoxy(64,3);
		printf("Ø€");
		delay(100);
		printf("\b\b €");
		delay(100);
		printf("\b€Ø");
		delay(50);
		printf("\b \b\b\b");
		a++;
	} while (a < 3);
}
/*Muestra el estado de la lista principal y sus opciones*/
void Imprimir_Cola(COLAS *CabColaPrincipal, int n)
{
	COLAS CabPtr = NULL, BorraPtr = NULL;
        char Datos[50];

	CabPtr = *CabColaPrincipal;
	BorraPtr = *CabColaPrincipal;
	int ID, y = 1, op = 0;
	cleardevice();
	settextstyle(2, 0, 5);
	outtextxy(20, 7, "ID");
	outtextxy(100, 7, "NOMBRE DEL JOB");
	outtextxy(250, 7, "TAMANO EN KB");
	outtextxy(390, 7, "PRIORIDAD");
	outtextxy(500, 7, "ESTADO");
	rectangle(1, 1, maxX, maxY);
	rectangle(2, 2, maxX - 2, maxY - 2);

	while (CabPtr)
	{
		itoa((CabPtr)->Code, Datos, 10);
		outtextxy(20, 22*y, Datos);
		outtextxy(115, 22*y,(CabPtr)->Nombre);
		itoa((CabPtr)->Size, Datos, 10);
		outtextxy(270, 22*y, Datos);
		itoa((CabPtr)->Priority, Datos, 10);
		outtextxy(412, 22*y, Datos);
		Impresion_Animado();
		CabPtr = (CabPtr)->SigPtr;
		y++;

	}
	if (n == 2)
	{
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		bar3d(50, maxY - 100, maxX - 50, maxY - 40, 0, 0);
		textcolor(3);
		settextstyle(3, 0, 1);
		outtextxy(240, maxY - 99, "Opciones del Spooler");
		settextstyle(2, 0, 5);
		outtextxy(70, maxY - 70, "1.Detalles del Job.");
		outtextxy(230, maxY - 70, "2.Eliminar Job.");
		outtextxy(350, maxY - 70, "3.Regresar Al Menu Principal.");
		gotoxy(38, 29);
		printf("[  ]\b\b");

		if (BorraPtr)
		{
			while (!kbhit())
			{
				Impresion_Animado();
				gotoxy(38, 29);
				printf("[  ]\b\b");
			}
		}

		scanf("%d", &op);
		if (op == 1 || op == 2)
		{
			if (BorraPtr)
			{
				gotoxy(25, 23);
				printf("ID del Job: ");
				scanf("%d", &ID);
				if (op == 1)
				{
					while (BorraPtr && (BorraPtr->Code != ID))
					{
						BorraPtr = BorraPtr->SigPtr;
					}
					if (BorraPtr->Code == ID)
					{
						cleardevice();
						gotoxy(2, 2);
						printf("ID: %d ", BorraPtr->Code);
						gotoxy(2, 3);
						printf("Nombre: %s ", BorraPtr->Nombre);
						gotoxy(2, 3);
						printf("Contenido: %s ", BorraPtr->Contenido);
						gotoxy(2, 4);
						printf("Tamano: %dKb ", BorraPtr->Size);
						gotoxy(2, 5);
						printf("Priodidad: %d ", BorraPtr->Priority);
						gotoxy(2, 6);
						printf("Hora de Envio: %d:%d:%d ", BorraPtr->t.ti_hour, BorraPtr->t.ti_min, BorraPtr->t.ti_sec);
						Esperar();
					}

				}
				else if (op == 2)
				{
					Borrar_Job(&BorraPtr, ID);
				}

			}
			else
			{
				gotoxy(15, 20);
				printf("No hay Jobs en la Cola.");

			}
		}
	}
	else
	{
		delay(1500);
	}

}


/*Genera un Numero de Tamano aleatorio para el Job*/
int Generar_Size()
{
	int Numero;
	srand(time(NULL));
	Numero = (rand() % 9000) + 1000;
	return (Numero);
}

/*Elimina un Job (Nodo) de la Lista Principal*/
void Borrar_Job(COLAS *lista, int n)
{
	COLAS anterior, nodo;

	nodo = *lista;
	anterior = NULL;

	while (nodo && nodo->Code < n)
	{
		anterior = nodo;
		nodo = nodo->SigPtr;
	}
	if (!nodo || nodo->Code != n)
		return;

	else
	{
		if (!anterior)
		{
			*lista = nodo->SigPtr;
		}
		else
		{
			anterior->SigPtr = nodo->SigPtr;
			free(nodo);
		}
	}
}

/*Establece una Pausa en la ejecucion del programa*/
void Esperar()
{

	gotoxy(20, 29);
	printf("Presione Cualquier tecla para continuar");
	while (!kbhit());
}

/*Procesa la Cola de Impresion segun su tamano y el tiempo de envio al Spooler*/
void Procesar_Jobs(COLAS *CabColaPrincipal, COLAS *ColaPrincipal)
{
	struct time T;
	COLAS BkpPtr = NULL;
	int st = 0;
	FILE *AccesPtr;
	char Hora[10], Fecha[10], nombre[20];
	int code, size, priority;

	_strdate(Fecha);
	_strtime(Hora);

	BkpPtr = *CabColaPrincipal;

	gettime(&T);

	if (BkpPtr)
	{
		if (BkpPtr->Size <= 3000)
		{
			if ((T.ti_hour - BkpPtr->t.ti_hour >= 0) && (T.ti_min - BkpPtr->t.ti_min >= 1))
			{
				*CabColaPrincipal = BkpPtr->SigPtr;
				code = BkpPtr->Code;
				strcpy(nombre, BkpPtr->Nombre);
				size = BkpPtr->Size;
				priority = BkpPtr->Priority;
				free(BkpPtr);
				st = 1;
				if (!*CabColaPrincipal)
				{
					*ColaPrincipal = NULL;
				}
			}
		}

		if ((BkpPtr->Size > 3000) && (BkpPtr->Size <= 6000))
		{
			if ((T.ti_hour - BkpPtr->t.ti_hour >= 0) && (T.ti_min - BkpPtr->t.ti_min >= 1))
			{
				*CabColaPrincipal = BkpPtr->SigPtr;
				code = BkpPtr->Code;
				strcpy(nombre, BkpPtr->Nombre);
				size = BkpPtr->Size;
				priority = BkpPtr->Priority;
				free(BkpPtr);
				st = 1;
				if (!*CabColaPrincipal)
				{
					*ColaPrincipal = NULL;
				}
			}
		}

		if ((BkpPtr->Size > 6000))
		{
			if ((T.ti_hour - BkpPtr->t.ti_hour >= 0) && (T.ti_min - BkpPtr->t.ti_min >= 3))
			{
				*CabColaPrincipal = BkpPtr->SigPtr;
				code = BkpPtr->Code;
				strcpy(nombre, BkpPtr->Nombre);
				size = BkpPtr->Size;
				priority = BkpPtr->Priority;
				free(BkpPtr);
				st = 1;
				if (!*CabColaPrincipal)
				{
					*ColaPrincipal = NULL;
				}
			}
		}
	}

	if (st == 1)
	{
		if ((AccesPtr = fopen("c:\\temp\\JSpooler\\Logdeuso.dat", "a+")) == NULL)
		{
			printf("Error AADA");
		}
		else
		{
			fprintf(AccesPtr, "%d %s %d %d %s %s\n", code, nombre, size, priority, Fecha, Hora);

		}
		fclose(AccesPtr);
	}

}
/*Gestiona las opciones del administrador del Spooler*/
void Manejo_Administrador()
{
	//Gestiona todas las opciones del administrador
	int i = 0, p, key_1 = 1, key_2 = 1;
	char pass[25] = "", user[] = "DelatorreJ";

	rectangle(100, 350, 500, 400);
	gotoxy(33, 23);
	printf("PASSWORD");
	gotoxy(25, 25);
	printf("[                       ]");
	gotoxy(29, 25);
	printf(" ");

	while (p != 13)
	{
		p = getch();
		fflush(stdin);
		if ((p != 13) && (i < 25))
		{

			if (p != 8)
			{
				pass[i] = p;
				printf("*");
				i++;
			}
			else if ((p == 8) && (i > 0))
			{
				pass[i] = '\0';
				printf("\b \b");
				i--;
			}
		}
	}

	key_1 = strcmp(user, pass);
	key_2 = Leer_Clave(pass);

	if ((key_1 == 0) || (key_2 == 0))
	{
		Pantalla_Administrador();
	}
	else
	{
		gotoxy(25, 27);
		printf("Clave Erronea Intente otra vez");
		while (!kbhit());

	}

}

/*Compara la clave de acceso de administrador con la Almacenada en archivo*/
int Leer_Clave(char *pass)
{
	FILE *KeyPtr = NULL;
	struct Password P;
	int i = 0, ValClave[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Usuario[25] = "";

	if ((KeyPtr = fopen("c:\\temp\\JSpooler\\AdminKey.dat", "r")) == NULL)
	{
		printf("Error PASS0AFEO");
		while (!kbhit())
			;

	}
	else
	{
		rewind(KeyPtr);
		while (P.Pass != 0)
		{
			fread(&P, sizeof(struct Password), 1, KeyPtr);
			if (P.Pass != 0)
			{
				ValClave[i] = P.Pass / 2;
				Usuario[i] = ValClave[i];
			}
			i++;
		}
		fclose(KeyPtr);

	}
	i = strcmp(pass, Usuario);
	return i;

}
/*Lee el archivo con el registro de Jobs*/
void Log_Impresion()
{
	/*Muestra los accesos a la Aplicacion*/
	FILE *LogImp = NULL;
	char Nombre[20], Fecha[10], Hora[10];
	int x = 7, i = 1, j = 1, ID, Tamano, Prioridad;

	cleardevice();
	if ((LogImp = fopen("c:\\temp\\JSpooler\\LogdeUso.dat", "r")) == NULL)
	{
		printf("No existe Archivo de Log.");
	}
	else
	{
		gotoxy(4, 4);
		printf("%s\t%s\t\t%s\t\t\b\b%s\t %s\t\t%s\n\n", "ID", "ARCHIVO", "TAMANO", "PRIORD", "FECHA", "HORA");
		fscanf(LogImp, "%d %s %d %d %s %s", &ID, Nombre, Tamano, &Prioridad, Fecha, Hora);
		while (!feof(LogImp))
		{
			gotoxy(4, x);
			printf("%d\t%s\t%dKb\t\t%d\t%s\t%s\n", ID, Nombre, Tamano, Prioridad, Fecha, Hora);
			fscanf(LogImp, "%d %s %d %d %s %s", &ID, Nombre, &Tamano, &Prioridad, Fecha, Hora);
			delay(100);
			i++;
			x++;
			if (i % 20 == 0)
			{
				gotoxy(4, x + 1);
				printf("Pagina: %d", j);
				gotoxy(25, 35);
				printf("Presione Cualquier tecla ");
				getch();
				j++;
			}

		}
		fclose(LogImp);
	}
	Esperar();
}
/*Cambia la clave del administrador */
void Nueva_Clave()
{

	FILE *KeyPointer;
	struct Password clave, RegNull = {0};
	int x;
	gotoxy(10, 22);
	printf("Digite Su Nueva Clave Maximo 25 Caracteres: ");
	fflush(stdin);

	if ((KeyPointer = fopen("c:\\temp\\JSpooler\\AdminKey.dat", "w+b")) == NULL)
	{
		printf("Error PAS0SAFEO");
		while (!kbhit());

	}
	else
	{
		fclose(KeyPointer);
	}
	KeyPointer = NULL;

	do
	{
		if ((KeyPointer = fopen("c:\\temp\\JSpooler\\AdminKey.dat", "a+b")) == NULL)
		{
			printf("Error PAS0SAFEO");
			while (!kbhit());
		}
		else
		{
			x = getch();
			printf("%c", x);
			fflush(stdin);
			clave.Pass = x * 2;
			if (x == 13)
			{
				fseek(KeyPointer, (1) * sizeof(struct Password), SEEK_END);
				fwrite(&RegNull, sizeof(struct Password), 1, KeyPointer);
				fclose(KeyPointer);
			}
			else
			{
				fwrite(&clave, sizeof(struct Password), 1, KeyPointer);
				fclose(KeyPointer);
			}
		}
	} while (x != 13);

}
/*Muestra las Opciones de Administrador*/
void Pantalla_Administrador()
{
	int opc;
	char *sel;

	do
	{
		cleardevice();
		settextstyle(3, 0, 3);
		outtextxy(180, 15, "Administrador MyJobSPooler");
		gotoxy(10, 8);
		printf("1.Ver Log de Impresion.");
		gotoxy(10, 10);
		printf("2.Cambiar Clave de Acceso.");
		gotoxy(10, 12);
		printf("3.Regresar.");
		gotoxy(10, 14);
		printf("Su Opcion: [ ]\b\b");
		fflush(stdin);
		gets(sel);
		fflush(stdin);
		opc = atoi(sel);

		switch (opc)
		{
			case 1:
				Log_Impresion();
				break;
			case 2:
				Nueva_Clave();
				break;

			default:

				break;
		}
	} while (opc != 3);

}
