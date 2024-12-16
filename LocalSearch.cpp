#include "LocalSearch.h"
#include "Funciones.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cmath>

// Constructor de la clase
LocalSearch::LocalSearch(const std::vector<std::string>& data) : dataset(data) {
    srand(static_cast<unsigned int>(time(0)));
}

// Método privado: genera un vecino a partir de la solución actual
std::string LocalSearch::generate_neighbor(const std::string& current_solution) {
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

// Método público: implementa la búsqueda local
std::string LocalSearch::local_search(const std::string& current_solution, int temp, float thr) {
    std::string best_solution = generate_neighbor(current_solution);

    int best_distance = contarDiferencias(current_solution, dataset, thr);

    bool improved = true;
    while (improved || temp >= 1) {
        improved = false;
        std::vector<std::string> neighbors;

        for (int i = 0; i < 2; ++i) {
            neighbors.push_back(generate_neighbor(best_solution));
        }

        for (const auto& neighbor : neighbors) {
            int neighbor_distance = contarDiferencias(neighbor, dataset, thr);
            if (neighbor_distance > best_distance) {
                best_solution = neighbor;
                best_distance = neighbor_distance;
                improved = true;
            }
        }
        temp -= 1;
    }

    return best_solution;
}
