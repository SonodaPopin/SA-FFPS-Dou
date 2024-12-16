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
    for (int i = 0; i < valoresN.size();) {
        if (valoresN[i] == mejor){
            valoresTOP.push_back(valoresN[i]);
            cadenasTOP.push_back(cadenasN[i]);
            valoresN.erase(valoresN.begin() + i);
            cadenasN.erase(cadenasN.begin() + i);
        }else{
            i++;
        }
    }
    while (valoresTOP.size() > sizeM){
            size_t index = rand() % valoresTOP.size();
            string mutado = mutar.local_search(cadenasTOP[index], temp, thr);
            int valormutado = contarDiferencias(mutado, cadenasOriginales, thr);
            valoresN.push_back(valormutado);
            cadenasN.push_back(mutado);
            valoresTOP.erase(valoresTOP.begin() + index);
            cadenasTOP.erase(cadenasTOP.begin() + index);
    }
}

void Hybrid::cruzador(){
    for (int i = 0; i < cadenasN.size(); i++) {
        string hijo = cruce.sexo(cadenasN[i], cadenasTOP[i % cadenasTOP.size()], alpha, temp);
        cadenasN[i] = hijo;
        valoresN[i] = contarDiferencias(hijo, cadenasOriginales, thr);
    }
    for (int i = 0; i < cadenasTOP.size(); i++){
        valoresN.push_back(valoresTOP[i]);
        cadenasN.push_back(cadenasTOP[i]);  
    }
    valoresTOP.clear();
    cadenasTOP.clear();
}

void Hybrid::genetizar() {
    startTime = system_clock::now();
    int maxValue = *std::max_element(valoresN.begin(), valoresN.end()); // Declaración única de maxValue
    while (!checkTime()) {
        selecMejores(maxValue); // Usa el valor actualizado en cada iteración
        cruzador();
        maxValue = *std::max_element(valoresN.begin(), valoresN.end()); // Actualización del mismo maxValue
        if (maxValue > solQuality) {
            solQuality = maxValue;
            bestTime = system_clock::now();
        }
    }
}


Hybrid::Hybrid(const std::string& ifp, int maxTime, int sizeN, int sizeM, float thr, float alpha) 
    : maxTime(maxTime), cadenasOriginales(leerArchivo(ifp)), thr(thr), alpha(alpha), codicia(ifp, alpha), cruce(ifp), mutar(leerArchivo(ifp)), sizeM(sizeM), sizeN(sizeN){
    cadenasN.resize(sizeN);
    valoresN.resize(sizeN);
    cadenasN = codicia.generarSolucion(sizeN);
    for (int i = 0; i < sizeN; i++) {
        valoresN[i] = contarDiferencias(cadenasN[i], cadenasOriginales, thr);
    }
    genetizar();
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