// CashOptimization.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <vector>


void compute(int _valueToMatch, int* _counter, const std::vector<int>* _cash, std::string _cashName)
{
    for (int value : *_cash) {
        int cashCount = 0;
        while (*_counter + value <= _valueToMatch) {
            *_counter += value;
            cashCount++;
        }
        if (cashCount > 0) {
            std::cout << cashCount << " " + _cashName + " " << value << "\n";
        }
    }
}



int main()
{

    std::vector<int> billets = { 20000, 10000, 5000, 2000, 1000, 500 };
    std::vector<int> pieces = { 200, 100, 50, 20, 10, 5, 2, 1 };

    float input;
    int valueToMatch = 0;
    int counter = 0;

    std::cout << "Entrez une valeur a atteindre.\nValeur : ";
    std::cin >> valueToMatch;

    //moron security
    if (valueToMatch <= 0) {
        ShellExecute(0, 0, L"https://fr.wikipedia.org/wiki/Liste_des_troubles_mentaux", 0, 0, SW_SHOW);
        return 1;
    }

    //loop
    compute(valueToMatch, &counter, &billets, "billet");
    compute(valueToMatch, &counter, &pieces, "piece");
}
