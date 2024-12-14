#include "Sexo.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Funciones.h"
#include <time.h>

using namespace std;

// Implementación de los métodos de la clase Sexo

/**
 * @brief Constructor que inicializa la clase leyendo un archivo de entrada.
 * @param archivo La ruta del archivo a leer.
 */
Sexo::Sexo(const string& archivo) : ifp(archivo) {
    dataset = leerArchivo(ifp);
}

/**
 * @brief Cuenta la frecuencia de un carácter específico en una posición dada dentro del dataset.
 * @param caracter El carácter cuya frecuencia se evalúa.
 * @param posicion La posición en la que se evalúa el carácter.
 * @return La frecuencia del carácter en la posición especificada.
 */
int Sexo::contarFrecuencia(char caracter, int posicion) {
    int frecuencia = 0;
    for (const string& cadena : dataset) {
        if (cadena[posicion] == caracter) {
            frecuencia++;
        }
    }
    return frecuencia;
}

/**
 * @brief Genera un "hijo" genético basado en las frecuencias de caracteres de los padres en el dataset.
 * @param padre1 Primera cadena parental.
 * @param padre2 Segunda cadena parental.
 * @return La cadena resultante que representa al "hijo".
 */
string Sexo::sexo(const string& padre1, const string& padre2) {
    srand(static_cast<unsigned>(time(0)));
    dph;
    mdph;
    dp1 = contarDiferencias(padre1,dataset,0.8);
    dp2 = contarDiferencias(padre2,dataset,0.8);

    dpdou = (dp1 < dp2) ? dp2 : dp1;

    string hijo;
    string mhijo;

    alpha = 0.95;

    int longitud = padre1.size();

    for(int j = 0; j < 6; j++){
        for (int i = 0; i < longitud; i++) {
            char char1 = padre1[i];
            char char2 = padre2[i];

            char menosp;
            char masp;

            int frecuencia1 = contarFrecuencia(char1, i);
            int frecuencia2 = contarFrecuencia(char2, i);
            
            if (frecuencia1 < frecuencia2) {
                menosp = char1;
                masp = char2;
            } else {
                menosp = char2;
                masp = char1;
            }

            double p = static_cast<double>(rand()) / RAND_MAX;
            if (p < alpha) {
                
                hijo += menosp;
            } else {
                hijo += masp;
            }
        }
        dph = contarDiferencias(hijo,dataset,0.8);

        if (dph > dpdou) {
            return hijo;
        }

        if (dph > mdph) {
            mdph = dph;
            mhijo = hijo;
        }
    }

    return mhijo;
}

