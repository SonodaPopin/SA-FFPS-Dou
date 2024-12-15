#include "Sexo.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Funciones.h"
#include <time.h>
#include "Funciones.cpp"

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
string Sexo::sexo(const string& padre1, const string& padre2, float alpha, int numh) {
    srand(static_cast<unsigned>(time(0)));
    dh;
    mdh = 0;
    dp1 = contarDiferencias(padre1,dataset,0.8);
    dp2 = contarDiferencias(padre2,dataset,0.8);

    dpdou = (dp1 < dp2) ? dp2 : dp1;

    string hijo;
    string mhijo;

    int longitud = padre1.size();

    for(int j = 0; j < numh; j++){
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
        dh = contarDiferencias(hijo,dataset,0.8);

        if (dh > dpdou) {
            return hijo;
        }

        if (dh > mdh) {
            mdh = dh;
            mhijo = hijo;
        }
    }

    return mhijo;
}

main(){
    std::string padre1 = "GGAGAATTATTGTGTTTCCAGGTTGCTGGCAGCGCGCTTGAACGATTAATCAACACGTTGCGTAAAACAGGTCAACTTGTCCAACGTCAACTATCGTCAGCAACGAGGCGGTCCCACGGAAATCTTTAGATGAAGGAAAGCTATCAGTCGGACTCCGAAAGCTGTTTAGTTACCTTGCTTATATCCTACGGATGTACGCGTCTCCTGTCATATCTTGCTACCCACAATGTTTTTTACTGTTGATATCTCGAGATGGGCGAGGGCGAACATATAGCGCTTGCTGGGCCGGTGGGCGGATCA";
    std::string padre2 = "TGGGACTCAACCCGGAAAGGACCGGTTACGTTCACCGAAACAAAGCGAACTTACGACAAAATCCGGTCACTTAACCGGTTACAGTGTACGTGGTACCGCTTCGCGGGAGGGGCCGTATGGCTGGTACGCGGCCCAGAGTCAGACGGTTCTAGGCGAATTGCGGCGTCGATTCCTAGAATCATGTAAACAAAACGCGCACCAAGCGCCAAATACCCGCCACAGAATAACAGTGCATATGTCTATTCAAGTGGAAGGGCCGTATAGCTTTATCAGGTCCCGTAACCGCGGGCTGTATGTTGA";
    string dataset = "D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/SA-FFPS-Dou/Dataset/100-300-001.txt";
    std::vector<std::string> ifp = leerArchivo(dataset);
    
    Sexo sexo_obj(dataset);

    float alpha = 0.8;
    
    std::string hijo = sexo_obj.sexo(padre1, padre2, alpha,10);
    
    cout << "Hijo generado: " << hijo << endl;
    cout << "padre1 " << contarDiferencias(padre1,ifp,0.8) << endl;
    cout << "padre2 " << contarDiferencias(padre2,ifp,0.8) << endl;
    cout << contarDiferencias(hijo, ifp ,0.8) << endl;
    
    return 0;
    }
