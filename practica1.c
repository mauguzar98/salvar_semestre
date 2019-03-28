#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void Leerarchivo(int *f, int *c, char filenames[30], int *k);
void Negativo(int f, int c, char filenames[30], int k);
void Ecualizacion(int f, int c, char filenames[30], int k);
void Reducir(int f, int c, char filenames[30], int k);
void Ampliar(int f, int c, char filenames[30], int k);

int main (void)
{
    int f, c, opcion, k;//donde f es filas y columnas es c, y k es numero de espacios
    char filenames[30];
    system("clear");
    printf("\n\n\t\t\tElaborado por mauricio guzman\n");
    printf("presione enter para continuar: ");
    getchar();
    printf("Objetivo se realiza un procesador digital de imagenes que cumple con 4 funciones ecualizar, darnegativos, ampliar y reducir\n");
    printf("presione enter para continuar: ");
    getchar();
    system("clear");
    printf("\tMENU");
    printf("\n1. Negativo de la imagen\n2. Ecualizar la imagen\n3. Reducir la imagen\n4. Ampliar la imagen\n5. Salir\n");

    do
    {
        printf("dame la opcion correspondiente: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
            {
                Leerarchivo(&f, &c, filenames, &k);
                Negativo(f, c, filenames, k);
            }break;
            case 2:
            {
                Leerarchivo(&f, &c, filenames, &k);
                Ecualizacion(f, c, filenames, k);
            }break;
            case 3:
            {
                Leerarchivo(&f, &c, filenames, &k);
                Reducir(f, c, filenames, k);
            }break;
            case 4:
            {
                Leerarchivo(&f, &c, filenames, &k);
                Ampliar(f, c, filenames, k);
            }break;
            case 5:
            {
                printf("bye\n");
            }break;
            default:
            {
                printf("opcion incorrecta\n");
            }break;
        }
    }while(opcion!=5);
}


void Leerarchivo(int *f, int *c, char filenames[30], int *k)
{
    int espacios=0;
    FILE *archivo;
    char  encabezado[20];
    *k=0;
    printf("Escribe el nombre del archivo (sin extension): ");
    fpurge(stdin);
    gets(filenames);
    strcat(filenames,".raw");
    archivo=fopen(filenames, "rb");
    
    if(archivo!=NULL)//se valida que exista el archivo.
    {
        while(espacios<4)
        {
            fread(&encabezado[*k], sizeof(char), 1, archivo);
            if(encabezado[*k]==' ')
                espacios++;
            (*k)++;
        }
        sscanf(encabezado, "P5 %d %d 255 ", c, f);
        fclose(archivo);
    }
    else
    {
        printf("Error: el archivo no existe");
    }
}

void Negativo(int f, int c, char filenames[30], int k)
{
    unsigned char **Imagen, **Negativa;
    int i, j, h=0, s=0,x=0;
    char name[30];
    FILE *archivo, *archivo2;
    
    
    archivo=fopen(filenames, "rb");
    fseek(archivo, k, SEEK_SET); //se recorre para empezar a leer el archivo
    Imagen=(unsigned char**)malloc(sizeof(unsigned char*)*f);
    while(h<f)
    {
        Imagen[h]=(unsigned char*)malloc(sizeof(unsigned char)*c);
        h++;
    } //asigna espacio de memoria a la imagen
    for(i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            fread(&Imagen[i][j], sizeof(unsigned char), 1, archivo);
        }
    }//se lee el archivo
    fclose(archivo);
    Negativa=(unsigned char**)malloc(sizeof(unsigned char*)*f);
    while(s<f)
    {
        Negativa[s]=(unsigned char*)malloc(sizeof(unsigned char)*c);
        s++;
    }//se crea la otra amtriz para poder gurdar la nueva imagen
    
    for (i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            Negativa[i][j]=Imagen[i][j]*(-1)+255;
        }
    }
    
    printf("Escribe el nombre del nuevo archivo (sin extension): ");
    fpurge(stdin);
    gets(name);
    strcat(name,".pgm");
    archivo2=fopen(name, "wt");
    fprintf(archivo2, "P5 %d %d 255 ", c, f);
    for(i=0; i<f; i++)
    {
        for (j=0; j<c; j++)
        {
            fprintf(archivo2, "%c", Negativa[i][j]); //copia al archivo los pixeles
        }
    }
    fclose(archivo2);
    
    
    for(i=0; i<f; i++)
    {
        free(Imagen[i]);
    }
    
    free(Imagen);
    
    for(i=0; i<f; i++)
    {
        free(Negativa[i]);
    }
    
    free(Negativa); //borra el espacio de memoria dinamico
}


void Ecualizacion(int f, int c, char filenames[30], int k)
{
    char name[30];
    int i, j, h=0, Mayor=0, Menor=9999, s=0;
    float m, b;
    
    FILE *archivo, *archivo2;
    unsigned char **Imagen, **Ecualizada;
    archivo=fopen(filenames, "rb");
    fseek(archivo, k, SEEK_SET);
    
    Imagen=(unsigned char**)malloc(sizeof(unsigned char*)*f);
    while(h<f)
    {
        Imagen[h]=(unsigned char*)malloc(sizeof(unsigned char)*c);
        h++;
    }//crea el espacio de memoria a imagen
    for(i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            fread(&Imagen[i][j], sizeof(unsigned char), 1, archivo);
        }
    }//lee la imagen
    fclose(archivo);
    Ecualizada=(unsigned char**)malloc(sizeof(unsigned char*)*f);
    while(s<f)
    {
        Ecualizada[s]=(unsigned char*)malloc(sizeof(unsigned char)*c);
        s++;
    }//asigna el espacio de memoria para ecualizada
    for (i=0; i<f; i++)//encuentra el menor y el mayor
    {
        for (j=0; j<c; j++)
        {
            if(Imagen[i][j]>Mayor)
                Mayor=Imagen[i][j];
            if(Imagen[i][j]<Menor)
                Menor=Imagen[i][j];
        }
    }
    
    m=(255)/(Mayor-Menor);
    b=255-(m*Mayor);
    
    for(i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            Ecualizada[i][j]=(m*Imagen[i][j])+b;
        }
    }
    printf("Escribe el nombre del nuevo archivo (sin extension): ");
    fpurge(stdin);
    gets(name);
    strcat(name,".pgm");
    archivo2=fopen(name, "wt");
    fprintf(archivo2, "P5 %d %d 255 ", c, f);
    for(i=0; i<f; i++)
    {
        for (j=0; j<c; j++)
        {
            fprintf(archivo2, "%c", Ecualizada[i][j]); //graba ecualizada al archivo
        }
    }
    fclose(archivo2);
    for(i=0; i<f; i++)
    {
        free(Imagen[i]);
    }
    free(Imagen);
    for(i=0; i<f; i++)
    {
        free(Ecualizada[i]);
    }
    free(Ecualizada); //libera el espacio de memoria de imagen y de ecualizada
}

void Reducir(int f, int c, char filenames[30], int k)
{
    FILE *archivo, *archivo2;
    int i, j, h=0, s=0;
    char name[30];
    unsigned char **Imagen, **Reducida;
    archivo=fopen(filenames, "rb");
    fseek(archivo, k, SEEK_SET); //se recorre hasta donde acaba el encabezado para empezar a leer los pixeles
    Imagen=(unsigned char**)malloc(sizeof(unsigned char*)*f);
    while(h<f)
    {
        Imagen[h]=(unsigned char*)malloc(sizeof(unsigned char)*c);
        h++;
    }//asigna espacio a imagen
    for(i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            fread(&Imagen[i][j], sizeof(unsigned char), 1, archivo);//lee la imagen
        }
    }
    fclose(archivo);
    Reducida=(unsigned char**)malloc(sizeof(unsigned char*)*(f/2));
    while(s<(f/2))
    {
        Reducida[s]=(unsigned char*)malloc(sizeof(unsigned char)*(c/2));
        s++;
    }//asigna espacio a reducida
    for (i=0; i<f; i++)
    {
        for (j=0; j<c; j++)
        {
            if(i==0 && j==0)
            {
                Reducida[i][j]=Imagen[i][j];
            }
            if(i==0 && j%2==0)
            {
                Reducida[i][j/2]=Imagen[i][j];
            }
            if(i%2==0 && j==0)
            {
                Reducida[i/2][j]=Imagen[i][j];
            }
            if(i%2==0 && j%2==0)
            {
                Reducida[i/2][j/2]=Imagen[i][j];
            }
        }
    }
    printf("Escribe el nombre del nuevo archivo (sin extension): ");
    fpurge(stdin);
    gets(name);
    strcat(name,".pgm");
    archivo2=fopen(name, "wt");
    fprintf(archivo2, "P5 %d %d 255 ", (c/2), (f/2));
    for(i=0; i<(f/2); i++)
    {
        for (j=0; j<(c/2); j++)
        {
            fprintf(archivo2, "%c", Reducida[i][j]); //graba reducida al archivo
        }
    }
    fclose(archivo2);
    for(i=0; i<f; i++)
    {
        free(Imagen[i]);
    }
    free(Imagen);
    for (i=0; i<(f/2); i++)
    {
        free(Reducida[i]);
    }
    free(Reducida); //libera el espacio de memoria utilizado
}

void Ampliar(int f, int c, char filenames[30], int k)
{
    int i, j, h=0, s=0;
    FILE *archivo, *archivo2;
    char name[30];
    unsigned char **Imagen, **Ampliada;
    archivo=fopen(filenames, "rb");
    fseek(archivo, k, SEEK_SET);//se recorre hasta a donde acaba el encabezado para empezar a leer la imagen
    Imagen=(unsigned char**)malloc(sizeof(unsigned char*)*f);
    while(h<f)
    {
        Imagen[h]=(unsigned char*)malloc(sizeof(unsigned char)*c);
        h++;
    }//asigna espacio a la imagen
    for(i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            fread(&Imagen[i][j], sizeof(unsigned char), 1, archivo); //lee la imagen
        }
    }
    fclose(archivo);
    
    Ampliada=(unsigned char**)malloc(sizeof(unsigned char*)*(2*f));
    while(s<(2*f))
    {
        Ampliada[s]=(unsigned char*)malloc(sizeof(unsigned char)*(2*c));
        s++;
    }//asigna espacio a ampliada para la nueva imagen
    for (i=0; i<f; i++)
    {
        for(j=0; j<c; j++)
        {
            if((i==0) &&(j==0))
            {
                Ampliada[i][j]=Imagen[i][j];
                Ampliada[i+1][j]=Imagen[i][j];
                Ampliada[i][j+1]=Imagen[i][j];
                Ampliada[i+1][j+1]=Imagen[i][j];
            }
            if((i==0) && (j>0))
            {
                Ampliada[i][j*2]=Imagen[i][j];
                Ampliada[i][(j*2)+1]=Imagen[i][j];
                Ampliada[i+1][j*2]=Imagen[i][j];
                Ampliada[i+1][(j*2)+1]=Imagen[i][j];
            }
            if((i>0) && (j==0))
            {
                Ampliada[i*2][j]=Imagen[i][j];
                Ampliada[(i*2)+1][j]=Imagen[i][j];
                Ampliada[i*2][j+1]=Imagen[i][j];
                Ampliada[(i*2)+1][j+1]=Imagen[i][j];
            }
            if((i>0) && (j>0))
            {
                Ampliada[i*2][i*2]=Imagen[i][j];
                Ampliada[(i*2)+1][j*2]=Imagen[i][j];
                Ampliada[i*2][(j*2)+1]=Imagen[i][j];
                Ampliada[(i*2)+1][j*2+1]=Imagen[i][j];
            }
        }
    }
    
    printf("Escribe el nombre del nuevo archivo (sin extension): ");
    fpurge(stdin);
    gets(name);
    strcat(name,".pgm");
    archivo2=fopen(name, "wt");
    fprintf(archivo2, "P5 %d %d 255 ", 2*c, 2*f);
    for(i=0; i<f*2; i++)
    {
        for (j=0; j<c*2; j++)
        {
            fprintf(archivo2, "%c", Ampliada[i][j]);//graba ampliada al archivo
        }
    }
    fclose(archivo2);
    for(i=0; i<f; i++)
    {
        free(Imagen[i]);
    }
    free(Imagen);
    for(i=0; i<f*2; i++)
    {
        free(Ampliada[i]);
    }
    free(Ampliada);//libera el espacio de memoria utilizado
}

