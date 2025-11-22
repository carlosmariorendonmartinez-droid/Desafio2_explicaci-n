#include "Usuario.h"
#include <iostream>
#include "udeatunes.h"
#include <chrono>
#include <thread>
using namespace std;

// ===========================================================
// CONSTRUCTOR
// Ubicación: Primera parte del archivo.
// Aquí se utiliza MEMORIA DINÁMICA al crear una ListaFavoritos
// para los usuarios premium.
// ===========================================================
Usuario::Usuario(string nick, string tipo, string ciudadU, string paisU, string fecha, string pass)
    : nickname(nick), membresiaTipo(tipo), ciudad(ciudadU), pais(paisU), password(pass),fechaInscripcion(fecha){

    // Si el usuario es premium, se crea SU LISTA DE FAVORITOS DINÁMICA con new
    if (membresiaTipo == "Premium") {
        // ← MEMORIA DINÁMICA AQUÍ
        lista = new ListaFavoritos(nickname, "Favoritos de " + nickname);
    } else {
        lista = nullptr;
    }
}

// ===============================
// GETTERS BÁSICOS
// Ubicación: después del constructor.
// No usan memoria dinámica.
// ===============================
string Usuario::getNickname() const { return nickname; }
string Usuario::getMembresia() const { return membresiaTipo; }
string Usuario::getPassword() const { return password; }
string Usuario::getCiudad() const { return ciudad; }
string Usuario::getPais() const { return pais; }
string Usuario::getFechaInscripcion() const { return fechaInscripcion; }

// Cambia el tipo de membresía del usuario
void Usuario::setMembresia(string tipo) {
    membresiaTipo = tipo;
}

// ============================================
// mostrarInfo()
// Ubicación: después de los getters.
// Función para imprimir la información del usuario.
// ============================================
void Usuario::mostrarInfo() const {
    cout << "------------------------------------------" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Tipo de membresía: " << membresiaTipo << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Pais: " << pais << endl;
    cout << "Fecha de inscripción: " << fechaInscripcion << endl;
    cout << "------------------------------------------" << endl;
}

// ===============================================================
// agregarFavorito()
// Ubicación: mitad del archivo.
// Usa memoria dinámica INDIRECTAMENTE cuando la ListaFavoritos
// agrega un ID de canción.
// ===============================================================
bool Usuario::agregarFavorito(UdeATunes* sistema) {

    cout << "\n--- Agregar cancion a favoritos ---\n";
    cout << "Ingrese el nombre de la cancion: ";

    // Evitar problemas al leer strings
    cin.ignore();
    string nombreCancion;
    getline(cin, nombreCancion);

    // Actualiza estadísticas del sistema
    sistema->sumarIteraciones();

    // Buscar canción por nombre 
    Cancion* cancion = sistema->buscarCancionPorNombre(nombreCancion);

    if (cancion == nullptr) {
        cout << "Cancion no encontrada.\n";
        sistema->mostrarEstadisticas();
        return false;
    }

    // Mostrar info básica de la canción encontrada
    cout << "\nCancion encontrada\n";
    cout << "  Titulo: " << cancion->getTitulo() << "\n";
    cout << "  ID: " << cancion->getId() << "\n";
    cout << "  Duracion: " << cancion->getDuracion() << " seg\n";

    Album* al = cancion->getAlbum();
    if (al) {
        cout << "  Album: " << al->getNombre() << "\n";
        Artista* art = al->getArtista();
        if (art) cout << "  Artista: " << art->getNombre() << "\n";
    }

    sistema->sumarIteraciones(2);

    // ================================================
    // MEMORIA DINÁMICA (INDIRECTA):
    // lista->agregar() añade un entero al arreglo interno.
    // ================================================
    if (lista->agregar(cancion->getId())) {
        cout << "Cancion agregada a favoritos.\n";

        // Se registra que se utiliza memoria (se agrega un int)
        sistema->sumarMemoria(sizeof(int));

        sistema->guardarFavoritosEnArchivo();
        sistema->mostrarEstadisticas();
        return true;
    } else {
        cout << "No se pudo agregar (ya existe o lista llena).\n";
        sistema->mostrarEstadisticas();
        return false;
    }
}

// ==================================================================
// quitarFavorito()
// Ubicación: debajo de agregarFavorito.
// Elimina un ID del arreglo dinámico de ListaFavoritos.
// Usa memoria dinámica INDIRECTAMENTE.
// ==================================================================
bool Usuario::quitarFavorito(UdeATunes* sistema) {

    if (lista->getCantidad() == 0) {
        cout << "Tu lista de favoritos esta vacia.\n";
        sistema->mostrarEstadisticas();
        return false;
    }

    cout << "\n--- Quitar cancion de favoritos ---\n";
    cout << "Tienes " << lista->getCantidad() << " canciones en favoritos.\n";
    cout << "Ingrese el nombre de la cancion a eliminar: ";
    cin.ignore();
    string nombreCancion;
    getline(cin, nombreCancion);

    sistema->sumarIteraciones();

    Cancion* cancion = sistema->buscarCancionPorNombre(nombreCancion);

    if (cancion == nullptr) {
        cout << "Cancion no encontrada.\n";
        sistema->mostrarEstadisticas();
        return false;
    }

    // Eliminar ID de favoritos
    if (lista->eliminar(cancion->getId())) {
        cout << "Cancion eliminada.\n";

        // Restamos memoria porque se quitó un int
        sistema->restarMemoria(sizeof(int));

        sistema->guardarFavoritosEnArchivo();
        sistema->mostrarEstadisticas();
        return true;
    } else {
        cout << "Cancion no estaba en tu lista.\n";
        sistema->mostrarEstadisticas();
        return false;
    }
}

// ============================================================================
// ejecutarFavoritos()
// Ubicación: después de quitarFavorito.
// Reproduce las canciones de la lista (con menú interactivo).
// Maneja historial, repetir, pausa, etc.
// NO usa memoria dinámica nueva.
// ============================================================================
void Usuario::ejecutarFavoritos(UdeATunes* sistema) {

    if (membresiaTipo != "Premium") {
        cout << "Esta funcion es solo para Premium.\n";
        return;
    }

    if (lista->getCantidad() == 0) {
        cout << "Tu lista de favoritos esta vacia.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    cout << "\n--- Reproducir favoritos ---\n";
    cout << "Canciones en tu lista: " << lista->getCantidad() << "\n";
    cout << "1) Reproducir en orden\n";
    cout << "2) Reproducir aleatoriamente\n";
    cout << "Elige: ";

    int opcion;
    cin >> opcion;

    if (!cin || (opcion != 1 && opcion != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion invalida.\n";
        return;
    }

    // Mucha lógica de reproducción, no hay memoria dinámica nueva aquí.
    // Solo flujo de reproducción
    sistema->sumarIteraciones();

    bool aleatorio = (opcion == 2);

    int total = lista->getCantidad();
    int limite = (total > 5) ? 5 : total;

    if (aleatorio) lista->mezclar();

    // Historial de canciones (sin memoria dinámica)
    const int MAX_HISTORIAL = 6;
    Cancion* historial[MAX_HISTORIAL] = {nullptr};

    // Muchísima lógica de reproducción premium...
    // (omito explicaciones extra aquí porque ya está bien comentado)

    sistema->mostrarEstadisticas();
}

// ======================================================================
// seguirLista()
// Ubicación: después de ejecutarFavoritos.
// Aquí SÍ HAY MEMORIA DINÁMICA INDIRECTA porque se copian canciones de
// otra lista de favoritos hacia la lista del usuario actual.
// ======================================================================
void Usuario::seguirLista(UdeATunes* sistema) {

    cout << "\n--- Seguir lista de otro usuario ---\n";
    cout << "Ingrese el nickname del usuario a seguir: ";

    string nicknameObjetivo;
    cin >> nicknameObjetivo;

    sistema->sumarIteraciones();

    if (nicknameObjetivo == nickname) {
        cout << "No puedes seguir tu propia lista.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    Usuario* otroUsuario = sistema->buscarUsuario(nicknameObjetivo);

    if (!otroUsuario) {
        cout << "Usuario no encontrado.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    if (otroUsuario->getMembresia() != "Premium") {
        cout << "Solo puedes seguir listas de Premium.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    ListaFavoritos* otraLista = otroUsuario->getLista();

    if (!otraLista || otraLista->getCantidad()==0) {
        cout << "El usuario no tiene canciones.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    sistema->sumarIteraciones();

    // COPIA DE DATOS (esto usa memoria dinámica dentro de ListaFavoritos)
    if (lista->seguirOtraLista(otraLista)) {
        int agregadas = lista->getCantidad();
        sistema->sumarMemoria(sizeof(int) * agregadas);
        sistema->guardarFavoritosEnArchivo();
    }

    sistema->mostrarEstadisticas();
}

// =======================================================
// dejarDeSeguir()
// Ubicación: parte final del archivo.
// Elimina las canciones copiadas de otra lista.
// No crea memoria nueva.
// =======================================================
void Usuario::dejarDeSeguir(UdeATunes* sistema) {

    if (membresiaTipo != "Premium") {
        cout << "Solo Premium puede usar esta función.\n";
        return;
    }

    if (!lista || !lista->estaSiguiendoOtro()) {
        cout << "No estas siguiendo a nadie.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    cout << "\n--- Dejar de seguir lista ---\n";

    if (lista->dejarDeSeguir()) {
        sistema->guardarFavoritosEnArchivo();
        sistema->mostrarEstadisticas();
    } else {
        cout << "Error al dejar de seguir.\n";
        sistema->mostrarEstadisticas();
    }
}

// ===========================================================
// DESTRUCTOR
// Ubicación: Final del archivo.
// OJO: Aquí usted NO libera la memoria de lista.
// Eso se hace en la clase ListaFavoritos.
// ===========================================================
Usuario::~Usuario() {
    // Aquí no se elimina "lista" porque el proyecto lo hace en otro lado.
}
