#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct palabra
{
    char palabra[20];
    int frecuencia;
    struct palabra *izq, *der;
}tipodato;

void Inserta(tipodato **raiz, char palabra[20], int frecuencia);
void valida(tipodato *raiz, int *bandera, char palabra[20]);
void ImprimirOrden(tipodato *raiz);
void ImprimirPreOrden(tipodato *raiz);
void ImprimirPostOrden(tipodato *raiz);
tipodato *Buscar(tipodato *raiz, char busca[20]);
void Borrar(tipodato *raiz);

int main (void)
{
    FILE *Archivo;
    char NombreArchivo[20], palabra[20], busca[20];
    tipodato *raiz=NULL, *ap;
    int opc, frecuencia=1, bandera=0;
    printf("Escribe el nombre del archivo (con extension): ");
    gets(NombreArchivo);
    Archivo=fopen(NombreArchivo, "rt");
    if(Archivo!=NULL)
    {
        while(fscanf(Archivo, "%s\n", palabra)==1)
        {
            valida(raiz, &bandera, palabra);
            if(bandera==0)
                Inserta(&raiz, palabra, frecuencia);
            bandera=0;
        }
        fclose(Archivo);
    }
    else
    {
        printf("No existe el archivo\n");
        exit(0);
    }
    do
    {
        printf("Menu:\n1. Imprimir en orden\n2. Imprimir en pre orden\n3. Imprimir en post orden\n4. Buscar palabra\n5. Salir\n");
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
                ImprimirOrden(raiz);
                break;
            case 2:
                ImprimirPreOrden(raiz);
                break;
            case 3:
                ImprimirPostOrden(raiz);
                break;
            case 4:
                printf("Escribe la palabra que quieres buscar: ");
                fpurge(stdin);
                gets(busca);
                ap=Buscar(raiz, busca);
                if(ap!=NULL)
                    printf("La palabra que buscaste es %s, tiene una frecuencia de %d y esta en %p\n", ap->palabra, ap->frecuencia, ap);
                else
                    printf("La palabra no esta en el arbol\n");
                break;
            case 5:
                Borrar(raiz);
                break;
            default:
                printf("La opcion no existe\n");
                break;
        }
    }while(opc!=5);
}

void Inserta(tipodato **raiz, char palabra[20], int frecuencia)
{
    tipodato *avanza, *temp;
    avanza=*raiz;
    temp=(tipodato*)malloc(sizeof(tipodato));
    strcpy(temp->palabra, palabra);
    temp->frecuencia=frecuencia;
    temp->der=NULL;
    temp->izq=NULL;
    while(avanza!=NULL)
    {
        if(strcmp(avanza->palabra, temp->palabra)<0)
        {
            if(avanza->der!=NULL)
                avanza=avanza->der;
            else
            {
                avanza->der=temp;
                return;
            }
        }
        if(strcmp(avanza->palabra, temp->palabra)>=0)
        {
            if(avanza->izq!=NULL)
                avanza=avanza->izq;
            else
            {
                avanza->izq=temp;
                return;
            }
        }
    }
    avanza=temp;
    *raiz=avanza;
}

void valida(tipodato *raiz, int *bandera, char palabra[20])
{
    if(raiz!=NULL)
    {
        valida(raiz->izq, bandera, palabra);
        if(strcmp(raiz->palabra, palabra)==0)
        {
            *bandera=1;
            raiz->frecuencia=raiz->frecuencia+1;
        }
        valida(raiz->der, bandera, palabra);
    }
    
}

void ImprimirOrden(tipodato *raiz)
{
    if(raiz!=NULL)
    {
        ImprimirOrden(raiz->izq);
        printf("%s: %d\n", raiz->palabra, raiz->frecuencia);
        ImprimirOrden(raiz->der);
    }
}

void ImprimirPreOrden(tipodato *raiz)
{
    if(raiz!=NULL)
    {
        printf("%s: %d\n", raiz->palabra, raiz->frecuencia);
        ImprimirPreOrden(raiz->izq);
        ImprimirPreOrden(raiz->der);
    }
}

void ImprimirPostOrden(tipodato *raiz)
{
    if(raiz!=NULL)
    {
        ImprimirPostOrden(raiz->izq);
        ImprimirPostOrden(raiz->der);
        printf("%s: %d\n", raiz->palabra, raiz->frecuencia);
    }
}

tipodato *Buscar(tipodato *raiz, char busca[20])
{
    while(raiz!=NULL)
    {
        if(strcmp(busca, raiz->palabra)==0)
            return raiz;
        else
        {
            if(strcmp(busca, raiz->palabra)>0)
                raiz=raiz->der;
            else
                raiz=raiz->izq;
        }
    }
    return NULL;
}

void Borrar(tipodato *raiz)
{
    if(raiz!=NULL)
    {
        Borrar(raiz->izq);
        Borrar(raiz->der);
        free(raiz);
    }
}



