#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "../gamefile.h"
#include "../board.h"
#include "../player.h"
#include "../gaster.h"
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

	public:
		Game();

		void Update();
};

#endif