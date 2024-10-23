#include "Grid.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <format>
#include <sstream>

Grid::Grid()
{
	gameState = std::make_shared<GameState>();
	gameState->playerPlayed = EnumTileState::Empty;
	gameState->winConfig = EnumWinningConfig::None;
}

void Grid::resetGrid()
{
	std::memset(array, static_cast<int>(EnumTileState::Empty), sizeof(array));
}

bool Grid::isTileAvailable(int _x, int _y)
{
	return array[_x][_y] == EnumTileState::Empty;
}

bool Grid::gameRunning()
{
	return gameState->win;
}

bool Grid::arrayIsFull()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (isTileAvailable(i, j))
				return false;
		}
	}
	return true;
}

bool Grid::playTurn(EnumTileState _player, int _x, int _y)
{
	if (!isTileAvailable(_x, _y))
		return false;
	array[_x][_y] = _player;
	playerPlayed = _player;

	gameState = std::make_shared<GameState>(updateGameState());
	return true;
}

void Grid::printGrid()
{
	std::wstring s[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (array[i][j]) {
				case EnumTileState::Cross:
					s[i][j] = colorTile(L"X", i, j); break;
				case EnumTileState::Circle: 
					s[i][j] = colorTile(L"O", i, j); break;
				default: 
					s[i][j] = L" "; break;
			}
		}
	}

	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wstringstream board;
	board << L"╔═══╤═══╤═══╗\n";
	board << L"║ " << s[0][0] << L" │ " << s[0][1] << L" │ " << s[0][2] << L" ║\n";
	board << L"╟───┼───┼───╢\n";
	board << L"║ " << s[1][0] << L" │ " << s[1][1] << L" │ " << s[1][2] << L" ║\n";
	board << L"╟───┼───┼───╢\n";
	board << L"║ " << s[2][0] << L" │ " << s[2][1] << L" │ " << s[2][2] << L" ║\n";
	board << L"╚═══╧═══╧═══╝\n";
	
	std::wcout << board.str();
}

std::shared_ptr<GameState> Grid::getGameState()
{
	return gameState;
}

std::wstring Grid::colorTile(std::wstring _tile, int _x, int _y)
{
	if (!gameState->win)
		return _tile;

	std::wstring winTile = WIN_COLOR_OPEN + _tile + COLOR_CLOSE;

	switch (gameState->winConfig) {
	case EnumWinningConfig::Column :
		return (_y == gameState->winIndex) ? winTile : _tile; break;
	case EnumWinningConfig::Line:
		return (_x == gameState->winIndex) ? winTile : _tile; break;
	case EnumWinningConfig::DiagBLTR:
		return (_x == 0 && _y == 2 || _x == _y == 1 || _x == 2 && _y == 0) ? winTile : _tile; break;
	case EnumWinningConfig::DiagTLBR:
		return (_x == 2 && _y == 0 || _x == _y == 1 || _x == 0 && _y == 2) ? winTile : _tile; break;
	default:
		return _tile; break;
	}
}

GameState Grid::updateGameState()
{
	GameState gameState;
	auto pair = checkVictory();
	gameState.winConfig = pair.first;
	gameState.winIndex = pair.second;
	gameState.win = gameState.winConfig != EnumWinningConfig::None || arrayIsFull();
	gameState.playerPlayed = playerPlayed;
	return gameState;
}

std::pair<EnumWinningConfig, int> Grid::checkVictory()
{
	// Vérification des lignes
	for (int i = 0; i < 3; ++i) {
		if (array[i][0] != EnumTileState::Empty && array[i][0] == array[i][1] && array[i][1] == array[i][2]) {
			return { EnumWinningConfig::Line, i }; // Victoire par ligne
		}
	}

	// Vérification des colonnes
	for (int j = 0; j < 3; ++j) {
		if (array[0][j] != EnumTileState::Empty && array[0][j] == array[1][j] && array[1][j] == array[2][j]) {
			return { EnumWinningConfig::Column, j }; // Victoire par colonne
		}
	}

	// Vérification des diagonales
	if (array[0][0] != EnumTileState::Empty && array[0][0] == array[1][1] && array[1][1] == array[2][2]) {
		return { EnumWinningConfig::DiagTLBR, -1 }; // Victoire par diagonale de haut en bas
	}

	if (array[0][2] != EnumTileState::Empty && array[0][2] == array[1][1] && array[1][1] == array[2][0]) {
		return { EnumWinningConfig::DiagBLTR, -1 }; // Victoire par diagonale de bas en haut
	}

	// Aucune victoire
	return { EnumWinningConfig::None, -1 };
}
