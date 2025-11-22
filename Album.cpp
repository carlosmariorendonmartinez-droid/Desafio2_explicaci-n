#include "album.h"
#define CAPACIDAD_INICIAL 3
using namespace std;

// ----------------------------------------------
// CONSTRUCTOR VACÍO
// Ubicación: líneas 4–16 del archivo
// ----------------------------------------------
Album::Album() {

    // Datos básicos inicializados por defecto
    nombre = "Sin nombre";
    genero = "Desconocido";
    anio = 0;

    // Contador de canciones y capacidad inicial del arreglo
    totalCanciones = 0;
    capacidad = CAPACIDAD_INICIAL;   // capacidad = 3

    // -----------------------------
    // MEMORIA DINÁMICA
    // Se crea un arreglo dinámico de punteros a Cancion.
    // Esto permite que el tamaño crezca después.
    // -----------------------------
    canciones = new Cancion*[capacidad];

    // El artista aún no está asignado
    artista = nullptr;

    // Inicializo todas las posiciones en nullptr
    for (int i = 0; i < capacidad; ++i)
        canciones[i] = nullptr;
}


// ----------------------------------------------
// CONSTRUCTOR CON PARÁMETROS
// Ubicación: líneas 18–40 del archivo
// ----------------------------------------------
Album::Album(const std::string& _id, const std::string& _idArtista,
             const std::string& _nombre, const std::string& _genero,
             const std::string& _fecha, int _duracion,
             const std::string& _sello, int _puntuacion,
             const std::string& _rutaPortada) {

    // Asigno los valores recibidos
    id = _id;
    idArtista = _idArtista;
    nombre = _nombre;
    genero = _genero;

    // Extraigo el año de la fecha (primeros 4 dígitos)
    anio = stoi(_fecha.substr(0,4));

    rutaPortada = _rutaPortada;
    sello = _sello;
    puntuacion = _puntuacion;
    duracionTotalAlbum = _duracion;

    // Inicializo manejo de canciones
    totalCanciones = 0;
    capacidad = CAPACIDAD_INICIAL;

    // -----------------------------
    // MEMORIA DINÁMICA
    // Igual que en el constructor vacío: un arreglo de punteros
    // -----------------------------
    canciones = new Cancion*[capacidad];
    artista = nullptr;

    for (int i = 0; i < capacidad; ++i)
        canciones[i] = nullptr;
}


// ----------------------------------------------
// DESTRUCTOR
// Ubicación: líneas 42–45
// ----------------------------------------------
Album::~Album() {

    // -----------------------------
    // MEMORIA DINÁMICA
    // Libera el arreglo de punteros creado con new[]
    // (No se borran las canciones porque no fueron creadas aquí)
    // -----------------------------
    delete[] canciones;
}



// ----------------------------------------------
// ampliarEspacio()
// Ubicación: líneas 47–66
// Esta función duplica la capacidad del arreglo canciones.
// ----------------------------------------------
void Album::ampliarEspacio() {

    int nuevaCapacidad = capacidad * 2;

    // MEMORIA DINÁMICA: se crea un nuevo arreglo de tamaño mayor
    Cancion** nuevaLista = new Cancion*[nuevaCapacidad];

    // Copio las canciones existentes al nuevo arreglo
    for (int i = 0; i < totalCanciones; ++i)
        nuevaLista[i] = canciones[i];

    // El resto de posiciones se inicializan en nullptr
    for (int i = totalCanciones; i < nuevaCapacidad; ++i)
        nuevaLista[i] = nullptr;

    // Libero la memoria antigua
    delete[] canciones;

    // Actualizo puntero y capacidad
    canciones = nuevaLista;
    capacidad = nuevaCapacidad;
}



// ----------------------------------------------
// agregarCancion()
// Ubicación: líneas 68–83
// Agrega una canción al álbum, evitando duplicados.
// ----------------------------------------------
bool Album::agregarCancion(Cancion* c) {

    // Verifico que el puntero no sea nulo
    if (c == nullptr) return false;

    // Verifico que la canción no esté repetida en el arreglo
    for (int i = 0; i < totalCanciones; ++i)
        if (canciones[i] == c)
            return false;  // Ya existe → no la agrego

    // Si no hay espacio suficiente → aumento la capacidad
    if (totalCanciones >= capacidad)
        ampliarEspacio();

    // Inserto la canción y aumento el contador
    canciones[totalCanciones] = c;
    totalCanciones++;

    return true;
}


