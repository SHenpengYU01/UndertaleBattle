#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "player.h"
#include "gaster.h"
#include "board.h"
#include "gamefile.h"
// #include "window.h"

class Player;
class Gaster;
class Board;
// 在 game.h 文件中添加前向声明
class GameFile;

class Game
{
	private:
		// MainWindow window;
		sf::RenderWindow window;


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