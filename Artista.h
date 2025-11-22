#ifndef ARTISTA_H
#define ARTISTA_H

#include <iostream>
#include <string>
#include "album.h"

// ------------------------------------------------------------
// Clase Artista
// Archivo: artista.h
//
// Esta clase representa a un artista que tiene un conjunto de
// álbumes almacenados mediante MEMORIA DINÁMICA.
// ------------------------------------------------------------
class Artista {
private:

    // --------------------------------------------------------
    // Atributos básicos del artista
    // Ubicación: líneas 12–13
    // --------------------------------------------------------
    std::string nombre;   // Nombre del artista
    std::string pais;     // País de origen del artista


    // --------------------------------------------------------
    // Manejo de álbumes con MEMORIA DINÁMICA
    // Ubicación: líneas 15–17
    //
    // Album** albumes:
    //   → Es un arreglo dinámico de punteros a Album.
    //   → Su tamaño puede crecer usando ampliarEspacio().
    // --------------------------------------------------------
    Album** albumes;
    int totalAlbumes;   // Cantidad actual de álbumes almacenados
    int capacidad;      // Capacidad actual del arreglo dinámico


    // --------------------------------------------------------
    // Función privada que maneja el crecimiento del arreglo
    // Ubicación: línea 19
    //
    // ampliarEspacio():
    //   → Duplica la capacidad cuando el arreglo de álbumes
    //     queda lleno.
    // --------------------------------------------------------
    void ampliarEspacio();

public:

    // --------------------------------------------------------
    // CONSTRUCTORES Y DESTRUCTOR
    // Ubicación: líneas 22–26
    // --------------------------------------------------------
    Artista();
    // Constructor vacío: inicializa el artista con valores
    // predeterminados y crea el arreglo dinámico de álbumes.

    Artista(const std::string& _nombre, const std::string& _pais);
    // Constructor con parámetros: inicializa el artista con un
    // nombre y país específicos, y crea el arreglo dinámico.

    ~Artista();
    // Destructor: libera la memoria del arreglo dinámico de álbumes.


    // --------------------------------------------------------
    // OPERACIONES DE LA CLASE
    // Ubicación: líneas 28–29
    // --------------------------------------------------------
    bool agregarAlbum(Album* a);
    // Inserta un álbum en el arreglo dinámica:
    //   1. Evita duplicados
    //   2. Verifica si hay espacio
    //   3. Llama a ampliarEspacio() si el arreglo está lleno

    std::string getNombre() const;
    // Retorna el nombre del artista.


  
};

#endif
