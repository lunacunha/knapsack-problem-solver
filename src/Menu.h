#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Parser.h"
using namespace std;


class Menu {
public:
    Menu();
    void end();

private:
    void loadData(int option);
    void init();

    void runExhaustive();
    void runDynamic();
    void runGreedy();
    void runILP();

    string trim(const string &s);
    string toUpper(const string &s);


    int truckCapacity;
    vector<Pallet> pallets;
};

#endif
