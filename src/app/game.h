#ifndef _GAME_H_
#define _GAME_H_

#include "../viewmodel/gamefile.h"
#include "../viewmodel/board.h"
#include "../viewmodel/player.h"
#include "../viewmodel/gaster.h"
#include "../common/property_id.h"
#include "../view/mainwindow.h"


class MainWindow;
class Player;
class Gaster;
class Board;
class GameFile;

class Game
{
	private:
		MainWindow window;
		// sf::RenderWindow window;


		DWORD turn_tick;
		int current_turn;
		GameFile *gamefile;
		
		Board *board;
		Player *player;
		Gaster *gaster;
		std::vector<std::function<void()>> turn_handlers;

	public:
		Game();

		void Update();
		void HandleWindowEvent();
		void HandlePlayerDeath();
		void HandleGameEnd();
		void InitTurnHandlers();
};

#endif