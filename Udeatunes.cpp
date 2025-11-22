#include "UdeATunes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

#define CAP_INI 4   // Capacidad inicial para los arreglos dinámicos

// =========================
//   CONSTRUCTOR
// =========================
// Ubicación: Primera función del archivo.
// Explicación: Aquí se reserva memoria dinámica para TODOS los arreglos 
// de usuarios, artistas, canciones, álbumes y publicidades.
UdeATunes::UdeATunes() {

    // ---- Inicialización de capacidades ----
    capacidadUsuarios = CAP_INI;
    capacidadArtistas = CAP_INI;
    capacidadCanciones = CAP_INI;
    capacidadAlbumes = CAP_INI;
    capacidadPublicidades = CAP_INI;

    // ---- MEMORIA DINÁMICA ----
    // Se crean arreglos dinámicos de punteros
    usuarios     = new Usuario*[capacidadUsuarios];
    artistas     = new Artista*[capacidadArtistas];
    canciones    = new Cancion*[capacidadCanciones];
    albumes      = new Album*[capacidadAlbumes];

    // Publicidades NO es arreglo de punteros, sino objetos:
    publicidades = new MensajePublicidad[capacidadPublicidades];

    // ---- Inicialización de contadores ----
    totalUsuarios = totalArtistas = totalCanciones = totalPublicidades = 0;

    // ---- Inicialización de punteros en nullptr ----
    for (int i = 0; i < capacidadUsuarios; ++i) usuarios[i] = nullptr;
    for (int i = 0; i < capacidadArtistas; ++i) artistas[i] = nullptr;
    for (int i = 0; i < capacidadAlbumes; ++i) albumes[i] = nullptr;
    for (int i = 0; i < capacidadCanciones; ++i) canciones[i] = nullptr;

    // Variables de control estadísticas
    iteraciones = 0;
    memoriaEstimadaBytes = 0;
    ultimoAnuncioId = -1;
}


// =========================
//       DESTRUCTOR
// =========================
// Ubicación: Después del constructor.
// Explicación: Libera toda la memoria dinámica usada por el sistema.
UdeATunes::~UdeATunes() {

    // Se borran TODOS los objetos creados dinámicamente
    for (int i = 0; i < totalUsuarios; ++i) delete usuarios[i];
    for (int i = 0; i < totalArtistas; ++i) delete artistas[i];
    for (int i = 0; i < totalCanciones; ++i) delete canciones[i];
    for (int i = 0; i < totalAlbumes; ++i)   delete albumes[i];

    // Ahora se borran los arreglos dinámicos
    delete[] usuarios;
    delete[] artistas;
    delete[] canciones;
    delete[] publicidades;
    delete[] albumes;
}


// =========================
//   BUSCAR CANCIÓN POR ID
// =========================
// Ubicación: Después del destructor.
// Explicación: Recorre el arreglo dinámico *canciones* comparando IDs.
Cancion* UdeATunes::buscarCancionPorId(int id) {
    for (int i = 0; i < totalCanciones; i++) {

        sumarIteraciones(); // Para estadísticas

        if (canciones[i]->getId() == id) {
            return canciones[i];  // Devuelve la coincidencia
        }
    }
    return nullptr;  // No se encontró
}


// =========================
//  BUSCAR CANCIÓN POR NOMBRE
// =========================
// Ubicación: Debajo de buscarCancionPorId.
// Explicación: Convierte los nombres a minúsculas y compara.
Cancion* UdeATunes::buscarCancionPorNombre(const string& nombre) {

    for (int i = 0; i < totalCanciones; i++) {

        sumarIteraciones();

        string tituloCancion = canciones[i]->getTitulo();
        string nombreLower = nombre;
        string tituloLower = tituloCancion;

        // Convertimos todo a minúsculas para comparación
        for (char& c : nombreLower) c = tolower(c);
        for (char& c : tituloLower) c = tolower(c);

        if (tituloLower == nombreLower) {
            return canciones[i];
        }
    }
    return nullptr;
}


// =========================
//    BUSCAR USUARIO
// =========================
// Ubicación: Debajo de buscarCancionPorNombre.
// Explicación: Recorre el arreglo dinámico de usuarios comparando nickname.
Usuario* UdeATunes::buscarUsuario(const string& nickname) {
    for (int i = 0; i < totalUsuarios; i++) {
        sumarIteraciones();
        if (usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}


// =========================
//       INICIALIZAR
// =========================
// Ubicación: Debajo de buscarUsuario.
// Explicación: Inicializa el sistema de publicidad y contabiliza memoria.
void UdeATunes::inicializar() {

    // Inicializa el random para las publicidades
    MensajePublicidad::inicializarAzar();

    // Contabiliza memoria usada (para estadísticas)
    sumarMemoria(sizeof(UdeATunes));
    sumarMemoria(sizeof(Usuario*) * capacidadUsuarios);
    sumarMemoria(sizeof(Artista*) * capacidadArtistas);
    sumarMemoria(sizeof(Cancion*) * capacidadCanciones);
    sumarMemoria(sizeof(MensajePublicidad) * capacidadPublicidades);
}


// =========================
//     CARGA DE ARCHIVOS
// =========================
// Ubicación: Debajo de inicializar().
// Explicación: Llama varias funciones que leen los .txt y cargan objetos.
void UdeATunes::cargarArchivos() {

    cout << "\nCargando archivos predeterminados...\n";

    // Archivos utilizados
    const char* usuariosFile   = "usuarios.txt";
    const char* cancionesFile  = "canciones.txt";
    const char* publicidadFile = "publicidad.txt";
    const char* artistasFile   = "artistas.txt";
    const char* albumesFile    = "albumes.txt";
    const char* favoritosFile  = "favoritos.txt";

    // Funciones que leen y cargan datos a memoria dinámica
    cargarArtistasDesdeArchivo(artistasFile);
    cargarAlbumesDesdeArchivo(albumesFile);
    cargarCancionesDesdeArchivo(cancionesFile);
    cargarUsuariosDesdeArchivo(usuariosFile);
    cargarFavoritosDesdeArchivo(favoritosFile);
    cargarPublicidadesDesdeArchivo(publicidadFile);

    // Relaciona canciones → álbumes → artistas
    enlazarCancionesConAlbumesYArtistas();

    // Mostrar resumen
    cout << "Carga completa.\n";
    cout << "Usuarios: " << totalUsuarios
         << ", Canciones: " << totalCanciones
         << ", Publicidades: " << totalPublicidades
         << ", Artistas: " << totalArtistas << endl;
}


// ==============================
//   ASEGURAR CAPACIDAD USUARIOS
// ==============================
// Ubicación: Debajo de cargarArchivos().
// Explicación: Duplica el tamaño del arreglo dinámico cuando está lleno.
void UdeATunes::asegurarCapacidadUsuarios() {

    if (totalUsuarios < capacidadUsuarios) return;

    int nueva = capacidadUsuarios * 2;

    // Se crea nuevo arreglo dinámico
    Usuario** tmp = new Usuario*[nueva];

    // Se copian los punteros antiguos
    for (int i = 0; i < totalUsuarios; ++i) tmp[i] = usuarios[i];

    // Nuevas posiciones quedan vacías
    for (int i = totalUsuarios; i < nueva; ++i) tmp[i] = nullptr;

    delete[] usuarios; // Liberamos memoria vieja
    usuarios = tmp;    // Ahora usamos la nueva

    sumarMemoria(sizeof(Usuario*) * (nueva - capacidadUsuarios));
    capacidadUsuarios = nueva;
}


// ==============================
//   ASEGURAR CAPACIDAD ARTISTAS
// ==============================
void UdeATunes::asegurarCapacidadArtistas() {

    if (totalArtistas < capacidadArtistas) return;

    int nueva = capacidadArtistas * 2;

    Artista** tmp = new Artista*[nueva];

    for (int i = 0; i < totalArtistas; ++i) tmp[i] = artistas[i];
    for (int i = totalArtistas; i < nueva; ++i) tmp[i] = nullptr;

    delete[] artistas;
    artistas = tmp;

    sumarMemoria(sizeof(Artista*) * (nueva - capacidadArtistas));
    capacidadArtistas = nueva;
}


// ==============================
//   ASEGURAR CAPACIDAD CANCIONES
// ==============================
void UdeATunes::asegurarCapacidadCanciones() {

    if (totalCanciones < capacidadCanciones) return;

    int nueva = capacidadCanciones * 2;

    Cancion** tmp = new Cancion*[nueva];

    for (int i = 0; i < totalCanciones; ++i) tmp[i] = canciones[i];
    for (int i = totalCanciones; i < nueva; ++i) tmp[i] = nullptr;

    delete[] canciones;
    canciones = tmp;

    sumarMemoria(sizeof(Cancion*) * (nueva - capacidadCanciones));
    capacidadCanciones = nueva;
}


// ==============================
//   ASEGURAR CAPACIDAD ÁLBUMES
// ==============================
void UdeATunes::asegurarCapacidadAlbumes() {

    if (totalAlbumes < capacidadAlbumes) return;

    int nueva = capacidadAlbumes * 2;

    Album** tmp = new Album*[nueva];

    for (int i = 0; i < totalAlbumes; ++i) tmp[i] = albumes[i];
    for (int i = totalAlbumes; i < nueva; ++i) tmp[i] = nullptr;

    delete[] albumes;
    albumes = tmp;

    sumarMemoria(sizeof(Album*) * (nueva - capacidadAlbumes));
    capacidadAlbumes = nueva;
}


// ==============================
//   ASEGURAR CAPACIDAD PUBLICIDAD
// ==============================
void UdeATunes::asegurarCapacidadPublicidades() {

    if (totalPublicidades < capacidadPublicidades) return;

    int nueva = capacidadPublicidades * 2;

    MensajePublicidad* tmp = new MensajePublicidad[nueva];

    // Se copian TODOS los mensajes existentes
    for (int i = 0; i < totalPublicidades; ++i) tmp[i] = publicidades[i];

    delete[] publicidades;
    publicidades = tmp;

    sumarMemoria(sizeof(MensajePublicidad) * (nueva - capacidadPublicidades));
    capacidadPublicidades = nueva;
}

// ========================
//   CARGA DE USUARIOS
// ========================
// Ubicación: Parte media del archivo, debajo de asegurarCapacidadPublicidades().
// Función: Lee el archivo usuarios.txt y va creando usuarios dinámicamente.
// Memoria dinámica: aquí se usa "new Usuario(...)" para CREAR objetos usuario.
void UdeATunes::cargarUsuariosDesdeArchivo(const char* ruta) {

    ifstream f(ruta); // Abrimos el archivo

    if (!f.is_open()) { // Si no abre, informamos
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }

    string line;
    
    // Leemos línea por línea del archivo
    while (getline(f, line)) {

        if (line.empty()) continue;    // Saltar líneas vacías
        if (line[0] == '#') continue;  // Saltar comentarios del archivo

        stringstream ss(line);
        string nick, tipo, ciudad, pais, fecha, pass;

        // Cada dato está separado por '|'
        getline(ss, nick, '|');
        getline(ss, tipo, '|');
        getline(ss, ciudad, '|');
        getline(ss, pais, '|');
        getline(ss, fecha, '|');
        getline(ss, pass, '|'); // ← contraseña

        asegurarCapacidadUsuarios();   // Aumenta el array dinámico si ya está lleno

        // *** MEMORIA DINÁMICA ***
        // Creamos un nuevo Usuario en el HEAP
        usuarios[totalUsuarios++] = new Usuario(nick, tipo, ciudad, pais, fecha, pass);

        sumarIteraciones();             // Estadísticas
        sumarMemoria(sizeof(Usuario));  // Sumar memoria usada
    }

    f.close(); // Cerramos archivo
}



// ========================
//   CARGA DE PUBLICIDAD
// ========================
// Ubicación: justo debajo de cargarUsuariosDesdeArchivo()
// Función: lee publicidad.txt y llena el arreglo dinámico publicidades[].
// Memoria dinámica: aquí NO se usa new. Se usa asignación DIRECTA a un arreglo dinámico.
void UdeATunes::cargarPublicidadesDesdeArchivo(const char* ruta) {

    ifstream f(ruta);

    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }

    string line;
    int idCounter = 1; // Se asigna un ID incremental a cada publicidad

    while (getline(f, line)) {

        if (line.empty()) continue;
        if (line[0] == '#') continue;

        stringstream ss(line);

        string catStr;
        getline(ss, catStr, '|');

        string mensaje;
        getline(ss, mensaje);

        // Limpieza de espacios
        catStr.erase(0, catStr.find_first_not_of(" \t"));
        catStr.erase(catStr.find_last_not_of(" \t") + 1);

        if (catStr.empty()) catStr = "C";

        int prioridad = 1;
        if (catStr == "B") prioridad = 2;
        else if (catStr == "AAA") prioridad = 3;

        asegurarCapacidadPublicidades(); // Duplicar arreglo si se llena

        // *** NO hay new — el arreglo es dinámico pero de objetos, no punteros ***
        publicidades[totalPublicidades] =
            MensajePublicidad(idCounter++, mensaje, catStr, prioridad);

        totalPublicidades++;

        sumarIteraciones();
        sumarMemoria(sizeof(MensajePublicidad));
    }

    f.close();
}



// ========================
//   CARGA DE CANCIONES
// ========================
// Ubicación: Debajo de cargarPublicidadesDesdeArchivo.
// Función: Lee canciones.txt y crea cada canción dinámicamente.
// Memoria dinámica: Se usa new Cancion(...)
void UdeATunes::cargarCancionesDesdeArchivo(const string& ruta) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error al abrir " << ruta << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {

        if (linea.empty() || linea[0] == '#') continue;

        string idStr, titulo, albumNombre, duracionStr, rutaBase;

        stringstream ss(linea);
        getline(ss, idStr, '|');
        getline(ss, titulo, '|');
        getline(ss, albumNombre, '|');
        getline(ss, duracionStr, '|');
        getline(ss, rutaBase, '|');

        int id = stoi(idStr);
        int duracion = stoi(duracionStr);

        asegurarCapacidadCanciones();

        // *** MEMORIA DINÁMICA ***
        Cancion* c = new Cancion(id, titulo, duracion, rutaBase, rutaBase, albumNombre);

        canciones[totalCanciones++] = c;

        sumarIteraciones();
        sumarMemoria(sizeof(Cancion));
    }

    archivo.close();
    cout << "Canciones cargadas: " << totalCanciones << endl;
}



// ========================
//   CARGA DE ARTISTAS
// ========================
// Ubicación: Debajo de cargarCancionesDesdeArchivo.
// Función: lee artistas.txt y crea objetos Artista (dinámico).
void UdeATunes::cargarArtistasDesdeArchivo(const char* ruta) {

    ifstream f(ruta);

    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }

    string line;

    while (getline(f, line)) {

        if (line.empty()) continue;
        if (line[0] == '#') continue;

        stringstream ss(line);

        string idStr, nombre, edadStr, pais, seguidoresStr, tendenciaStr;

        // Leemos todos los campos aunque no todos se usan
        getline(ss, idStr, '|');
        getline(ss, nombre, '|');
        getline(ss, edadStr, '|');
        getline(ss, pais, '|');
        getline(ss, seguidoresStr, '|');
        getline(ss, tendenciaStr, '|');

        asegurarCapacidadArtistas();

        // *** MEMORIA DINÁMICA ***
        artistas[totalArtistas++] = new Artista(nombre, pais);

        sumarIteraciones();
        sumarMemoria(sizeof(Artista));
    }

    f.close();
}



// ========================
//   CARGA DE ALBUMES
// ========================
// Ubicación: Debajo de cargarArtistasDesdeArchivo.
// Función: Crea cada álbum dinámicamente y lo vincula a su artista.
void UdeATunes::cargarAlbumesDesdeArchivo(const string& ruta) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error al abrir " << ruta << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {

        if (linea.empty() || linea[0] == '#') continue;

        string id, idArtista, nombre, genero, fecha, duracionStr, sello, puntuacionStr, rutaPortada;

        stringstream ss(linea);

        getline(ss, id, '|');
        getline(ss, idArtista, '|');
        getline(ss, nombre, '|');
        getline(ss, genero, '|');
        getline(ss, fecha, '|');
        getline(ss, duracionStr, '|');
        getline(ss, sello, '|');
        getline(ss, puntuacionStr, '|');
        getline(ss, rutaPortada, '|');

        int duracion = stoi(duracionStr);
        int puntuacion = stoi(puntuacionStr);

        // *** Memoria dinámica ***
        Album* nuevo = new Album(id, idArtista, nombre, genero, fecha,
                                 duracion, sello, puntuacion, rutaPortada);

        Artista* artistaAsociado = nullptr;

        // Buscamos el artista correspondiente
        for (int i = 0; i < totalArtistas; i++) {
            if (to_string(i + 10001) == idArtista) {
                artistaAsociado = artistas[i];
                break;
            }
        }

        // Si encontramos el artista, lo enlazamos
        if (artistaAsociado != nullptr) {
            artistaAsociado->agregarAlbum(nuevo); // Lista interna del artista
            nuevo->setArtista(artistaAsociado);   // Relación en álbum
        }

        albumes[totalAlbumes++] = nuevo;

        asegurarCapacidadAlbumes(); // Si se llenó el arreglo, duplicar
    }

    archivo.close();
}



// ========================
//   CARGA DE FAVORITOS
// ========================
// Ubicación: Debajo de cargarAlbumesDesdeArchivo.
// Función: carga IDs de canciones que están en favoritos.txt
void UdeATunes::cargarFavoritosDesdeArchivo(const char* ruta) {

    ifstream f(ruta);

    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }

    string line;

    while (getline(f, line)) {

        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string nickname, idsStr;

        getline(ss, nickname, '|');
        getline(ss, idsStr);

        Usuario* user = buscarUsuario(nickname);

        if (user && user->getMembresia() == "Premium") {

            stringstream ssIds(idsStr);
            string idStr;

            // Cada ID está separado por comas
            while (getline(ssIds, idStr, ',')) {

                int idCancion = stoi(idStr);

                if (user->getLista()) {
                    user->getLista()->agregar(idCancion);
                }
            }
        }

        sumarIteraciones();
    }

    f.close();
}
