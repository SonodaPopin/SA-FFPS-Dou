#ifndef HYBRID_H
#define HYBRID_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "Funciones.h"
#include "AGreedy2.h"
#pragma once

class Hybrid {
private:
    float thr;                         ///< Umbral para determinar diferencias
    int maxTime;                             ///< Tiempo máximo permitido para la ejecución
    int solQuality = 0;                      ///< Calidad de la mejor solución encontrada
    AGreedy2 codicia;
    std::string bestSol;                     ///< Mejor solución generada
    std::vector<std::string> cadenasOriginales; ///< Cadenas originales leídas del archivo
    std::vector<std::string> cadenasN;    ///< Población actual de soluciones
    std::vector<int> valoresN;            ///< Calidad de las soluciones en `cadenas100`
    std::vector<std::string> cadenasTOP;    ///< Población actual de soluciones
    std::vector<int> valoresTOP;            ///< Calidad de las soluciones en `cadenas100`
    std::chrono::system_clock::time_point startTime; ///< Tiempo de inicio del algoritmo
    std::chrono::system_clock::time_point bestTime = std::chrono::system_clock::time_point::min(); ///< Tiempo de la mejor solución
    std::mt19937 gen;                        ///< Generador de números aleatorios

    bool checkTime();                        ///< Verifica si el tiempo máximo ha sido alcanzado
    void Hybrid::selecMejores(int mejor);
    void Hybrid::cruzador();
    void Hybrid::genetizar();

public:
    /**
     * @brief Constructor de la clase Genetico.
     * @param ifp Ruta del archivo de entrada.
     * @param maxTime Tiempo máximo para la ejecución del algoritmo.
     */
    Hybrid(const std::string& ifp, int maxTime, int sizeN, float thr, float alpha);

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