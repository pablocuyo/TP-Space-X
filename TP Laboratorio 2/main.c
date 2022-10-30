#include <stdio.h>
#include <stdlib.h>
#include "Mision.h"

int main()
{
    Fila filaDeMisiones;
    inicFila(&filaDeMisiones);
    nodoAstroArbol* arbolDeAstros = leerAstronautasDeArchivo();
    nodoNave * ListaDeNaves=ArchivoToListaNaves();
    nodoMision* listaTotal = deArchivoToFila(&filaDeMisiones,arbolDeAstros,ListaDeNaves);


    int opcion;

    do
    {


        printf("\n  SPACE X SYSTEM SOFTWARE\n");
        printf("\n--------------------------------\n");


        printf("\n  1-ASTRONAUTAS\n");
        printf("\n  2-NAVES\n");
        printf("\n  3-MISIONES\n");
        printf("\n  4-CR%cDITOS\n",144);
        printf("\n  5-SALIR\n");



        printf("\n--------------------------------\n");

        printf("\n  Elija una opci%cn: ",162);
        scanf("%d",&opcion);
        system("cls");

        switch(opcion)
        {

        case 1:
            menuAstronauta(arbolDeAstros);
            break;

        case 2:
            MenuNaves(ListaDeNaves);
            break;

        case 3:
            menuMisionPrincipal(&filaDeMisiones,listaTotal,arbolDeAstros,ListaDeNaves);
            break;

        case 4:
            puts(" ------------------------------------------------------------------------------------");
            puts(" | ---El presente software constituye el TP Final de la asignatura laboratorio 2.-- |");
            puts(" | Ha sido desarrollado entre los dias 12 y 18 de noviembre de 2021 por los alumnos |");
            puts(" | ----------Pablo Cugini ----------------- Juan Martin Alvarez Colombo---------- . |");
            puts(" ------------------------------------------------------------------------------------");
            system("pause");
            system("cls");
            break;

        }

    }
    while(opcion!=5);

    return 0;
}


// SI NO LLENE NAVES O ASTRONAUTAS PRIMERO, NO HAY NADA PARA AGREGAR.
