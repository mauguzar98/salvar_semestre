#include <stdio.h>
#include <stdlib.h>

typedef struct comensales
{
    float bebidas;
    float postres;
    float platos;
    struct comensales *abajo;
}comensal;

void pedir(comensal **inicio);
void consultar(comensal **inicio);
void total(comensal **inicio);
void liberar(comensal *inicio);

int main(void)
{
    int opcion;
    comensal *inicio=NULL;
    
    system("clear");
    do
    {
        printf("\t\tMENU\n");
        printf("opcion1--ingresar consumo\nopcion2--consultar consumo\nopcion3--total de consumos\n");
        printf("dame la opcion correspondiente: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
            {
                pedir(&inicio);
            }break;
            case 2:
            {
                consultar(&inicio);
            }break;
            case 3:
            {
                total(&inicio);
            }break;
            case 4:
            {
                liberar(inicio);
            }break;
        }
    }while(opcion!=4);
}

void pedir(comensal **inicio)
{
    comensal *temp, *temp2;
    temp=(comensal*)malloc(sizeof(comensal));
    printf("Ingrese el monto de bebidas consumido: ");
    scanf("%f", &temp->bebidas);
    printf("Ingrese el monto de platos fuertes consumido: ");
    scanf("%f", &temp->platos);
    printf("Ingrese el monto de postres comsumido: ");
    scanf("%f", &temp->postres);
    
    temp->abajo=NULL;
    
    if(*inicio!=NULL)
    {
        temp2=*inicio;
        while(temp2->abajo!=NULL)
        {
            temp2=temp2->abajo;
        }
        temp2->abajo=temp;
    }
    else
    {
        *inicio=temp;
    }
}

void consultar(comensal **inicio)
{
    comensal *aux;
    int i=1;
    aux=*inicio;
    while(aux!=NULL)
    {
        printf("\ncomensal #%d\n",i);
        printf("bebidas: %0.0f\n",aux->bebidas);
        printf("platos fuertes: %0.0f\n",aux->platos);
        printf("postres: %0.0f\n",aux->postres);
        printf("\n");
        aux=aux->abajo;
        i++;
    }
}

void total(comensal **inicio)
{
    
}

void liberar(comensal *inicio)
{
    comensal *aux;
    aux=inicio;
    while(aux!=NULL)
    {
        inicio=inicio->abajo;
        free(aux);
        aux=inicio;
    }
}
