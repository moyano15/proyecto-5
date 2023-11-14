#include <iostream>
#include <string>

using namespace std;

const int NFILAS = 8;
const int NCOLUMNAS = 8;
const float tarifa_por_hora = 3.000;

enum EstadoParqueadero { LIBRE, OCUPADO, ESQUINA, CAMINO, ENTRADA, SALIDA };

// Mostrar el estado del Parqueadero
void imprimirEstadoParqueadero(const int parqueadero[NFILAS][NCOLUMNAS]) {
    for (int fila = 0; fila < NFILAS; fila++) {
        for (int columna = 0; columna < NCOLUMNAS; columna++) {
            if (parqueadero[fila][columna] == OCUPADO) {
                cout << "Puesto en fila " << fila << " columna " << columna << " ocupado" << endl;
            } else if (parqueadero[fila][columna] == LIBRE) {
                cout << "Plaza en fila " << fila << " columna " << columna << " libre" << endl;
            }
            // Agrega más casos según sea necesario para otros estados
        }
    }
}
    // HORARIO DEL PARQUEADERO
bool esHoraPermitida() {
    // Simulación de hora actual ficticia para propósitos de prueba
    int horaActual = 8;  // Por ejemplo, 8 representa las 8 AM

    // Verificar si la hora está dentro del rango permitido (6 AM a 10 PM)
    return (horaActual >= 6 && horaActual < 22);
}
// PARA INGRESAR VEHÍCULO
void estacionarVehiculo(int parqueadero[NFILAS][NCOLUMNAS], int &nLibres, int &nOcupadas) {
    if (!esHoraPermitida()) {
        cout << "El parqueadero está cerrado en este momento." << endl;
        return;
    }

    string horaIngresada;
    cout << "Ingresa la hora (formato HH:MM): ";
    cin >> horaIngresada;

    string placa;
    cout << "Ingresa la placa del vehículo: ";
    cin >> placa;

    int fila, columna;
    bool estacionado = false;

    if (nLibres > 0) {
        do {
            cout << "Introduce el número de la fila: ";
            cin >> fila;
            cout << "Introduce el número de la columna: ";
            cin >> columna;

            if (fila >= 0 && fila < NFILAS && columna >= 0 && columna < NCOLUMNAS) {
                if (parqueadero[fila][columna] == LIBRE) {
                    parqueadero[fila][columna] = OCUPADO;
                    nLibres--;
                    nOcupadas++;
                    estacionado = true;
                    cout << "Vehículo con placa " << placa << " estacionado correctamente a las " << horaIngresada << endl;
                } else {
                    cout << "El puesto ya está ocupado, intenta de nuevo." << endl;
                }
            } else {
                cout << "Posición inválida, intenta de nuevo." << endl;
            }
        } while (!estacionado);
    } else {
        cout << "No quedan espacios libres" << endl;
    }
}
// PARA RETIRAR VEHÍCULO
void retirarVehiculo(int parqueadero[NFILAS][NCOLUMNAS], int &nLibres, int &nOcupadas) {
    if (!esHoraPermitida()) {
        cout << "El parqueadero está cerrado en este momento." << endl;
        return;
    }

    string horaIngresada;
    cout << "Ingresa la hora (formato HH:MM): ";
    cin >> horaIngresada;

    int fila, columna;
    bool liberado = false;

    if (nOcupadas > 0) {
        time_t horaSalida = time(nullptr);

        do {
            cout << "Introduce el número de la fila del parqueadero: ";
            cin >> fila;
            cout << "Introduce el número de la columna del parqueadero: ";
            cin >> columna;

            if (fila >= 0 && fila < NFILAS && columna >= 0 && columna < NCOLUMNAS) {
                if (parqueadero[fila][columna] == OCUPADO) {
                    parqueadero[fila][columna] = LIBRE;
                    liberado = true;
                    nLibres++;
                    nOcupadas--;

                    // Calcular la duración de la estadía en horas (simulado con un valor constante)
                    int duracionEstadia = 2;

                    // Calcular el monto a cobrar (simulado con un valor constante)
                    float montoCobrar = tarifa_por_hora * duracionEstadia;

                    cout << "El vehículo se ha retirado del parqueadero. Monto a cobrar: $" << montoCobrar << endl;
                } else {
                    cout << "La plaza indicado está libre, intenta de nuevo." << endl;
                }
            } else {
                cout << "Posición inválida, intenta de nuevo." << endl;
            }
        } while (!liberado);
    } else {
        cout << "No hay espacios ocupados" << endl;
    }
}

int main() {
    int parqueadero[NFILAS][NCOLUMNAS] = {  {2,0,0,0,5,0,0,2}, 
                                            {3,3,3,3,3,3,3,3}, 
                                            {3,0,0,0,0,0,0,3}, 
                                            {3,3,3,3,3,3,3,3},
                                            {3,0,0,0,0,0,0,3}, 
                                            {3,3,3,3,3,3,3,3}, 
                                            {3,0,0,0,0,0,0,3}, 
                                            {2,3,3,3,4,3,3,2}   };

    int nLibres = 23;
    int nOcupadas = 0;

    int opcion;

    do {
        cout << "\nBienvenido al parqueadero parking\n";
        cout << "Menu: " << endl;
        cout << "1-Estacionar un vehiculo" << endl;
        cout << "2-Retirar un vehiculo" << endl;
        cout << "3-Listar estado de plazas" << endl;
        cout << "0-Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            estacionarVehiculo(parqueadero, nLibres, nOcupadas);
            break;
        case 2:
            retirarVehiculo(parqueadero, nLibres, nOcupadas);
            break;
        case 3:
            imprimirEstadoParqueadero(parqueadero);
            break;
        }
    } while (opcion != 0);

    return 0;
}

