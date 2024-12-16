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
        cerr << "Uso: " << argv[0] << " -i <archivo> -t <tiempo> [-n <sizeN>] [-m <sizeM>] [-thr <umbral>] [-alpha <alpha>]" << endl;
        return 1;
    }

    std::string archivo;
    int tiempoMax = 0; 
    int sizeN = 100;      
    int sizeM = 30;       
    float thr = 0.8;     
    float alpha = 0.9;   

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-i" && i + 1 < argc) {
            archivo = argv[++i];  // Obtiene el nombre del archivo
        } else if (string(argv[i]) == "-t" && i + 1 < argc) {
            tiempoMax = stoi(argv[++i]);  // Convierte el tiempo máximo a int
        } else if (string(argv[i]) == "-n" && i + 1 < argc) {
            sizeN = stoi(argv[++i]);  // Convierte sizeN
        } else if (string(argv[i]) == "-m" && i + 1 < argc) {
            sizeM = stoi(argv[++i]);  // Convierte sizeM
        } else if (string(argv[i]) == "-thr" && i + 1 < argc) {
            thr = stof(argv[++i]);  // Convierte el umbral thr
        } else if (string(argv[i]) == "-alpha" && i + 1 < argc) {
            alpha = stof(argv[++i]);  // Convierte alpha
        } else {
            cerr << "Argumento no reconocido: " << argv[i] << endl;
            return 1;
        }
    }

    if (archivo.empty() || tiempoMax <= 0) {
        cerr << "Archivo o tiempo inválidos." << endl;
        return 1;
    }
    Hybrid hibrido(archivo, tiempoMax, sizeN, sizeM, thr, alpha);
    cout << "Mejor calidad obtenida: " << hibrido.getFinalQuality() 
         << " Tiempo usado para obtenerla: " << hibrido.getFinalTime() << " segundos." << endl;

    return 0;
}
