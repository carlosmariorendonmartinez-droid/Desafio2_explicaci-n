#include "colaborador.h"
#include <iostream>
using namespace std;

// ------------------------------------------------------------
// CONSTRUCTOR VACÍO
// Ubicación: líneas 4–10
//
// Inicializa todos los atributos del colaborador con cadenas vacías.
// NO usa memoria dinámica.
// ------------------------------------------------------------
Colaborador::Colaborador() {
    nombre = "";
    apellido = "";
    codigoAfiliacion = "";
    tipo = "";   // Productor, Músico o Compositor según el sistema
}


// ------------------------------------------------------------
// CONSTRUCTOR CON PARÁMETROS
// Ubicación: líneas 12–17
//
// Recibe datos reales de un colaborador y los asigna a los atributos.
// Tampoco usa memoria dinámica.
// ------------------------------------------------------------
Colaborador::Colaborador(const string& nom, const string& ape,
                         const string& cod, const string& tipo) {

    this->nombre = nom;
    this->apellido = ape;
    this->codigoAfiliacion = cod;
    this->tipo = tipo;
}



// ------------------------------------------------------------
// DESTRUCTOR
// Ubicación: líneas 19–20
//
// No se usa memoria dinámica en esta clase,
// por eso el destructor está vacío.
// ------------------------------------------------------------
Colaborador::~Colaborador() {}



// ------------------------------------------------------------
// mostrar()
// Ubicación: líneas 22–26
//
// Imprime por consola la información del colaborador.
// Sirve como método de visualización.
// ------------------------------------------------------------
void Colaborador::mostrar() const {
    cout << "Colaborador: " << nombre << " " << apellido
         << " | Código: " << codigoAfiliacion
         << " | Tipo: " << tipo << endl;
}



