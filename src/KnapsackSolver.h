//
// Created by martagfmartins on 4/22/25.
//

#ifndef KNAPSACKSOLVER_H
#define KNAPSACKSOLVER_H

#include "Parser.h"
#include <vector>
#include <chrono>

struct Solution {
    double time;
    int totalProfit;
    int totalWeight;
    std::vector<Pallet> selectedPallets;
};

// T2.1: Força bruta
Solution solveExhaustive(int capacity, const std::vector<Pallet>& pallets);

// T2.2: Programação dinâmica
Solution solveDynamic(int capacity, const std::vector<Pallet>& pallets);

// T2.3: Aproximação gananciosa
Solution solveGreedy(int capacity, const std::vector<Pallet>& pallets);

// T2.4: ILP (ou heurística alternativa)
Solution solveILP(int capacity, const std::vector<Pallet>& pallets);


#endif //KNAPSACKSOLVER_H
