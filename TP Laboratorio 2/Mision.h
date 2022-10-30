#ifndef MISION_H_INCLUDED
#define MISION_H_INCLUDED

#include "ListaNaves.h"

typedef struct{
int id;
int estado; // ( 0-Listo, 1-En vuelo, 2-Retornada, 3-Cancelada, 4-Fallida)
char destino[30];
char cargamento[20][20];
char detalles[50];
int tripulantes[20];
int validosTrip;
int idNave;
}Mision;

typedef struct{
Mision misionCargada;
Nave naveCargada;
nodoAstroLista* listaAstronautas;
struct nodoMision* ante;
struct nodoMision* sig;
}nodoMision;

typedef struct{
nodoMision* cabecera;
nodoMision* cola;
}Fila;

///////////////////////////

//F U N C I O N E S   D E   M I S I O N

Mision crearMision(nodoMision* listaDeMisionesTotal);
void ingresarCargamento(char cargamentoMatriz[20][20]);
void modificarMision(nodoMision* listaTotal);
void mostrarCargamento(Mision misionRecibida);
///////////////////////////

//F U N C I O N E S   D E   L I S T A

nodoMision* inicListaMision();
nodoMision * crearNodoMision(Mision Dada, nodoAstroLista * listaS, Nave navecita);
void mostrarMision(Mision dada);
void mostrarNodoMision(nodoMision* recibido);
nodoMision* agregarFinalListaMision(nodoMision* lista, nodoMision* nuevo);

///////////////////////////

//F U N C I O N E S   D E   F I L A

void inicFila(Fila* recibida);
void mostrarFila(Fila recibida);
nodoMision* cargarMisionNueva(nodoAstroArbol *,Fila* recibida, nodoMision* listaDeMisionesTotal, nodoNave *);
void agregarFinalFila(Fila* recibida, nodoMision* nuevo);
int ultimoIdListaTotal(nodoMision* listaTotal);



//FUNCIONES PARA SACAR UNA FILA DEL ARCHIVO
nodoMision * ListaTotalMisiones(nodoAstroArbol * ,nodoNave *);
nodoAstroLista* deArregloAListaTripulantes(int arregloTripulantes[], int validos, nodoAstroArbol* arbolDeAstronautas);
nodoMision* deListaCompletaToListaActivos(nodoMision* listaMisionesCompleta);
nodoMision* deArchivoToFila(Fila* recibida,nodoAstroArbol*,nodoNave*);

//FUNCIONES PARA GUARDAR UNA FILA EN ARCHIVO
int deListaTripulantesToArreglo(int arreglo[], nodoAstroLista* listaTripulantes);
void mostrarArchivo();
int extraerPrimerNodoDeFila(Fila* recibida);
nodoMision* encontrarNodoPorIdMision(nodoMision* listaTotal, int id);
nodoMision* lanzarMision(Fila* recibida, nodoMision* listaTotal);
nodoMision* cancelarMision(nodoAstroArbol* arbolAstros, Fila* recibida, nodoMision* listaTotal);
nodoMision* informarFallidaMision(nodoMision* listaTotal,nodoAstroArbol * arbol,nodoNave * naves);
void consultarMision(nodoMision * listaTotal);
void informarRetornoMision(nodoMision* ,nodoAstroArbol *,nodoNave *);
void deListaTotalToArchivo(nodoMision* listaDeMisionesTotal);

////////////////////////////

//F U N C I O N E S   D E   M E N U

void menuMisionPrincipal(Fila * , nodoMision *, nodoAstroArbol *,nodoNave *);
int selectMisionMenu();

#endif // MISION_H_INCLUDED
