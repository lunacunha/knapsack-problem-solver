//
// Created by martagfmartins on 4/22/25.
//

#include "KnapsackSolver.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>

// T2.1: Força bruta
void backtrack(int index, int currentWeight, int currentProfit,
               vector<int>& currentSelection, Solution& bestSolution,
               const vector<Pallet>& pallets, int capacity,
               int remainingMaxProfit) {

    // Poda por bound: se mesmo pegando todos os itens restantes não conseguimos melhorar
    if (currentProfit + remainingMaxProfit <= bestSolution.totalProfit) {
        return;
    }

    // Poda por peso: se já excedemos a capacidade
    if (currentWeight > capacity) {
        return;
    }

    // Caso base: processamos todos os itens
    if (index == pallets.size()) {
        if (currentProfit > bestSolution.totalProfit) {
            bestSolution.totalProfit = currentProfit;
            bestSolution.totalWeight = currentWeight;
            bestSolution.selectedPallets.clear();
            // Reconstroir a solução baseada nos índices selecionados
            for (int idx : currentSelection) {
                bestSolution.selectedPallets.push_back(pallets[idx]);
            }
        }
        return;
    }

    // Calcular o lucro máximo restante (dos itens ainda não processados)
    int newRemainingMaxProfit = remainingMaxProfit - pallets[index].profit;

    // Opção 1: NÃO pegar o item atual
    backtrack(index + 1, currentWeight, currentProfit,
              currentSelection, bestSolution, pallets, capacity, newRemainingMaxProfit);

    // Opção 2: PEGAR o item atual (só se couber)
    if (currentWeight + pallets[index].weight <= capacity) {
        currentSelection.push_back(index);
        backtrack(index + 1,
                  currentWeight + pallets[index].weight,
                  currentProfit + pallets[index].profit,
                  currentSelection, bestSolution, pallets, capacity, newRemainingMaxProfit);
        currentSelection.pop_back(); // backtrack
    }
}

Solution solveExhaustive(int capacity, const vector<Pallet>& pallets) {
    auto start = std::chrono::high_resolution_clock::now();

    Solution bestSolution;
    bestSolution.totalProfit = 0;
    bestSolution.totalWeight = 0;
    vector<int> currentSelection;

    // Calcular lucro máximo total para poda
    int totalMaxProfit = 0;
    for (const auto& pallet : pallets) {
        totalMaxProfit += pallet.profit;
    }

    // Chamar backtrack sem solução greedy inicial
    backtrack(0, 0, 0,
        currentSelection, bestSolution, pallets, capacity, totalMaxProfit);

    auto end = std::chrono::high_resolution_clock::now();
    bestSolution.time = std::chrono::duration<float, std::milli>(end - start).count();

    return bestSolution;
}

// T2.2: Dynamic Programming
Solution solveDynamic(int capacity, const vector<Pallet>& pallets) {
    auto start = std::chrono::high_resolution_clock::now();
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

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = end - start;

    return {duration.count(), totalProfit, totalWeight, selected};
}

// T2.3: Greedy (placeholder)
Solution solveGreedy(int capacity, const vector<Pallet>& pallets) {
    auto start = std::chrono::high_resolution_clock::now();

    // Ordenar por profit/weight (decrescente)
    vector<Pallet> sortedPallets = pallets;
    sort(sortedPallets.begin(), sortedPallets.end(),
        [](const Pallet& a, const Pallet& b) {
        return (double)a.profit / a.weight > (double)b.profit / b.weight;
    });

    int totalWeight = 0, totalProfit = 0;
    vector<Pallet> selected;

    for (const auto& pallet : sortedPallets) {
        if (totalWeight + pallet.weight <= capacity) {
            selected.push_back(pallet);
            totalWeight += pallet.weight;
            totalProfit += pallet.profit;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return {
        std::chrono::duration<float, std::milli>(end - start).count(),
        totalProfit,
        totalWeight,
        selected
    };
}

// T2.4: ILP
Solution solveILP(int capacity, const std::vector<Pallet>& pallets) {
    auto start = std::chrono::high_resolution_clock::now();

    Solution solution;
    solution.totalProfit = 0;
    solution.totalWeight = 0;
    solution.selectedPallets.clear();

    // Create temporary input file
    const std::string input_file = "input.txt";
    const std::string output_file = "output.txt";

    // Remove old output file if it exists
    std::remove(output_file.c_str());

    // Write input data in the required format
    std::ofstream infile(input_file);
    if (!infile.is_open()) {
        std::cerr << "Error creating input file for ILP solver" << std::endl;
        return solution;
    }

    // First line: number of pallets
    infile << pallets.size() << "\n";

    // Second line: truck capacity
    infile << capacity << "\n";

    // Third line: weights
    for (const auto& pallet : pallets) {
        infile << pallet.weight << " ";
    }
    infile << "\n";

    // Fourth line: profits
    for (const auto& pallet : pallets) {
        infile << pallet.profit << " ";
    }
    infile << "\n";
    infile.close();

    // Call Python solver
    const std::string python_path = ".venv/bin/python";
    const std::string script_path = "src/knapsack_solver.py";
    std::string command = python_path + " " + script_path + " " + input_file + " " + output_file;
    int ret = system(command.c_str());

    if (ret != 0) {
        std::cerr << "Error running ILP solver (Python script failed)" << std::endl;
        return solution;
    }

    // Read results from output file
    std::ifstream outfile(output_file);
    if (!outfile.is_open()) {
        std::cerr << "Error reading ILP solver results" << std::endl;
        return solution;
    }

    std::string line;

    // First line: total profit
    std::getline(outfile, line);
    solution.totalProfit = std::stoi(line);

    // Second line: total weight
    std::getline(outfile, line);
    solution.totalWeight = std::stoi(line);

    // Third line: selected pallet indices
    std::getline(outfile, line);
    std::istringstream iss(line);
    int index;
    while (iss >> index) {
        // Add the actual pallet objects to the solution
        if (index >= 0 && index < static_cast<int>(pallets.size())+1) {
            solution.selectedPallets.push_back(pallets[index-1]);
        }
    }
    outfile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = end - start;
    solution.time = duration.count();

    return solution;
}