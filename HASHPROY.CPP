#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#inclcude <conio.h>

/*Constantes Hash para Operaciones*/
#define NHASHONE 1000
#define NHASHTWO 150
#define NHASHTHREE 100
#define OPERATOR 31

/*Estructuras para manejo de la entidad Estudiante - Colisiones Listas de Clases de Equivalencia*/
    struct stud
   {
      unsigned int Hash;
      char Name[20];
      char LastName1[20];
      char LastName2[20];
      char Grade[4];
      char ListNum[3];
   };
   typedef 
       struct students
      {
         struct stud Data;
         students *NextPtr;
      } ST;
   typedef ST *Students;

/*Estructuras para manejo de la entidad Profesores - Colisiones por Distribucion de Area Primaria*/
    struct teach
   {
      unsigned int Hash;
      char Id[10];
      char Name[30];
   };
   typedef 
       struct teachers
      {
         struct teach Data;
      } TEACH;
   typedef TEACH *Teachers;


/*Estructuras para manejo de la entidad Rutas - Colisiones por Bloques de Desbordamiento*/
    struct bu
   {
      unsigned int Hash;
      char Id[7];
      char Name[30];
   };
   typedef 
       struct bus
      {
         struct bu Data[NHASHTHREE];
         bus *NextPtr;
      } BUS;
   typedef BUS *Bus;

    struct Statistics
   {
      int Registry[3];
      int Colisions[3];
   };
   Statistics Ststcs;

   void InsertRegistryEst(Students StudentsTable[NHASHONE], int pos, char * *sstring);
   void InsertRegistryPro(Teachers TeachersTable[NHASHTWO], int pos, char * *sstring);
   void InsertRegistryBus(Bus *BusTable, int pos, char **sstring);
   void InitializeArrayEst(Students StudentsTable[NHASHONE]);
   void InitializeArrayPro(Teachers TeachersTable[NHASHTWO]);
   void InitializeArrayBus(Bus *BusTable);
   void LoadDataStudents(Students StudentsTable[NHASHONE]);
   void LoadDataTeachers(Teachers TeachersTable[NHASHTWO]);
   void LoadDataBus(Bus *BusTable);
   void LoadRegistryEst(Students StudentsTable[NHASHONE], int pos, char n[20], char l1[20], char l2[20], char g[4], char l[3]);
   void LoadRegistryPro(Teachers TeachersTable[NHASHONE], int pos, char n[20], char cc[10]);
   void LoadRegistryBus(Bus *BusTable, int pos, char n[20], char p[7]);
   void LoadStatistics(int op, int ent);
   void help();
   unsigned int HashOperation(char *, int);
   void Pause();

    int main(int narg, char **args)
   {
      FILE *FileWriteEstPtr;
      Students StudentsTable[NHASHONE], BkpEstPtr = NULL, FreeEstPtr = NULL;
      Teachers TeachersTable[NHASHTWO], BkpProPtr = NULL;
      Bus BusTable = NULL, BkpBusPtr = NULL;
   
      unsigned int HashCode;
      int i = narg;
      char KeyStringe[9];
   
      for (i = 0; i < 3; i++)
      {
         Ststcs.Registry[i] = 0;
         Ststcs.Colisions[i] = 0;
      }
   
   /*Ayuda*/
      if (strcmp(*(args + 1), "-?") == 0)
      {
         help();
      }
      
      /*Estudiantes*/
      else if (strcmp(*(args + 1), "-a") == 0)
      {
         InitializeArrayEst(StudentsTable);
         LoadDataStudents(StudentsTable);
         strcpy(KeyStringe, '\0');
         strncat(KeyStringe, *(args + 2), 1);
         strncat(KeyStringe, *(args + 3), 1);
         strncat(KeyStringe, *(args + 4), 1);
         strcat(KeyStringe, *(args + 5));
         strcat(KeyStringe, *(args + 6));
         strcat(KeyStringe, "\0");
      
         HashCode = HashOperation(KeyStringe, 1);
      
         InsertRegistryEst(StudentsTable, HashCode, args);
      
         if ((FileWriteEstPtr = fopen("STUDENTS.dat", "w")) != NULL)
         {
            for (i = 0; i < NHASHONE; i++)
            {
               if (StudentsTable[i] != NULL)
               {
                  BkpEstPtr = StudentsTable[i];
                  do
                  {
                     FreeEstPtr = BkpEstPtr;
                     fprintf(FileWriteEstPtr, "%d %s %s %s %s %s\n", BkpEstPtr->Data.Hash, BkpEstPtr->Data.Name, BkpEstPtr->Data.LastName1, BkpEstPtr->Data.LastName2, BkpEstPtr->Data.Grade, BkpEstPtr->Data.ListNum);
                     BkpEstPtr = BkpEstPtr->NextPtr;
                     free(FreeEstPtr);
                  } while (BkpEstPtr);
               
               }
            
            }
            fclose(FileWriteEstPtr);
            FileWriteEstPtr = NULL;
         }
         else
         {
            printf("\nError WESF");
            Pause;
         }
         LoadStatistics(0, 1);
      }
      
      /*Profesores*/
      else if (strcmp(*(args + 1), "-p") == 0)
      {
         InitializeArrayPro(TeachersTable);
         HashCode = HashOperation(*(args + 3), 2);
         LoadDataTeachers(TeachersTable);
         InsertRegistryPro(TeachersTable, HashCode, args);
      
         if ((FileWriteEstPtr = fopen("TEACHERS.dat", "w")) != NULL)
         {
            for (i = 0; i < NHASHTWO; i++)
            {
               if (TeachersTable[i] != NULL)
               {
                  BkpProPtr = TeachersTable[i];
                  fprintf(FileWriteEstPtr, "%d %s %s\n", BkpProPtr->Data.Hash, BkpProPtr->Data.Name, BkpProPtr->Data.Id);
                  free(BkpProPtr);
               }
            
            }
            fclose(FileWriteEstPtr);
            FileWriteEstPtr = NULL;
         }
         else
         {
            printf("\nError WTEF");
            Pause();
         }
         LoadStatistics(0, 2);
      }
      
      /*Rutas*/
      else if (strcmp(*(args + 1), "-r") == 0)
      {
         HashCode = HashOperation(*(args + 3), 3);
         LoadDataBus(&BusTable);
         InsertRegistryBus(&BusTable, HashCode, args);
      
         if ((FileWriteEstPtr = fopen("BUSES.dat", "w")) != NULL)
         {
            do
            {
               BkpBusPtr = BusTable;
               BusTable = BkpBusPtr->NextPtr;
               do
               {
               
                  for (i = 0; i < NHASHTHREE; i++)
                  {
                     if (strcmp(BkpBusPtr->Data[i].Name, " ") != 0)
                     {
                        fprintf(FileWriteEstPtr, "%d %s %s\n", BkpBusPtr->Data[i].Hash, BkpBusPtr->Data[i].Name, BkpBusPtr->Data[i].Id);
                     }
                  }
                  free(BkpBusPtr);
                  BkpBusPtr = NULL;
               
               } while (BkpBusPtr);
            } while (BusTable);
         
            fclose(FileWriteEstPtr);
            FileWriteEstPtr = NULL;
            LoadStatistics(0, 3);
         }
      
      }
      
      /*Estadisticas*/
      else if (strcmp(*(args + 1), "-e") == 0)
      {
         LoadStatistics(1, 4);
      }
      
      /*Busqueda de Alumno*/
      else if (strcmp(*(args + 1), "-ba") == 0)
      {
         LoadDataStudents(StudentsTable);
         strcpy(KeyStringe, '\0');
         strncat(KeyStringe, *(args + 2), 1);
         strncat(KeyStringe, *(args + 3), 1);
         strncat(KeyStringe, *(args + 4), 1);
         strcat(KeyStringe, *(args + 5));
         strcat(KeyStringe, *(args + 6));
         strcat(KeyStringe, "\0");
         HashCode = HashOperation(KeyStringe, 1);
         if ((StudentsTable[HashCode]->Data.Hash == HashCode))
         {
            printf("\t\nRegistro encontrado en la Posicion %d", HashCode);
         }
         else
         {
            printf("\t\nRegistro NO encontrado.");
         }
      
      }
      
      /*Busqueda de Profesor*/
      else if (strcmp(*(args + 1), "-bp") == 0)
      {
         LoadDataTeachers(TeachersTable);
         HashCode = HashOperation(*(args + 3), 2);
      
         if ((TeachersTable[HashCode]->Data.Hash == HashCode))
         {
            printf("\t\nRegistro encontrado en la Posicion %d", HashCode);
         }
         else
         {
            printf("\t\nRegistro NO encontrado.");
         }
      
      }
      
      /*Busqueda de Ruta*/
      else if (strcmp(*(args + 1), "-br") == 0)
      {
         LoadDataBus(&BusTable);
         HashCode = HashOperation(*(args + 3), 3);
      
         if ((BusTable->Data[HashCode].Hash== HashCode))
         {
            printf("\t\nRegistro encontrado en la Posicion %d", HashCode);
         }
         else
         {
            printf("\t\nRegistro NO encontrado.");
         }
      }
      /*Ayuda*/
      else
      {
         help();
      }
      return 0;
   }
/*Hace la operacion HASH*/
    unsigned int HashOperation(char *chain, int opc)
   {
      unsigned int n = 0;
   
      for ( ; *chain; chain++)
         n = OPERATOR * n + *chain;
   
      if (opc == 1)
      {
         return (n % NHASHONE);
      }
      else if (opc == 2)
      {
         return (n % NHASHTWO);
      }
      else if (opc == 3)
      {
         return (n % NHASHTHREE);
      }
      return 0;
   }

    void InitializeArrayEst(Students StudentsTable[NHASHONE])
   {
      for (int i = 0; i < NHASHONE; i++)
         StudentsTable[i] = NULL;
   }
    void InitializeArrayPro(Teachers TeachersTable[NHASHTWO])
   {
      for (int i = 0; i < NHASHTWO; i++)
         TeachersTable[i] = NULL;
   }
    void InitializeArrayBus(Bus *BusTable)
   {
      for (int i = 0; i < NHASHTWO; i++)
      {
         (*BusTable)->Data[i].Hash = 0;
         strcpy((*BusTable)->Data[i].Name, " ");
         strcpy((*BusTable)->Data[i].Id, " ");
         (*BusTable)->NextPtr = NULL;
      }
   }

    void InsertRegistryEst(Students StudentsTable[NHASHONE], int pos, char * *sstring)
   {
      Students p = NULL, TemPtr;
      int i = 0;
   
      p = (Students)malloc(sizeof(students));
      strcpy(p->Data.Name, *(sstring + 2));
      strcpy(p->Data.LastName1, *(sstring + 3));
      strcpy(p->Data.LastName2, *(sstring + 4));
      strcpy(p->Data.Grade, *(sstring + 5));
      strcpy(p->Data.ListNum, *(sstring + 6));
      p->Data.Hash = pos;
      p->NextPtr = NULL;
   
      Ststcs.Registry[0] = Ststcs.Registry[0] + 1;
      if (StudentsTable[pos])
      {
         TemPtr = StudentsTable[pos];
         i++;
         while (TemPtr->NextPtr)
         {
            TemPtr = TemPtr->NextPtr;
         }
         Ststcs.Colisions[0] = Ststcs.Colisions[0] + i;
         TemPtr->NextPtr = p;
      }
      else
      {
         StudentsTable[pos] = p;
         Ststcs.Colisions[0] = Ststcs.Colisions[0] + i;
      }
   }

    void InsertRegistryPro(Teachers TeachersTable[NHASHTWO], int pos, char * *sstring)
   {
      Teachers p = NULL;
      p = (Teachers)malloc(sizeof(teachers));
      strcpy(p->Data.Name, *(sstring + 2));
      strcpy(p->Data.Id, *(sstring + 3));
      p->Data.Hash = pos;
   
      Ststcs.Registry[1] = Ststcs.Registry[1] + 1;
      if (TeachersTable[pos])
      {
         Ststcs.Colisions[1] = Ststcs.Colisions[1] + 1;
         do
         {
            pos++;
            if (TeachersTable[pos] == NULL)
            {
               p->Data.Hash = pos;
               TeachersTable[pos] = p;
               return;
            }
         } while (TeachersTable[pos] != NULL);
      
      }
      else
      {
         TeachersTable[pos] = p;
      }
   }

    void InsertRegistryBus(Bus *BusTable, int pos, char **sstring)
   {
      Bus b = NULL, BackupPtr = NULL;
   
      Ststcs.Registry[2] = Ststcs.Registry[2] + 1;
      if (*BusTable)
      {
         if ((*BusTable)->Data[pos].Hash != pos)
         {
            strcpy((*BusTable)->Data[pos].Name, *(sstring + 2));
            strcpy((*BusTable)->Data[pos].Id, *(sstring + 3));
            (*BusTable)->Data[pos].Hash = pos;
         }
         else
         {
            BackupPtr = *BusTable;
            b = (Bus)malloc(sizeof(bus));
            InitializeArrayBus(&b);
            strcpy(b->Data[pos].Name, *(sstring + 2));
            strcpy(b->Data[pos].Id, *(sstring + 3));
            b->Data[pos].Hash = pos;
            b->NextPtr = NULL;
            BackupPtr->NextPtr = b;
            Ststcs.Colisions[2] = Ststcs.Colisions[2] + 1;
         }
      }
      else
      {
         b = (Bus)malloc(sizeof(bus));
         InitializeArrayBus(&b);
         strcpy(b->Data[pos].Name, *(sstring + 2));
         strcpy(b->Data[pos].Id, *(sstring + 3));
         b->Data[pos].Hash = pos;
         b->NextPtr = NULL;
         *BusTable = b;
      }
   
   }

    void LoadDataStudents(Students StudentsTable[NHASHONE])
   {
      FILE *FReadPtr = NULL;
      char n[20], l1[20], l2[20], g[4], l[3];
      int k;
   
      if ((FReadPtr = fopen("STUDENTS.dat", "r")) != NULL)
      {
         while (!feof(FReadPtr))
         {
            fscanf(FReadPtr, "%d %s %s %s %s %s\n", &k, n, l1, l2, g, l);
            LoadRegistryEst(StudentsTable, k, n, l1, l2, g, l);
         }
         fclose(FReadPtr);
         FReadPtr = NULL;
      }
   }

    void LoadDataTeachers(Teachers TeachersTable[NHASHTWO])
   {
      FILE *FReadPtr = NULL;
      char n[20], cc[10];
      int k;
   
      if ((FReadPtr = fopen("TEACHERS.dat", "r")) != NULL)
      {
         while (!feof(FReadPtr))
         {
            fscanf(FReadPtr, "%d %s %s\n", &k, n, cc);
            LoadRegistryPro(TeachersTable, k, n, cc);
         }
         fclose(FReadPtr);
         FReadPtr = NULL;
      }
   
   }

    void LoadDataBus(Bus *BusTable)
   {
      FILE *FReadPtr = NULL;
      char n[20], p[7];
      int k;
   
      if ((FReadPtr = fopen("BUSES.dat", "r")) != NULL)
      {
         while (!feof(FReadPtr))
         {
            fscanf(FReadPtr, "%d %s %s\n", &k, n, p);
            LoadRegistryBus(BusTable, k, n, p);
         }
         fclose(FReadPtr);
         FReadPtr = NULL;
      }
   }

    void LoadRegistryEst(Students StudentsTable[NHASHONE], int pos, char n[20], char l1[20], char l2[20], char g[4], char l[3])
   {
      Students r = NULL, BackupPtr = NULL;
      int i = 0;
      r = (Students)malloc(sizeof(students));
      strcpy(r->Data.Name, n);
      strcpy(r->Data.LastName1, l1);
      strcpy(r->Data.LastName2, l2);
      strcpy(r->Data.Grade, g);
      strcpy(r->Data.ListNum, l);
      r->Data.Hash = pos;
      r->NextPtr = NULL;
   
      Ststcs.Registry[0] = Ststcs.Registry[0] + 1;
      if (StudentsTable[pos])
      {
         BackupPtr = StudentsTable[pos];
         i++;
         while (BackupPtr->NextPtr)
         {
            BackupPtr = BackupPtr->NextPtr;
         }
         Ststcs.Colisions[0] = Ststcs.Colisions[0] + i;
         BackupPtr->NextPtr = r;
      }
      else
      {
         StudentsTable[pos] = r;
         Ststcs.Colisions[0] = Ststcs.Colisions[0] + i;
      }
   }

    void LoadRegistryPro(Teachers TeachersTable[NHASHONE], int pos, char n[20], char cc[10])
   {
      Teachers r = NULL;
      r = (Teachers)malloc(sizeof(teachers));
      strcpy(r->Data.Name, n);
      strcpy(r->Data.Id, cc);
      r->Data.Hash = pos;
   
      Ststcs.Registry[1] = Ststcs.Registry[1] + 1;
      if (TeachersTable[pos])
      {
         Ststcs.Colisions[1] = Ststcs.Colisions[1] + 1;
         do
         {
            pos++;
            if (TeachersTable[pos] == NULL)
            {
               r->Data.Hash = pos;
               TeachersTable[pos] = r;
               return;
            }
         } while (TeachersTable[pos] != NULL);
      
      }
      else
      {
         TeachersTable[pos] = r;
      }
   }

    void LoadRegistryBus(Bus *BusTable, int pos, char n[20], char p[7])
   {
      Bus b = NULL, BackupPtr = NULL;
   
      Ststcs.Registry[2] = Ststcs.Registry[2] + 1;
      if (*BusTable)
      {
         if ((*BusTable)->Data[pos].Hash != pos)
         {
            strcpy((*BusTable)->Data[pos].Name, n);
            strcpy((*BusTable)->Data[pos].Id, p);
            (*BusTable)->Data[pos].Hash = pos;
         }
         else
         {
            BackupPtr = *BusTable;
            b = (Bus)malloc(sizeof(bus));
            InitializeArrayBus(&b);
            strcpy(b->Data[pos].Name, n);
            strcpy(b->Data[pos].Id, p);
            b->Data[pos].Hash = pos;
            b->NextPtr = NULL;
            BackupPtr->NextPtr = b;
            Ststcs.Colisions[2] = Ststcs.Colisions[2] + 1;
         }
      }
      else
      {
         b = (Bus)malloc(sizeof(bus));
         InitializeArrayBus(&b);
         strcpy(b->Data[pos].Name, n);
         strcpy(b->Data[pos].Id, p);
         b->Data[pos].Hash = pos;
         b->NextPtr = NULL;
         *BusTable = b;
      }
   
   }

    void LoadStatistics(int op, int ent)
   {
      FILE *FReadPtr = NULL, *FWritePtr = NULL;
      int i = 0, r = 0, c = 0;
   
      if ((FReadPtr = fopen("STATISCS.dat", "r")) != NULL)
      {
         while (!feof(FReadPtr))
         {
            fscanf(FReadPtr, "%d %d\n", &r, &c);
         
            if (Ststcs.Registry[i] == 0)
            {
               Ststcs.Registry[i] = r;
            }
            if (ent == 2)
            {
               Ststcs.Colisions[i] = Ststcs.Colisions[i] + c;
            }
         
            if (ent == 4)
            {
               Ststcs.Registry[i] = r;
               Ststcs.Colisions[i] = c;
            }
            i++;
         }
      
         fclose(FReadPtr);
         FReadPtr = NULL;
      }
   
      if (op == 1)
      {
         printf("\n\tEstudiantes-> Registros: %d Colisiones: %d", Ststcs.Registry[0], Ststcs.Colisions[0]);
         printf("\n\tProfesores -> Registros: %d Colisiones: %d", Ststcs.Registry[1], Ststcs.Colisions[1]);
         printf("\n\tRutas      -> Registros: %d Colisiones: %d", Ststcs.Registry[2], Ststcs.Colisions[2]);
         Pause();
      }
   
      if ((FWritePtr = fopen("STATISCS.dat", "w")) != NULL)
      {
         for (i = 0; i < 3; i++)
         {
            r = Ststcs.Registry[i];
            c = Ststcs.Colisions[i];
            fprintf(FWritePtr, "%d %d\n", r, c);
         }
         fclose(FWritePtr);
         FWritePtr = NULL;
      }
   }
/*Realiza una pausa en la ejecucion del Programa*/
    void Pause()
   {
      printf("\n\tPresione Cualquier tecla para continuar.");
      while (!kbhit());
   }

/*Despliega la Ayuda del Programa en Consola*/
    void help()
   {
      printf("\n\tUso: hashproy [-a]/[-p]/[-r]/[-e]/[-b][Datos]");
      printf("\n\tPara Ingresar Alumno\n\t-a Nombre Apellido1 Apellido2 Grado Numero_de_Lista");
      printf("\n\tPara Ingresar Profesor\n\t-p Nombre_Profesor Cedula");
      printf("\n\tPara Ingresar Ruta\n\t-r Nombre_Conductor Placa");
      printf("\n\tPara Mostrar Estadisticas\n\t-e");
      printf("\n\tPara Buscar un Alumno\n\t-ba Nombre Apellido1 Apellido2 Grado Numero_de_Lista");
      printf("\n\tPara Buscar un Profesor\n\t-bp Nombre_Profesor Cedula");
      printf("\n\tPara Buscar una Ruta\n\t-br Nombre_Conductor Placa");
      printf("\n\tPara La Ayuda\n\t-?");
   }