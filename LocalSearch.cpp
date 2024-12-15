#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cmath>
#include "Funciones.cpp"
#include "Funciones.h"
#include "LocalSearch.h"

class LocalSearch {
private:
    std::vector<std::string> dataset; 

    std::string generate_neighbor(const std::string& current_solution) {
    std::string neighbor = current_solution;
    size_t num_changes = static_cast<size_t>(current_solution.size() * 0.05);

    char alfabeto[] = {'A', 'C', 'G', 'T'};
    for (size_t i = 0; i < num_changes; ++i) {
        size_t pos = rand() % neighbor.size();

        char current_char = neighbor[pos];

        char new_char;
        do {
            new_char = alfabeto[rand() % 4];
        } while (new_char == current_char);

        neighbor[pos] = new_char;
    }

    return neighbor;
}


public:
    LocalSearch(const std::vector<std::string>& data) : dataset(data) {
        srand(static_cast<unsigned int>(time(0)));
    }

    std::string local_search(const std::string& current_solution, int temp, float thr) {
        std::string best_solution = generate_neighbor(current_solution);

        int best_distance = contarDiferencias(current_solution,dataset,thr);

        bool improved = true;
        while (improved || temp >= 1) {
            improved = false;
            std::vector<std::string> neighbors;

            for (int i = 0; i < 2; ++i) {
                neighbors.push_back(generate_neighbor(best_solution));
            }

            for (const auto& neighbor : neighbors) {
                int neighbor_distance = contarDiferencias(neighbor,dataset,thr);
                if (neighbor_distance > best_distance) {
                    best_solution = neighbor;
                    best_distance = neighbor_distance;
                    improved = true;
                }
            }
            temp -=1;
        }

        return best_solution;
    }
};

int main() {
    
    string dataset = "D:/Joako/Desktop/Archivos de la U/SistemasAdaptativos/SA-FFPS-Dou/Dataset/100-300-001.txt";
    std::vector<std::string> ifp = leerArchivo(dataset);
    
    LocalSearch ls(ifp);
    std::string initial_solution = "GGCCCATTATTCTGGTTCCACCTTTAAGTCACTGTGCTCGGCAGATTAGAAGATCCGATGCGATTGGCCCTAATGGTCCGCAAGCGCGTTGCGCAATTAGATGCTAAGCTGTGTACTCATAACAGCTTGTTGGACGGAAGTTGGTTGTAACATGCGCGCATCTGCGACAAGACTCATCTTAATTCCAGCGCTTGGAGGCGGCTGCGCTCGTAATTCGGTTCGATAACTGAGGAAATTTTTTAATAAACCCTGATTTTAGAGAGCAAAAACAAAGTGGTCGCTGGAGAATTGGGCGGGCGC";
    
    cout << contarDiferencias(initial_solution,ifp,0.8) << endl;

    std::string best_solution = ls.local_search(initial_solution,10,0.8);

    std::cout << "Mejor solución encontrada: " << best_solution << std::endl;

    cout << contarDiferencias(best_solution,ifp,0.8) << endl;

    return 0;
}
