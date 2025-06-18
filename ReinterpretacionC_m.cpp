#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono> // Para medir tiempo

using namespace std;
using namespace chrono; // Para evitar escribir std::chrono:: cada vez

// Función para calcular constante mágica
int constanteMagica(int n) {
    return (n * n * n + n) / 2;
}

// Función para medir duración y generar combinaciones
void generarCombinaciones(int n, const string& nombreArchivo) {
    auto inicio = high_resolution_clock::now(); // ⏱️ Inicio

    int limite = n * n;
    int sumaObjetivo = constanteMagica(n);
    
    vector<int> numeros;
    for (int i = 1; i <= limite; ++i)
        numeros.push_back(i);
    
    ofstream fout(nombreArchivo);

    vector<bool> seleccion(limite, false);
    fill(seleccion.end() - n, seleccion.end(), true);

    int total = 0;
    do {
        vector<int> combinacion;
        int suma = 0;

        for (int i = 0; i < limite; ++i) {
            if (seleccion[i]) {
                combinacion.push_back(numeros[i]);
                suma += numeros[i];
            }
        }

        if (suma == sumaObjetivo) {
            for (int i = 0; i < n; ++i) {
                fout << combinacion[i] << (i < n - 1 ? " " : "\n");
            }
            ++total;
        }
    } while (next_permutation(seleccion.begin(), seleccion.end()));

    fout.close();

    auto fin = high_resolution_clock::now(); // ⏱️ Fin
    duration<double> duracion = fin - inicio;

    cout << "Se encontraron " << total << " combinaciones con suma = " << sumaObjetivo << endl;
    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;
}

int main() {
    int n = 8; // Cambia el valor aquí si lo deseas

    generarCombinaciones(n, "Combinaciones_d.txt");

    return 0;
}
