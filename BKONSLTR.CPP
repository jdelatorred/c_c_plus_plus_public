#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <myfuncio.h>


void Actualizar(FILE *);
void Busqueda(FILE *);
void Cargar_Archivo(FILE *);
void Eliminar(FILE *);
void Escribir_Archivo(FILE *);
void Esperar(FILE *);
int Generar_PIN();
void Gestion_Administrador(FILE *);
void Gestion_Usuario(FILE *, int PIN);
void Inicializar_Bd(FILE *);
void Leer_Archivo(FILE *);
void Leer_Accesos();
void Menu();




struct DatosBiblioteca
{
	int Codigo;
	char Titulo[30];
	char Autor[30];
	char Materia[30];
	char Editorial[30];
	char Tipo[10];
	int NPaginas;

};

void main()
{
	Menu();
}

void Actualizar(FILE *ActPtr)
{

}
void Busqueda(FILE *BusqPtr)
{

}

void Cargar_Archivo(FILE *CargPtr)
{


}
void Eliminar(FILE *ElimPrt)
{

}

void Esperar()
{

	gotoxy(22, 40);
	printf("Presione Cualquier tecla para continuar");
	while (!kbhit())
		;


}

void Escribir_Archivo(FILE *DtbasePtr)
{

	int i, Reg, Tmp = 1;
	struct DatosBiblioteca BasedeDatos, Bd[100];
	BasedeDatos.Codigo = 1;

	if ((DtbasePtr = fopen("c:\\BKonsltr\\BaseDato.dat", "a+")) == NULL)
		printf("Error al Abrir el Archivo.");

	else
	{
		for (i = 0; i < 100; i++)
		{
			fread(&Bd[i], sizeof(struct DatosBiblioteca), 1, DtbasePtr);
			if (Bd[i].Codigo != 0)
			{
				Tmp = Bd[i].Codigo;
			}
			else
			{
				i = 100;
			}
		}
		printf("Cuantos Registros desea Ingresar: ");
		scanf("%d", &Reg);
		fflush(stdin);
		while (Reg > 0)
		{

			gotoxy(3, 7);
			printf("Ingrese el Titulo del Libro: ");
			gets(BasedeDatos.Titulo);
			fflush(stdin);

			gotoxy(3, 8);
			printf("Ingrese el Autor: ");
			gets(BasedeDatos.Autor);
			fflush(stdin);

			gotoxy(3, 9);
			printf("Ingrese la Materia: ");
			gets(BasedeDatos.Materia);
			fflush(stdin);

			gotoxy(3, 10);
			printf("Ingrese la Editorial: ");
			gets(BasedeDatos.Editorial);
			fflush(stdin);

			gotoxy(3, 11);
			printf("Ingrese El Tipo del Libro(Libro,Revista,Video,Atlas): ");
			gets(BasedeDatos.Tipo);
			fflush(stdin);

			gotoxy(3, 12);
			printf("Ingrese El Numero de Paginas: ");
			scanf("%d", &BasedeDatos.NPaginas);
			fflush(stdin);

			BasedeDatos.Codigo = Tmp;
			Reg--;
			fseek(DtbasePtr, (Tmp - 1) * sizeof(struct DatosBiblioteca), SEEK_SET);
			fwrite(&BasedeDatos, sizeof(struct DatosBiblioteca), 1, DtbasePtr);
			Tmp++;
			clrscr();
			pantalla_marco();

		}
	}
	fclose(DtbasePtr);
}


void Inicializar_Bd(FILE *IniciPtr)
{

	int i;
	struct DatosBiblioteca BdVacia = {0, "", "", "", "", "", 0};

	if ((IniciPtr = fopen("c:\\BKonsltr\\BaseDato.dat", "w")) == NULL)
	{
		printf("Error al Abrir el Archivo.");
	}
	else
	{

		for (i = 1; i <= 100; i++)
		{
			fwrite(&BdVacia, sizeof(struct DatosBiblioteca), 1, IniciPtr);

		}
		fclose(IniciPtr);

	}

}
void Leer_Accesos()
{

	char Usuario[30];
	int PIN;
	char Fecha[10];
	char Hora[10];
	FILE *AccesosPtr;
	if ((AccesosPtr = fopen("c:\\BKonsltr\\Accesos.dat", "r")) == NULL)
		printf("El archivo no pudo ser Abierto\n");
	else
	{
	      printf("%-10s%-13s%-4s%s\n","USUARIO","PIN","FECHA","HORA");
		fscanf(AccesosPtr, "%s\n%d\n%s\n%s\n", Usuario, &PIN, Fecha, Hora);
		while (!feof(AccesosPtr))
		{
			printf("%-10s%-4d%-10s%-10s\n", Usuario, PIN, Fecha, Hora);
			fscanf(AccesosPtr, "%s\n%d\n%s\n%s\n", Usuario, &PIN, Fecha, Hora);
		}
		fclose(AccesosPtr);
	}

}

void Leer_Archivo(FILE *LeerPtr)
{

	struct DatosBiblioteca BasedeDatos;

	if ((LeerPtr = fopen("c:\\BKonsltr\\BaseDato.dat", "r")) == NULL)
	{
		printf("Error al Abrir el Archivo.\n");
		Esperar();
	}
	else
	{
		printf("%s%-8s%-11s%-10s%-10s%-10s%-10s\n\n", "Codigo", "Titulo", "Autor", "Materia", "Editorial", "Tipo", "N Paginas");


		while (!feof(LeerPtr))
		{

			fread(&BasedeDatos, sizeof(struct DatosBiblioteca), 1, LeerPtr);
			printf("%-6d%-10s%-10s%-10s%-10s%-10s%10d\n", BasedeDatos.Codigo, BasedeDatos.Titulo, BasedeDatos.Autor, BasedeDatos.Materia, BasedeDatos.
				Editorial, BasedeDatos.Tipo, BasedeDatos.NPaginas);
			delay(100);
		}

		fclose(LeerPtr);
	}

}

void Menu(void)
{
	FILE *BdatosPtr;
	int i, choice, PIN;
	char *opc;
	do
	{
		pantalla_inicio();
		gets(opc);
		fflush(stdin);
		choice = atoi(opc);

		switch (choice)
		{

			case 1:
				PIN = Generar_PIN();
				pantalla_PIN(PIN);
				Esperar();
				break;

			case 2:
				Gestion_Usuario(BdatosPtr, PIN);
				break;

			case 3:
				Gestion_Administrador(BdatosPtr);
				break;

			default:
				if (choice == 4)
				{
					gotoxy(25, 40);
					printf("Saliendo.");
					for (i = 1; i <= 20; i++)
					{
						delay(100);
						printf(".");
					}
				}

				break;
		}

	} while (choice != 4);

}

int Generar_PIN()
{
	int i, Numero;
	srand(time(NULL));
	Numero = (rand() % 9000) + 1000;
	return (Numero);
}

void Gestion_Administrador(FILE *Database)
{
	int key, choice;
	char *clave, *opc;

	password_administrador();
	gets(clave);
	fflush(stdin);
	key = atoi(clave);

	if (key == 100)
	{
		do
		{

			pantalla_administrador();
			gets(opc);
			fflush(stdin);
			choice = atoi(opc);
			if (choice == 1)
			{
				pantalla_marco();
				Escribir_Archivo(Database);

			}
			else if (choice == 2)
			{

				pantalla_marco();

			}

			else if (choice == 3)
			{

				pantalla_Listado();
				Leer_Archivo(Database);
				Esperar();

			}

			else if (choice == 4)
			{
                        pantalla_Listado();
				Leer_Accesos();
				Esperar();

			}

			else if (choice == 5)
			{

				Inicializar_Bd(Database);
				Esperar();

			}

		} while (choice != 6);

	}
	else
	{
		gotoxy(25, 29);
		printf("Clave Erronea Intente otra vez");
		Esperar();

	}


}

void Gestion_Usuario(FILE *Database, int PIN)
{
	FILE *AccesPtr;
	int password, choice;
	char *opcion, *Usuario, Fecha[9], Hora[9];

	_strdate(Fecha);
	_strtime(Hora);
	if (PIN != 0)
	{
		pantalla_AccesoU();
		gets(Usuario);
		fflush(stdin);
		clrscr();
		pantalla_password();
		scanf("%d", &password);
		fflush(stdin);
		/*-Registra el Acceso de los usuarios de la aplicacion-*/
		if ((AccesPtr = fopen("c:\\BKonsltr\\Accesos.dat", "a+")) == NULL)
		{
			printf("El archivo no pudo ser abierto");

		}
		else
		{
			fprintf(AccesPtr, "%s\n%d\n%s\n%s\n", Usuario, PIN, Fecha, Hora);
			fclose(AccesPtr);
		}

		if (password == PIN)
		{
			do
			{
				clrscr();
				pantalla_consulta();
				gets(opcion);
				fflush(stdin);
				choice = atoi(opcion);
				if (choice == 1)
				{

				}
			} while (choice != 4);
		}
		else
		{
			gotoxy(28, 29);
			printf("Clave Erronea Intente otra vez");
			Esperar();
		}
	}

	else
	{
		gotoxy(28, 29);
		printf("Debe Generar Primero un PIN");
		Esperar();
	}

}








