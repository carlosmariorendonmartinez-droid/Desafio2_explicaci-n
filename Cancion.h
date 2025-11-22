#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// ------------------------------------------------------------
// Declaración adelantada de Album
// (evita dependencias circulares)
// ------------------------------------------------------------
class Album;


// ------------------------------------------------------------
// Clase Cancion
// Archivo: cancion.h
//
// Representa una canción individual dentro del sistema,
// con su información básica y estadísticas de reproducción.
// ------------------------------------------------------------
class Cancion {
private:

    // --------------------------------------------------------
    // Atributos básicos de la canción
    // Ubicación: líneas 14–21
    // --------------------------------------------------------
    int id;                    // Identificador único (9 dígitos)
    std::string titulo;        // Nombre de la canción
    int duracion;              // Duración en segundos
    std::string rutaBaja;      // Ruta del archivo .ogg de 128 kbps
    std::string rutaAlta;      // Ruta del archivo .ogg de 320 kbps
    std::string albumID;       // ID del álbum al que pertenece
    long reproducciones;       // Veces que se ha reproducido

    // Puntero al álbum dueño
    // NO es memoria dinámica, solo un puntero externo
    Album* album;

public:

    // --------------------------------------------------------
    // CONSTRUCTORES
    // Ubicación: líneas 23–29
    // No usan memoria dinámica.
    // --------------------------------------------------------
    Cancion();
    Cancion(int _id, const std::string& _titulo, int _duracion,
            const std::string& _rutaBaja, const std::string& _rutaAlta, const std::string& _albumID);

    // --------------------------------------------------------
    // CONSTRUCTOR DE COPIA
    // Ubicación: línea 30
    // Copia todos los atributos de otra Cancion
    // --------------------------------------------------------
    Cancion(const Cancion& otra);

    // --------------------------------------------------------
    // OPERADOR DE ASIGNACIÓN (=)
    // Ubicación: línea 31
    //
    // Permite hacer: c1 = c2;
    // Copia exactamente los mismos atributos.
    // --------------------------------------------------------
    Cancion& operator=(const Cancion& otra);

    // --------------------------------------------------------
    // DESTRUCTOR
    // Ubicación: línea 32
    // No usa memoria dinámica → destructor vacío.
    // --------------------------------------------------------
    ~Cancion();


    // --------------------------------------------------------
    // MÉTODO sumarReproduccion()
    // Ubicación: línea 34
    //
    // Aumenta en 1 el contador de reproducciones.
    // --------------------------------------------------------
    void sumarReproduccion();


    // --------------------------------------------------------
    // GETTERS Y SETTERS
    // Ubicación: líneas 36–44
    // Devuelven datos básicos de la canción.
    // --------------------------------------------------------
    int getId() const;
    std::string getTitulo() const;
    int getDuracion() const;
    long getReproducciones() const;
    std::string getRutaAlta() const;
    std::string getRutaBaja() const;
    std::string getAlbumID() const;

    void setAlbum(Album* a);   // Asigna el puntero al álbum
    Album* getAlbum() const;   // Devuelve el álbum dueño


    // --------------------------------------------------------
    // SOBRECARGA DE OPERADOR ==
    // Ubicación: línea 46
    //
    // Compara dos canciones por su ID:
    //      if (c1 == c2)
    // --------------------------------------------------------
    bool operator==(const Cancion& otra) const;


    // --------------------------------------------------------
    // SOBRECARGA DE OPERADOR <<
    // Ubicación: línea 47
    //
    // Permite imprimir la canción con:
    //      cout << cancion;
    //
    // Como usa cout, debe ser friend.
    // --------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const Cancion& c);
};

#endif
