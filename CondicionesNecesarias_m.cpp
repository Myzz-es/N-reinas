#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

// Leer archivo de combinaciones
vector<vector<int>> leerCombinaciones(const string& nombreArchivo, int n) {
    ifstream fin(nombreArchivo);
    vector<vector<int>> combinaciones;
    string linea;
    while (getline(fin, linea)) {
        istringstream iss(linea);
        vector<int> fila;
        int num;
        while (iss >> num) fila.push_back(num);
        if (fila.size() == n) combinaciones.push_back(fila);
    }
    return combinaciones;
}

// Escribir combinaciones válidas
void escribirCombinaciones(const string& nombreArchivo, const vector<vector<int>>& combis) {
    ofstream fout(nombreArchivo, ios::app);
    for (const auto& fila : combis) {
        for (size_t i = 0; i < fila.size(); ++i) {
            fout << fila[i] << (i < fila.size() - 1 ? " " : "\n");
        }
    }
}

// Función principal
pair<int, vector<vector<int>>> ComprobacionSistemaCondicionesNecesarias(int n, const string& fichero) {
    auto t0 = chrono::high_resolution_clock::now();

    vector<vector<int>> combinacionesValidas;
    vector<vector<int>> A = leerCombinaciones(fichero, n);
    size_t m = A.size();

    for (size_t i = 0; i < m; ++i) {
        vector<int> d = A[i];

        // Primera condición
        vector<int> aux;
        for (int val : d) aux.push_back((val - 1) / n);
        vector<int> nr1(n, 0);
        for (int j : aux) ++nr1[j];
        if (count_if(nr1.begin(), nr1.end(), [](int x) { return x <= 1; }) != n) continue;

        // Segunda condición
        vector<int> dn(n);
        for (int j = 0; j < n; ++j) dn[j] = d[j] % n;
        vector<int> nr2(n, 0);
        for (int j : dn) ++nr2[j];
        if (count_if(nr2.begin(), nr2.end(), [](int x) { return x <= 1; }) != n) continue;

        // Cuarta condición
        vector<int> dnminus1(n);
        for (int j = 0; j < n; ++j) dnminus1[j] = d[j] % (n - 1);
        vector<int> nr4(n - 1, 0);
        for (int j : dnminus1) ++nr4[j];
        if (nr4[0] > 2 || nr4[1] > 3) continue;
        if (count_if(nr4.begin() + 2, nr4.end(), [](int x) { return x <= 2; }) != n - 3) continue;

        // Quinta condición
        vector<int> dnplus1(n);
        for (int j = 0; j < n; ++j) dnplus1[j] = d[j] % (n + 1);
        vector<int> nr5(n + 1, 0);
        for (int j : dnplus1) ++nr5[j];
        if (nr5[0] > 1 || nr5[1] > 1 || nr5[2] > 1) continue;
        if (count_if(nr5.begin() + 3, nr5.end(), [](int x) { return x <= 2; }) != n - 2) continue;

        // Pasa todas las condiciones
        combinacionesValidas.push_back(d);
    }

    string nombreSalida = "combinaciones_necesarias_" + to_string(n) + ".txt";
    escribirCombinaciones(nombreSalida, combinacionesValidas);

    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = t1 - t0;
    cout << "Tiempo de ejecución: " << duracion.count() << " segundos\n";

    return { static_cast<int>(combinacionesValidas.size()), combinacionesValidas };
}
int main() {
    int n = 8; // Cambia este valor según sea necesario
    string fichero = "Combinaciones_d.txt"; // Archivo de combinaciones

    auto resultado = ComprobacionSistemaCondicionesNecesarias(n, fichero);
    cout << "Número de combinaciones válidas: " << resultado.first << endl;

    return 0;
}