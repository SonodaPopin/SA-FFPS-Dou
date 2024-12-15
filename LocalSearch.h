#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <string>
#include <vector>

class LocalSearch {
private:
    // Atributo para almacenar el conjunto de datos
    std::vector<std::string> dataset;

    // Método privado para generar un vecino a partir de una solución actual
    std::string generate_neighbor(const std::string& current_solution);

public:
    // Constructor que inicializa el conjunto de datos
    explicit LocalSearch(const std::vector<std::string>& data);

    // Método de búsqueda local
    std::string local_search(const std::string& current_solution, int temp, float thr);
};

#endif // LOCALSEARCH_H
