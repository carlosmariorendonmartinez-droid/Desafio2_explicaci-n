#ifndef MENSAJEPUBLICIDAD_H
#define MENSAJEPUBLICIDAD_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

/*
    Clase MensajePublicidad
    ------------------------
    Representa un mensaje de publicidad, con su ID, texto, categoría
    y una prioridad que se usa para seleccionar mensajes al azar.

    Esta clase NO usa memoria dinámica y NO sobrecarga operadores.
*/
class MensajePublicidad {
private:

    // ID único del mensaje
    int id;

    // El contenido del mensaje publicitario
    std::string mensaje;

    // Categoría del mensaje (por ejemplo A, B, C)
    std::string categoria;

    // Prioridad para elegirlo aleatoriamente (más alta → más probabilidad)
    int prioridad;

public:

    // ------------------------------------------------------------
    // Constructor por defecto
    // Inicializa con valores básicos.
    // ------------------------------------------------------------
    MensajePublicidad();

    // ------------------------------------------------------------
    // Constructor con parámetros
    // Permite inicializar un mensaje real.
    // El parámetro prioridad tiene valor por defecto = 1.
    // ------------------------------------------------------------
    MensajePublicidad(int _id, const std::string& _mensaje,
                      const std::string& _categoria, int _prioridad = 1);

    // ------------------------------------------------------------
    // Destructor
    // No hay memoria dinámica, por eso está vacío.
    // ------------------------------------------------------------
    ~MensajePublicidad();


    // ---------------- GETTERS ----------------
    int getPrioridad() const;
    int getId() const;
    std::string getMensaje() const;
    std::string getCategoria() const;

    // ------------------------------------------------------------
    // inicializarAzar()
    // Método estático.
    // Inicializa la semilla aleatoria del sistema.
    // ------------------------------------------------------------
    static void inicializarAzar();

    // ------------------------------------------------------------
    // elegirAleatorio()
    // Método estático.
    // Recibe un arreglo de mensajes y escoge uno según su prioridad.
    // Intenta evitar repetir al último mensaje mostrado.
    // Devuelve el índice del mensaje en el arreglo.
    // ------------------------------------------------------------
    static int elegirAleatorio(const MensajePublicidad* lista,
                               int cantidad, int ultimoId);
};

#endif
