#ifndef _GAME_H_
#define _GAME_H_

#include "../viewmodel/GameViewModel.h"
#include "../common/property_id.h"
#include "../view/mainwindow.h"

class MainWindow;
class Player;
class Gaster;
class Board;
class GameFile;
class GameViewModel;

class Game
{
	private:
		MainWindow window;
		// sf::RenderWindow window;

		std::vector<std::function<void()>> turn_handlers;

	public:
		GameViewModel *m_GameViewModel;
		Game();
		Game(const Game&) = delete;
		~Game() noexcept
		{	
		}
		Game& operator=(const Game&) = delete;
		void HandleWindowEvent();
        bool initialize();
		void Update();
		void Run();
};

#endif