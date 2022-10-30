#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "Astronauta.h"

//F U N C I O N E S   D E   A S T R O N A U T A

Astronauta crearAstronautaManual(int idRecibido)
{
    Astronauta nuevo;

    printf("\nINGRESE LOS DATOS DEL ASTRONAUTA A INGRESAR");

    nuevo.id = idRecibido;

    printf("\nNOMBRE: ");
    fflush(stdin);
    gets(nuevo.nombre);
    strupr(nuevo.nombre);

    printf("APELLIDO: ");
    fflush(stdin);
    gets(nuevo.apellido);
    strupr(nuevo.apellido);

    printf("APODO: ");
    fflush(stdin);
    gets(nuevo.apodo);
    strupr(nuevo.apodo);

    nuevo.edad = IngresarEdad();

    printf("NACIONALIDAD: ");
    fflush(stdin);
    gets(nuevo.nacionalidad);
    strupr(nuevo.nacionalidad);

    printf("ESPECIALIDAD: ");
    fflush(stdin);
    gets(nuevo.especialidad);
    strupr(nuevo.especialidad);

    nuevo.horasDeVuelo = ingresarHsDeVuelo();

    nuevo.misiones = 0;

    nuevo.horasEEI = IngresarHsEEI();

    nuevo.estado = 1;

    nuevo.enMision = 0;

    return nuevo;
}

int IngresarEdad()//FN PARA VALIDAR LA EDAD DEL ASTRONAUTA Q SE CARGA
{
    int edad=-1;
    while(edad<20 || edad>65)
    {
        printf("INGRESE EDAD:");
        scanf("%d",&edad);
        if(edad<20 || edad>65)
            printf("\nLA EDAD INGRESADA DEBE ESTAR DENTRO DEL RANGO 20 A 65... \nPorfavor vuelva a ingresar...\n");
    }
    return edad;
}
int ingresarHsDeVuelo()//SOLICITA, VALIDA Y RETORNA UN ENTERO PARA LAS HS DE VUELO DE ASTRO
{
    int hs=-1;
    while(hs<0 || hs>1000)
    {
        printf("INGRESE HS DE VUELO ACUMULADAS:\n");
        scanf("%d",&hs);
        if(hs<0 || hs>1000)
            printf("\nEL VALOR INGRESADO DEBE ESTAR DENTRO DEL RANGO 0 A 1000... \nPorfavor vuelva a ingresar...\n");
    }
    return hs;
}
int IngresarHsEEI()//SOLICITA, VALIDA Y RETORNA DATO ENTERO DE HS EN LA EEII
{
    int hs=-1;
    while(hs<0 || hs>10000)
    {
        printf("INGRESE HORAS EN LA ESTACION ESPACIAL INTERNACIONAL:\n");
        scanf("%d",&hs);
        if(hs<0 || hs>10000)
            printf("\nLA CANTIDAD DE HORAS DEBE ESTAR EN  UN RANGO DE 1 A 10000... \nPorfavor vuelva a ingresar...\n");
    }
    return hs;
}

void mostrarAstronauta(Astronauta recibido)//MUESTRA ASTRONAUTA
{
    printf("ID: %i", recibido.id);

    printf("\nNOMBRE: ");
    puts(recibido.nombre);

    printf("APELLIDO: ");
    puts(recibido.apellido);

    printf("APODO: ");
    puts(recibido.apodo);

    printf("EDAD: %i", recibido.edad);

    printf("\nNACIONALIDAD: ");
    puts(recibido.nacionalidad);

    printf("ESPECIALIDAD: ");
    puts(recibido.especialidad);

    printf("HORAS DE VUELO: %i", recibido.horasDeVuelo);

    recibido.misiones = 0;
    printf("\nMISIONES REALIZADAS: %i", recibido.misiones);

    printf("\nHORAS EN LA EEI: %i", recibido.horasEEI);

    printf("\nESTADO: ");
    if(recibido.estado == 1)
        puts("ACTIVO");
    else
        puts("INACTIVO");

    printf("\n------------\n");
}


//F U N C I O N E S   D E   A R B O L
nodoAstroArbol* inicArbol()//RETORNA NULL
{
    return NULL;
}
nodoAstroArbol* crearNodoArbol(Astronauta recibido)//CREA UN NODO CON EL DATO ASTRONAUTA, PARA EL ARBOL
{
    nodoAstroArbol* nuevo = malloc(sizeof(nodoAstroArbol));

    nuevo->dato = recibido;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

nodoAstroArbol* agregarOrdenadoArbol(nodoAstroArbol* raiz, nodoAstroArbol* nuevo) //CARGA EL ARBOL ORDENADO POR ID
{
    if(!raiz)
        raiz = nuevo;
    else
    {
        if((nuevo->dato).id < (raiz->dato).id)
            raiz->izq = agregarOrdenadoArbol(raiz->izq, nuevo);
        else
            raiz->der = agregarOrdenadoArbol(raiz->der, nuevo);
    }

    return raiz;
}

void mostrarArbolInOrder(nodoAstroArbol* raiz)//MUESTRA TODOS LOS ASTRONAUTAS EN ORDEN DE ID DEL ARBOL
{
    if(raiz)
    {
        mostrarArbolInOrder(raiz->izq);
        mostrarAstronauta(raiz->dato);
        mostrarArbolInOrder(raiz->der);
    }
}

void mostrarActivosArbol(nodoAstroArbol* raiz)//MUESTRA LOS ASTRONAUTAS ACTIVOS
{
    if(raiz)
    {
        mostrarActivosArbol(raiz->izq);
        if(raiz->dato.estado==1)
            mostrarAstronauta(raiz->dato);
        mostrarActivosArbol(raiz->der);
    }
}
void mostrarDisposiblesArbol(nodoAstroArbol* raiz)//MUESTRA LOS ASTRONAUTAS DISPONIBLES
{
    if(raiz)
    {
        mostrarDisposiblesArbol(raiz->izq);
        if(raiz->dato.enMision==0 && raiz->dato.estado==1)
            mostrarAstronauta(raiz->dato);
        mostrarDisposiblesArbol(raiz->der);
    }
}
void mostrarBajasArbol(nodoAstroArbol* raiz)//MUESTRA LOS ASTRONAUTAS EN BAJA
{
    if(raiz)
    {
        mostrarBajasArbol(raiz->izq);
        if(raiz->dato.estado==2)
            mostrarAstronauta(raiz->dato);
        mostrarBajasArbol(raiz->der);
    }
}
int existeAstroEnArbol(nodoAstroArbol* raiz, int idBuscado)//RETORNA UN ENTERO SI EXISTE ELDATO CARGADO ID
{
    int existe = 0;
    if(raiz)
    {
        if(raiz->dato.id == idBuscado)
            existe = 1;
        else if(idBuscado < raiz->dato.id)
            existe = existeAstroEnArbol(raiz->izq, idBuscado);
        else
            existe = existeAstroEnArbol(raiz->der, idBuscado);
    }
    return existe;
}
int enMisionAstroEnArbol(nodoAstroArbol* raiz, int idBuscado)// RETORNA UN ENTERO PARA SABER SI EL ASTRONAUTA ESTA EN MISION
{
    int ocupado = 0;

    if(raiz)
    {
        if(raiz->dato.id == idBuscado && raiz->dato.enMision==1)
            ocupado = 1;
        else if(idBuscado < raiz->dato.id)
            ocupado = enMisionAstroEnArbol(raiz->izq, idBuscado);
        else
            ocupado = enMisionAstroEnArbol(raiz->der, idBuscado);
    }
    return ocupado;
}

nodoAstroArbol* buscarAstroArbolPorId(nodoAstroArbol* raiz, int idBuscado)//BUSCA UN ASTRONAUTA Y LO RETORNA DEL ARBOL
{
    nodoAstroArbol* nodoEncontrado = NULL;
    if(raiz)
    {
        if(raiz->dato.id == idBuscado)
            nodoEncontrado = raiz;
        else
        {
            nodoEncontrado = buscarAstroArbolPorId(raiz->izq, idBuscado);
            if(!nodoEncontrado)
                nodoEncontrado = buscarAstroArbolPorId(raiz->der, idBuscado);
        }
    }

    return nodoEncontrado;
}
void bajaAstronauta(nodoAstroArbol * arbol,int id)//DA DE BAJA UN ASTRONAUTA DEL ARBOL
{
    nodoAstroArbol * Buscado=inicArbol();
    if(id==-1)
    {
        printf("\nINGRESE EL ID DEL ASTRONAUTA:\n");
        scanf("%d",&id);
    }
    Buscado=buscarAstroArbolPorId(arbol,id);
    mostrarAstronauta(Buscado->dato);
    if(Buscado && Buscado->dato.estado==1)
    {
        char seguir = 'n';
        printf("\nDESEA DAR DE BAJA ESTE ASTRONAUTA? (s/n)");
        fflush(stdin);
        scanf("%c", &seguir);
        if(seguir == 's')
        {
            Buscado->dato.estado=2;
            printf("\nEL ASTRONAUTA SE DIO DE BAJA CON EXITO\n");
            mostrarAstronauta(Buscado->dato);
            system("pause");
        }
    }

    else if(Buscado && Buscado->dato.estado==2)
        printf("nEL ASTRONAUTA YA SE ENCUENTRA EN ESTADO DE BAJA...\n");
    else
        printf("\nNO SE ENCONTRO EL ASTRONAUTA...\n");

}
void actualizarAstronautasPostMision(int T[],int validos,nodoAstroArbol * arbol)//CAMBIA DATOS DE LA TRIPULACION EN EL ARBOL
{
    printf("\nACTUALIZACION DE TRIPULACION:\n");
    nodoAstroArbol * actualizado=inicArbol();
    for(int i=0; i<validos; i++)
    {
        actualizado=buscarAstroArbolPorId(arbol,T[i]);
        modificarAstronauta(arbol,T[i]);
        actualizado->dato.enMision=0;
        printf("\nCARGADO...\n");


    }
}


void modificarAstronauta(nodoAstroArbol * arbol, int id)//MODIFICA LOS DATOS DE ASTRONAUTA, RECIBE UN ENTERO Y ACTUA DE ACUERDO A LA CIRCUNSTANCIA
{
    int opcion=-1;//EL CASO DE -1 ES POR EL LLAMADO DESDE EL MENU ASTRONAUTA, LOS DEMAS SON ID RECIBIDOS DESDE LA FUNCION Q ACTUALIZA EL ARREGLO DE LA MISION
    nodoAstroArbol * modificado=inicArbol();
    if(id<0)
    {
        printf("\nINGRESE EL ID DEL ASTRONAUTA:\n");
        scanf("%d",&id);
    }
    modificado=buscarAstroArbolPorId(arbol,id);
    if(modificado && modificado->dato.estado == 1)
    {
        mostrarAstronauta(modificado->dato);
        do
        {
            printf("\n1.INGRESAR NUEVO REGISTRO DE HORAS DE VUELO:\n2.INGRESAR NUEVO REGISTRO DE HS EN LA ESTACION ESPACIAL INTERNACIONAL:\n3.SALIR\n");
            fflush(stdin);
            scanf("%d",&opcion);

            switch(opcion)
            {
            case 1:
                aumentarHsVueloAstronauta(modificado);
                break;
            case 2:
                aumentarHsEEI(modificado);
                break;
            }

        }
        while(opcion!=3);

    }
    else if(modificado && modificado->dato.estado == 2)
        printf("\nEL ASTRONAUTA ESTA RETIRADO\n");
    else
        printf("\nNO SE ENCONTRO EL ASTRONAUTA\n");

}
void aumentarHsVueloAstronauta(nodoAstroArbol * modificado)//AUMENTA HS DE VUELO PARA UN NODO ASTRONAUTA
{
    int hs=-1;
    char continuar='n';
    while(hs>5000 || hs<1)
    {
        printf("\nINGRESE HORAS:\n ");
        scanf("%d",&hs);
        if(hs>5000 || hs<1)
            printf("\nINGRESE UNA CANTIDAD DE HORAS VALIDA (MENOS DE 5000, MAS DE 0)");
    }
    printf("\nDESEA GRABAR LOS DATOS?\nPresione s\n");
    fflush(stdin);
    scanf("%c",&continuar);
    if(continuar=='s')
    {
        modificado->dato.horasDeVuelo=modificado->dato.horasDeVuelo+hs;
        mostrarAstronauta(modificado->dato);
        printf("\nLOS DATOS FUERON ACTUALIZADOS CON EXITO\n");
    }
    else
        printf("\nLOS DATOS NO FUERON GRABADOS.\n");

}
void aumentarHsEEI(nodoAstroArbol * modificado)//AUMENTA HS EN EEI PARA UN NODO ASTRONAUTA
{
    int hs=-1;
    char continuar='n';
    while(hs>50000 || hs<1)
    {
        printf("\nINGRESE HORAS:\n");
        scanf("%d",&hs);
        if(hs>5000 || hs<1)
        {
            printf("\nINGRESE UNA CANTIDAD DE HORAS VALIDA (MENOS DE 50000, MAS DE 0)");
        }
    }
    printf("\nDESEA GRABAR LOS DATOS?\nPresione s\n");
    fflush(stdin);
    scanf("%c",&continuar);
    if(continuar=='s')
    {
        modificado->dato.horasEEI=modificado->dato.horasEEI+hs;
        mostrarAstronauta(modificado->dato);
        printf("\nLOS DATOS FUERON ACTUALIZADOS CON EXITO\n");
    }

    else
        printf("\nLOS DATOS NO FUERON GRABADOS.\n");

}

//FUNCIONES DE ARCHIVO DE ARBOL
void guardarAstronautasEnArchivo(nodoAstroArbol* raiz)
{
    if(raiz)
    {
        FILE* archivo = fopen("astronautas", "wb");

        if(archivo)
        {
            fwriteRecursivoArbol(raiz, archivo);
            fclose(archivo);
        }
    }
}

void fwriteRecursivoArbol(nodoAstroArbol* raiz, FILE* archivo)//GRABA EL ARBOL ACTUALIZADO EN EL ARCHIVO
{
    if(raiz)
    {
        fwrite(&(raiz->dato), sizeof(Astronauta), 1, archivo);
        fwriteRecursivoArbol(raiz->izq, archivo);
        fwriteRecursivoArbol(raiz->der, archivo);
    }

}

nodoAstroArbol* leerAstronautasDeArchivo()//LEVANTA EL ARCHIVO AL ARBOL
{
    nodoAstroArbol* nuevo = inicArbol(); //crear el arbol adentro, retorna un null si no leyo el archivo
    FILE* archivo = fopen("astronautas", "rb");

    if(archivo)
    {
        Astronauta aux;
        while(fread(&aux, sizeof(Astronauta), 1, archivo) > 0)
        {
            nuevo = agregarOrdenadoArbol(nuevo, crearNodoArbol(aux));
        }
    }
    return nuevo;
}

//F U N C I O N E S   D E   L I S T A

nodoAstroLista* inicListaAstro()
{
    return NULL;
}

nodoAstroLista* crearNodoListaAstro(Astronauta recibido)//CREA NODO ASTRONAUTA DE LISTA DOBLE
{
    nodoAstroLista* nuevo = malloc(sizeof(nodoAstroLista));

    nuevo->dato = recibido;
    nuevo->sig = NULL;

    return nuevo;
}

nodoAstroLista* agregarAlFinalAstro(nodoAstroLista* lista, nodoAstroLista* nuevo)//AGREGA EL NODO A UNA LISTA DOBLE
{
    if(lista)
    {
        while(lista->sig)
        {
            lista = lista->sig;
        }

        lista->sig = nuevo;
    }
    else
        lista = nuevo;

    return lista;
}

int existeAstroEnLista(nodoAstroLista* lista, int idBuscado)//RETORNA SI EXISTE EL ASTRONAUTA YA CARGADO EN LA LISTA DE TRIPULANTES
{
    int encontrado = 0;
    while(lista)
    {
        if(lista->dato.id == idBuscado)
        {
            encontrado = 1;
        }

        lista = lista->sig;
    }

    return encontrado;
}

nodoAstroLista* buscarAstroListaPorId(nodoAstroLista* lista, int idBuscado)//RETORNA NODO ASTRO DE LA LISTA DOBLE
{
    nodoAstroLista* nodoEncontrado = NULL;
    while(lista)
    {
        if(lista->dato.id == idBuscado)
        {
            nodoEncontrado = lista;
        }

        lista = lista->sig;
    }

    return nodoEncontrado;
}

void mostrarListaAstro(nodoAstroLista* lista)//MUESTRA TODA UNA LISTA DOBLE DE ASTRONAUTAS
{
    while(lista)
    {
        mostrarAstronauta(lista->dato);
        lista = lista->sig;
    }
}

void consultaAstronauta(arbolDeAstros)//SOLICITA UN ENTERO ID PARA BUSCAR UN ASTRONAUTA Y MOSTRARLO,LLAMA A UNA SUBFUNCION
{
    int idBuscado;
    printf("\nINGRESE EL ID DEL ASTRONAUTA QUE QUIERE CONSULTAR: ");
    fflush(stdin);
    scanf("%i", &idBuscado);

    nodoAstroArbol* nodoEncontrado = buscarAstroArbolPorId(arbolDeAstros, idBuscado);
    if(nodoEncontrado)
        mostrarAstronauta(nodoEncontrado->dato);
    else
        printf("\nNO SE ENCONTRO EL ASTRONAUTA\n");

}


nodoAstroLista* cargarAstronautasMision(nodoAstroArbol * arbolDeAstronautas)//DEVUELVE UNA LISTA DE LISTA S
{

    //generar una lista nueva de astronautas
    nodoAstroLista* listaDeAstronautas = inicListaAstro();
    //preguntar cuantos astronautas desea ingresar a la lista
    int cantidadAstros;
    do
    {
        printf("\nCUANTOS ASTRONAUTAS DESEA INGRESAR: ");
        fflush(stdin);
        scanf("%i", &cantidadAstros);
        if(cantidadAstros < 1 || cantidadAstros > 5)
        {
            printf("\nINGRESE UNA CANTIDAD DE ASTRONAUTAS VALIDA (entre 1 y 5)\n");
        }
    }
    while(cantidadAstros < 1 || cantidadAstros > 5);

    //loopear por la cantidad de astronautas que se agregan
    for(int i = 0; i < cantidadAstros; i++)
    {
        printf("\n\n - ASTRONAUTAS DISPONIBLES - \n");
        mostrarDisposiblesArbol(arbolDeAstronautas);

        printf("\n\nINGRESE EL ASTRONAUTA QUE QUIERE AGREGAR A LA MISION");

        //preguntar por id de astronauta
        int idBuscado;
        printf("\nID DEL ASTRONAUTA: ");
        fflush(stdin);
        scanf("%i", &idBuscado);

        //checkear que existe en el arbol y chekear que no este en mision
        while(!existeAstroEnArbol(arbolDeAstronautas, idBuscado) || enMisionAstroEnArbol(arbolDeAstronautas, idBuscado) )
        {
            printf("\nEL ASTRONAUTA NO EXISTE O ESTA REGISTRADO EN OTRA MISION. INGRESE OTRO ASTRONAUTA.");
            printf("\nID DEL ASTRONAUTA: ");
            fflush(stdin);
            scanf("%i", &idBuscado);
        }

        //copiar nodo del arbol y agregarlo a la lista
        nodoAstroArbol* nodoEncontrado = buscarAstroArbolPorId(arbolDeAstronautas, idBuscado); //creo un puntero al nodo encontrado

        nodoEncontrado->dato.misiones = nodoEncontrado->dato.misiones+1; //aumento en 1 la cantidad de misiones que realizo ese astronauta

        nodoEncontrado->dato.enMision = nodoEncontrado->dato.enMision = 1; //cambio el estado del astronauta a enMision = 1

        Astronauta astroNuevo = nodoEncontrado->dato; //copiar el astro (NO EL NODO), y crearNodoLista con ese dato.

        listaDeAstronautas = agregarAlFinalAstro(listaDeAstronautas, crearNodoListaAstro(astroNuevo));

        printf("\n");

    }

    //guardar el arbol con los datos actualizados en el archivo
    guardarAstronautasEnArchivo(arbolDeAstronautas);

    return listaDeAstronautas;

}

// F U N C I O N E S   D E   M E N U
void menuAstronauta(nodoAstroArbol * arbolDeAstros)
{

    int opcion;
    int optar;

    //abrir el arbol del archivo
    //nodoAstroArbol* arbolDeAstros = leerAstronautasDeArchivo();

    do
    {

        printf("\n  ASTRONAUTAS\n");
        printf("\n--------------------------------\n");
        printf("\n  1-ALTAS\n");
        printf("\n  2-BAJAS\n");
        printf("\n  3-MODIFICACIONES\n");
        printf("\n  4-CONSULTAS\n");
        printf("\n  5-LISTADOS\n");
        printf("\n  6-VOLVER\n");
        printf("\n--------------------------------\n");

        printf("\n  Elija una opci%cn: ",162);
        scanf("%d",&opcion);
        system("cls");

        switch(opcion)
        {

        case 1:
            arbolDeAstros = altaAstronauta(arbolDeAstros);
            //guardo el arbol de nuevo en el archivo
            guardarAstronautasEnArchivo(arbolDeAstros);
            system("cls");
            break;

        case 2:
            bajaAstronauta(arbolDeAstros,-1);
            //guardo el arbol de nuevo en el archivo
            guardarAstronautasEnArchivo(arbolDeAstros);
            system("cls");
            break;

        case 3:
            modificarAstronauta(arbolDeAstros,-1);
            system("pause");
            system("cls");
            //guardo el arbol de nuevo en el archivo
            guardarAstronautasEnArchivo(arbolDeAstros);
            break;

        case 4:
            consultaAstronauta(arbolDeAstros);
            system("pause");
            system("cls");
            break;

        case 5:
            do
            {


                system("cls");
                printf("\n  LISTADOS\n");

                printf("\n--------------------------------\n");
                printf("\n  1-TODOS\n");
                printf("\n  2-ACTIVOS\n");
                printf("\n  3-DISPONIBLES\n");
                printf("\n  4-RETIRADOS\n");
                printf("\n  5-VOLVER\n");
                printf("\n--------------------------------\n");

                printf("\nElija una opci%cn: ",162);
                scanf("%d",&optar);
                system("cls");


                switch(optar)
                {
                case 1:
                    mostrarArbolInOrder(arbolDeAstros);
                    system("pause");
                    system("cls");
                    break;


                case 2:
                    mostrarActivosArbol(arbolDeAstros);
                    system("pause");
                    system("cls");
                    break;

                case 3:
                    mostrarDisposiblesArbol(arbolDeAstros);
                    system("pause");
                    system("cls");
                    break;

                case 4:

                    mostrarBajasArbol(arbolDeAstros);
                    system("pause");
                    system("cls");
                    break;
                }
            }
            while(optar!=5);
        }
    }
    while(opcion!=6);
}

nodoAstroArbol* altaAstronauta(nodoAstroArbol* arbolDeAstros)
{

    //preguntar por multiples astronautas
    char seguir = 's';
    do
    {
        int idIngresado;
        printf("\nINGRESE EL ID DEL ASTRONAUTA QUE QUIERE CARGAR: ");
        fflush(stdin);
        scanf("\n%i", &idIngresado);

        //si el id no existe guardo el astronauta en el arbol
        if(!existeAstroEnArbol(arbolDeAstros, idIngresado))
        {
            arbolDeAstros = agregarOrdenadoArbol(arbolDeAstros, crearNodoArbol(crearAstronautaManual(idIngresado)));
        }
        else
        {
            printf("\nEL ASTRONAUTA INGRESADO YA SE ENCUENTRA EN LA BASE DE DATOS\n");
        }

        //desea continuar?
        printf("\nDESEA CONTINUAR INGRESANDO ASTRONAUTAS? (s/n)");
        fflush(stdin);
        scanf("\n%c", &seguir);
    }
    while(seguir=='s');

    return arbolDeAstros;

}
