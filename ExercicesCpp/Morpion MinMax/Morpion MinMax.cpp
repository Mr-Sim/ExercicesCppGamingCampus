// Morpion MinMax.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Grid.h"

int main()
{
    Grid morpion;
    morpion.printGrid();
    
    EnumTileState nextTurn = EnumTileState::Cross;
    
    while (!morpion.gameRunning()) {
        int x; 
        int y;
        int numpad;
        std::wcout << L"choisir votre tour :";
        std::cin >> numpad;

        switch (numpad) {
        case 1: x = 2; y = 0;break;
        case 2: x = 2; y = 1;break;
        case 3: x = 2; y = 2;break;
        case 4: x = 1; y = 0;break;
        case 5: x = 1; y = 1;break;
        case 6: x = 1; y = 2;break;
        case 7: x = 0; y = 0;break;
        case 8: x = 0; y = 1;break;
        case 9: x = 0; y = 2;break;
        }


        morpion.playTurn(nextTurn, x, y);
        nextTurn = (nextTurn == EnumTileState::Cross) ? EnumTileState::Circle : EnumTileState::Cross;
        morpion.printGrid();
    }
}

