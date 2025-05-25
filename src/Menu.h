#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Parser.h"
using namespace std;


class Menu {
public:
    struct ILPResult {
        int totalProfit;
        int totalWeight;
        std::vector<int> selectedIndices;
        bool success;
    };

    Menu();
    void end();
    void runBenchmark(const string& datasetId, const string& algorithmId);

private:
    void loadData(int option);
    void init();

    void runExhaustive();
    void runDynamic();
    void runGreedy();
    void runILP();

    bool createILPInputFile(const std::string &filename, int capacity, const std::vector<Pallet> &pallets);
    ILPResult readILPOutput(const std::string &filename);
    void displayILPResults(const ILPResult& result, int capacity, const std::vector<Pallet>& pallets);

    string trim(const string &s);
    string toUpper(const string &s);


    int truckCapacity;
    vector<Pallet> pallets;
};

#endif
