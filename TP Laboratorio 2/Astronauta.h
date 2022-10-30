#ifndef ASTRONAUTA_H_INCLUDED
#define ASTRONAUTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int id;
    char nombre[20];
    char apellido[20];
    char apodo[20];
    int edad;
    char nacionalidad[20];
    char especialidad[20];
    int horasDeVuelo;
    int misiones;
    int horasEEI;
    int estado;
    int enMision;
} Astronauta;

typedef struct
{
    Astronauta dato;
    struct nodoAstroArbol* izq;
    struct nodoAstroArbol* der;
}nodoAstroArbol;

typedef struct
{
    Astronauta dato;
    struct nodoAstroLista* sig;
}nodoAstroLista;


//F U N C I O N E S   D E   A S T R O N A U T A
Astronauta crearAstronautaManual(int idRecibido);
int IngresarEdad();
int ingresarHsDeVuelo();
int IngresarHsEEI();
void mostrarAstronauta(Astronauta recibido);


//F U N C I O N E S   D E   A R B O L

//FUNCIONES BASICAS DE ARBOL
nodoAstroArbol* inicArbol();
nodoAstroArbol* crearNodoArbol(Astronauta recibido);
nodoAstroArbol* agregarOrdenadoArbol(nodoAstroArbol* raiz, nodoAstroArbol* nuevo);

//MOSTRAR ASTRONAUTA
void mostrarArbolInOrder(nodoAstroArbol* raiz);
void mostrarActivosArbol(nodoAstroArbol* raiz); //muestra los que estan Activos
void mostrarDisposiblesArbol(nodoAstroArbol* raiz);
void mostrarBajasArbol(nodoAstroArbol* raiz); //muestra los que estan de baja

//VALIDACIONES y BUSQUEDAS
int existeAstroEnArbol(nodoAstroArbol* raiz, int idBuscado);
int enMisionAstroEnArbol(nodoAstroArbol* raiz, int idBuscado);
nodoAstroArbol* buscarAstroArbolPorId(nodoAstroArbol* raiz, int idBuscado);

//DAR DE BAJA ASTRONAUTA
void bajaAstronauta(nodoAstroArbol * arbol, int);
void bajaDeTripulacion(int A[],int validos,nodoAstroArbol * arbol);

//FUNCIONES DE MODIFICAR ASTRONAUTA
void modificarAstronauta(nodoAstroArbol * arbol,int );
void aumentarHsVueloAstronauta(nodoAstroArbol * modificado);
void aumentarHsEEI(nodoAstroArbol * modificado);

//FUNCIONES DE ARCHIVO DE ARBOL
void guardarAstronautasEnArchivo(nodoAstroArbol* raiz);
nodoAstroArbol* leerAstronautasDeArchivo();//levanta archivo en lista
void fwriteRecursivoArbol(nodoAstroArbol* raiz, FILE *);



//F U N C I O N E S   D E   L I S T A SIMPLE
nodoAstroLista* inicListaAstro();
nodoAstroLista* crearNodoListaAstro(Astronauta recibido);
nodoAstroLista* agregarAlFinalAstro(nodoAstroLista* lista, nodoAstroLista* nuevo);
int existeAstroEnLista(nodoAstroLista* lista, int idBuscado);
nodoAstroLista* buscarAstroListaPorId(nodoAstroLista* lista, int idBuscado);
void mostrarListaAstro(nodoAstroLista* lista);
nodoAstroLista* cargarAstronautasMision(nodoAstroArbol *);

// F U N C I O N E S   D E   M E N U
void menuAstronauta(nodoAstroArbol *);
nodoAstroArbol* altaAstronauta(nodoAstroArbol* arbolDeAstros);


#endif // ASTRONAUTA_H_INCLUDED
