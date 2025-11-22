#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

/*
    Clase: ListaFavoritos
    Esta clase representa una lista de reproducción donde se guardan 
    IDs de canciones. La lista permite agregar, eliminar, mezclar 
    canciones y también seguir otra lista (copiando sus canciones nuevas).
*/
class ListaFavoritos {
private:

    // Nombre del usuario dueño de la lista
    std::string propietarioNick;

    // Nombre de la lista (por defecto "Favoritos")
    std::string nombreLista;

    /*
        Arreglo DINÁMICO que guarda los IDs de canciones.
        Se usa: new int[capacidad]
    */
    int *canciones;

    // Capacidad máxima del arreglo dinámico
    int capacidad;

    // Cantidad real de canciones almacenadas actualmente
    int cantidad;

    /*
        Cuando esta lista sigue a otra, se agregan canciones automáticamente.
        Este arreglo guarda SOLO esos IDs que fueron agregados "por seguimiento".
        También se maneja con memoria dinámica.
    */
    int *agregadasPorSeguir;

    // Cantidad de canciones agregadas "por seguir a otra lista"
    int cantidadAgregadasPorSeguir;

    // Nick del usuario cuya lista estamos siguiendo
    std::string siguiendoA;

    // Indica si se está siguiendo otra lista
    bool estaSiguiendo;

    /*
        Método privado:
        Busca el índice en el arreglo 'canciones' donde está un ID específico.
        Devuelve -1 si no lo encuentra.
    */
    int indiceDeCancion(int id) const;

public:

    /*
        Constructor principal:
        Crea la lista, asigna valores y reserva memoria dinámica
        para el arreglo 'canciones'.
    */
    ListaFavoritos(const std::string& propietario, const std::string& nombre = "Favoritos");

    /*
        Constructor de copia:
        Realiza una COPIA PROFUNDA (deep copy).
        Reserva nueva memoria y copia cada elemento.
    */
    ListaFavoritos(const ListaFavoritos& otro);

    /*
        Operador de asignación:
        También realiza copia profunda.
        Libera la memoria existente y copia la del otro objeto.
    */
    ListaFavoritos& operator=(const ListaFavoritos& otro);

    /*
        Destructor:
        Libera toda la memoria dinámica reservada:
        - canciones
        - agregadasPorSeguir (si existe)
    */
    ~ListaFavoritos();

    // Métodos GET simples
    std::string getPropietario() const;
    int getCantidad() const;
    int getCancionEn(int indice) const;

    /*
        agregar():
        Agrega un ID de canción si:
        - es válido
        - hay espacio
        - no está repetida
    */
    bool agregar(int idCancion);

    /*
        eliminar():
        Elimina una canción por ID.
        Utiliza eliminación rápida moviendo la última al espacio vacío.
    */
    bool eliminar(int idCancion);

    /*
        mezclar():
        Mezcla las canciones usando algoritmo tipo Fisher–Yates.
    */
    void mezclar();

    /*
        seguirOtraLista():
        Copia canciones nuevas desde otra lista.
        Guarda cuáles fueron agregadas por seguimiento.
        Usa memoria dinámica.
    */
    bool seguirOtraLista(ListaFavoritos* otra);

    /*
        dejarDeSeguir():
        Elimina solamente las canciones que se agregaron 
        por seguir otra lista.
        Libera agregadasPorSeguir.
    */
    bool dejarDeSeguir();

    /*
        Indica si esta lista actualmente está siguiendo otra.
    */
    bool estaSiguiendoOtro();
};

#endif // LISTAFAVORITOS_H
