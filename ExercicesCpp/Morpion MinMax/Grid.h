#pragma once
#include <memory>
#include <string>

#define WIN_COLOR_OPEN L"\033[31m"
#define COLOR_CLOSE L"\033[m"

enum class EnumTileState {
	Empty,
	Cross,
	Circle
};

enum class EnumWinningConfig {
	None,
	Column,
	Line,
	DiagBLTR,
	DiagTLBR
};

struct GameState {
	bool win;
	EnumTileState playerPlayed;
	EnumWinningConfig winConfig;
	int winIndex;
};


class Grid
{
public:
	Grid();
	void resetGrid();
	bool playTurn(EnumTileState _player, int _x, int _y);
	void printGrid();
	std::shared_ptr<GameState> getGameState();
	bool isTileAvailable(int _x, int _y);
	bool gameRunning();
	bool arrayIsFull();
private:
	std::wstring colorTile(std::wstring _tile, int _x, int _y);
	GameState updateGameState();
	std::pair<EnumWinningConfig, int> checkVictory();
	EnumTileState array[3][3];
	std::shared_ptr<GameState> gameState;
	EnumTileState playerPlayed;
};

