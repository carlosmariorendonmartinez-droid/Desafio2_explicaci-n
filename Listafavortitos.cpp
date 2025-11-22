#include "listafavoritos.h"
#include <iostream>

using namespace std;

static const int MAX_CAP = 10000; // Capacidad máxima de la lista


// --------------------------------------------------------------------
// indiceDeCancion()
// Ubicación: líneas 9–15
// Busca el índice donde se encuentra una canción por su ID.
// Devuelve -1 si no está.
// No usa memoria dinámica.
// --------------------------------------------------------------------
int ListaFavoritos::indiceDeCancion(int id) const {
    for (int i = 0; i < cantidad; ++i) {
        if (canciones[i] == id) return i;   // Encontrada
    }
    return -1;  // No está
}


// --------------------------------------------------------------------
// CONSTRUCTOR PRINCIPAL
// Ubicación: líneas 18–28
//
// Aquí se usa MEMORIA DINÁMICA:
//   - canciones = new int[capacidad];
//   - agregadasPorSeguir = nullptr inicialmente
//
// La lista inicia vacía y con capacidad MAX_CAP.
// --------------------------------------------------------------------
ListaFavoritos::ListaFavoritos(const string& propietario, const string& nombre)
    : propietarioNick(propietario), nombreLista(nombre),
      capacidad(MAX_CAP), cantidad(0),
      agregadasPorSeguir(nullptr), cantidadAgregadasPorSeguir(0),
      siguiendoA(""), estaSiguiendo(false)
{
    // MEMORIA DINÁMICA: arreglo de IDs de canciones
    canciones = new int[capacidad];

    // Inicializo en 0
    for (int i = 0; i < capacidad; ++i) canciones[i] = 0;

    // Inicializo semilla de aleatoriedad
    srand((unsigned) time(nullptr));
}


// --------------------------------------------------------------------
// CONSTRUCTOR DE COPIA
// Ubicación: líneas 30–48
//
// Aquí también hay MEMORIA DINÁMICA:
//   - Se copia el arreglo "canciones" creando uno nuevo.
//   - Se copia "agregadasPorSeguir" si existía.
//
// Es una COPIA PROFUNDA (deep copy).
// --------------------------------------------------------------------
ListaFavoritos::ListaFavoritos(const ListaFavoritos& otro)
    : propietarioNick(otro.propietarioNick), nombreLista(otro.nombreLista),
      capacidad(otro.capacidad), cantidad(otro.cantidad),
      agregadasPorSeguir(nullptr), cantidadAgregadasPorSeguir(0),
      siguiendoA(otro.siguiendoA), estaSiguiendo(otro.estaSiguiendo)
{
    // Copia del arreglo principal
    canciones = new int[capacidad];
    for (int i = 0; i < cantidad; ++i)
        canciones[i] = otro.canciones[i];

    // Si el otro estaba siguiendo a alguien...
    if (otro.cantidadAgregadasPorSeguir > 0) {
        cantidadAgregadasPorSeguir = otro.cantidadAgregadasPorSeguir;

        // MEMORIA DINÁMICA para las canciones agregadas por seguir
        agregadasPorSeguir = new int[cantidadAgregadasPorSeguir];

        for (int i = 0; i < cantidadAgregadasPorSeguir; ++i)
            agregadasPorSeguir[i] = otro.agregadasPorSeguir[i];
    } else {
        agregadasPorSeguir = nullptr;
    }
}


// --------------------------------------------------------------------
// OPERADOR ASIGNACIÓN (=)
// Ubicación: líneas 50–81
//
// Este operador también usa MEMORIA DINÁMICA:
//   - Libera con delete[]
//   - Reserva nueva memoria con new[]
//   - Copia datos desde "otro"
//
// También es una copia profunda.
// --------------------------------------------------------------------
ListaFavoritos& ListaFavoritos::operator=(const ListaFavoritos& otro) {

    // Evita autoasignación
    if (this == &otro) return *this;

    // Libero memoria previa
    delete[] canciones;
    delete[] agregadasPorSeguir;

    // Copio datos simples
    propietarioNick = otro.propietarioNick;
    nombreLista = otro.nombreLista;
    capacidad = otro.capacidad;
    cantidad = otro.cantidad;

    // Copio el arreglo principal
    canciones = new int[capacidad];
    for (int i = 0; i < cantidad; ++i)
        canciones[i] = otro.canciones[i];

    // Copio agregadasPorSeguir si corresponde
    if (otro.cantidadAgregadasPorSeguir > 0) {
        cantidadAgregadasPorSeguir = otro.cantidadAgregadasPorSeguir;

        // MEMORIA DINÁMICA
        agregadasPorSeguir = new int[cantidadAgregadasPorSeguir];

        for (int i = 0; i < cantidadAgregadasPorSeguir; ++i)
            agregadasPorSeguir[i] = otro.agregadasPorSeguir[i];
    } else {
        agregadasPorSeguir = nullptr;
        cantidadAgregadasPorSeguir = 0;
    }

    siguiendoA = otro.siguiendoA;
    estaSiguiendo = otro.estaSiguiendo;

    return *this;
}


// --------------------------------------------------------------------
// Getters simples
// Ubicación: líneas 83–92
// --------------------------------------------------------------------
string ListaFavoritos::getPropietario() const { return propietarioNick; }
int ListaFavoritos::getCantidad() const { return cantidad; }
int ListaFavoritos::getCancionEn(int indice) const {
    if (indice < 0 || indice >= cantidad) return -1;
    return canciones[indice];
}


// --------------------------------------------------------------------
// agregar()
// Ubicación: líneas 94–100
//
// Agrega una canción por ID.
// Verifica:
//   - id válido
//   - espacio suficiente
//   - no repetida
// --------------------------------------------------------------------
bool ListaFavoritos::agregar(int idCancion) {

    if (idCancion <= 0) return false;
    if (cantidad >= capacidad) return false;
    if (indiceDeCancion(idCancion) != -1) return false;

    canciones[cantidad++] = idCancion;
    return true;
}


// --------------------------------------------------------------------
// eliminar()
// Ubicación: líneas 102–109
//
// Elimina una canción por ID usando eliminación rápida:
//   canciones[idx] = canciones[--cantidad];
// --------------------------------------------------------------------
bool ListaFavoritos::eliminar(int idCancion) {

    int idx = indiceDeCancion(idCancion);
    if (idx == -1) return false;

    canciones[idx] = canciones[--cantidad];
    return true;
}



// --------------------------------------------------------------------
// mezclar()
// Ubicación: líneas 111–121
//
// Mezcla aleatoriamente las canciones con Fisher–Yates Shuffle.
// --------------------------------------------------------------------
void ListaFavoritos::mezclar() {

    if (cantidad <= 1) return;

    for (int i = cantidad - 1; i > 0; --i) {

        int j = rand() % (i + 1);

        int tmp = canciones[i];
        canciones[i] = canciones[j];
        canciones[j] = tmp;
    }
}



// --------------------------------------------------------------------
// seguirOtraLista()
// Ubicación: líneas 123–172
//
// Este método hace varias cosas:
//
// 1. Verifica que:
//    - No sea nullptr
//    - No sea la misma lista
//    - No esté ya siguiendo a alguien
//
// 2. Crea un arreglo temporal dinâmico: int* temp;
//
// 3. Copia canciones nuevas que NO existan en la lista actual.
//
// 4. Asigna agregadasPorSeguir con new[].
//
// 5. Actualiza:
//    - cantidad
//    - siguiendoA
//    - estaSiguiendo
//
// MUCHÍSIMA MEMORIA DINÁMICA aquí.
// --------------------------------------------------------------------
bool ListaFavoritos::seguirOtraLista(ListaFavoritos* otra) {

    if (otra == nullptr) return false;
    if (otra == this) return false;

    if (estaSiguiendo) {
        cout << "Ya estas siguiendo a: " << siguiendoA << ". Debes dejar de seguir antes.\n";
        return false;
    }

    int nuevas = 0;
    int maxAgregar = otra->getCantidad();

    // MEMORIA DINÁMICA TEMPORAL
    int *temp = new int[maxAgregar];

    // Agrego solo las canciones nuevas
    for (int i = 0; i < otra->getCantidad(); ++i) {
        int id = otra->getCancionEn(i);

        if (indiceDeCancion(id) == -1) {
            if (cantidad + nuevas >= capacidad) break;
            temp[nuevas++] = id;
        }
    }

    if (nuevas == 0) {
        delete[] temp;
        cout << "No se agregaron canciones (ya existían o no hay espacio).\n";
        return false;
    }

    // Si ya tenía canciones agregadas previamente
    if (agregadasPorSeguir != nullptr) {
        delete[] agregadasPorSeguir;
        agregadasPorSeguir = nullptr;
        cantidadAgregadasPorSeguir = 0;
    }

    // MEMORIA DINÁMICA DEFINITIVA
    agregadasPorSeguir = new int[nuevas];

    // Copio canciones a la lista principal
    for (int i = 0; i < nuevas; ++i) {
        canciones[cantidad + i] = temp[i];
        agregadasPorSeguir[i] = temp[i];
    }

    cantidadAgregadasPorSeguir = nuevas;
    cantidad += nuevas;

    // Actualizo seguimiento
    siguiendoA = otra->getPropietario();
    estaSiguiendo = true;

    delete[] temp;

    cout << "Ahora sigues la lista de " << siguiendoA
         << ". Se agregaron " << nuevas << " canciones.\n";

    return true;
}



// --------------------------------------------------------------------
// dejarDeSeguir()
// Ubicación: líneas 174–197
//
// Elimina solo las canciones incorporadas por "seguir otra lista".
// Luego elimina agregadasPorSeguir.
// --------------------------------------------------------------------
bool ListaFavoritos::dejarDeSeguir() {

    if (!estaSiguiendo) {
        cout << "No sigues a nadie actualmente.\n";
        return false;
    }

    // Elimino las canciones agregadas por seguimiento
    for (int i = 0; i < cantidadAgregadasPorSeguir; ++i) {

        int id = agregadasPorSeguir[i];
        int idx = indiceDeCancion(id);

        if (idx != -1) {
            canciones[idx] = canciones[--cantidad];
        }
    }

    // Libero memoria
    delete[] agregadasPorSeguir;

    agregadasPorSeguir = nullptr;
    cantidadAgregadasPorSeguir = 0;

    cout << "Has dejado de seguir a " << siguiendoA
         << ". Las canciones agregadas por seguir fueron eliminadas.\n";

    siguiendoA = "";
    estaSiguiendo = false;

    return true;
}



// --------------------------------------------------------------------
// estaSiguiendoOtro()
// Ubicación: líneas 199–202
// Devuelve si la lista está siguiendo a otra.
// --------------------------------------------------------------------
bool ListaFavoritos::estaSiguiendoOtro()
{
    return estaSiguiendo;
}
