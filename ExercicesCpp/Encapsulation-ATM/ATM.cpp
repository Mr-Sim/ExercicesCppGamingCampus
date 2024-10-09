#include <iostream>
#include <windows.h>

enum State {
	MainMenu,
	Solde,
	Depot,
	Retrait
};

State state;

bool shouldQuit;

const std::string mainMenu =
"- |||===========================================||| -\n"
"- ||| -             MENU PRINCIPAL            - ||| -\n"
"- ||| -                                       - ||| -\n"
"- ||| 1) VOIR LE SOLDE    | 3) FAIRE UN DEPOT   ||| -\n"
"- ||| 2) FAIRE UN RETRAIT | 4) QUITTER          ||| -\n"
"- ||| -                                       - ||| -\n"
"-_|||_                                         _|||_-\n\n";

const std::string prompt = "Sélectionnez une action : ";
void HandleMoron() {
	ShellExecute(0, 0, L"https://fr.wikipedia.org/wiki/Liste_des_troubles_mentaux", 0, 0, SW_SHOW);
	exit(1);
}

int AskInt(std::string _prompt, int _min, int _max) {
	int input;
	std::cout << _prompt;
	std::cin >> input;

	if (input < _min || input > _max) {
		HandleMoron();
	}
	return input;
}

void HandleMainMenu() {
	std::cout.clear();
	std::cout << mainMenu;
	int choice = AskInt(prompt, 1, 4);
	switch (choice) {
	case 1: state = State::Solde; break;
	case 2: state = State::Retrait; break;
	case 3: state = State::Depot; break;
	case 4: shouldQuit = true; break;
	}
}



void main() {
	shouldQuit = false;
	state = State::MainMenu;

	while (!shouldQuit) {
		switch (state) {
		case MainMenu: HandleMainMenu();
		case Solde: HandleMainMenu();
		case Depot: HandleMainMenu();
		case Retrait: HandleMainMenu();
		}
	}

}

