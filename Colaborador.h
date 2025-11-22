#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <iostream>

// ------------------------------------------------------------
// Clase Colaborador
// Archivo: colaborador.h
//
// Representa a un colaborador musical (productor, músico,
// compositor). Solo almacena información básica.
// ------------------------------------------------------------
class Colaborador {
private:

    // --------------------------------------------------------
    // Atributos básicos del colaborador
    // Ubicación: líneas 10–13
    // --------------------------------------------------------
    std::string nombre;            // Nombre del colaborador
    std::string apellido;          // Apellido del colaborador
    std::string codigoAfiliacion;  // Código de la sociedad de autores
    std::string tipo;              // Tipo de colaborador (músico, productor, etc.)

public:

    // --------------------------------------------------------
    // CONSTRUCTORES
    // Ubicación: líneas 15–17
    //
    // No usan memoria dinámica. Solo inicializan strings.
    // --------------------------------------------------------
    Colaborador();
    Colaborador(const std::string& nom, const std::string& ape,
                const std::string& cod, const std::string& tipo);

    // --------------------------------------------------------
    // DESTRUCTOR
    // Ubicación: línea 19
    //
    // Clase sin memoria dinámica → destructor vacío.
    // --------------------------------------------------------
    ~Colaborador();

    // --------------------------------------------------------
    // mostrar()
    // Ubicación: línea 21
    //
    // Imprime los datos del colaborador en consola.
    // --------------------------------------------------------
    void mostrar() const;

    // --------------------------------------------------------
    // GETTERS
    // Ubicación: líneas 23–26
    //
    // Devuelven información individual del colaborador.
    // --------------------------------------------------------
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    std::string getCodigo() const { return codigoAfiliacion; }
    std::string getTipo() const { return tipo; }

    
};

#endif // COLABORADOR_H
