#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include "cancion.h"

// ------------------------------------------------------------
// Declaración adelantada de la clase Artista
// (esto evita dependencias circulares)
// ------------------------------------------------------------
class Artista;

// ------------------------------------------------------------
// Clase Album
// Archivo: album.h
// ------------------------------------------------------------
class Album {
private:

    // --------------------------------------------------------
    // Atributos básicos del álbum
    // Ubicación: líneas 12–20
    // --------------------------------------------------------
    std::string id;              // Identificador del álbum
    std::string idArtista;       // ID del artista dueño del álbum
    std::string rutaPortada;     // Ruta a la imagen de portada
    std::string nombre;          // Nombre del álbum
    std::string genero;          // Género musical
    int anio;                    // Año de lanzamiento
    std::string sello;           // Sello discográfico
    int puntuacion;              // Puntuación asignada por usuarios
    int duracionTotalAlbum;      // Duración total del álbum en segundos/minutos según formato

    // --------------------------------------------------------
    // Manejo de canciones
    // Aquí es donde se usa la MEMORIA DINÁMICA
    // Ubicación: líneas 22–25
    // --------------------------------------------------------
    Cancion** canciones; // Arreglo dinámico de punteros a Cancion
    int totalCanciones;  // Número actual de canciones
    int capacidad;       // Capacidad del arreglo dinámico

    // --------------------------------------------------------
    // Relación con la clase Artista
    // Ubicación: línea 27
    // --------------------------------------------------------
    Artista* artista;    // Puntero al artista dueño del álbum

    // --------------------------------------------------------
    // Función privada
    // Ubicación: líneas 29–30
    //
    // ampliarEspacio() duplica el tamaño del arreglo dinámico
    // cuando ya no alcanza para más canciones.
    // --------------------------------------------------------
    void ampliarEspacio();

public:

    // --------------------------------------------------------
    // CONSTRUCTORES
    // Ubicación: líneas 33–38
    // --------------------------------------------------------

    Album();  
    // Constructor vacío → inicializa valores por defecto
    // y crea un arreglo dinámico de tamaño inicial CAPACIDAD_INICIAL.

    Album(const std::string& _id, const std::string& _idArtista,
          const std::string& _nombre, const std::string& _genero,
          const std::string& _fecha, int _duracion,
          const std::string& _sello, int _puntuacion,
          const std::string& _rutaPortada);
    // Constructor completo → recibe todos los datos del álbum
    // e inicializa también el arreglo dinámico de canciones.

    // --------------------------------------------------------
    // DESTRUCTOR
    // Ubicación: línea 39
    //
    // Libera la memoria dinámica usada por "canciones".
    // --------------------------------------------------------
    ~Album();

    // --------------------------------------------------------
    // agregarCancion
    // Ubicación: línea 41
    //
    // Agrega una canción al álbum:
    // 1. Evita duplicados
    // 2. Amplía el arreglo si está lleno
    // 3. Inserta la canción y suma contador
    // --------------------------------------------------------
    bool agregarCancion(Cancion* c);

    // --------------------------------------------------------
    // GETTERS
    // Ubicación: líneas 42–47
    //
    // Devuelven información simple del álbum.
    // No usan memoria dinámica.
    // --------------------------------------------------------
    std::string getIdArtista() const { return idArtista; }
    std::string getNombre() const { return nombre; }
    int getTotalCanciones() const { return totalCanciones; }
    std::string getRutaPortada() const { return rutaPortada; }

    // --------------------------------------------------------
    // Relación con la clase Artista
    // Ubicación: líneas 49–51
    //
    // getArtista → devuelve el puntero al artista
    // setArtista → asigna el artista al álbum
    // --------------------------------------------------------
    void setArtista(Artista* a) { artista = a; }
    Artista* getArtista() const { return artista; }
};

#endif
