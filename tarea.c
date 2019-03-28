#include <stdio.h>
#include <stdlib.h>

typedef struct num
{
    int num;
    struct num *abajo;
    struct num *arriba;
}numero;

void rellenar(numero **inicio,numero **final);
void insertar(numero **inicio,int num1,numero **final);
void insertar_fin(numero **final);
void mostrar(numero **inicio);
void mostrar_reves(numero **final);
void salir(numero **inicio);
void insertar_medio(numero **inicio);

int main(void)
{
    int opcion,num1;
    numero *inicio=NULL;
    numero *final;
    
    rellenar(&inicio,&final);
    system("clear");
    printf("1--insertar num\n2--mostrar nums\n3--mostrar alreves\n4--inserta fin\n5--salir\n");
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
                insertar(&inicio,num1,&final);
            }break;
            case 2:
            {
                mostrar(&inicio);
            }break;
            case 3:
            {
                mostrar_reves(&final);
            }break;
            case 4:
            {
                insertar_fin(&final);
            }break;
            case 5:
            {
                salir(&inicio);
            }break;
        }
    }while(opcion!=5);
}

void rellenar(numero **inicio, numero **final)
{
    numero *nodo,*aux,*aux1;
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
            (*inicio)->arriba=NULL;
            aux=nodo;
            aux1=nodo;
        }else
        {
            
            nodo=malloc(sizeof(numero));
            nodo -> num = numb2;
            aux->abajo=nodo;
            aux=nodo;
            aux->arriba=aux1;
            aux1=aux;
        }
        i++;
    }
    (*final)=aux;
    aux->abajo=NULL;
}

void insertar(numero **inicio,int num1,numero **final)
{
    numero *aux,*temp;
    aux=malloc(sizeof(numero));
    aux->num=num1;
    aux->abajo=*inicio;
    (*inicio)->arriba=aux;
    *inicio=aux;
    (*inicio)->arriba=NULL;
    
}

void mostrar(numero **inicio)
{
    numero *aux;
    
    aux=*inicio;
    while(aux!=NULL)
    {
        printf("%d\n",aux->num);
        aux=aux->abajo;
    }
}

void salir(numero **inicio)
{
    numero *aux,*nodo;
    aux=*inicio;
    nodo=*inicio;
    
    while(aux!=NULL)
    {
        aux=aux->abajo;
        free(nodo);
        nodo=aux;
    }
}

void mostrar_reves(numero **final)
{
    numero *aux;
    
    aux=*final;
    while(aux!=NULL)
    {
        printf("%d\n",aux->num);
        aux=aux->arriba;;
    }
}

void insertar_fin(numero **final)
{
    numero *aux;
    int numeri;
    printf("dame el numero a insertar: ");
    scanf("%d",&numeri);
    
    aux=malloc(sizeof(numero));
    aux->num=numeri;
    
    aux->arriba=*final;
    (*final)->abajo=aux;
    *final=aux;
    aux->abajo=NULL;
}

void insertar_medio(numero **inicio)
{
    int numss;
    numero *aux,*aux1,*aux2;
    
    printf("dame el numero a insertar: ");
    scanf("%d",&numss);
    
    aux=malloc(sizeof(numero));
    aux->num=numss;
    
    aux1=*inicio;
    while(aux1->num==numss)
    {
        aux1=aux1->abajo;
        
    }
}
