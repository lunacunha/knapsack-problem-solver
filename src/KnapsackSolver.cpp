//
// Created by martagfmartins on 4/22/25.
//

#include "KnapsackSolver.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// T2.1: Força bruta
Solution solveExhaustive(int capacity, const std::vector<Pallet>& pallets) {
    int n = pallets.size();
    int bestProfit = 0;
    int bestWeight = 0;
    std::vector<Pallet> bestSelection;

    int totalCombinations = 1 << n; // 2^n

    for (int mask = 0; mask < totalCombinations; ++mask) {
        int currentWeight = 0;
        int currentProfit = 0;
        std::vector<Pallet> currentSelection;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                currentWeight += pallets[i].weight;
                currentProfit += pallets[i].profit;
                currentSelection.push_back(pallets[i]);
            }
        }

        if (currentWeight <= capacity && currentProfit > bestProfit) {
            bestProfit = currentProfit;
            bestWeight = currentWeight;
            bestSelection = currentSelection;
        }
    }

    return {bestProfit, bestWeight, bestSelection};
}

// T2.2: Programação dinâmica (placeholder)
Solution solveDynamic(int capacity, const vector<Pallet>& pallets) {
    int n = pallets.size();
    vector<int> dp(capacity + 1, 0);
    vector<vector<bool>> keep(n, vector<bool>(capacity + 1, false));

    // Preencher a tabela
    for (int i = 0; i < n; ++i) {
        for (int w = capacity; w >= pallets[i].weight; --w) {
            int without = dp[w];
            int with = dp[w - pallets[i].weight] + pallets[i].profit;

            if (with > without) {
                dp[w] = with;
                keep[i][w] = true;
            }
        }
    }

    // Reconstruir a solução
    int w = capacity;
    vector<Pallet> selected;
    for (int i = n - 1; i >= 0; --i) {
        if (keep[i][w]) {
            selected.push_back(pallets[i]);
            w -= pallets[i].weight;
        }
    }

    int totalProfit = dp[capacity];
    int totalWeight = 0;
    for (const auto& p : selected)
        totalWeight += p.weight;

    return {totalProfit, totalWeight, selected};
}

// T2.3: Greedy (placeholder)
Solution solveGreedy(int capacity, const vector<Pallet>& pallets) {
    // Criar um vetor auxiliar com razão lucro/peso
    vector<Pallet> sortedPallets = pallets;

    sort(sortedPallets.begin(), sortedPallets.end(), [](const Pallet& a, const Pallet& b) {
        double ratioA = static_cast<double>(a.profit) / a.weight;
        double ratioB = static_cast<double>(b.profit) / b.weight;
        return ratioA > ratioB; // ordem decrescente
    });

    int totalWeight = 0;
    int totalProfit = 0;
    vector<Pallet> selected;

    for (const auto& p : sortedPallets) {
        if (totalWeight + p.weight <= capacity) {
            selected.push_back(p);
            totalWeight += p.weight;
            totalProfit += p.profit;
        }
    }

    return {totalProfit, totalWeight, selected};
}

// T2.4: ILP (placeholder)
Solution solveILP(int capacity, const std::vector<Pallet>& pallets) {
    std::cout << "[TODO] ILP solver not implemented yet.\n";
    return {};
}