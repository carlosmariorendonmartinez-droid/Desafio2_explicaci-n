#include "cancion.h"
using namespace std;

// ------------------------------------------------------------
// CONSTRUCTOR VACÍO
// Ubicación: líneas 4–14
// No usa memoria dinámica.
// ------------------------------------------------------------
Cancion::Cancion() {
    id = 0;
    titulo = "Sin título";
    duracion = 0;

    // Rutas de los archivos (baja y alta calidad)
    rutaBaja = "";
    rutaAlta = "";

    albumID = "";          // Relación con su álbum por ID
    reproducciones = 0;    // Contador de veces reproducida

    // Puntero al álbum al que pertenece
    // (No se crea dinámicamente, solo se apunta)
    album = nullptr;
}



// ------------------------------------------------------------
// CONSTRUCTOR CON PARÁMETROS
// Ubicación: líneas 16–27
// No usa memoria dinámica.
// ------------------------------------------------------------
Cancion::Cancion(int _id, const string& _titulo, int _duracion,
                 const string& _rutaBaja, const string& _rutaAlta,
                 const string& _albumID) {

    id = _id;
    titulo = _titulo;
    duracion = _duracion;
    rutaBaja = _rutaBaja;
    rutaAlta = _rutaAlta;
    albumID = _albumID;

    reproducciones = 0;  // Siempre inicia en cero

    album = nullptr;    // No se asigna álbum todavía
}



// ------------------------------------------------------------
// CONSTRUCTOR DE COPIA
// Ubicación: líneas 29–38
//
// Este constructor copia todos los atributos de otra canción.
// IMPORTANTE: No usa memoria dinámica, solo copia valores.
// ------------------------------------------------------------
Cancion::Cancion(const Cancion& otra) {
    id = otra.id;
    titulo = otra.titulo;
    duracion = otra.duracion;
    rutaBaja = otra.rutaBaja;
    rutaAlta = otra.rutaAlta;
    albumID = otra.albumID;
    reproducciones = otra.reproducciones;

    // Copia el puntero al álbum (shallow copy)
    album = otra.album;
}



// ------------------------------------------------------------
// SOBRECARGA DE OPERADOR ASIGNACIÓN (=)
// Ubicación: líneas 40–54
//
// Permite hacer:
//     c1 = c2;
//
// Realiza lo mismo que el constructor de copia.
// ------------------------------------------------------------
Cancion& Cancion::operator=(const Cancion& otra) {

    // Evita copiar sobre sí misma
    if (this == &otra) return *this;

    id = otra.id;
    titulo = otra.titulo;
    duracion = otra.duracion;
    rutaBaja = otra.rutaBaja;
    rutaAlta = otra.rutaAlta;
    albumID = otra.albumID;
    reproducciones = otra.reproducciones;

    album = otra.album;  // Copia del puntero existente

    return *this;
}



// ------------------------------------------------------------
// DESTRUCTOR
// Ubicación: líneas 55–56
//
// No maneja memoria dinámica → destructor vacío.
// ------------------------------------------------------------
Cancion::~Cancion() {}



// ------------------------------------------------------------
// sumarReproduccion()
// Ubicación: líneas 58–60
// Incrementa en 1 el contador de reproducciones.
// ------------------------------------------------------------
void Cancion::sumarReproduccion() {
    reproducciones++;
}



// ------------------------------------------------------------
// GETTERS Y SETTERS
// Ubicación: líneas 61–76
//
// Devuelven los valores básicos de la canción.
// ------------------------------------------------------------
int Cancion::getId() const { return id; }
string Cancion::getTitulo() const { return titulo; }
int Cancion::getDuracion() const { return duracion; }
long Cancion::getReproducciones() const { return reproducciones; }
string Cancion::getRutaAlta() const { return rutaAlta; }
string Cancion::getRutaBaja() const { return rutaBaja; }
string Cancion::getAlbumID() const { return albumID; }

void Cancion::setAlbum(Album* a) { album = a; }
Album* Cancion::getAlbum() const { return album; }



// ------------------------------------------------------------
// SOBRECARGA DE OPERADOR ==
// Ubicación: líneas 79–82
//
// Compara dos canciones por su ID.
//     if (c1 == c2)
// ------------------------------------------------------------
bool Cancion::operator==(const Cancion& otra) const {
    return id == otra.id;
}



// ------------------------------------------------------------
// SOBRECARGA DE OPERADOR <<
// Ubicación: líneas 85–92
//
// Permite imprimir una canción usando:
//
//     cout << cancion;
//
// ------------------------------------------------------------
ostream& operator<<(ostream& os, const Cancion& c) {
    os << "Canción: " << c.getTitulo()
       << " | Duración: " << c.getDuracion() << " seg"
       << " | ID: " << c.getId();

    return os;
}
