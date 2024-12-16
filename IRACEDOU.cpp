#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <random>
#include "AGreedy2.h"
#include "Hybrid.h"
#include "Sexo.h"
#include "Funciones.h"
#include "LocalSearch.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Uso: " << argv[0] << " <seed> <tiempo> <otra-cosa> <archivo> [-n <sizeN>] [-m <sizeM>] [-thr <umbral>] [-alpha <alpha>] [-temp <temp>]" << endl;
        return 1;
    }

    std::string archivo = argv[4];  // Cuarto argumento: archivo
    int tiempoMax = 10; // Segundo argumento: tiempo máximo
    int sizeN = 100;               // Default
    int sizeM = 30;                // Default
    float thr = 0.8;               // Default
    float alpha = 0.9;             // Default
    int temp = 10;

    for (int i = 5; i < argc; i++) { // Procesar parámetros opcionales a partir del 5to argumento
        if (string(argv[i]) == "-n" && i + 1 < argc) {
            sizeN = stoi(argv[++i]);
        } else if (string(argv[i]) == "-m" && i + 1 < argc) {
            sizeM = stoi(argv[++i]);
        } else if (string(argv[i]) == "-thr" && i + 1 < argc) {
            thr = stof(argv[++i]);
        } else if (string(argv[i]) == "-alpha" && i + 1 < argc) {
            alpha = stof(argv[++i]);
        } else if (string(argv[i]) == "-temp" && i + 1 < argc) {
            temp = stoi(argv[++i]);  // Convierte temp 
        }else {
            cerr << "Argumento no reconocido: " << argv[i] << endl;
            return 1;
        }
    }

    if (archivo.empty() || tiempoMax <= 0) {
        cerr << "Archivo o tiempo inválidos." << endl;
        return 1;
    }

    Hybrid hibrido(archivo, tiempoMax, sizeN, sizeM, thr, alpha, temp);
    int iracequality = hibrido.getFinalQuality() * -1;
    cout << iracequality << " " << hibrido.getFinalTime() << endl;

    return 0;
}
