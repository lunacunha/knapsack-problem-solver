#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
using namespace std;

struct Pallet {
    int id;
    int weight;
    int profit;
};

struct Dataset {
    int capacity;
    vector<Pallet> pallets;
};

int parseTruckCapacity(const string& path);
vector<Pallet> parsePallets(const string& path);
Dataset loadDataset(const string& id);

#endif
