#include <stdio.h>
#include <stdlib.h>
#include "ListaNaves.h"
#include "strings.h"
Nave InicNave()//INICIALIZA LA NAVE EN CASO QUE NO FUERA ENCONTRADA EN UNA FN Y SE MUESTRE ALGO
{
    Nave retornada;
    retornada.idNave=-1;
    retornada.Tipo=-1;
    retornada.cantVuelos=-1;
    retornada.HsAcumuladas=-1;
    retornada.Estado=-1;
    return retornada;

}
Nave CargarNave(int id)//CREA NAVE A PARTIR DEL PARAMETRO CONFIRMADO COMO ID
{
    Nave nueva;
    nueva.idNave=id;
    printf("\nINGRESE TIPO:\n1.STARSHIP.\n2.FALCON 9.\n3.FALCON HEAVY.\n");//Starship, Falcon 9, Falcon Heavy
    scanf("%d",&nueva.Tipo);
    nueva.cantVuelos=ingresarVuelos();
    nueva.HsAcumuladas=ingresarHsDeVuelo();
    printf("\nINGRESE ESTADO DE LA NAVE:\n0.Manteniemiento.\n1.Lista para su uso.\n2.Actualmente en Mision.\n3.de Baja.\n");
    scanf("%d",&nueva.Estado);
    return nueva;
}
int ingresarVuelos()//RETORNA EL VALOR INGRESADO, TIENE POR FINALIDAD VALIDAD LOS MISMOS
{
    int vuelos=-1;
    while(vuelos<0 || vuelos>10)
    {
        printf("\nINCRESE  CANTIDAD DE  VUELOS:\n");
        scanf("%d",&vuelos);
        if(vuelos<0 || vuelos>10)
            printf("\nEL VALOR INGRESADO DEBE ESTAR DENTRO DEL RANGO DE 1 A 10... \nPOR FAVOR VUELVA A INGRESAR LOS DATOS...\n");
    }
    return vuelos;
}

nodoNave * CargarMultiplesNaves(nodoNave * ListaDeNaves)//CARGA SISTEMATICA DE NAVES EN EL SISTEMA.
{
    char cont='s';
    int id;
    Nave nueva;
    nodoNave * nuevo;
    while(cont=='s')
    {
        printf("\nINGRESE EL ID DE LA NAVE:\n");
        scanf("%d",&id);
        if(ExisteNaveID(ListaDeNaves,id)==0)
        {
            nueva=CargarNave(id);
            nuevo=CrearNodoNave(nueva);
            ListaDeNaves=AgregarPpioNave(ListaDeNaves,nuevo);
        }
        else
            printf("\nEL ID CORRESPONDE A UNA NAVE YA INGRESADA.\n");//Quizas deberia cambiar el msj

        printf("\nDESEA CONTINUAR? (s).\n");
        fflush(stdin);
        scanf("%c",&cont);
    }
    return ListaDeNaves;
}
void MostrarNave(Nave mostrada)
{
    printf("\nID NAVE: ");
    printf("%d",mostrada.idNave);
    printf("\nTIPO: ");
    printf("%d",mostrada.Tipo);
    printf("\nCANTIDAD DE VUELOS REALIZADOS: ");
    printf("%d",mostrada.cantVuelos);
    printf("\nHS DE VUELO ACUMULADAS: ");
    printf("%d",mostrada.HsAcumuladas);
    if(mostrada.Estado==0)
        printf("\nESTADO DE LA NAVE: EN MANTENIMIENTO.");
    else if(mostrada.Estado==1)
        printf("\nESTADO DE LA NAVE: LISTA PARA SU USO.");
    else if(mostrada.Estado==2)
        printf("\nESTADO DE LA NAVE: ACTUALMENTE EN MISION.");
    else
        printf("\nESTADO DE LA NAVE: DE BAJA.");
    printf("\n\n-------------------------\n");

}
void ConsultarNave(nodoNave * Lista)//DEVUELVE EL NODO DE UNA NAVE PARA SER MOSTRADA O LO QUE EL SISTEMA REQUIERA
{
    int id;
    nodoNave * consultada=inicNodoNave();
    printf("\nINGRESE EL ID DE LA NAVE QUE DESEA CONSULTAR:\n");
    scanf("%d",&id);
    consultada=BuscarNodoNave(Lista, id);
    if(consultada)
    {
        MostrarNave(consultada->NaveGuardada);
    }
    else
        printf("\nNO SE ENCONTRO LA NAVE...\n");
}
nodoNave * inicNodoNave() //INICIALIZA EL NODO NAVE
{
    return NULL;
}
nodoNave * CrearNodoNave(Nave recibida)
{
    nodoNave * nuevoNodoNave=malloc(sizeof(nodoNave));
    nuevoNodoNave->NaveGuardada=recibida;
    nuevoNodoNave->ante=inicNodoNave();
    nuevoNodoNave->siguiente=inicNodoNave();
    return nuevoNodoNave;
}
nodoNave * AgregarPpioNave(nodoNave * lista, nodoNave * nuevo) //AGREGA AL PRINCIPIO DE LA LISTA DE NAVE UN NUEVO NODO
{
    if(!lista)
        lista=nuevo;
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}
void MostrarListaNaves(nodoNave * listaNaves) //MUESTRA UNA LISTA DE NAVES
{
    if(listaNaves)
    {
        MostrarNave(listaNaves->NaveGuardada);
        MostrarListaNaves(listaNaves->siguiente);
    }
}
void MostrarNavesDisponibles(nodoNave * listaNaves) //MUESTRA UNA LISTA DE NAVES DISPONIBLES
{
    if(listaNaves)
    {
        if(listaNaves->NaveGuardada.Estado==1)
        {
            MostrarNave(listaNaves->NaveGuardada);
        }
        MostrarNavesDisponibles(listaNaves->siguiente);
    }
}
int ExisteNaveID(nodoNave * lista,int id) //DEVUELVE 1 SI LA NAVE DE ID RECIBIDO POR PARAMETRO EXISTE EN LA LISTA DE NAVES
{
    int resultado=0;
    if(lista)
    {
        while(lista && resultado==0)
        {
            if(lista->NaveGuardada.idNave==id)
                resultado=1;
            lista=lista->siguiente;
        }
    }
    return resultado;
}
nodoNave * BuscarNodoNave(nodoNave * lista, int id) //DEVUELVE EL NODO DE LA NAVE DE ID RECIBIDO POR PARAMETRO SI EXISTE EN LA LISTA
{
    nodoNave * retornada=inicNodoNave();
    int terminado=0;
    if(lista)
    {
        while(lista && terminado==0)
        {
            if(lista->NaveGuardada.idNave==id)
            {
                retornada=lista;
                terminado=1;
            }
            lista=lista->siguiente;
        }
    }
    return retornada;

}

Nave buscoNave(nodoNave* lista, int id) //DEVUELVE LA NAVE DE ID RECIBIDO POR PARAMETRO SI EXISTE EN LA LISTA
{
    Nave aux = InicNave();

    if(BuscarNodoNave(lista, id))
    {
        aux = BuscarNodoNave(lista, id)->NaveGuardada;
    }

    return aux;
}

void ModificarNave(nodoNave * ListaDeNaves) //MODIFICA MANUALMENTE LOS CAMPOS DE CANTIDAD DE VUELOS, HORAS DE VUELO ACUMULADAS Y/O ESTADO DE LA NAVE DE UNA NAVE SELECCIONADA POR ID
{
    nodoNave * modificado;
    int opcion, id;
    printf("\nINGRESE EL ID DE LA NAVE:\n");
    scanf("%d",&id);
    if((ExisteNaveID(ListaDeNaves,id))!= 0)
    {
        modificado=BuscarNodoNave(ListaDeNaves,id);
        if(modificado->NaveGuardada.Estado!=3)
        {
            printf("\nNAVE A MODIFICAR:\n\n");
            MostrarNave(modificado->NaveGuardada);

            printf("\nQUE CAMPO DESEA MODIFICAR:\n1)AUMENTAR CANTIDAD DE VUELOS Y HORAS DE VUELO ACUMULADAS.\n2)ESTADO DE LA NAVE.\n");
            scanf("%d",&opcion);
            if(opcion==1 || opcion==2)
            {
                if(opcion==1)
                    AumentarVueloHs(modificado);
                else if(opcion==2)
                    CambiarEstadoNave(modificado);
                MostrarNave(modificado->NaveGuardada);
            }
        }
        else
            printf("\nNO SE PUEDE MODIFICAR DATOS DE UNA NAVE EN ESTADO DE BAJA.\n\n");
        MostrarNave(modificado->NaveGuardada);
    }
    else
        printf("\nNO SE  PUDO ENCONTRAR LA NAVE.\n");
}
void BajaNave(nodoNave * ListaDeNaves) //DA DE BAJA UNA NAVE DE ID INGRESADO POR TECLADO
{
    int id;
    char cont='n';
    printf("\nINGRESE EL ID DE LA NAVE QUE DESEA DAR DE BAJA:\n");
    scanf("%d",&id);
    nodoNave * Debaja=BuscarNodoNave(ListaDeNaves,id);
    if(Debaja)
    {
        MostrarNave(Debaja->NaveGuardada);
        printf("\nPRESIONE S PARA DAR DE BAJA LA NAVE.");
        fflush(stdin);
        scanf("%c",&cont);
        if(cont=='s')
        {
            if(Debaja->NaveGuardada.Estado==0)
            {
                Debaja->NaveGuardada.Estado=3;
                MostrarNave(Debaja->NaveGuardada);
                printf("\nDATOS MODIFICADOS CON EXITO.\n");
            }
            else if(Debaja->NaveGuardada.Estado==1)
            {
                Debaja->NaveGuardada.Estado=3;
                MostrarNave(Debaja->NaveGuardada);
                printf("\nDATOS MODIFICADOS CON EXITO.\n");
            }
            else
                printf("\nNO SE PUDO DAR DE BAJA LA NAVE EN ESTE MOMENTO...");
        }

    }
    else
        printf("\nNO SE PUDO ENCONTRAR LA NAVE.\n\n");


}
nodoNave * AumentarVueloHs(nodoNave * modificado) //AUMENTA LA CANTIDAD DE VUELOS Y HORAS DE VUELO DE UNA NAVE GUARDADA EN UN NODO RECIBIDO POR PARAMETRO
{
    int vuelos, hs;
    char cont='n';
    printf("\nINGRESE LA CANTIDAD DE  VUELOS QUE DESEA REGISTRAR A LA NAVE:\n");
    scanf("%d",&vuelos);
    printf("\nINGRESE LA CANTIDAD DE HORAS VUELOS QUE DESEA REGISTRAR A LA NAVE:\n");
    scanf("%d",&hs);
    printf("\nDATOS INGRESADOS:\nVUELOS:%d\nHHORAS:%d",vuelos, hs);
    printf("\nPRESIONE S PARA REGISTRARLOS DATOS U OTRA TECLAPARA VOLVER A  INGRESARLOS DATOS...\n");
    fflush(stdin);
    scanf("%c",&cont);
    if(cont=='s' && (vuelos>0 && vuelos<20)&& (hs>1 && hs<2000))
    {
        modificado->NaveGuardada.cantVuelos=modificado->NaveGuardada.cantVuelos+vuelos;
        modificado->NaveGuardada.HsAcumuladas=modificado->NaveGuardada.HsAcumuladas+hs;
    }
    else if(cont!='s')
    {
        printf("\nLOS  DATOS NO  SE GUARDARON:\nDESEA VOLVERA  INGRESAR LOS DATOS?(S)\n");
        fflush(stdin);
        scanf("%c",&cont);
        if(cont=='s')
            modificado=AumentarVueloHs(modificado);
    }
    else if(vuelos<0 || vuelos>20 || hs<0 || hs>2000)
    {
        printf("\nALGUNOS DE  LOS CAMPOS  INGRESADOS  SON INCORRECTOS.\nDESEA VOLVER A INGRESAR LOS DATOS?(S)\n");
        fflush(stdin);
        scanf("%c",&cont);
        modificado=AumentarVueloHs(modificado);
    }
    return modificado;

}
void CambiarEstadoNave(nodoNave * cambiado) //CAMBIA EL ESTADO MANUALMENTE DE UNA NAVE GUARDADA EN UN NODO RECIBIDO POR PARAMETRO
{
    int nuevoEstado=(-1);

    // CUANDO LOS ESTADIOS SON LOS MISMOS
    while(nuevoEstado<0 || nuevoEstado>3)
    {
        printf("\n0.EN MANTENIMIENTO.\n1.LISTA PARA SU USO.\n2.ACTUALMENTE EN MISION.\n3.DE BAJA.\n");
        scanf("%d",&nuevoEstado);
        if(cambiado->NaveGuardada.Estado==nuevoEstado)
        {
            printf("\nLA NAVE YA SE ENCUENTRA EN ESTADO.\n");
        }
        //CASOS PARA LA NAVE EN MANTENIMIENTO
        else if(cambiado->NaveGuardada.Estado==0 && nuevoEstado==1)
        {
            cambiado->NaveGuardada.Estado=1;    //cambia de en mantenimiento a lista
        }
        else if(cambiado->NaveGuardada.Estado==0 && nuevoEstado==2)
        {
            printf("\nEROR\nLA NAVE SE ENCUENTRA EN  MANTENIMIENTO.\n");   // no puede cambiar de mantenimiento a en vuelo
        }
        else if(cambiado->NaveGuardada.Estado==0 && (nuevoEstado==3))
        {
            cambiado->NaveGuardada.Estado=3;    // Se dio de baja la nave que estaba en mantenimiento.
        }
        //CASOS PARA LA NAVE LISTA PARA SU USO
        else if(cambiado->NaveGuardada.Estado==1 && nuevoEstado==0)
        {
            cambiado->NaveGuardada.Estado=0; //Paso de lista a mantenimiento.
        }
        else if(cambiado->NaveGuardada.Estado==1 && nuevoEstado==2)
        {
            cambiado->NaveGuardada.Estado=2;   //Cambia de lista a En vuelo
        }
        else if(cambiado->NaveGuardada.Estado==1 && nuevoEstado==3)
        {
            cambiado->NaveGuardada.Estado=3; //Cambia de lista De baja
        }
        //CASOS PARA LA NAVE EN VUELO.
        else if(cambiado->NaveGuardada.Estado==2 && nuevoEstado==0)
        {
            cambiado->NaveGuardada.Estado=0;  //Cambia de En vuelo a mantenimiento( se interpreta que hay un retorno)
        }
        else if(cambiado->NaveGuardada.Estado==2 && nuevoEstado==1)
        {
            cambiado->NaveGuardada.Estado=0;// Cambia de En vuelo a Listo (non-sense)
        }
        else if(cambiado->NaveGuardada.Estado==2 && (nuevoEstado==3))
        {
            printf("\nERROR\nLA NO PUEDE DARSE DE BAJA EN ESTE MOMENTO.\n");
        }
        //CASOS PARA LA NAVE DE BAJA
        else if(cambiado->NaveGuardada.Estado==3 )
        {
            printf("\nLA NAVE SE ENCUENTRA EN ESTADO DE BAJA.");
        }


    }
}
nodoNave * ArchivoToListaNaves() //ARMA UNA LISTA DOBLE DE NAVES A PARTIR DE UN ARCHIVO DE NAVES GUARDADAS
{
    Nave aux;
    nodoNave * ListaDoble=inicNodoNave();
    FILE * Archivo=fopen("Naves","rb");
    if(Archivo)
    {
        while(fread(&aux,sizeof(Nave),1,Archivo)>0)
        {
            ListaDoble=AgregarPpioNave(ListaDoble,CrearNodoNave(aux));
        }
    }
    fclose(Archivo);
    return ListaDoble;
}
void GrabarListaNaves(nodoNave * Lista) //GUARDA EN ARCHIVO LAS NAVES DE UNA LISTA DOBLE DE NAVES
{
    if(Lista)
    {
        FILE * Archivo=fopen("Naves","wb");
        if(Archivo)
        {
            while(Lista)
            {
                fwrite(&(Lista->NaveGuardada), sizeof(Nave),1,Archivo);
                Lista=Lista->siguiente;
            }
            fclose(Archivo);
        }
    }
}
Nave cargarNaveMision(nodoNave * listaNaves) //DEVUELVE UNA NAVE DISPONIBLE SELECCIONADA POR ID Y LE CAMBIA EL ESTADO A "EN MISION"
{
    printf("\n - LISTA DE NAVES - \n");
    MostrarNavesDisponibles(listaNaves);

    int idBuscado;

    nodoNave* encontrado = NULL;
    Nave encontrada = InicNave();

    do
    {
        printf("\nINGRESE EL ID DE LA NAVE QUE DESEA SELECCIONAR: ");
        fflush(stdin);
        scanf("%i", &idBuscado);
        if(ExisteNaveID(listaNaves, idBuscado))
        {
            encontrado = BuscarNodoNave(listaNaves, idBuscado);
        }
        else
        {
            printf("\nLA NAVE NO EXISTE, INGRESE NUEVAMENTE:\n");
        }

    }while(!ExisteNaveID(listaNaves, idBuscado) || BuscarNodoNave(listaNaves, idBuscado)->NaveGuardada.Estado!=1 );

    enVueloNave(encontrado);
    encontrada = encontrado->NaveGuardada;

    GrabarListaNaves(listaNaves);

    return encontrada; //retornar la nave guardada en el nodo retornado por BuscarNodoNave;
}

void enVueloNave(nodoNave * volando) //LE CAMBIA EL ESTADO A "EN MISION" A UNA NAVE GUARDADA EN UN NODO RECIBIDO POR PARAMETRO
{
    if(volando && volando->NaveGuardada.Estado==1)
    {
        volando->NaveGuardada.Estado=2;
    }
}

void MenuNaves(nodoNave * ListaDeNaves)
{
    //nodoNave * ListaDeNaves=ArchivoToListaNaves();

    int opcion;

    do
    {


        printf("\n\tNAVES\n");
        printf("\n--------------------------------\n");
        printf("\n\t1-ALTAS\n");
        printf("\n\t2-BAJAS\n");
        printf("\n\t3-MODIFICACIONES\n");
        printf("\n\t4-CONSULTAS\n");
        printf("\n\t5-LISTADOS\n");
        printf("\n\t6-VOLVER\n");
        printf("\n--------------------------------\n");

        printf("\n\t\tElija una opci%cn: ",162);
        scanf("%d",&opcion);
        system("cls");

        switch(opcion)
        {

        case 1:
            ListaDeNaves=CargarMultiplesNaves(ListaDeNaves);
            GrabarListaNaves(ListaDeNaves);
            printf("\n\n\n");
            system("cls");
            break;

        case 2:
            BajaNave(ListaDeNaves);
            GrabarListaNaves(ListaDeNaves);
            printf("\n\n\n");
            system("pause");
            system("cls");
            break;

        case 3:
            ModificarNave(ListaDeNaves);
            GrabarListaNaves(ListaDeNaves);
            printf("\n\n\n");
            system("pause");
            system("cls");
            break;

        case 4:
            ConsultarNave(ListaDeNaves);
            printf("\n\n\n");
            system("pause");
            system("cls");
            break;

        case 5:
            printf("\tELIJA LA OPCION:\n\n");
            printf("\t1.TODAS LAS NAVES.\n\n");
            printf("\t2.NAVES DISPONIBLES.\n");

            scanf("%d",&opcion);
            switch(opcion)
            {
            case 1:
                MostrarListaNaves(ListaDeNaves);
                system("pause");
                system("cls");
                break;
            case 2:
                MostrarNavesDisponibles(ListaDeNaves);
                system("pause");
                system("cls");
                break;
            }
        }
    }
    while(opcion!=6);
}
