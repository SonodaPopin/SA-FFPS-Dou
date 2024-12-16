#ifndef HYBRID_H
#define HYBRID_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "Funciones.h"
#include "AGreedy2.h"
#include "Sexo.h"
#include "LocalSearch.h"
#pragma once

class Hybrid {
private:
    float thr = 0.8;                         ///< Umbral para determinar diferencias
    int maxTime;                             ///< Tiempo máximo permitido para la ejecución
    int sizeM = 20;
    int sizeN = 100;
    int temp = 10;
    int solQuality = 0;                      ///< Calidad de la mejor solución encontrada
    float alpha;
    AGreedy2 codicia;
    Sexo cruce;
    LocalSearch mutar;
    std::string bestSol;                     ///< Mejor solución generada
    std::vector<std::string> cadenasOriginales; ///< Cadenas originales leídas del archivo
    std::vector<std::string> cadenasN;    ///< Población actual de soluciones
    std::vector<int> valoresN;            ///< Calidad de las soluciones en `cadenas100`
    std::vector<std::string> cadenasTOP;    ///< Población actual de soluciones
    std::vector<int> valoresTOP;            ///< Calidad de las soluciones en `cadenas100`
    std::chrono::system_clock::time_point startTime; ///< Tiempo de inicio del algoritmo
    std::chrono::system_clock::time_point bestTime = std::chrono::system_clock::time_point::min(); ///< Tiempo de la mejor solución

    bool checkTime();                        ///< Verifica si el tiempo máximo ha sido alcanzado
    void selecMejores(int mejor);
    void cruzador();
    void genetizar();

public:
    /**
     * @brief Constructor de la clase Genetico.
     * @param ifp Ruta del archivo de entrada.
     * @param maxTime Tiempo máximo para la ejecución del algoritmo.
     */
    Hybrid(const std::string& ifp, int maxTime, int sizeN, int sizeM, float thr, float alpha);

    /**
     * @brief Obtiene la calidad final de la mejor solución encontrada.
     * @return Calidad de la mejor solución.
     */
    int getFinalQuality();

    /**
     * @brief Obtiene el tiempo en el que se encontró la mejor solución.
     * @return Tiempo transcurrido desde el inicio hasta la mejor solución.
     */
    double getFinalTime();
};

#endif // HYBRID_H