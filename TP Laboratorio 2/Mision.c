#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "Mision.h"

//F U N C I O N E S   D E   M I S I O N

nodoMision * crearNodoMision(Mision Dada, nodoAstroLista * listaS, Nave navecita) //CREA UN NODO DE MISION A PARTIR DE UNA MISION, UNA LISTA DE ASTRONAUTAS Y UNA NAVE
{
    nodoMision * aux = malloc(sizeof(nodoMision));
    aux->misionCargada=Dada;
    aux->listaAstronautas=listaS;
    aux->naveCargada=navecita;
    aux->ante = inicNodoNave();
    aux->sig = inicNodoNave();

    return aux;
}

void ingresarCargamento(char cargamentoMatriz[20][20]) //CARGA UNA MATRIZ CON EL CARGAMENTO PARA UNA MISION
{
    printf("\n\tINGRESE EL CARGAMENTO DE LA MISION");

    char check = 'y';
    int fila = 0;
    while(check != 'n' && fila<20)
    {
        printf("\nCARGA NUMERO %i: ", fila+1);
        fflush(stdin);
        gets(cargamentoMatriz[fila]);
        fila++;

        printf("\nDESEA INGRESAR OTRA CARGA? (s/n)\n");
        fflush(stdin);
        scanf("%c", &check);
    }

    while(fila<20)//si quedaron filas vacias, las llena con -1
    {
        strcpy(cargamentoMatriz[fila], "-1");
        fila++;
    }

}

void modificarMision(nodoMision* listaTotal) //MODIFICA UNO DE LOS CAMPOS DE UNA MISION A PARTIR DE UN ID INGRESADO POR TECLADO
{
    int id;
    printf("\n\tINGRESE EL ID DE LA MISION QUE QUIERE MODIFICAR: ");
    fflush(stdin);
    scanf("%i", &id);

    nodoMision* nodoEncontrado = encontrarNodoPorIdMision(listaTotal, id);
    if(nodoEncontrado && (nodoEncontrado->misionCargada.estado==0 || nodoEncontrado->misionCargada.estado==2))
    {
        mostrarMision(nodoEncontrado->misionCargada);
        printf("\n\tSELECCIONE EL CAMPO A MODIFICAR");
        printf("\n1-DESTINO\n2-CARGAMENTO\n3-DETALLES\n4-VOLVER\n\n");
        int campo = 0;
        fflush(stdin);
        scanf("%i", &campo);

        if(campo == 1)
        {
            printf("\nNUEVO DESTINO: ");
            fflush(stdin);
            gets(nodoEncontrado->misionCargada.destino);
            strupr(nodoEncontrado->misionCargada.destino);
        }
        else if(campo == 2)
        {
            printf("\nNUEVO CARGAMENTO: \n");
            fflush(stdin);
            ingresarCargamento(nodoEncontrado->misionCargada.cargamento);
        }
        else if(campo == 3)
        {
            printf("\nNUEVO DETALLE: ");
            fflush(stdin);
            gets(nodoEncontrado->misionCargada.detalles);
            strupr(nodoEncontrado->misionCargada.detalles);
        }
    }
    else if(nodoEncontrado && (nodoEncontrado->misionCargada.estado!=1 && nodoEncontrado->misionCargada.estado!=2))
        printf("\n\tLA MISION NO PUEDE SER MODIFICADA EN ESTE MOMENTO.\n");
    else
        printf("\n\tLA MISION NO PUDO SER ENCONTRADA\n");
}


//F U N C I O N E S   D E   L I S T A

nodoMision* inicListaMision() //INICIALIZA UNA LISTA DOBLE DE MISIONES
{
    return NULL;
}

void mostrarMision(Mision dada) //MUESTRA UNA MISION RECIBIDA POR PARAMETRO
{
    printf("\n//////////////\n");
    printf("\nID DE LA MISION: %i", dada.id);

    printf("\nESTADO: ");
    if(dada.estado == 0)
    {
        puts("LISTA");
    }
    else if(dada.estado == 1)
    {
        puts("EN VUELO");
    }
    else if(dada.estado == 2)
    {
        puts("RETORNADA");
    }
    else if(dada.estado == 3)
    {
        puts("CANCELADA");
    }
    else
    {
        puts("FALLIDA");
    }

    printf("DESTINO: ");
    puts(dada.destino);

    mostrarCargamento(dada);

    printf("\nDETALLES: ");
    puts(dada.detalles);

    printf("ID de los astronautas: ");
    for(int i = 0; i < dada.validosTrip; i++)
    {
        printf("[%i] ", dada.tripulantes[i]);
    }
    printf("\nValidos Trip: %i", dada.validosTrip);
    printf("\nID de la nave: %i", dada.idNave);
    printf("\n\n--------------");

}

void mostrarNodoMision(nodoMision* recibido) //MUESTRA UN NODO DE MISION RECIBIDO POR PARAMETRO
{
    if(recibido)
    {
        mostrarMision(recibido->misionCargada);

        ///////////////////////////

        printf("\n\n - [LISTA DE ASTRONAUTAS EN LA MISION] - \n\n");
        mostrarListaAstro(recibido->listaAstronautas);

        ///////////////////////////

        printf("\n - [NAVE ASIGNADA] - \n");
        MostrarNave(recibido->naveCargada);

        printf("\n\n//////////////////");

    }
}

void mostrarCargamento(Mision misionRecibida) //MUESTRA EL CARGAMENTO DE UNA MISION RECIBIDA POR PARAMETRO
{
    printf("CARGAMENTO:");
    int i = 0;
    while(i < 20)
    {
        if(strcmp(misionRecibida.cargamento[i], "-1") != 0)
        {
            printf("[%s] ", misionRecibida.cargamento[i]);
        }
        i++;
    }
}

nodoMision* agregarFinalListaMision(nodoMision* lista, nodoMision* nuevo) //AGREGA UN NODO DE MISION A UNA LISTA DE MISIONES
{
    if(!lista)
        lista = nuevo;
    else
    {
        nodoMision* actual = lista;
        while(actual->sig)
        {
            actual = actual->sig;
        }
        nuevo->ante = actual;
        actual->sig = nuevo;
    }

    return lista;
}

///////////////////////////
///////////////////////////

//F U N C I O N E S   D E   F I L A

void inicFila(Fila* recibida) //INICIALIZA UNA FILA
{
    recibida->cabecera = inicListaMision();
    recibida->cola = inicListaMision();
}

void mostrarFila(Fila recibida) //MUESTRA UNA FILA RECIBIDA POR PARAMETRO
{
    nodoMision* actual = recibida.cabecera;
    printf("\n   -   LISTA DE LANZAMIENTOS   -   ");
    if(!actual)
    {
        printf("\nNO HAY MISIONES GUARDADAS\n");
    }
    else
    {
        mostrarListaMisiones(actual);
    }
}

void mostrarListaMisiones(nodoMision* listaMisiones) //MUESTRA UNA LISTA DE MISIONES
{
    nodoMision* actual = listaMisiones;

    while(actual)
    {
        printf("\n\n\t[DATOS DE MISION]\n");
        mostrarNodoMision(actual);
        actual = actual->sig;
    }
}

Mision crearMision(nodoMision* listaDeMisionesTotal) //CREA UNA MISION CON SUS DATOS CORRESPONDIENTES Y LA DEVUELVE
{
    Mision nueva;
    nueva.id = ultimoIdListaTotal(listaDeMisionesTotal) + 1;
    printf("\n\tID DE LA MISION A CARGAR: %i", nueva.id);

    printf("\nDESTINO: ");
    fflush(stdin);
    gets(nueva.destino);
    strupr(nueva.destino);

    ingresarCargamento(nueva.cargamento);

    printf("\n\tDETALLES DE LA MISION: ");
    fflush(stdin);
    gets(nueva.detalles);
    strupr(nueva.detalles);

    nueva.validosTrip = 0;

    return nueva;
}

nodoMision* cargarMisionNueva(nodoAstroArbol * arbol,Fila* recibida, nodoMision* listaDeMisionesTotal, nodoNave * listaDeNaves) //CARGA UN NODO DE MISION Y LO GUARDA EN LA LISTA TOTAL DE MISIONES Y EN LA FILA DE MISIONES LISTAS
{
    printf("\n\tINGRESE LOS DATOS DE LA MISION NUEVA A SER AGREGADA\n");

    //DATOS DE LA ESTRUCTURA MISION
    Mision nueva = crearMision(listaDeMisionesTotal);

    //NAVE
    Nave naveMision = cargarNaveMision(listaDeNaves);

    //LISTA DE ASTRONAUTAS
    nodoAstroLista* listaAstronautasMision = cargarAstronautasMision(arbol); // esta funcion crea una lista y la llena con astronautas

    nueva.validosTrip = deListaTripulantesToArreglo(nueva.tripulantes, listaAstronautasMision);
    nueva.idNave = naveMision.idNave;

    //CREAR UN NODOMISION Y CARGARLO CON TODO LO ARMADO //crearNodo(con los 3 parametros)
    nodoMision* nodoNuevo = crearNodoMision(nueva, listaAstronautasMision, naveMision);

    //AGREGAR EL NODOMISION A LA LISTA DE MISIONES
    agregarFinalFila(recibida, nodoNuevo);

    //AGREGAR EL NODO A LA LISTATOTAL DE MISIONES
    nodoMision* nodoNuevoTotal = crearNodoMision(nueva, listaAstronautasMision, naveMision);
    listaDeMisionesTotal = agregarFinalListaMision(listaDeMisionesTotal, nodoNuevoTotal);

    return listaDeMisionesTotal;

}

void agregarFinalFila(Fila* recibida, nodoMision* nuevo) //AGREGA AL FINAL DE UNA FILA UN NUEVO NODO DE MISION
{
    recibida->cabecera = agregarFinalListaMision(recibida->cabecera, nuevo);
    recibida->cola = nuevo;
}

int ultimoIdListaTotal(nodoMision* listaTotal) //retorna 0 si no hay elemento en la lista, retorna el id del ultimo elemento sino
{
    int ultimoId = 0;

    if(listaTotal)
    {
        while(listaTotal->sig)
        {
            listaTotal = listaTotal->sig;
        }
        ultimoId = listaTotal->misionCargada.id;
    }


    return ultimoId;
}


// EXTRAER DE ARCHIVO LA FILA DE MISIONES //


nodoMision * ListaTotalMisiones(nodoAstroArbol * arbolDeAstronautas,nodoNave * ListaDeNaves) //CREA UNA LISTA TOTAL DE MISIONES A PARTIR DE LAS MISIONES GUARDADAS EN UN ARCHIVO
{
    FILE * Archivo=fopen("misiones","rb");
    nodoMision * ListaDeMisiones=inicListaMision();
    Mision aux;
    //recorrer el archivo y armar cada nodoMision de la listaDeMisionesCompleta
    if(Archivo)
    {
        while(fread(&aux,sizeof(Mision),1,Archivo)>0)
        {
            nodoAstroLista* listaTripulantes=deArregloAListaTripulantes(aux.tripulantes, aux.validosTrip, arbolDeAstronautas);
            Nave Navecita=buscoNave(ListaDeNaves, aux.idNave);
            ListaDeMisiones=agregarFinalListaMision(ListaDeMisiones,crearNodoMision(aux,listaTripulantes,Navecita));
        }
        fclose(Archivo);
    }

    return ListaDeMisiones;
}

nodoAstroLista* deArregloAListaTripulantes(int arregloTripulantes[], int validos, nodoAstroArbol* arbolDeAstronautas) //CREA UNA LISTA DE TRIPULANTES A PARTIR LOS ID GUARDADOS EN EL ARREGLO PERTENECIENTE A LA MISION
{
    nodoAstroLista* listaTripulantes = inicListaAstro();

    for(int i = 0; i < validos; i++)
    {
        nodoAstroArbol* nodoEncontrado = buscarAstroArbolPorId(arbolDeAstronautas, arregloTripulantes[i]);
        nodoAstroLista* nodoNuevo = crearNodoListaAstro(nodoEncontrado->dato);
        listaTripulantes = agregarAlFinalAstro(listaTripulantes, nodoNuevo); //EL PRIMER PARAMETRO DE ESTO ES UNA FILA
    }

    return listaTripulantes;
}

nodoMision* deListaCompletaToListaActivos(nodoMision* listaTotal) //CREA UNA LISTA NUEVA DE MISIONES LISTAS A PARTIR DE UNA LISTA CON TODAS LAS MISIONES
{
    nodoMision* listaActivos = inicListaAstro();

    nodoMision* actual = listaTotal;

    while(actual)
    {
        if(actual->misionCargada.estado == 0)
        {
            Mision nuevaMision = actual->misionCargada;
            Nave navecita = actual->naveCargada;
            nodoAstroLista* listaTripulacion = actual->listaAstronautas;
            listaActivos = agregarFinalListaMision(listaActivos, crearNodoMision(nuevaMision, listaTripulacion, navecita));
        }


        actual = actual->sig;
    }
    return listaActivos;
}

nodoMision* deArchivoToFila(Fila* recibida,nodoAstroArbol * arbol, nodoNave * listaNaves) //CREA UNA FILA DE MISIONES A PARTIR DE LAS MISIONES GUARDADAS EN UN ARCHIVO
{
    nodoMision* listaTotal = ListaTotalMisiones(arbol,listaNaves);

    nodoMision* listaActivos = deListaCompletaToListaActivos(listaTotal);

    recibida->cabecera = listaActivos;

    nodoMision* actual = listaActivos;


    if(actual)
    {
        while(actual->sig)
        {
            actual = actual->sig;
        }
    }

    recibida->cola = actual;

    return listaTotal;
}

nodoMision* encontrarMisionPorId(nodoMision* listaDeMisiones, int id) //DEVUELVE UN NODO MISION A PARTIR DE UN ID
{
    nodoMision* encontrado = NULL;

    while(listaDeMisiones)
    {
        if(listaDeMisiones->misionCargada.id == id)
        {
            encontrado = listaDeMisiones;
        }

        listaDeMisiones = listaDeMisiones->sig;
    }

    return encontrado;
}

void deListaTotalToArchivo(nodoMision* listaDeMisionesTotal) //GUARDA LA LISTA TOTAL DE MISIONES EN UN ARCHIVO
{
    FILE* archivo = fopen("misiones", "wb");

    if(archivo)
    {
        while(listaDeMisionesTotal)
        {
            fwrite(&(listaDeMisionesTotal->misionCargada), sizeof(Mision), 1, archivo);

            listaDeMisionesTotal = listaDeMisionesTotal->sig;
        }
        fclose(archivo);
    }
}

int deListaTripulantesToArreglo(int arreglo[], nodoAstroLista* listaTripulantes) //GUARDA EN UN ARREGLO LOS ID DE LOS ASTRONAUTAS GUARDADOS EN UNA LISTA Y RETORNA LOS VALIDOS DEL ARREGLO
{
    int validos = 0;
    while(listaTripulantes)
    {
        arreglo[validos] = listaTripulantes->dato.id;
        validos++;
        listaTripulantes = listaTripulantes->sig;
    }

    return validos;
}

void mostrarArchivo() //MUESTRA LAS MISIONES GUARDADAS EN UN ARCHIVO
{
    FILE* archivo = fopen("misiones", "rb");

    if(archivo)
    {
        Mision aux;
        while(fread(&aux, sizeof(Mision), 1, archivo) > 0)
        {
            mostrarMision(aux);
        }
        fclose(archivo);
    }
}

//CANCELAR, FALLAR y COMPLETAR MISION

int extraerPrimerNodoDeFila(Fila* recibida) //EXTRAE EL PRIMER NODO DE UNA FILA DE MISIONES Y RETORNA EL ID
{
    nodoMision* extraido = recibida->cabecera;

    if(extraido)
    {
        if(extraido->sig) //si hay mas de uno
        {
            ((nodoMision*)(extraido->sig))->ante = NULL;
            recibida->cabecera = extraido->sig;
        }
        else //si hay uno solo
        {
            recibida->cabecera = NULL;
            recibida->cola = NULL;
        }
    }

    extraido->sig = NULL;
    extraido->ante = NULL;

    return extraido->misionCargada.id;

}

nodoMision* encontrarNodoPorIdMision(nodoMision* listaTotal, int id) //RETORNA EL NODO DE UNA LISTA DE MISIONES A PARTIR DE UN ID
{
    nodoMision* extraido=inicListaMision();

    while(listaTotal)
    {
        if(listaTotal->misionCargada.id == id)
        {
            extraido = listaTotal;
        }
        listaTotal = listaTotal->sig;
    }

    return extraido;
}

nodoMision* lanzarMision(Fila* recibida, nodoMision* listaTotal) //CAMBIA EL ESTADO DE UNA MISION A "EN VUELO" Y ACTUALIZASUS PARAMETROS (ASTRONAUTAS Y NAVE)
{
    if(recibida->cabecera)
    {
        int idMisionExtraida = extraerPrimerNodoDeFila(recibida);
        nodoMision* modificar = encontrarNodoPorIdMision(listaTotal, idMisionExtraida);
        modificar->misionCargada.estado = 1;
        printf("\nSE LANZARA LA SIGUIENTE MISION:\n");
        mostrarMision(modificar->misionCargada);
    }
    else
    {
        printf("\nNO HAY MISIONES LISTAS PARA LANZAR\n");
    }

    return listaTotal;
}


nodoMision* cancelarMision(nodoAstroArbol* arbolAstros, Fila* recibida, nodoMision* listaTotal) //CAMBIA EL ESTADO DE UNA MISION A "CANCELADA" Y ACTUALIZA SUS PARAMETROS (ASTRONAUTAS Y NAVE)
{
    char cancelar='n';
    int cont=0;
    if(recibida->cabecera)
    {
        int idMisionExtraida = extraerPrimerNodoDeFila(recibida);
        nodoMision* modificar = encontrarNodoPorIdMision(listaTotal, idMisionExtraida);

        while(cancelar=='n'&& cont<1)
        {
            printf("\n\nLA SIGUIENTE MISION SERA CANCELADA:\n");
            mostrarNodoMision(modificar);
            printf("\n\nDESEA CONTINUAR?:\n");
            fflush(stdin);
            scanf("%c",&cancelar);
            cont=1;
            if(cancelar=='s')
            {
                modificar->misionCargada.estado = 3;//cambvia estado de la mision
                //por cada astronauta de la lista, buscar ese astronauta en el arbol y cambiarle enMision a 0
            for(int i = 0; i < modificar->misionCargada.validosTrip; i++)
            {
                nodoAstroArbol* nodoEncontrado = buscarAstroArbolPorId(arbolAstros, modificar->misionCargada.tripulantes[i]);
                nodoEncontrado->dato.enMision = 0;
            }

            //CAMBIAR EL ESTADO DE LA NAVE ASIGNADA A LISTA PARA SU USO
            nodoNave* listaNaves = ArchivoToListaNaves();
            nodoNave* nodoNaveEncontrado = BuscarNodoNave(listaNaves, modificar->misionCargada.idNave);
            nodoNaveEncontrado->NaveGuardada.Estado = 1;
            GrabarListaNaves(listaNaves);

            //guardar archivo de astros
            guardarAstronautasEnArchivo(arbolAstros);
            printf("\n\nLA MISION HA SIDO CANCELADA.\n");
            }
            else
            printf("\nNO SE HA CANCELADO LA MISION\n");
        }

    }
    else
    {
        printf("\nNO HAY MISIONES PARA CANCELAR\n");
    }

    return listaTotal;

}
void consultarMision(nodoMision * listaTotal) //MUESTRA UNA MISION A PARTIR DE UN ID INGRESADO POR TECLADO
{
    int id;
    printf("\nINGRESE EL ID DE LA MISION QUE DESEE VISUALIZAR:\n\n");
    scanf("%d",&id);
    nodoMision * retornado=encontrarNodoPorIdMision(listaTotal,id);
    if(retornado)
        mostrarNodoMision(retornado);
    else
        printf("\nNO SE ENCONTRO LA MISION.\n");
}

nodoMision* informarFallidaMision(nodoMision* listaTotal,nodoAstroArbol * arbol,nodoNave * naves) //CAMBIA EL ESTADO DE UNA MISION A "FALLIDA" Y ACTUALIZA SUS CAMPOS (ASTRONAUTAS Y NAVE)
{
    nodoMision * retornado=inicListaMision();
    nodoMision * seg=listaTotal;
    int hay=0;
    //esta funcion tiene que mostrar todas las misiones en vuelo y dejarte elegir una
    if(seg)
    {
        printf("\n\tLISTA DE MISIONES EN VUELO:\n\n");
        while(seg)
        {
            if(seg->misionCargada.estado==1)
            {
                hay++;
                mostrarNodoMision(seg);
            }
            seg=seg->sig;
        }
        if(hay>0)
        {
            printf("\n\nINGRESE ID DE LA MISION QUE DESEA INFORMAR SU FALLO:\n\n");
            int id;
            scanf("%d",&id);
            retornado=encontrarNodoPorIdMision(listaTotal,id);
            if(retornado && retornado->misionCargada.estado==1)
            {
                char cont='n';
                mostrarMision(retornado->misionCargada);
                printf("\nDESEA INFORMAR EL FALLO DE LA MISION:\n");
                fflush(stdin);
                scanf("%c",&cont);
                if(cont=='s')
                {
                    retornado->misionCargada.estado=4;
                    bajaDeTripulacion(retornado->misionCargada.tripulantes,retornado->misionCargada.validosTrip,arbol);
                    nodoNave * regresada=BuscarNodoNave(naves,retornado->misionCargada.idNave);
                    regresada->NaveGuardada.Estado=3;
                    retornado->naveCargada=regresada->NaveGuardada;
                    guardarAstronautasEnArchivo(arbol);
                    GrabarListaNaves(naves);
                }
                else
                    printf("\nLOS DATOS NO SE GUARDARON.\n");

            }
            else
                printf("\nNO SE PUDO ENCONTRAR LA MISION.\n");

        }
        else
            printf("\n\nNO EXISTEN MISIONES EN VUELO.\n");
    }



}
void bajaDeTripulacion(int A[],int validos,nodoAstroArbol * arbol) //DA DE BAJA LOS ASTRONAUTAS A PARTIR DE UN ARREGLO CON LOS ID DE ELLOS
{

    for(int i=0; i<validos; i++)
    {
        bajaAstronauta(arbol,A[i]);
    }
}

void informarRetornoMision(nodoMision* listaTotal,nodoAstroArbol * arbol,nodoNave * naves) //CAMBIA EL ESTADO DE UNA MISION A "RETORNADA" Y ACTUALIZA LOS ASTRONAUTAS Y LA NAVE
{
    nodoMision * retornado=inicListaMision();
    nodoMision * seg=listaTotal;
    int hay=0;
    //esta funcion tiene que mostrar todas las misiones en vuelo y dejarte elegir una
    if(seg)
    {
        printf("\n\tLISTA DE MISIONES EN VUELO:\n\n");
        while(seg)
        {
            if(seg->misionCargada.estado==1)
            {
                hay++;
                mostrarNodoMision(seg);
            }
            seg=seg->sig;
        }
        if(hay>0)
        {
            printf("\n\nINGRESE ID DE LA MISION QUE DESEA INFORMAR SU RETORNO:\n\n");
            int id;
            scanf("%d",&id);
            retornado=encontrarNodoPorIdMision(listaTotal,id);
            if(retornado && retornado->misionCargada.estado==1)
            {
                char cont='n';
                mostrarMision(retornado->misionCargada);
                printf("\nDESEA INFORMAR EL RETORNO DE LA MISION:\n");
                fflush(stdin);
                scanf("%c",&cont);
                if(cont=='s')
                {
                    retornado->misionCargada.estado=2;
                    actualizarAstronautasPostMision(retornado->misionCargada.tripulantes,retornado->misionCargada.validosTrip,arbol);
                    nodoNave * regresada=BuscarNodoNave(naves,retornado->misionCargada.idNave);
                    regresada=AumentarVueloHs(regresada);
                    regresada->NaveGuardada.Estado=1;
                    retornado->naveCargada=regresada->NaveGuardada;
                    guardarAstronautasEnArchivo(arbol);
                    GrabarListaNaves(naves);
                }
                else
                    printf("\nLOS DATOS NO SE GUARDARON.\n");

            }
            else
                printf("\nNO SE PUDO ENCONTRAR LA MISION.\n");

        }
        else
            printf("\n\nNO EXISTEN MISIONES EN VUELO.\n");
    }



}

//F U N C I O N E S   D E   M E N U

void menuMisionPrincipal(Fila *filaDeMisiones, nodoMision * listaTotal, nodoAstroArbol * arbolAstro, nodoNave * listaDeNaves)
{

    int selected;
    do
    {
        system("cls");
        selected=selectMisionMenu();
        switch(selected)
        {
        case 1: //ALTA
        {
            listaTotal = cargarMisionNueva(arbolAstro,filaDeMisiones, listaTotal,listaDeNaves);
            printf("\nFIN DE CARGAR MISION NUEVA\n");

            deListaTotalToArchivo(listaTotal);
            printf("\nGUARDADO\n");
            system("PAUSE");
            break;
        }
        case 2: //LANZAR MISION
        {
            listaTotal = lanzarMision(filaDeMisiones, listaTotal);
            deListaTotalToArchivo(listaTotal);
            printf("\nFIN DE LANZAR MISION\n");
            system("PAUSE");
            break;
        }
        case 3: //CANCELAR MISION
        {
            listaTotal = cancelarMision(arbolAstro, filaDeMisiones, listaTotal);
            deListaTotalToArchivo(listaTotal);
            printf("\nFIN DE CANCELAR MISION\n");
            system("PAUSE");
            break;
        }
        case 4: //FALLAR MISION
        {
            informarFallidaMision(listaTotal,arbolAstro,listaDeNaves);
            deListaTotalToArchivo(listaTotal);
            printf("\nRIP\n");
            system("PAUSE");
            break;
        }
        case 5: //INFORMAR RETORNO MISION
        {
            informarRetornoMision(listaTotal,arbolAstro,listaDeNaves);
            deListaTotalToArchivo(listaTotal);
            printf("\nFIN DE COMPLETAR MISION\n");
            system("PAUSE");
            break;
        }
        case 6: //TODAS
        {
            mostrarListaMisiones(listaTotal);
            system("PAUSE");
            break;
        }
        case 7: //LISTAS
        {
            mostrarFila(*filaDeMisiones);
            system("PAUSE");
            break;
        }
        case 8: //LISTAS
        {
            consultarMision(listaTotal);
            system("PAUSE");
            break;
        }
        case 9: // MODIFICAR MISION
        {
            modificarMision(listaTotal);
            system("PAUSE");
            break;
        }
        }
    }
    while(selected!=10);
    system("cls");
}

int selectMisionMenu()
{
    int input;
    printf("\n MISIONES.\n");
    printf("\n----------------------\n");
    printf("\n 1-CARGAR NUEVA MISION.\n");
    printf("\n 2-LANZAR MISION.\n");
    printf("\n 3-CANCELAR MISION.\n");
    printf("\n 4-INFORMAR MISION FALLIDA.\n");
    printf("\n 5-INFORMAR RETORNO.\n");
    printf("\n 6-MOSTRAR TODAS LAS MISIONES.\n");
    printf("\n 7-MOSTRAR PROXIMOS LANZAMIENTOS.\n");
    printf("\n 8-CONSULTAR MISION.\n");
    printf("\n 9-MODIFICAR MISION\n");
    printf("\n 10-VOLVER\n");
    printf("\n----------------------\n");
    printf("\n Elija una opcion: ");
    scanf("%i", &input);
    return input;
}

