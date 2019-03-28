#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct lista{//Lista con cuatro apuntadores
  char simbol;
  float prob;
  char contenido[50];
  char binario[50];
  int fin;
  struct lista *ant,*sig,*izq,*der;
}tipolista;

void Insertar(tipolista **Inicio);
void Listar(tipolista *Inicio2);
void Eliminar(tipolista **Inicio);
void Modificar(tipolista **Inicio);
void Copia(tipolista *Inicio,tipolista **Inicio2);
void Generar(tipolista **Inicio);
void Codificar(tipolista *Inicio,tipolista *Inicio2,tipolista **Codificar);
void Decodificar(tipolista *Inicio, tipolista *Inicio2);
void Salir(tipolista *Inicio2,tipolista *Inicio,tipolista *Codificar);
void Menu();


int main ()
{
  int op;
  int time;
  tipolista *Primero=NULL,*Primero2=NULL,*Codi=NULL;
  struct nodo *raiz=NULL;

  for(time=0;time<4;time++)
    {
      printf("Cargando...\n");
      usleep(500000);
      system("clear");
    }

  printf("\tMANUEL MIKEL CABECERA LOPEZ\n\tLAURA MORENO NAVA\n\tGUSTAVO GUTIERREZ MIRANADA\n");
  fpurge(stdin);
  getchar();
  printf("El siguiente programa desplegara un menu con las isguientes opciones:");
  printf("\n\t1.Introducir simbolo (El nuevo símbolo será introducido a una estructura junto con su probabilidad).\n");
  printf("\n\t2.Listar simbolos.(Desplegará en la pantalla todos los símbolos que se encuentran actualmente en la estructura junto con la probabilidad de cada uno)\n");
  printf("\n\t3.Borrar simbolos.(El programa buscara y eliminará este símbolo junto con su probabilidad)\n");
  printf("\n\t4.Generar codigos.(Se generará los códigos de longitud variable para la serie de símbolos que se encuentra en la estructura.)\n");
  printf("\n\t5.Codificar mensaje.(Le asignara codigos a cada uno de los simbolos que el usuario halla seleccionado y generara un solo archivo con el mensaje codificado)\n");
  printf("\n\t6.Decodificar mensaje.(Imprimir el mensaje que envuelve la codificación este se guardara en un archivo)\n");
  printf("\n\t7.Modificar un simbolo(Solicitará al usuario que ingrese el símbolo que desea modificar, el programa buscará dicho símbolo en la estructura y solicitará al usuario que ingrese la nueva probabilidad de este símbolo)\n");
  printf("\n\t8.Salir del programa.(Borra todo el arbol y sale del programa)\n");
  getchar();
  system("clear");
    do
      {
	Menu();
	scanf("%d", &op);
	system("clear");
	switch(op)
	  {
	  case 1:
	    Insertar(&Primero);
	    Copia(Primero,&Primero2);
	    break;
	  case 2:
	    Listar(Primero2);
	    break;
	  case 3:
	    Eliminar(&Primero);
	    break;
	  case 4:
	    Modificar(&Primero);
	    break;
	  case 5:
	    Generar(&Primero);
	    break;
	  case 6:
	    Codificar(Primero,Primero2,&Codi);
	    break;
	  case 7:
	    Decodificar(Primero,Primero2);
	    break;
	  case 8:
	    Salir(Primero2,Primero,Codi);
	    printf("\n\nLista eliminada\n\n");
	    break;
	  default:printf("Opción invalida\n");
	  }
      }while(op!=8);
}
void Menu()
{
  printf("    MENU.\n\n");
  printf("Elige una opcion:\n\n");
  printf("1. Insertar simbolos\n 2. Listar simbolos\n 3. Borrar  simbolo\n 4. Modificar simbolo\n 5. Generar codigos\n 6. Codificar Mensaje\n 7. Decodificar mensaje\n 8. Salir\n\n");
  printf("Introduzca la opcion deseada:");
}
void Insertar(tipolista **Inicio)
{
  float suma=0;
  float pro;
  char sim;
  tipolista *temp,*temp2,*posicion;
  do//Introduce en orden y checa si no acaba con el simbolo (-), si llega a teclear el menos se genera la lista y valida la suma
    {
      temp=(tipolista*)malloc(sizeof(tipolista));
      printf("Introduce tu simbolo,probabilidad (pon (-) para terminar)\n");
      fpurge(stdin);
      scanf("%c,%f",&sim,&pro);
      if(sim!='-')//Ordena en orden
	{
	  temp->simbol=sim;
	  temp->prob=pro;
	  temp->ant=NULL;
	  temp->fin=1;
	  temp->der=NULL;
	  temp->izq=NULL;
	  posicion=*Inicio;
	  if(*Inicio!=NULL)
	    {
	      while((posicion!=NULL) && (temp->prob>posicion->prob))
		{
		  posicion=posicion->sig;
		}
	      if(posicion!=NULL)
		{
		  temp->sig=posicion;
		  posicion->ant=temp;
		  if(posicion!=*Inicio)
		    {
		      temp2=*Inicio;
		      while(temp2->sig!=posicion)
			{
			  temp2=temp2->sig;
			}
		      temp2->sig=temp;
		      temp->ant=temp2;
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
		    {
		      temp2=temp2->sig;
		    }
		  temp2->sig=temp;
		  temp->ant=temp2;
		  temp->sig=NULL;
		}
	    }
	  else
	    {
	      temp->sig=*Inicio;
	      *Inicio=temp;
	    }
	}
    }while(sim!='-');

  temp=*Inicio;

  while(temp!=NULL)
    {
      suma=suma+temp->prob;
      temp=temp->sig;
    }

  if(suma!=100)//Validacion de la suma igual a 100 si no da borra los datos ingresados
    {
      printf("Tus valores no dan 100\n \tIngresa otra vez la lista");
      while(temp!=NULL)
	{
	  *Inicio=temp->sig;
	  free(temp);
	  temp=*Inicio;
	}
      *Inicio=NULL;
    }
}
void Eliminar(tipolista **Inicio)//Elimina un elemnto de la lista y averigua si no da 100 te manda a la funcion modificar
{
  tipolista *temp,*pos,*temp2;
  char sim;
  float suma;
  pos=*Inicio;
  printf("Ingresa el elmento que deseas modificar\n");
  fpurge(stdin);
  scanf("%c",&sim);
  while(pos!=NULL && pos->simbol!=sim)
    {
      pos=pos->sig;
    }
  if(pos!=*Inicio && pos!=NULL &&  pos->sig!=NULL)
    {
      temp=pos->ant;
      temp2=pos->sig;
      temp->sig=temp2;
      temp2->ant=temp;
      free(pos);
    }
  if(pos->sig==NULL && pos!=*Inicio)
    {
      temp=*Inicio;
      while(temp->sig!=pos)
	{
	  temp=temp->sig;
	}
      temp->sig=NULL;
      free(pos);
    }
  if(pos==*Inicio)
    {
      temp=*Inicio;
      *Inicio=temp->sig;
      free(temp);
    }
  if(pos==NULL)
    {
      printf("Ese simbolo no existe\n");
    }
  while(temp!=NULL)
    {
      suma=suma+temp->prob;
      temp=temp->sig;
    }
  if(suma!=100)
    {
      printf("Tus valores no dan 100, tienes que modificar un valor\n");
      Modificar(Inicio);
    }


}
void Modificar(tipolista **Inicio)//Cambia un elemento de la lista y sale de la funcion hasta que se cumpla una sumatoria de 100
{
  tipolista *temp;
  int op;
  char simbolo;
  float suma=0;
  temp=*Inicio;

  printf("Que elemento quieres modificar\n");
  fpurge(stdin);
  scanf("%c",&simbolo);
  while(temp!=NULL && temp->simbol!=simbolo)
    {
      temp=temp->sig;
    }
  if(temp!=NULL)
    {
      do{//Da la opcion a que quieres modificar
      printf("Que deseas moificar\n 1.-Simbolo\n 2.-Porcentaje\n 3.-Salir\n");
      fpurge(stdin);
      scanf("%d",&op);
      switch(op)
	{
	case 1:
	  printf("Ingresa el nuevo simbolo\n");
	  fpurge(stdin);
	  scanf("%c",&temp->simbol);
	  break;
	case 2:
	  printf("Ingresa la nueva probabilidad\n");
	  fpurge(stdin);
	  scanf("%f",&temp->prob);
	  break;
	case 3:
	  printf("Saliste\n");
	  break;
	default:printf("Opcion no valida...\n");
	}
      }while(op!=3);
    }
  if(temp==NULL)
    {
      printf("EL numero no existe\n");
    }
  while(temp!=NULL)
    {
      suma=suma+temp->prob;
      temp=temp->sig;
    }
  if(suma!=100)
    {
      printf("Tus valores no dan 100\n");
      Modificar(Inicio);
    }

}
void Salir(tipolista *Inicio2,tipolista *Inicio,tipolista *Codificar)//Borra las listas y el arbol
{
  tipolista *temp,*temp1,*temp2;

  temp=Inicio2;
  while(temp!= NULL)
    {
      Inicio=temp->sig;
      free(temp);
      temp=Inicio;
    }

  temp2=Codificar;
  while(temp2!= NULL)
    {
      Codificar=temp2->sig;
      free(temp2);
      temp2=Codificar;
    }

  temp1=Inicio;
  if(temp1!=NULL)
    {
      Salir(Inicio2,Inicio->izq,Codificar);
      Salir(Inicio2,Inicio->der,Codificar);
      free(temp);
    }
}
void Listar(tipolista *Inicio2)//Imprime la lista en orden
{
  tipolista *temp;
  temp=Inicio2;
  while(temp!=NULL)
    {
      printf("%c porcentaje: %.2f\n",temp->simbol,temp->prob);
      temp=temp->sig;
    }
}
void Copia(tipolista *Inicio,tipolista **Inicio2)//Genera una copia de la lista para usarla en un futura en la funcion decodificar
{
  tipolista *temp,*temp2,*temp3;
  temp=Inicio;
  while(temp!=NULL)
    {
      temp2=(tipolista*)malloc(sizeof(tipolista));
      temp2->simbol=temp->simbol;
      temp2->prob=temp->prob;
      temp2->sig=NULL;
      if(*Inicio2!=NULL)
	{
	  temp3=*Inicio2;
	  while(temp3->sig!=NULL)
	    {
	      temp3=temp3->sig;
	    }
	  temp3->sig=temp2;
	}
      else
	{
	  *Inicio2=temp2;
	}
      temp=temp->sig;
    }
}
void Generar(tipolista **Inicio)//Genera el arbol a partir de la lista ingresada
{
  tipolista *nuevo,*pos,*pos2,*posicion,*temp2;
  int si=0;
  while(si!=1)//Bandera para saber si ya acabo de ordenar
    {
      pos=*Inicio;
      pos2=pos->sig;
      nuevo=(tipolista*)malloc(sizeof(tipolista));
      nuevo->prob=pos->prob+pos2->prob;
      strcat(nuevo->contenido,&pos->simbol);
      strcat(nuevo->contenido,&pos2->simbol);
      strcat(nuevo->contenido,pos->contenido);
      strcat(nuevo->contenido,pos2->contenido);
      nuevo->izq=pos;
      nuevo->der=pos2;
      printf("%.2f\n",nuevo->prob);
      printf("%c=%.2f,",(nuevo->izq)->simbol,(nuevo->izq)->prob);
      printf("%c=%.2f\n",(nuevo->der)->simbol,(nuevo->der)->prob);
      printf("letras del nodo %s\n",nuevo->contenido);
      *Inicio=pos2->sig;
      pos->sig=NULL;
      pos2->sig=NULL;
      nuevo->ant=NULL;
      posicion=*Inicio;
      if(*Inicio!=NULL)
	{
	  while((posicion!=NULL) && (nuevo->prob>posicion->prob))
	    {
	      posicion=posicion->sig;
	    }
	  if(posicion!=NULL)
	    {
	      nuevo->sig=posicion;
	      posicion->ant=nuevo;
	      if(posicion!=*Inicio)
		{
		  temp2=*Inicio;
		  while(temp2->sig!=posicion)
		    {
		      temp2=temp2->sig;
		    }
		  temp2->sig=nuevo;
		  nuevo->ant=temp2;
		}
	      else
		{
		  *Inicio=nuevo;
		}
	    }
	  else
	    {
	      temp2=*Inicio;
	      while(temp2->sig!=NULL)
		{
		  temp2=temp2->sig;
		}
	      temp2->sig=nuevo;
	      nuevo->ant=temp2;
	      nuevo->sig=NULL;
	    }
	}
      else
	{
	  si=1;
	  nuevo->sig=*Inicio;
	  *Inicio=nuevo;
	}
    }
}
void Codificar(tipolista *Inicio,tipolista *Inicio2,tipolista **Codificar)//Genera los codigos para cada simbolo y su probabilidad en codigo binario
//Recorre el arbol y a partir de condicion y identificadores en cada codigo toma la desicion de irse a la derecha o a la izquierda y asigna un 0 para la izquierda o un 1 a la derecha
{

  FILE *archivo,*archivo1;
  char nombre[50],nombre1[50];
  int si=0,s=0,i,flag=0;
  tipolista *temp,*raiz,*nuevo;

  temp=Inicio2;
  raiz=Inicio;

  while(temp!=NULL)
  {
    nuevo=(tipolista *)malloc(sizeof(tipolista));
    nuevo->simbol=temp->simbol;
    for(int i=0;i<50;i++)
      {
	nuevo->binario[i]='\0';
      }
    do{
      si=3;
      for(i=0;i<strlen((raiz->izq)->contenido);i++)
	{
	  if((raiz->izq)->contenido[i]==temp->simbol)
	    {
	      si=0;
	    }
	}
      for(i=0;i<strlen((raiz->der)->contenido);i++)
	{
	  if((raiz->der)->contenido[i]==temp->simbol)
	    {
	      si=1;
	    }
	}
      if(si==3)
	{
	  if((raiz->izq)->simbol==temp->simbol)
	    {
	      strcat(nuevo->binario,"0");
	      s=1;
	    }
	  if((raiz->der)->simbol==temp->simbol)
	    {
	      strcat(nuevo->binario,"1");
	      s=1;
	    }
	}
      if(si==0)
	{
	  raiz=raiz->izq;
	  strcat(nuevo->binario,"0");
	  if(&(raiz->izq)->simbol== NULL || &(raiz->der)->simbol==NULL && strcmp(&(raiz->izq)->simbol,&temp->simbol)==0)
	    {
	      s=1;
	    }
	}
      if(si==1)
	{
	  raiz=raiz->der;
	  strcat(nuevo->binario,"1");
	  if(&(raiz->izq)->simbol== NULL || &(raiz->der)->simbol==NULL && strcmp(&(raiz->der)->simbol,&temp->simbol)==0)
	    {
	      s=1;
	    }
	}

    }while(s!=1);
    nuevo->sig=*Codificar;
    *Codificar=nuevo;
    temp=temp->sig;
    raiz=Inicio;
    s=0;
  }

  temp=*Codificar;
  while(temp!=NULL)
    {
      printf("%c binario: %s\n",temp->simbol,temp->binario);
      temp=temp->sig;
    }
  do
    {
      printf("Introduce el nombre del archivo a codificar\n");
      fpurge(stdin);
      gets(nombre);
      archivo=fopen(nombre,"rt");
      if(archivo==NULL)
	{
	  printf("El archivo no existe\n");
	}
    }while(archivo==NULL);

  char c;
  char codificacion[100];

  temp=*Codificar;
  while(!feof(archivo))
    {
      temp=*Codificar;
      c=fgetc(archivo);
      while(temp!=NULL)
	{
	  if(c==temp->simbol)
	  {
	    strcat(codificacion,temp->binario);
	  }
	  temp=temp->sig;
	}
    }
    printf("Codificacion:%s\n",codificacion);
    fclose(archivo);

    printf("Ingresa el nombre del archivo para guardar el mensaje codificado \n");
    fpurge(stdin);
    gets(nombre1);
    archivo1=fopen(nombre1,"wt");
    fputs(codificacion,archivo1);
    fclose(archivo1);

}
void Decodificar(tipolista *Inicio, tipolista *Inicio2)//abre el archivo para extraer el mensaje en binario, si es un 1 se va a la derecha y si es un 0 se va a la izquierda y acaba cuando encuentra un simbolo para luego regresarse al inicio
{
  FILE *archivo,*archivo1;
  char nombre[50],nombre1[50];
  tipolista *temp;
  int  flag=0,flag2=0,i=0,j;
  char b,simbol;
  unsigned char deco[100];

  for(j=0;j<100;j++)
    {
      deco[0]='\0';
    }

  do
    {
      printf("Ingresa el nombre del archivo a descodificar\n");
      fpurge(stdin);
      gets(nombre);
      archivo=fopen(nombre,"rt");
      if(archivo==NULL)
	{
	  printf("El archivo no existe\n");
	}
    }while(archivo==NULL);

  temp=Inicio;
  while(!feof(archivo))
    {
      temp=Inicio;
      do
	{
	  b=fgetc(archivo);
	  if(b=='0')
	    {
	      temp=temp->izq;
	      if(temp->fin==1)
		{
		  flag=1;
		  flag2=1;
		}
	    }
	  if(b=='1')
	    {
	      temp=temp->der;
	      if(temp->fin==1)
		{
		  flag=1;
		  flag2=1;
		}
	    }
	  if(b!='1' && b!='0')
	    {
	      flag=1;
	    }
	}while(flag!=1);
      flag=0;
      if(flag2==1)
	{
	  strcat(&deco[i],&temp->simbol);
	  i++;
	}
      flag2=0;
    }

  printf("decodificacion: ");
  puts(deco);
  printf("\n");
  fclose(archivo);

  printf("Ingresa el nombre del archivo para guardar el mensaje decodificado \n");
  fpurge(stdin);
  gets(nombre1);
  archivo1=fopen(nombre1,"wt");
  fputs(deco,archivo1);
  fclose(archivo1);
}
