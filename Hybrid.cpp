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

Hybrid::Hybrid(const std::string& ifp, int maxTime, int sizeN, float thr, float alpha) 
    : maxTime(maxTime), cadenasOriginales(leerArchivo(ifp)), thr(thr), codicia(ifp, alpha){
    cadenasN.resize(sizeN);
    valoresN.resize(sizeN);
    cadenasN = codicia.generarSolucion(sizeN);
    for (int i = 0; i < 100; i++) {
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