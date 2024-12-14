#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include "Funciones.h"
#include "AGreedy2.h"
#include "Hybrid.h"

using namespace std;
using namespace chrono;

bool Hybrid::checkTime() {
    auto tiempoActual = system_clock::now();
    return duration_cast<seconds>(tiempoActual - startTime).count() >= maxTime;
}

void Hybrid::selecMejores(int mejor) {
    for (int i = 0; i < valoresN.size(); i++) {
        if (valoresN[i] = mejor){
            valoresTOP.push_back(valoresN[i]);
            cadenasTOP.push_back(cadenasN[i]);
            valoresN.erase(valoresN.begin() + i);
            cadenasN.erase(cadenasN.begin() + i);
        }
    }
}

void Hybrid::cruzador(){
    for (int i = 0; i < cadenasN.size(); i++) {
        //hijo = sexo(cadenasN[i], cadenasTOP[i % cadenasTOP.size()])
        //cadenasN[i] = hijo;
        //valoresN[i] = contarDiferencias(cadenasN[i], cadenasOriginales, thr);
    }
}

void Hybrid::genetizar() {
    cerr << "genetizando" << endl;
    startTime = system_clock::now();
    while (!checkTime()) {
        int maxValue = *std::max_element(valoresN.begin(), valoresN.end());
        cerr << "mejor obtenida de generacion " << maxValue << endl;
        selecMejores(maxValue);
        //matador();
        if (maxValue > solQuality) {
            solQuality = maxValue;
            bestTime = system_clock::now();
            cout << "Mejor calidad obtenida: " << solQuality 
                 << " Tiempo usado para obtenerla: " << getFinalTime() << " segundos." << endl;
        }
    }
}

Hybrid::Hybrid(const std::string& ifp, int maxTime, int sizeN, float thr, float alpha) 
    : maxTime(maxTime), cadenasOriginales(leerArchivo(ifp)), thr(thr), codicia(ifp, alpha){
    cadenasN.resize(sizeN);
    valoresN.resize(sizeN);
    cadenasTOP.resize(sizeN);
    valoresTOP.resize(sizeN);
    cadenasN = codicia.generarSolucion(sizeN);
    for (int i = 0; i < sizeN; i++) {
        valoresN[i] = contarDiferencias(cadenasN[i], cadenasOriginales, thr);
    }
}

int Hybrid::getFinalQuality() {
    return solQuality;
}

double Hybrid::getFinalTime() {
    if (bestTime == system_clock::time_point::min()) {
        return 0.0;
    }
    return duration_cast<seconds>(bestTime - startTime).count();
}