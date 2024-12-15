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

class LocalSearch {
private:
    std::vector<std::string> dataset; 

    std::string generate_neighbor(const std::string& current_solution) {
        std::string neighbor = current_solution;
        size_t pos = rand() % neighbor.size();
        char alfabeto[] = {'A', 'C', 'G', 'T'};
        char current_char = neighbor[pos];
        char new_char;
        do {
            new_char = alfabeto[rand() % 4];
        } while (new_char == current_char);
        neighbor[pos] = new_char;
        return neighbor;
    }

public:
    LocalSearch(const std::vector<std::string>& data) : dataset(data) {
        srand(static_cast<unsigned int>(time(0)));
    }

    std::string simulated_annealing(const std::string& current_solution, double initial_temp, double cooling_rate, int max_iterations) {
        std::string best_solution = current_solution;
        int best_distance = contarDiferencias(current_solution,dataset,0.8);
        std::string current_solution_annealing = current_solution;
        int current_distance = best_distance;

        double temp = initial_temp;
        int iteration = 0;

        while (temp > 1 && iteration < max_iterations) {
            std::string neighbor = generate_neighbor(current_solution_annealing);
            int neighbor_distance = contarDiferencias(neighbor,dataset,0.8);

            if (neighbor_distance > current_distance || (rand() / double(RAND_MAX)) < exp((current_distance - neighbor_distance) / temp)) {
                current_solution_annealing = neighbor;
                current_distance = neighbor_distance;

                if (current_distance > best_distance) {
                    best_solution = current_solution_annealing;
                    best_distance = current_distance;
                }
            }

            temp *= cooling_rate; 
            iteration++;
        }

        return best_solution;
    }

    std::string local_search(const std::string& current_solution, int num_neighbors) {
        std::string best_solution = current_solution;
        int best_distance = contarDiferencias(current_solution,dataset,0.8);

        bool improved = true;
        while (improved) {
            improved = false;
            std::vector<std::string> neighbors;

            for (int i = 0; i < num_neighbors; ++i) {
                neighbors.push_back(generate_neighbor(best_solution));
            }

            for (const auto& neighbor : neighbors) {
                int neighbor_distance = contarDiferencias(neighbor,dataset,0.8);
                if (neighbor_distance > best_distance) {
                    best_solution = neighbor;
                    best_distance = neighbor_distance;
                    improved = true;
                }
            }
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
    std::string dou_solution = ls.simulated_annealing(initial_solution,1000,0.999,10000);
    std::string best_solution = ls.local_search(initial_solution,20);

    std::cout << "Mejor solución encontrada: " << best_solution << std::endl;
    std::cout << "dou solución encontrada: " << dou_solution << std::endl;

    cout << contarDiferencias(best_solution,ifp,0.8) << endl;
    cout << contarDiferencias(dou_solution,ifp,0.8) << endl;

    return 0;
}
