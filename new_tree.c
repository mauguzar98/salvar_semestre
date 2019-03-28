#include<stdio.h>
#include<stdlib.h>

typedef struct arbol
{
    char letra;
    struct arbol *der, *izq;
}tipodato;

void Insertar(tipodato **raiz, char letra);
void Imprimir(tipodato *raiz);
void Nodos(tipodato *raiz, int *nodos);
void Altura(tipodato *raiz, int *altura);
void Hojas(tipodato *raiz, int *hojas);
void Borrar(tipodato *raiz);

int main(void)
{
    FILE *Archivo;
    tipodato *raiz=NULL;
    int opc, nodos=0, hojas=0, altura=0;
    char letra;
    char NombreArchivo[15];
    printf("Escribe el nombre del archivo (con extension): ");
    gets(NombreArchivo);
    strcat(NombreArchivo."bin");
    Archivo=fopen(NombreArchivo, "rt");
    if(Archivo!=NULL)
    {
        while(fscanf(Archivo, "%c\n", &letra)==1)
        {
            Insertar(&raiz, letra);
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
        printf("Menu:\n1. Imprimir en orden\n2. Numero de nodos\n3. Altura del arbol\n4. Numero de hojas\n5. Salir\n");
        scanf("%d",&opc);
        switch (opc)
        {
            case 1:
                Imprimir(raiz);
                break;
            case 2:
                Nodos(raiz, &nodos);
                printf("El numero de nodos es %d\n", nodos);
                break;
            case 3:
                Altura(raiz, &altura);
                printf("La altura es %d\n", altura);
                break;
            case 4:
                Hojas(raiz, &hojas);
                printf("El numero de hojas es %d\n", hojas);
                break;
            case 5:
                Borrar(raiz);
                break;
            default:
                printf("No existe esa opcion\n");
                break;
        }
    }while(opc!=5);
}

void Insertar(tipodato **raiz, char letra)
{
    tipodato *avanza, *temp;
    avanza=*raiz;
    temp=(tipodato*)malloc(sizeof(tipodato));
    temp->letra=letra;
    temp->izq=NULL;
    temp->der=NULL;
    while(avanza!=NULL)
    {
        if(letra>avanza->letra)
        {
            if(avanza->der!=NULL)
            {
                avanza=avanza->der;
            }
            else
            {
                avanza->der=temp;
                return;
            }
        }
        if(letra<=avanza->letra)
        {
            if(avanza->izq!=NULL)
            {
                avanza=avanza->izq;
            }
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
void Imprimir(tipodato *raiz)
{
    if(raiz!=NULL)
    {
        Imprimir(raiz->izq);
        printf("%c\n", raiz->letra);
        Imprimir(raiz->der);
    }
}

void Nodos(tipodato *raiz, int *nodos)
{
    if(raiz!=NULL)
    {
        Nodos(raiz->izq, nodos);
        (*nodos)++;
        Nodos(raiz->der, nodos);
    }
}
void Altura(tipodato *raiz, int *altura)
{
    if(raiz!=NULL)
    {
        Altura(raiz->izq, altura);
        if((raiz->der!=NULL)||(raiz->izq!=NULL))
            (*altura)++;
        Altura(raiz->der, altura);
    }
}

void Hojas(tipodato *raiz, int *hojas)
{
    if(raiz!=NULL)
    {
        Hojas(raiz->izq, hojas);
        if((raiz->der==NULL)&&(raiz->izq==NULL))
            (*hojas)++;
        Hojas(raiz->der, hojas);
    }
}

void Borrar(tipodato *raiz)
{
    if (raiz!=NULL)
    {
        Borrar(raiz->izq);
        Borrar(raiz->der);
        free(raiz);
    }
}
