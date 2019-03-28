#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *@brief programa que nos muestra los datos de 10 empleados
 *@file Practica3.c
 *
 *@author programador(es):
 *Mauricio Guzman Arguello.
 *@date fecha de creacion:
 *15 de enero del 2019
 *@author ultimo en modificar el programa
 * mauricio guzman
 *@date fecha de la ultima modificacion
 * 17 de enero del 2019;
 */

typedef struct empleado
{
    char name[50];
    int age;
    int old;
    float salary;
}Empleado;

void leer_empleado(Empleado *employe,int *i);
void imprimir_empleados(Empleado *employe, int *i);
void buscar_empleado(Empleado *employe, int *i);
void imprimir_antiguo(Empleado *employe,int *i);
void mayusculas(Empleado *employe,int *i, int l,Empleado *pointer);
void convertir(int l,Empleado *pointer);
void guardar(Empleado *employe, int *i);
void recuperar(Empleado *employe,int *i);

int main(void)
{
    int opcion,i=0;
    Empleado employe[11];
    Empleado pointer;
    int l;
    
    
    system("clear");
    
    do
    {
        printf("\n");
        printf("opcion 1 registrar\nopcion 2 imprimir\n");
        printf("opcion 3 buscar\nopcion 4 buscar por antiguedad\n");
        printf("opcion 5 convertir a mayusculas\n");
        printf("opcion 6 salir\n\n");
        printf("dame la opcion correspondiente: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
            {
                if(i!=10)
                {
                    leer_empleado(employe,&i);
                    i++;
                    guardar(employe,&i);
                }else
                {
                    printf("ya no se pueden registrar a mas\n");
                }
            }break;
            case 2:
            {
                imprimir_empleados(employe,&i);
            }break;
            case 3:
            {
                buscar_empleado(employe,&i);
            }break;
            case 4:
            {
                imprimir_antiguo(employe,&i);
            }break;
            case 5:
            {
                mayusculas(employe,&i,l,&pointer);
            }break;
            case 6:
            {
                system("clear");
                printf("bye\n");
            }break;
            case 7:
            {
                recuperar(employe,&i);
            }
        }
    }while(opcion!=6);
}


void leer_empleado(Empleado *employe,int *i)
{
    system("clear");
    printf("\n");
    printf("dame el nombre del empleado: ");
    fpurge(stdin);
    gets(employe[*i].name);
    printf("dame la edad del empleado: ");
    fpurge(stdin);
    scanf("%d",&employe[*i].age);
    printf("dame la antiguedad del empleado: ");
    fpurge(stdin);
    scanf("%d",&employe[*i].old);
    printf("dame el sueldo del empleado: ");
    fpurge(stdin);
    scanf("%f",&employe[*i].salary);
    
}

void guardar(Empleado *employe, int *i)
{
    FILE *archivo;
    archivo=fopen("empleados.pdf","at");
    fprintf(archivo,"carrera:%s\n",temp->carrera);
    fprintf(archivo,"cali1:%0.2f\n",temp->cali[0]);
    fprintf(archivo,"cali2:%0.2f\n",temp->cali[1]);
    fprintf(archivo,"cali3:%0.2f\n",temp->cali[2]);
    fprintf(archivo,"cali4:%0.2f\n",temp->cali[3]);
}

void imprimir_empleados(Empleado *employe, int *i)
{
    int j;
    
    system("clear");
    for(j=0;j<*i;j++)
    {
        printf("\n");
        printf("nombre: %s\n",employe[j].name);
        printf("edad: %d\n", employe[j].age);
        printf("antiguedad: %d\n",employe[j].old);
        printf("sueldo: $%0.2f\n",employe[j].salary);
    }
}

void buscar_empleado(Empleado *employe, int *i)
{
    int j,h;
    char aux[50];
    
    system("clear");
    printf("\n");
    printf("dame el nombre a buscar: ");
    fpurge(stdin);
    gets(aux);
    
    printf("\n");
    
    for(j=0;j<=*i;j++)
    {
        h=strcmp(aux,employe[j].name);
        if(h==0)
        {
            printf("nombre: %s\n",employe[j].name);
            printf("edad: %d\n", employe[j].age);
            printf("antiguedad: %d\n",employe[j].old);
            printf("sueldo: $%0.2f\n",employe[j].salary);
        }
    }
}
void recuperar(Empleado *employe,int *i)
{
    int k;
    int l,m,n;
    char namess[30];
    FILE *archivo;
    archivo=fopen("empleados.pdf","rt");
    while(!feof(archivo))
    {
        fgets(namess,60,archivo);
         fscanf(archivo,"cali1:%f\n",l);
        
    }

void imprimir_antiguo(Empleado *employe, int *i)
{
    int j,h;
    
    system("clear");
    printf("\n");
    printf("dame la antiguedad a mostrar: ");
    scanf("%d",&h);
    
    for(j=0;j<*i;j++)
    {
        if(h<=employe[j].old)
        {
            printf("\n");
            printf("nombre: %s\n",employe[j].name);
            printf("edad: %d\n", employe[j].age);
            printf("antiguedad: %d\n",employe[j].old);
            printf("sueldo: $%0.2f\n",employe[j].salary);
            printf("\n");
        }
    }
}

void mayusculas(Empleado *employe,int *i,int l,Empleado *pointer)
{
    char name[50];
    int j,h;
    
    printf("dame el nombre a convertir en mayusculas: ");
    fpurge(stdin);
    gets(name);
    
    for(j=0;j<=*i;j++)
    {
        h=strcmp(name,employe[j].name);
        if(h==0)
        {
            l=j;
            *pointer=employe[j];
            convertir(l,pointer);
            printf("\n");
            printf("nombre: %s\n",employe[j].name);
            printf("edad: %d\n", employe[j].age);
            printf("antiguedad: %d\n",employe[j].old);
            printf("sueldo: $%0.2f\n",employe[j].salary);
        }
    }
    
}

void convertir(int l,Empleado *pointer)
{
    int j,k,longitud;
    char let;
    
    longitud=strlen(pointer[l].name);
    
    for(j=0;j<longitud;j++)
    {
        pointer[l].name[j]= pointer[l].name[j]-'a'+'A';
    }
}

