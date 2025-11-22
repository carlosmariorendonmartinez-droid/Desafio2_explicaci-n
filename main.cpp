#include "UdeATunes.h" 
// Incluimos la clase principal del sistema. 
// Aquí es donde está toda la lógica de la aplicación UdeATunes.

int main() {
    UdeATunes app;  
    // Se crea un objeto de la clase UdeATunes.
    // Aquí se reserva memoria para todos los atributos internos del sistema
    // (listas, usuarios, catálogo, etc. dependiendo de la implementación).

    app.inicializar();
    // Llamo al método inicializar().
    // Generalmente este método se usa para:
    //  - cargar archivos
    //  - enlazar canciones con álbumes
    //  - enlazar álbumes con artistas
    //  - preparar listas de reproducción
    //  - dejar todo listo antes de mostrar el menú

    app.menuPrincipal();
    // Llama al menú general del programa.
    // Este menú identifica qué tipo de usuario está entrando (Admin, Profe, Estudiante)
    // y muestra las opciones correspondientes:
    //  - explorar música
    //  - ver favoritos
    //  - crear listas
    //  - seguir otros usuarios
    //  - etc.

    return 0;
    // Retorno 0 significa que el programa terminó correctamente.
}
