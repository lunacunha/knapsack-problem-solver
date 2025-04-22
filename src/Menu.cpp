#include "Menu.h"
#include "Parser.h"
#include "KnapsackSolver.h"
#include <iostream>
#include <string>
#include <algorithm>

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
             <<"#   E -> EXIT                  #" << "\n"
             <<"################################" << "\n"
             <<"Option: ";

        cin >> inp;

        if (inp == "1") loadData(1);
        else if (inp == "2") loadData(2);
        else if (inp == "3") loadData(3);
        else if (inp == "4") loadData(4);
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
    Dataset data = loadDataset(id);
    truckCapacity = data.capacity;
    pallets = data.pallets;

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
    cout << "Selected pallets: ";
    for (const auto& p : solution.selectedPallets) {
        cout << p.id << " ";
    }
    cout << "\n===================================\n";
}

void Menu::runILP() {
    cout << "[TODO] Executar ILP." << endl;
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
