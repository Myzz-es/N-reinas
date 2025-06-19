#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <chrono>
#define NREINAS 7 // Número de reinas a colocar en el tablero
using namespace std;

vector<int> sol;
int nro_sol = 1;
ofstream archivo_salida("soluciones.txt");

inline bool contiene(const vector<int>& v, const int val)
{
    return find(v.begin(), v.end(), val) != v.end();
}

void reinas(int k, vector<int> col, vector<int> diag45, vector<int> diag135)
{
    if (k == NREINAS)
    {
        archivo_salida << nro_sol++ << ":";
        for (int j = 0; j < NREINAS; j++)
            archivo_salida << " (" << j + 1 << "," << sol[j] << ")";
        archivo_salida << endl;
    }
    else
    {
        for (int j = 1; j <= NREINAS; j++)
        {
            if (!contiene(col, j) && !contiene(diag45, j - k) && !contiene(diag135, j + k))
            {
                sol[k] = j;

                col.push_back(j);
                diag45.push_back(j - k);
                diag135.push_back(j + k);

                reinas(k + 1, col, diag45, diag135);

                col.pop_back();
                diag45.pop_back();
                diag135.pop_back();
            }
        }
    }
}

int main()
{
    cout << "SOLUCIONES AL PROBLEMA DE LAS " << NREINAS << " REINAS" << endl;

    auto inicio = chrono::high_resolution_clock::now();

    sol.resize(NREINAS);
    reinas(0, vector<int>(), vector<int>(), vector<int>());

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    archivo_salida << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;
    archivo_salida.close();

    cout << "Soluciones guardadas en 'soluciones.txt'" << endl;
    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}
