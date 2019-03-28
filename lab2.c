#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Simbolos
{
    int porcentaje;
    char simbolo;
    struct Simbolos *sig,*ant,*der,*izq;
}tiposimb;

void Ingresar(int por,tiposimb **Inicio,char simb);
void Listar(tiposimb *Inicio);
void Eliminar(tiposimb *Inicio);
//void Modificar();
//void Generar();
void Codificar(tiposimb *Raiz,char cod [1000],char texto[1000]);
void Decodificar(tiposimb *Raiz);
void BorrarLista(tiposimb *Inicio);
void BorrarArbol(tiposimb *Raiz);

int main(void)
{
    tiposimb *Inicio=NULL,*Raiz=NULL;
    char simb;
    int op,por;
    int name[50];
    char cod[1000];
    char texto[1000];
    
    system("clear");
    printf("Bienvenido\n");
    printf("Este Programa fue desarollado por:\n");
    printf("\t-E. Michelle Castro León\n");
    printf("\t-Mauricio Alejandro Guzmán Argüello\n");
    printf("\t-José Pablo Romero Niembro\n");
    printf("Presiona enter para continuar\n");
    getchar();
    system("clear");
    printf("\nObjetivo del program:\nes realizar la cidifcacion de mensajes que han sido guardados en un archivo de texto, esto los codifica de manera binaria.\n");
    getchar();
    system("clear");
    while(op!=8)
    {
        system("clear");
        printf("Escoge una opcion\n");
        printf("1....Ingresar un simbolo y su probabilidad\n");
        printf("2....Listar simbolos\n");
        printf("3....Eliminar un simbolo\n");
        printf("4....Modificar un simbolo\n");
        printf("5....Generar codigos\n");
        printf("6....Codificar mensaje\n");
        printf("7....Decodificar mensaje\n");
        printf("8....Salir\n");
        __fpurge(stdin);
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                printf("ingrese el simbolo seguido del porcentaje con un espacio\n");
                printf("para finalizar introduce el 1000\n");
                do
                {
                    __fpurge(stdin);
                    scanf("%c %d",&simb,&por);
                    if(por!=1000)
                        Ingresar(por,&Inicio,simb);
                }while(por!=1000);
                break;
            case 2:
            {
                Listar(Inicio);
                getchar();
                getchar();
                break;
            }
            case 3:
            {
                Eliminar(Inicio);
                getchar();
                getchar();
                break;
            }
            case 4:
            {
                printf("4\n");
                //Modificar();
                getchar();
                getchar();
                break;
            }
            case 5:
            {
                printf("5\n");
                //Generar();
                getchar();
                getchar();
                break;
            }
            case 6:
            {
                printf("6\n");
                Codificar(Raiz,texto,cod);
                getchar();
                getchar();
                break;
            }
            case 7:
            {
                printf("7\n");
                Decodificar(Raiz);
                getchar();
                getchar();
                break;
            }
            case 8:
                BorrarLista(Inicio);
                BorrarArbol(Raiz);
                printf("Gracias buen dia\n");
                printf("Presione enter para salir por completo\n");
                getchar();
                getchar();
                break;
        }
    }
    
}
void BorrarLista(tiposimb *Inicio)
{
    tiposimb *temp;
    temp=Inicio;
    while(temp!=NULL)
    {
        Inicio=temp->sig;
        free(temp);
        temp=Inicio;
    }
}
void BorrarArbol(tiposimb *Raiz)
{
    if(Raiz!=NULL)
    {
        BorrarArbol(Raiz->izq);
        BorrarArbol(Raiz->der);
        free(Raiz);
    }
}
void Listar(tiposimb *Inicio)
{
    tiposimb *temp;
    temp=Inicio;
    printf("Simbolo   Porcentaje\n");
    while(temp!=NULL)
    {
        printf("   %c           %d\n",temp->simbolo,temp->porcentaje);
        temp=temp->sig;
    }
}
void Ingresar(int por,tiposimb **Inicio,char simb)
{
    tiposimb *temp,*temp2,*posicion;
    temp=(tiposimb*)malloc(sizeof(tiposimb));
    temp->porcentaje=por;
    temp->simbolo=simb;
    posicion=*Inicio;
    printf("%d  %c\n",temp->porcentaje,temp->simbolo);
    if(*Inicio!=NULL)
    {
        while((posicion!=NULL) && (temp->porcentaje > posicion->porcentaje))
        {
            posicion=posicion->sig;
        }
        if(posicion!=NULL)
        {
            temp->sig=posicion;
            if(posicion!=*Inicio)
            {
                temp2=*Inicio;
                while(temp2->sig!=posicion)
                {
                    temp2=temp2->sig;
                }
                temp2->sig=temp;
            }
            else
            {
                *Inicio=temp;
            }
        }
        else
        {
            temp2=*Inicio;
            while(temp2->sig!=NULL)
                temp2=temp2->sig;
            temp2->sig=temp;
            temp->sig=NULL;
        }
    }
    else
    {
        temp->sig=*Inicio;
        *Inicio=temp;
    }
}

void Eliminar(tiposimb *Inicio)
{
    char eliminado;
    tiposimb *temp,*temp2;
    if(Inicio!=NULL)
    {
        printf("Escribe el simbolo que deseas eliminar\n");
        __fpurge(stdin);
        gets(eliminado);
        temp=Inicio;
        while(temp->simbolo != eliminado)
            temp=temp->sig;
        if(temp==Inicio)
        {
            Inicio=temp->sig;
            free(temp);
            printf("El simbolo fue eliminado exitosamente\n");
        }
        else
        {
            if(temp!=NULL)
            {
                temp2=Inicio;
                while(temp2->sig!=NULL)
                    temp2=temp2->sig;
                temp2->sig=temp->sig;
                printf("El simbolo fue eliminado exitosamente\n");
            }
            else
                printf("El simbolo no existe\n");
        }
    }
    else
        printf("No se puede eliminar un elemento de una lista vacia\n");
}

void Codificar(tiposimb *Raiz,char cod [1000],char texto[1000])
{
    int i=0,j=0;
    char name[50];
    FILE *archivo;
    
    if(Raiz!=NULL)
    {
        if(Raiz->izq!=NULL)//si se puede mover a la izquierda por lo tanto es 0
        {
            cod[i]='0';
            Codificar(Raiz->izq,texto,cod);
            i+1;
            cod[i]='\0';
        }
        if(Raiz->der!NULL)
        {
            cod[i]='1';
            Codificar(Raiz->der,texto,cod);
            i+1;
            cod[i]'\0';
        }
        if(texto[j]==Raiz->simbolo)
        {
            cod[i]='\0'
            if(j==0)
            {
                printf("\nescribe el nombre del archivo donde quieres que se guarde(sin extension): ");
                __fpurge(stdin);
                gets(name);
                strcat(name,".txt");
                
            }
            archivo=fopen(name,"at");
            fprintf(archivo,"s",cod);
            fclose(archivo);
        }
    }
}

void Decodificar(tiposimb *Raiz)
{
    char name[50];
    char codigo[1000];
    char frase[1000];
    char name2[50];
    tiposimb *aux;
    int i=0,flag=0,j=0;
    FILE *archivo;
    
    printf("\nescribe el nombre del archivo(sin extension): ");
    __fpurge(stdin);
    gets(name);
    archivo=fopen(name,"rt");
    if(archivo==NULL)
    {
        printf("el archivo no existe \n");
    }
    else
    {
        fscanf(archivo,"%s",codigo);
        fclose(archivo);
        j=0;
        temp=Raiz;
        for(i=0;i<strlen(codigo);i++)
        {
            if(codigo[i]=='0'||codigo[i]=='1')
            {
                if(codigo[i]=='0')
                {
                    temp=temp->izq;
                }
                if(codigo[i]=='1')
                {
                    temp=temp->der;
                }
                if((temp->der==NULL)&&temp->izq==NULL))
                {
                    frase[j]=temp->simbolo;
                    j++;
                    temp=Raiz;
                }
            }else
            {
                printf("el codifo no es binario por lo tanto no se puede leer\n");
                flag=1;
            }
        }
        if(flag==0)
        {
            printf("\nescribe el nombre del archivo donde se guardar(sin extension: ");
            __fpurge(stdin);
            gets(name2);
            strcat(name2,".txt");
            archivo=fopne(name2,"at");
            fprintf(archivo,"%s",frase);
            fclose(archivo);
            
        }
    
}

