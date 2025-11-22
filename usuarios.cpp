#include "Usuario.h"
#include <iostream>
#include "udeatunes.h"
#include <chrono>
#include <thread>
using namespace std;

Usuario::Usuario(string nick, string tipo, string ciudadU, string paisU, string fecha, string pass)
    : nickname(nick), membresiaTipo(tipo), ciudad(ciudadU), pais(paisU), password(pass),fechaInscripcion(fecha){
    if (membresiaTipo == "Premium") {
        lista = new ListaFavoritos(nickname, "Favoritos de " + nickname);
    } else {
        lista = nullptr;
    }
}

string Usuario::getNickname() const {
    return nickname;
}

string Usuario::getMembresia() const {
    return membresiaTipo;
}

void Usuario::setMembresia(string tipo) {
    membresiaTipo = tipo;
}
string Usuario::getPassword() const {
    return password;
}
string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

string Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}
void Usuario::mostrarInfo() const {
    cout << "------------------------------------------" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Tipo de membresía: " << membresiaTipo << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Pais: " << pais << endl;
    cout << "Fecha de inscripción: " << fechaInscripcion << endl;
    cout << "------------------------------------------" << endl;
}

bool Usuario::agregarFavorito(UdeATunes* sistema) {
    cout << "\n--- Agregar cancion a favoritos ---\n";
    cout << "Ingrese el nombre de la cancion: ";
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
    if (lista->agregar(cancion->getId())) {
        cout << "Cancion agregada a favoritos.\n";
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
        cout << "Cancion no encontrada en el sistema.\n";
        sistema->mostrarEstadisticas();
        return false;
    }
    if (lista->eliminar(cancion->getId())) {
        cout << "Cancion eliminada de favoritos.\n";
        sistema->restarMemoria(sizeof(int));
        sistema->guardarFavoritosEnArchivo();
        sistema->mostrarEstadisticas();
        return true;
    } else {
        cout << "Cancion no encontrada en tu lista.\n";
        sistema->mostrarEstadisticas();
        return false;
    }
}
void Usuario::ejecutarFavoritos(UdeATunes* sistema) {
    if (membresiaTipo != "Premium") {
        cout << "Esta funcion es solo para usuarios Premium.\n";
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
        sistema->mostrarEstadisticas();
        return;
    }

    bool aleatorio = (opcion == 2);
    sistema->sumarIteraciones();

    cout << "\nReproduciendo favoritos "
         << (aleatorio ? "aleatoriamente" : "en orden") << "...\n\n";

    int total = lista->getCantidad();
    int limite = (total > 5) ? 5 : total;

    if (aleatorio) {
        lista->mezclar();
    }

    const int MAX_HISTORIAL = 6;
    Cancion* historial[MAX_HISTORIAL] = {nullptr};
    int totalEnHistorial = 0;

    bool reproduciendo = true;
    bool modoRepetir = false;
    bool pausado = false;
    int indiceLista = 0;
    Cancion* cancionActual = nullptr;

    while (reproduciendo && indiceLista < limite) {
        if (!modoRepetir) {
            int idCancion = lista->getCancionEn(indiceLista);

            if (idCancion <= 0) {
                indiceLista++;
                continue;
            }

            cancionActual = sistema->buscarCancionPorId(idCancion);

            if (cancionActual == nullptr) {
                cout << "Cancion con ID " << idCancion << " no encontrada.\n";
                indiceLista++;
                continue;
            }

            historial[totalEnHistorial % MAX_HISTORIAL] = cancionActual;
            totalEnHistorial++;
        }

        Album* al = cancionActual->getAlbum();
        Artista* a = (al != nullptr) ? al->getArtista() : nullptr;

        cout << "\n====================================================\n";
        cout << "REPRODUCIENDO MI LISTA DE FAVORITOS ";
        cout << (aleatorio ? "(ALEATORIO)" : "(EN ORDEN)");
        cout << (pausado ? " (PAUSADO)" : "") << "\n";
        cout << "====================================================\n";
        cout << "Cantante: " << (a ? a->getNombre() : "(Artista desconocido)") << "\n";
        cout << "Album: " << (al ? al->getNombre() : "(Album no disponible)") << "\n";
        if (al) cout << "Portada: " << al->getRutaPortada() << "\n";
        cout << "----------------------------------------------------\n";
        cout << "Titulo: " << cancionActual->getTitulo() << "\n";
        cout << "Duracion: " << cancionActual->getDuracion() << " segundos\n";
        if (membresiaTipo == "Premium") {
            cout << "Ruta: " << cancionActual->getRutaAlta() << " (320.ogg)\n";
        } else {
            cout << "Ruta: " << cancionActual->getRutaBaja() << " (128.ogg)\n";
        }
        cout << "====================================================\n";
        cout << "Estado: REPETIR [" << (modoRepetir ? "ON" : "OFF") << "]\n";
        cout << "Progreso: [" << (indiceLista + 1) << "/" << limite << "]\n";
        cout << "====================================================\n\n";

        cout << "--- OPCIONES DE REPRODUCCION PREMIUM ---\n";
        if (pausado) {
            cout << "1. Iniciar reproduccion\n";
        } else {
            cout << "1. Detener reproduccion\n";
        }
        cout << "2. Siguiente cancion\n";

        int cancionesDisponiblesAtras = (totalEnHistorial > MAX_HISTORIAL) ? MAX_HISTORIAL : (totalEnHistorial - 1);
        if (cancionesDisponiblesAtras > 0) {
            cout << "3. Cancion previa (hasta " << cancionesDisponiblesAtras << " hacia atras)\n";
        }

        cout << "4. " << (modoRepetir ? "Desactivar" : "Activar") << " modo repetir\n";
        cout << "5. Continuar (avanza automaticamente en 3s)\n";
        cout << "0. Salir de reproduccion\n";
        cout << "\nSeleccione una opcion: ";

        int opc;
        cin >> opc;

        switch(opc) {
        case 1:
            pausado = !pausado;
            cout << (pausado ? "\nReproduccion pausada.\n" : "\nReproduccion iniciada.\n");
            break;

        case 2:
            if (!pausado) {
                cout << "\nSiguiente cancion...\n";
                modoRepetir = false;
                indiceLista++;
                this_thread::sleep_for(chrono::seconds(1));
            } else {
                cout << "\nDebe iniciar la reproduccion primero.\n";
            }
            break;

        case 3: {
            int cancionesAtras = (totalEnHistorial > MAX_HISTORIAL) ? MAX_HISTORIAL : (totalEnHistorial - 1);

            if (cancionesAtras > 0 && !pausado) {
                int posActual = (totalEnHistorial - 1) % MAX_HISTORIAL;
                int posPrev = (posActual - 1 + MAX_HISTORIAL) % MAX_HISTORIAL;

                cancionActual = historial[posPrev];
                totalEnHistorial--;
                indiceLista--;

                cout << "\nCancion previa...\n";
                modoRepetir = false;
                this_thread::sleep_for(chrono::seconds(1));
            } else if (pausado) {
                cout << "\nDebe iniciar la reproduccion primero.\n";
            } else {
                cout << "\nNo hay canciones previas.\n";
            }
            break;
        }

        case 4:
            modoRepetir = !modoRepetir;
            cout << "\nModo repetir: " << (modoRepetir ? "ACTIVADO" : "DESACTIVADO") << "\n";
            break;

        case 5:
            if (!pausado) {
                cout << "\nContinuando reproduccion automaticamente...\n";
                this_thread::sleep_for(chrono::seconds(3));
                if (!modoRepetir) indiceLista++;
            } else {
                cout << "\nDebe iniciar la reproduccion primero.\n";
            }
            break;

        case 0:
            cout << "\nReproduccion finalizada por el usuario.\n";
            reproduciendo = false;
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

        sistema->sumarIteraciones(3);
    }

    cout << "\n[Reproduccion de favoritos finalizada]\n";
    sistema->mostrarEstadisticas();
}
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

    if (otroUsuario == nullptr) {
        cout << "Usuario no encontrado.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    if (otroUsuario->getMembresia() != "Premium") {
        cout << "Solo puedes seguir listas de usuarios Premium.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    ListaFavoritos* otraLista = otroUsuario->getLista();

    if (otraLista == nullptr || otraLista->getCantidad() == 0) {
        cout << "El usuario '" << nicknameObjetivo
             << "' no tiene canciones en su lista.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    sistema->sumarIteraciones();
    if (lista->seguirOtraLista(otraLista)) {
        int agregadas = lista->getCantidad();
        sistema->sumarMemoria(sizeof(int) * agregadas);
        sistema->guardarFavoritosEnArchivo();
        sistema->mostrarEstadisticas();
    } else {
        sistema->mostrarEstadisticas();
    }
}
void Usuario::dejarDeSeguir(UdeATunes* sistema) {
    if (membresiaTipo != "Premium") {
        cout << "Esta funcion es solo para usuarios Premium.\n";
        return;
    }

    if (lista == nullptr || !lista->estaSiguiendoOtro()) {
        cout << "\nNo estas siguiendo a ningun usuario.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    cout << "\n--- Dejar de seguir lista ---\n";
    if (lista->dejarDeSeguir()) {
        cout << "Has dejado de seguir la lista.\n";
        sistema->guardarFavoritosEnArchivo();
        sistema->mostrarEstadisticas();
    } else {
        cout << "Error al dejar de seguir.\n";
        sistema->mostrarEstadisticas();
    }
}
Usuario::~Usuario() {

}
