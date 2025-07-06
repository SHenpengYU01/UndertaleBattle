
#include "../common/property_id.h"

#include "GameViewModel.h"


GameViewModel::GameViewModel(Board& board, Player& player, GameFile& gamefile, Gaster& gaster):	m_board(&board),
	m_player(&player),
	m_gamefile(&gamefile),
	m_gaster(&gaster),
	current_turn(0),
	turn_tick(0)
{

}

void GameViewModel::HandleInput(){
    int cmd_id = CMD_ID::NONE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        cmd_id = CMD_ID::LEFT;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        cmd_id = CMD_ID::RIGHT;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        cmd_id = (cmd_id == CMD_ID::LEFT)? CMD_ID::LEFTUP:
                (cmd_id == CMD_ID::RIGHT)? CMD_ID::RIGHTUP:
                CMD_ID::UP;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        cmd_id = (cmd_id == CMD_ID::LEFT)? CMD_ID::LEFTDOWN:
                (cmd_id == CMD_ID::RIGHT)? CMD_ID::RIGHTDOWN:
                CMD_ID::DOWN;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        cmd_id = CMD_ID::Z;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        cmd_id = CMD_ID::X;
    }
    this->fire(PROP_ID::CMD,cmd_id);
}

void GameViewModel::Update()
{
	const DWORD current_tick = GetTickCount();

	if (this->m_player->GetPlayerHealth() > 0 && this->current_turn != last_turn) // If current_turn equals last_turn, the game finishes.
	{
		this->HandleInput();
		this->m_board->Update();

		if (!this->m_player->IsPlayerInTurn())
		{
			if (this->turn_tick < current_tick && this->m_player->GetButtonUseTick() < current_tick)
			{
				if( this->current_turn < this->turn_handlers.size() ){
					this->turn_handlers[current_turn]();
				}
			}
		}
		this->m_gaster->Update();
	}else{
		if (this->current_turn != last_turn){
			this->HandlePlayerDeath();
		}else{
			this->HandleGameEnd();
		}
	}

	if (this->current_turn != last_turn) // Player updates should stop on the last turn (in this case, the game finished).
	{
		this->m_player->Update();
	}

}


void GameViewModel::HandlePlayerDeath(){
	if ( !this->m_gamefile->IsMusicPaused() )
	{
		this->m_gamefile->StopMusic();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->m_board->SetBoardWidth(165.f);
		this->m_player->Reset();
		this->m_gaster->Reset();
		this->m_gamefile->PlayMusic();
		this->current_turn = 2;
		this->turn_tick = 0;
	}
	this->fire(PROP_ID::SPRITE, this->m_gamefile->GetGameOverSpirte() );
}


void GameViewModel::HandleGameEnd(){
	if ( this->m_gamefile->IsMusicPaused() )
	{
		this->m_gamefile->PlayMusic();
		this->m_gaster->Reset();
	}
	this->fire(PROP_ID::TEXT, this->m_gamefile->GetCreditsText() );
}

void GameViewModel::InitTurnHandlers(){
    DWORD current_tick = GetTickCount();
    this->turn_handlers = {
        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 1;
            this->turn_tick = current_tick + 4000;
            this->m_gaster->SetText("\n\n(￣▽￣)~*", 4000);
        },
        
        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 2;
            this->turn_tick = current_tick + 3000;
            this->m_gaster->SetText("测试用\n\n(=´o｀=)", 3000);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 3;
            this->turn_tick = current_tick + 5000;
            this->m_gaster->SetText("（若无其事）\n\n┗( ▔, ▔ )┛", 5000);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 4;
            this->turn_tick = current_tick + 2750;

            this->m_gaster->AddBlaster(sf::Vector2f(256.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 100);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 235.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 1000);
            this->m_gaster->AddBlaster(sf::Vector2f(181.f, 90.f), Blaster_Direction::Direction_Down, 1200, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 301.f), Blaster_Direction::Direction_Left, 1200, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(211.f, 90.f), Blaster_Direction::Direction_Down, 1350, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 271.f), Blaster_Direction::Direction_Left, 1350, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(241.f, 90.f), Blaster_Direction::Direction_Down, 1500, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 241.f), Blaster_Direction::Direction_Left, 1500, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(274.f, 90.f), Blaster_Direction::Direction_Down, 1650, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 208.f), Blaster_Direction::Direction_Left, 1650, Blaster_Type::Default_Blaster, 120);
            
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 5;
            this->turn_tick = current_tick + 720;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 6;
            this->turn_tick = current_tick + 720;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
            
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 7;
            this->turn_tick = current_tick + 1200;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);    
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->m_player->TogglePlayerTurn(true, "* 好吧\n\n (▼ヘ▼#)", 1000);
            this->m_board->SetBoardWidth(400.f);
            this->current_turn = 8;   
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 3100;
            this->m_gaster->AddBlaster(sf::Vector2f(70.f, 90.f), Blaster_Direction::Direction_Down);
            this->m_gaster->AddBlaster(sf::Vector2f(106.f, 90.f), Blaster_Direction::Direction_Down, 300);
            this->m_gaster->AddBlaster(sf::Vector2f(154.f, 90.f), Blaster_Direction::Direction_Down, 600);
            this->m_gaster->AddBlaster(sf::Vector2f(199.f, 90.f), Blaster_Direction::Direction_Down, 900);
            this->m_gaster->AddBlaster(sf::Vector2f(226.f, 90.f), Blaster_Direction::Direction_Down, 1200);
            this->m_gaster->AddBlaster(sf::Vector2f(286.f, 90.f), Blaster_Direction::Direction_Down, 1500);
            this->m_gaster->AddBlaster(sf::Vector2f(346.f, 90.f), Blaster_Direction::Direction_Down, 1800);
            this->m_gaster->AddBlaster(sf::Vector2f(5.f, 340.f), Blaster_Direction::Direction_Right, 2100);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, 280.f), Blaster_Direction::Direction_Left, 2100);
            this->current_turn = 9;    
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 10;
            this->m_gaster->ToggleGasterSurprised(true);
            this->turn_tick = current_tick + 10000;
            this->m_gaster->SetText("尝尝这个 \n\no(*｀ー´)o^", 4500);

            this->m_gaster->AddBlaster(sf::Vector2f(70.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(106.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(154.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(199.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(337.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(373.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(409.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(442.f, 90.f), Blaster_Direction::Direction_Down, 4600, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(70.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(106.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(154.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(199.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(337.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(373.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(409.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(442.f, 90.f), Blaster_Direction::Direction_Down, 5800, Blaster_Type::Orange_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(70.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(106.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(154.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(199.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(337.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(373.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(409.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(442.f, 90.f), Blaster_Direction::Direction_Down, 7000, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(70.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(106.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Default_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(154.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(199.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Default_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Default_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(337.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(373.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Default_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(409.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(442.f, 90.f), Blaster_Direction::Direction_Down, 8200, Blaster_Type::Default_Blaster, 500);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->m_gaster->ToggleGasterSurprised(false);
            this->m_player->TogglePlayerTurn(true, "* 感觉要寄", 700);
            this->current_turn = 11;
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 12;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 13;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 14;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 15;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 16;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 2510;
            this->current_turn = 17;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);

            this->m_gaster->AddBlaster(sf::Vector2f(70.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(106.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(154.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(199.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(337.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(373.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(409.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
            this->m_gaster->AddBlaster(sf::Vector2f(442.f, 90.f), Blaster_Direction::Direction_Down, 800, Blaster_Type::Blue_Blaster, 500);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->m_player->TogglePlayerTurn(true, "* 她似乎在准备什么。。。", 700);
            this->m_board->SetBoardWidth(165.f);
            this->current_turn = 18;
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 2100;
            this->current_turn = 19;

            this->m_gaster->SetText("闹剧结束！\n\n\\(￣へ￣)/", 2000);
            this->m_gaster->ToggleGasterSurprised(true);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->m_gaster->ToggleGasterSurprised(false);
            this->turn_tick = current_tick + 720;
            this->current_turn = 20;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 21;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 22;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 23;

            this->m_gaster->AddBlaster(sf::Vector2f(m_player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(638.f, m_player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 3200;
            this->current_turn = 24;
            this->m_gaster->AddBlaster(sf::Vector2f(181.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 301.f), Blaster_Direction::Direction_Left, 200, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(211.f, 90.f), Blaster_Direction::Direction_Down, 350, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 271.f), Blaster_Direction::Direction_Left, 350, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(241.f, 90.f), Blaster_Direction::Direction_Down, 500, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 241.f), Blaster_Direction::Direction_Left, 500, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(274.f, 90.f), Blaster_Direction::Direction_Down, 650, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 208.f), Blaster_Direction::Direction_Left, 650, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(325.f, 90.f), Blaster_Direction::Direction_Down, 1000, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 157.f), Blaster_Direction::Direction_Left, 1000, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 1150, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 187.f), Blaster_Direction::Direction_Left, 1150, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(265.f, 90.f), Blaster_Direction::Direction_Down, 1300, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 223.f), Blaster_Direction::Direction_Left, 1300, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(238.f, 90.f), Blaster_Direction::Direction_Down, 1550, Blaster_Type::Default_Blaster, 120);
            this->m_gaster->AddBlaster(sf::Vector2f(530.f, 253.f), Blaster_Direction::Direction_Left, 1550, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 4600;
            this->current_turn = 25;
            this->m_gaster->SetText("算了吧\n\no(´^｀)o", 4500);
            this->m_gamefile->StopMusic();
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 5100;
            this->current_turn = 26;
            this->m_gaster->ToggleGasterSurprised(true);
            this->m_gaster->SetText("你赢了\n\no(╥﹏╥)o", 5100);
            this->m_gaster->AddBlaster(sf::Vector2f(181.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->m_gaster->AddBlaster(sf::Vector2f(217.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->m_gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->m_gaster->AddBlaster(sf::Vector2f(271.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->m_gaster->AddBlaster(sf::Vector2f(301.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->m_gaster->AddBlaster(sf::Vector2f(325.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
        },

        [this](){
            this->current_turn = 27; // This turn means the game finished.
        }
    };
}
