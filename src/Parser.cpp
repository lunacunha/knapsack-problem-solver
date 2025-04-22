#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int parseTruckCapacity(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERRO] Não consegui abrir " << path << endl;
        return -1;
    }

    string line;
    getline(file, line); // header
    getline(file, line); // data
    stringstream ss(line);
    string capacityStr;
    getline(ss, capacityStr, ',');
    return stoi(capacityStr);
}

vector<Pallet> parsePallets(const std::string& path) {
    vector<Pallet> pallets;
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERRO] Não consegui abrir " << path << endl;
        return pallets;
    }

    string line;
    getline(file, line); // header
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, weightStr, profitStr;
        getline(ss, idStr, ',');
        getline(ss, weightStr, ',');
        getline(ss, profitStr, ',');

        Pallet p;
        p.id = stoi(idStr);
        p.weight = stoi(weightStr);
        p.profit = stoi(profitStr);
        pallets.push_back(p);
    }

    return pallets;
}

// função utilitária
Dataset loadDataset(const string& id) {
    string basePath = "/home/martagfmartins/Desktop/faculdade/da/project2_DA/datasets/";
    string truckPath = basePath + "TruckAndPallets_" + id + ".csv";
    string palletsPath = basePath + "Pallets_" + id + ".csv";

    Dataset dataset;
    dataset.capacity = parseTruckCapacity(truckPath);
    dataset.pallets = parsePallets(palletsPath);
    return dataset;
}