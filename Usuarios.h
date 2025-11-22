#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "listafavoritos.h"
class UdeATunes;
class Usuario {
private:
    std::string nickname;
    std::string membresiaTipo; // "Premium" o "Estandar"
    std::string ciudad;
    std::string pais;
    std::string password;
    std::string fechaInscripcion;
    ListaFavoritos* lista;

public:
    Usuario(std::string nick, std::string tipo, std::string ciudadU, std::string paisU, std::string fecha, std::string pass);
    ~Usuario();

    std::string getNickname() const;
    std::string getMembresia() const;
    void setMembresia(std::string tipo);
    std::string getCiudad() const;
    std::string getPais() const;
    std::string getFechaInscripcion() const;
    std::string getPassword() const;
    ListaFavoritos* getLista() const { return lista; }

    void mostrarInfo() const;
    bool agregarFavorito(UdeATunes* sistema);
    bool quitarFavorito(UdeATunes* sistema);
    void ejecutarFavoritos(UdeATunes* sistema);
    void seguirLista(UdeATunes* sistema);
    void dejarDeSeguir(UdeATunes* sistema);

};


#endif // USUARIO_H
