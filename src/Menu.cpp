#include "Menu.h"
#include "Parser.h"
#include "KnapsackSolver.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

Menu::Menu() {
    string inp;
    while (true) {
        cout <<"################################" << "\n"
             <<"#     Select a dataset:        #" << "\n"
             <<"#------------------------------#" << "\n"
             <<"#   1 -> Dataset 01            #" << "\n"
             <<"#   2 -> Dataset 02            #" << "\n"
             <<"#   3 -> Dataset 03            #" << "\n"
             <<"#   4 -> Dataset 04            #" << "\n"
             <<"#   5 -> Dataset 05            #" << "\n"
             <<"#   6 -> Dataset 06            #" << "\n"
             <<"#   7 -> Dataset 07            #" << "\n"
             <<"#   8 -> Dataset 08            #" << "\n"
             <<"#   9 -> Dataset 09            #" << "\n"
             <<"#  10 -> Dataset 10            #" << "\n"
             <<"#------------------------------#" << "\n"
             <<"#   E -> EXIT                  #" << "\n"
             <<"################################" << "\n"
             <<"Option: ";

        cin >> inp;

        if (inp == "1") loadData(1);
        else if (inp == "2") loadData(2);
        else if (inp == "3") loadData(3);
        else if (inp == "4") loadData(4);
        else if (inp == "5") loadData(5);
        else if (inp == "6") loadData(6);
        else if (inp == "7") loadData(7);
        else if (inp == "8") loadData(8);
        else if (inp == "9") loadData(9);
        else if (inp == "10") loadData(10);
        else if (inp == "e" || inp == "E") exit(0);
        else {
            cout << "Insert a valid input!" << endl;
            cin.clear();
            Menu();
        }

        init();
    }
}

void Menu::loadData(int option) {
    string id = option < 10 ? "0" + to_string(option) : to_string(option);

    // Determine which path to use
    string basePath = (option >= 5 && option <= 10)
        ? "datasets-extra/"
        : "datasets/";

    string truckPath = basePath + "TruckAndPallets_" + id + ".csv";
    string palletsPath = basePath + "Pallets_" + id + ".csv";

    Dataset dataset;
    dataset.capacity = parseTruckCapacity(truckPath);
    dataset.pallets = parsePallets(palletsPath);

    truckCapacity = dataset.capacity;
    pallets = dataset.pallets;

    cout << "[INFO] Loaded dataset " << id << " with capacity " << truckCapacity 
         << " and " << pallets.size() << " pallets.\n";
}

void Menu::init() {
    string inp;
    while (true) {
        cout <<"################################" << "\n"
             <<"#   Select Algorithm:          #" << "\n"
             <<"#------------------------------#" << "\n"
             <<"#   1 -> Exhaustive Search     #" << "\n"
             <<"#   2 -> Dynamic Programming   #" << "\n"
             <<"#   3 -> Greedy Approximation  #" << "\n"
             <<"#   4 -> ILP                   #" << "\n"
             <<"#   B -> BACK                  #" << "\n"
             <<"#   E -> EXIT                  #" << "\n"
             <<"################################" << "\n"
             <<"Option: ";

        cin >> inp;

        if (inp == "1") runExhaustive();
        else if (inp == "2") runDynamic();
        else if (inp == "3") runGreedy();
        else if (inp == "4") runILP();
        else if (inp == "b" || inp == "B") return;
        else if (inp == "e" || inp == "E") exit(0);
        else {
            cout << "Insert a valid input!" << endl;
            cin.clear();
            init();
        }
    }
}

// Placeholder para as chamadas
void Menu::runExhaustive() {
    auto solution = solveExhaustive(truckCapacity, pallets);

    cout << "\n=== Exhaustive Search Result ===" << endl;
    cout << "Total profit: " << solution.totalProfit << endl;
    cout << "Total weight: " << solution.totalWeight << endl;
    cout << "Execution time: " << solution.time << " ms" << endl;
    cout << "Selected pallets: ";
    for (const auto& p : solution.selectedPallets) {
        cout << p.id << " ";
    }
    cout << "\n=================================\n";
}

void Menu::runDynamic() {
    auto solution = solveDynamic(truckCapacity, pallets);

    cout << "\n=== Dynamic Programming Result ===" << endl;
    cout << "Total profit: " << solution.totalProfit << endl;
    cout << "Total weight: " << solution.totalWeight << endl;
    cout << "Execution time: " << solution.time << " ms" << endl;
    cout << "Selected pallets: ";
    for (const auto& p : solution.selectedPallets) {
        cout << p.id << " ";
    }
    cout << "\n==================================\n";
}

void Menu::runGreedy() {
    auto solution = solveGreedy(truckCapacity, pallets);

    cout << "\n=== Greedy Approximation Result ===" << endl;
    cout << "Total profit: " << solution.totalProfit << endl;
    cout << "Total weight: " << solution.totalWeight << endl;
    cout << "Execution time: " << solution.time << " ms" << endl;
    cout << "Selected pallets: ";
    for (const auto& p : solution.selectedPallets) {
        cout << p.id << " ";
    }
    cout << "\n===================================\n";
}

void Menu::runILP() {
    Solution solution = solveILP(truckCapacity, pallets);

    if (solution.selectedPallets.empty()) {
        std::cerr << "ILP solver failed or returned no pallets." << std::endl;
        return;
    }

    std::cout << "\n=== ILP Solver Results ===" << std::endl;
    std::cout << "Total profit: " << solution.totalProfit << std::endl;
    std::cout << "Total weight: " << solution.totalWeight << " / " << truckCapacity << std::endl;
    cout << "Execution time: " << solution.time << " ms" << endl;
    std::cout << "Selected pallets: ";
    for (const auto& pallet : solution.selectedPallets) {
        std::cout << pallet.id << " ";
    }
    std::cout << "\n===========================\n";
}

string Menu::trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos || end == string::npos) ? "" : s.substr(start, end - start + 1);
}

string Menu::toUpper(const string &s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void Menu::end() {
    cout << "Exiting..." << endl;
}
