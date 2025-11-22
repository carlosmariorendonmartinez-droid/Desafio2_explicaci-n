#include "artista.h"
using namespace std;
#define CAPACIDAD_INICIAL 3

// --------------------------------------------------------------
// CONSTRUCTOR VACÍO
// Ubicación: líneas 5–13
// --------------------------------------------------------------
Artista::Artista() {

    // Valores por defecto para un artista sin datos
    nombre = "Desconocido";
    pais = "N/A";

    totalAlbumes = 0;
    capacidad = CAPACIDAD_INICIAL; // capacidad inicial = 3

    // ----------------------------------------------------------
    // MEMORIA DINÁMICA:
    // Se crea un arreglo dinámico de punteros a Album.
    // Este arreglo podrá crecer usando ampliarEspacio().
    // ----------------------------------------------------------
    albumes = new Album*[capacidad];

    // Inicializo las posiciones con nullptr
    for (int i = 0; i < capacidad; ++i)
        albumes[i] = nullptr;
}



// --------------------------------------------------------------
// CONSTRUCTOR CON PARÁMETROS
// Ubicación: líneas 15–23
// --------------------------------------------------------------
Artista::Artista(const string& _nombre, const string& _pais) {

    // Asigno los valores entregados
    nombre = _nombre;
    pais = _pais;

    totalAlbumes = 0;
    capacidad = CAPACIDAD_INICIAL;

    // MEMORIA DINÁMICA: igual que en el otro constructor
    albumes = new Album*[capacidad];

    // Inicializo posiciones
    for (int i = 0; i < capacidad; ++i)
        albumes[i] = nullptr;
}



// --------------------------------------------------------------
// DESTRUCTOR
// Ubicación: líneas 25–28
// --------------------------------------------------------------
Artista::~Artista() {

    // ----------------------------------------------------------
    // MEMORIA DINÁMICA
    // Libera el arreglo de punteros creado con new[].
    // No elimina los álbumes porque no fueron creados aquí.
    // ----------------------------------------------------------
    delete[] albumes;
}



// --------------------------------------------------------------
// ampliarEspacio()
// Ubicación: líneas 30–47
// Duplica la capacidad del arreglo cuando se llena.
// --------------------------------------------------------------
void Artista::ampliarEspacio() {

    int nuevaCapacidad = capacidad * 2;

    // MEMORIA DINÁMICA: creo un arreglo más grande
    Album** nuevaLista = new Album*[nuevaCapacidad];

    // Copio los álbumes existentes al nuevo arreglo
    for (int i = 0; i < totalAlbumes; ++i)
        nuevaLista[i] = albumes[i];

    // Inicializo el resto en nullptr
    for (int i = totalAlbumes; i < nuevaCapacidad; ++i)
        nuevaLista[i] = nullptr;

    // Libero memoria del arreglo anterior
    delete[] albumes;

    // Actualizo puntero y capacidad
    albumes = nuevaLista;
    capacidad = nuevaCapacidad;
}



// --------------------------------------------------------------
// agregarAlbum()
// Ubicación: líneas 49–63
// Agrega un álbum al artista evitando duplicados.
// --------------------------------------------------------------
bool Artista::agregarAlbum(Album* a) {

    // Verifico que el puntero sea válido
    if (a == nullptr) return false;

    // Verifico que no exista ya el álbum en la lista
    for (int i = 0; i < totalAlbumes; ++i)
        if (albumes[i] == a)
            return false; // duplicado

    // Si se alcanzó la capacidad actual → la duplico
    if (totalAlbumes >= capacidad)
        ampliarEspacio();

    // Inserto el nuevo álbum
    albumes[totalAlbumes] = a;
    totalAlbumes++;

    return true;
}



// --------------------------------------------------------------
// getNombre()
// Ubicación: líneas 65–69
// Devuelve el nombre del artista.
// --------------------------------------------------------------
string Artista::getNombre() const {
    return nombre;
}




