
#ifndef __GAME_VIEW_MODEL_H__
#define __GAME_VIEW_MODEL_H__

#include "../common/frame.h"
#include "board.h"
#include "player.h"
#include "gaster.h"
#include "gamefile.h"
#include "../common/property_id.h"


class GameViewModel : public PropertyTrigger
{
public:
	GameViewModel();
	GameViewModel(Board* board, Player* player, GameFile* gamefile, Gaster* gaster);
	GameViewModel(const GameViewModel&) = delete;
	~GameViewModel() noexcept
	{
	}

	GameViewModel& operator=(const GameViewModel&) = delete;

//properties


//commands
	std::function<void()> get_next_step_command();

//methods
	void next_step(int turn);
    
	void HandlePlayerDeath();

	void HandleGameEnd();

	void InitTurnHandlers();
    
	void HandleInput();

	void Update();

	Board* m_board;
	Player* m_player;
	GameFile* m_gamefile;
	int current_turn;
	DWORD turn_tick;
    Gaster* m_gaster;
	
private:
    const int last_turn = 27;
	std::vector<std::function<void()>> turn_handlers;


};

#endif
