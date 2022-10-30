#ifndef LISTANAVES_H_INCLUDED
#define LISTANAVES_H_INCLUDED

#include "Astronauta.h"

typedef struct
{
    int idNave;
    int Tipo;//Starship, Falcon 9, Falcon Heavy
    int cantVuelos;
    int HsAcumuladas;
    int Estado;//0- mantenimiento 1- Lista para su uso 2- Actualmente en misión 3- De baja
}Nave;

typedef struct
{
    Nave NaveGuardada;
    struct nodoNave * ante;
    struct nodoNave * siguiente;
}nodoNave;

//F U N C I O N E S   D E   N A V E

Nave InicNave();
Nave CargarNave(int id);
int ingresarVuelos();
void MostrarNave(Nave );

//F U N C I O N E S   D E   L I S T A   D O B L E   D E   N A V E S

nodoNave * CargarMultiplesNaves(nodoNave *);
void ModificarNave(nodoNave * );
nodoNave * AumentarVueloHs(nodoNave * );
void CambiarEstadoNave(nodoNave * );

//FUNCIONES DE MOSTRAR LISTA DOBLE DE NAVES

void MostrarListaNaves(nodoNave *);
void MostrarNavesDisponibles(nodoNave * );

nodoNave * inicNodoNave();
nodoNave * CrearNodoNave(Nave );
nodoNave * AgregarPpioNave(nodoNave *,nodoNave *);
int ExisteNaveID(nodoNave *,int id);
nodoNave * BuscarNodoNave(nodoNave *,int );
Nave buscoNave(nodoNave* lista, int id);

//FUNCIONES DE ARCHIVO DE LISTA DOBLE DE NAVES
nodoNave * ArchivoToListaNaves();
void GrabarListaNaves(nodoNave *);
Nave cargarNaveMision(nodoNave *);
void enVueloNave(nodoNave * volando);

void MenuNaves(nodoNave *);





#endif // LISTANAVES_H_INCLUDED
