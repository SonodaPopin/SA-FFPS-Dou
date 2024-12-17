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

double calcularMedia(const std::vector<double>& valores) {
    double suma = std::accumulate(valores.begin(), valores.end(), 0.0);
    return suma / valores.size();
}

    /**
     * @brief Calcula la desviación estándar de un vector de doubles.
     * @return La desviación estándar.
     */
double calcularDesviacionEstandar(const std::vector<double>& valores, double media) {
    double sumaCuadrados = 0.0;
    for (double valor : valores) {
        sumaCuadrados += std::pow(valor - media, 2);
    }
    return std::sqrt(sumaCuadrados / valores.size());
}

void loopHybrid(int N, int M, float umbral, int tiempoMax){

    std::string archivo;
    int sizeN = 80;      
    int sizeM = 40;       
    float thr = 0.8;     
    float alpha = 0.92;  
    int temp = 6; 
        std::vector<double> calidades;
        std::vector<double> tiempos;
        std::string j = "000";
        for (int i = 1; i <= 100; ++i) {
            if (i < 10){
                j = "00" +std::to_string(i);
            }else if(i < 100){
                j = "0" +std::to_string(i); 
            }else{
                j = "100";
            }
            std::string archivo = "D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/GreedysDou/Dataset/" + std::to_string(N) + "-" + std::to_string(M) + "-" + j + ".txt";

            Hybrid hibrido(archivo, tiempoMax, sizeN, sizeM, umbral, alpha,temp);
            cout << "Mejor calidad obtenida: " << hibrido.getFinalQuality() 
            << " Tiempo usado para obtenerla: " << hibrido.getFinalTime() << " segundos." << endl;
        }
        double mediaCalidad = calcularMedia(calidades);
        double desviacionCalidad = calcularDesviacionEstandar(calidades, mediaCalidad);
        double tiempoPromedio = calcularMedia(tiempos);
        std::cout << "Media Calidad Hybrid: " << mediaCalidad << std::endl;
        std::cout << "Desviacion Estandar Calidad Hybrid: " << desviacionCalidad << std::endl;
        std::cout << "Tiempo Promedio Hybrid: " << tiempoPromedio << std::endl;
    }

    /**
     * @brief Función main que realiza las pruebas
     */
int main() {

   loopHybrid(100,300,0.8,10);
    return 0;
}
/*
int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Uso: " << argv[0] << " -i <archivo> -t <tiempo> [-n <sizeN>] [-m <sizeM>] [-thr <umbral>] [-alpha <alpha>] [-temp <temp>]" << endl;
        return 1;
    }

    std::string archivo;
    int tiempoMax = 10; 
    int sizeN = 80;      
    int sizeM = 40;       
    float thr = 0.8;     
    float alpha = 0.92;  
    int temp = 6; 

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
    cout << "Mejor calidad obtenida: " << hibrido.getFinalQuality() 
    << " Tiempo usado para obtenerla: " << hibrido.getFinalTime() << " segundos." << endl;

    return 0;
}*/