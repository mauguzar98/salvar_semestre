#include <stdio.h>
#include <stdlib.h>

typedef struct num
{
    int num;
    struct num *derecha;
    struct num *izquierda;
}numero;

void rellenar(numero **inicio);
void insertar(numero **inicio,int num1);
void mostrar(numero **inicio);
void salir(numero **inicio);

int main(void)
{
    int opcion,num1;
    numero *inicio=NULL;
    
    rellenar(&inicio);
    system("clear");
    printf("1--insertar num\n2--mostrar nums\n3--salir\n");
    do
    {
        printf("dame la opcion correspondiente: ");
        scanf("%d",&opcion);
        
        switch(opcion)
        {
            case 1:
            {
                printf("que numero desea insertar: ");
                scanf("%d",&num1);
                insertar(&inicio,num1);
            }break;
            case 2:
            {
                mostrar(&inicio);
            }break;
            case 3:
            {
                salir(&inicio);
            }break;
        }
    }while(opcion!=3);
}

void rellenar(numero **inicio)
{
    numero *nodo,*aux;
    int i=0,numb,numb2;
    
    printf("cuantos numero va ingresar: ");
    scanf("%d",&numb);
    
    
    while(i<numb)
    {
        printf("dame los valores: ");
        scanf("%d",&numb2);
        if(*inicio==NULL)
        {
            nodo=malloc(sizeof(numero));
            *inicio=nodo;
            (*inicio) -> num = numb2;
            aux=nodo;
        }else
        {
            
            nodo=malloc(sizeof(numero));
            nodo -> num = numb2;
            aux->derecha=nodo;
            aux=nodo;
        }
        i++;
    }
    aux->derecha=NULL;
}

void insertar(numero **inicio,int num1)
{
    numero *aux,*temp;
    aux=malloc(sizeof(numero));
    aux->num=num1;
    aux->derecha=*inicio;
    *inicio=aux;
    
    
}

void mostrar(numero **inicio)
{
    numero *aux;
    
    aux=*inicio;
    while(aux!=NULL)
    {
        printf("%d\n",aux->num);
        aux=aux->derecha;
    }
}

void salir(numero **inicio)
{
    numero *aux,*nodo;
    aux=*inicio;
    nodo=*inicio;
    
    while(aux!=NULL)
    {
        aux=aux->derecha;
        free(nodo);
        nodo=aux;
    }
}
