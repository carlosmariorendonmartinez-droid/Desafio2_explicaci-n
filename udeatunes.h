#ifndef UDEATUNES_H
#define UDEATUNES_H

// Aquí se incluyen todas las clases que usa UdeATunes.
// Estas clases estarán en otros archivos .h
#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "mensajepublicidad.h"
#include "listafavoritos.h"

class UdeATunes {
private:

    // ============================
    //     MEMORIA DINÁMICA
    // ============================
    // Cada uno de estos es un arreglo dinámico que se crea con "new"
    // en el constructor de UdeATunes.
    // Ubicación: Parte privada de la clase.
    Usuario** usuarios;              // Arreglo dinámico de punteros a Usuario
    Artista** artistas;              // Arreglo dinámico de punteros a Artista
    Cancion** canciones;             // Arreglo dinámico de punteros a Cancion
    Album** albumes;                 // Arreglo dinámico de punteros a Album
    MensajePublicidad* publicidades; // Arreglo dinámico (no punteros) de objetos

    // Variables que llevan el control de cuántos elementos están llenos.
    int totalUsuarios, totalArtistas, totalAlbumes, totalCanciones, totalPublicidades;

    // Capacidades de los arreglos dinámicos (para saber cuándo duplicarlos)
    int capacidadUsuarios, capacidadArtistas, capacidadAlbumes, capacidadCanciones, capacidadPublicidades;

    // Contadores para estadísticas internas
    unsigned long iteraciones;
    unsigned long memoriaEstimadaBytes;

    // Para evitar mostrar la misma publicidad 2 veces seguidas
    int ultimoAnuncioId;

    // =====================================================
    //      FUNCIONES PRIVADAS DE EXPANSIÓN DE MEMORIA
    // =====================================================
    // Todas estas funciones duplican la capacidad de los arreglos dinámicos
    // usando new[] y delete[] para manejar memoria manualmente.
    // Ubicación: Parte private, después de atributos.
    void asegurarCapacidadUsuarios();
    void asegurarCapacidadArtistas();
    void asegurarCapacidadCanciones();
    void asegurarCapacidadPublicidades();
    void asegurarCapacidadAlbumes();

public:

    // =============================
    //   CONSTRUCTOR Y DESTRUCTOR
    // =============================

    // Se encuentra en: parte pública del .h
    // En UdeATunes.cpp se reserva memoria dinámica para todos los arreglos.
    UdeATunes();

    // Libera TODA la memoria dinámica reservada con new en la clase.
    ~UdeATunes();

    // ===========================================
    //     FUNCIONES DE BÚSQUEDA (PÚBLICAS)
    // ===========================================

    // Busca canción por ID dentro del arreglo dinámico canciones[]
    // Hace recorrido lineal.
    Cancion* buscarCancionPorId(int id);

    // Busca canción por nombre comparando el título convertido en minúsculas
    Cancion* buscarCancionPorNombre(const std::string& nombre);

    // Busca objeto Usuario por su nickname.
    Usuario* buscarUsuario(const std::string& nickname);

    // ================================
    //  INICIALIZACIÓN GENERAL
    // ================================
    // Inicializa la semilla de publicidad y calcula memoria base asignada.
    void inicializar();

    // ======================================
    //  REPRODUCCIÓN ALEATORIA
    // ======================================
    // Toca canciones al azar. Si esPremium = true no se muestran anuncios.
    void reproducirAleatorio(int k, bool esPremium = false);

    // ==========================================
    //  CARGA DE ARCHIVOS EXTERNOS
    // ==========================================
    // Todas estas funciones leen archivos .txt y crean objetos dinámicos.
    void cargarAlbumesDesdeArchivo(const std::string& ruta);
    void cargarUsuariosDesdeArchivo(const char* ruta);
    void cargarPublicidadesDesdeArchivo(const char* ruta);
    void cargarCancionesDesdeArchivo(const std::string& ruta);
    void cargarArtistasDesdeArchivo(const char* ruta);
    void cargarFavoritosDesdeArchivo(const char* ruta);

    // Guarda lista de favoritos en un archivo de texto.
    void guardarFavoritosEnArchivo(const char* ruta = "favoritos.txt");

    // Muestra el menú principal para cualquier usuario
    void menuPrincipal();

    // Carga todos los archivos del sistema al inicio del programa
    void cargarArchivos();

    // ==========================================
    //  MÉTODOS PARA ESTADÍSTICAS
    // ==========================================
    // Estas funciones solo cuentan operaciones y memoria para análisis.
    void sumarIteraciones(unsigned long n = 1);
    void sumarMemoria(size_t bytes);
    void restarMemoria(size_t bytes);
    void mostrarEstadisticas() const;

    // ==========================================
    //  MENÚS DEPENDIENDO DEL TIPO DE USUARIO
    // ==========================================
    void menuPremium(Usuario* user);
    void menuEstandar(Usuario* user);

    // Vincula canciones con su álbum y artista después de cargar todo.
    void enlazarCancionesConAlbumesYArtistas();
};

#endif
