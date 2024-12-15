#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cmath>
#include "Funciones.h"

class LocalSearch {
private:
    std::vector<std::string> dataset;

    std::string generate_neighbor(const std::string& current_solution);

public:
    LocalSearch(const std::vector<std::string>& data);

    std::string local_search(const std::string& current_solution, int temp, float thr);
};

#endif // LOCALSEARCH_H