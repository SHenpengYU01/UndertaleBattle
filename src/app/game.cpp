#include "game.h"

Game::Game() : window(sf::VideoMode(642, 481), "Gaster Fight", sf::Style::Titlebar | sf::Style::Close), current_turn(0), turn_tick(0)
{
	this->window.setFramerateLimit(60);
	// this->window.setIcon(20, 19, this->gamefile->GetGameIcon().getPixelsPtr());
	
	this->gamefile = new GameFile();
	this->board = new Board();
	this->player = new Player(this->board);
	this->gaster = new Gaster(this->player);

    this->InitTurnHandlers();

	this->window.SetNextCommand( this->player->GetNextCommand() );
	for(int i=0; i < PROP_ID::PROP_ID_NUM; i++){
		this->player->AddNotification( this->window.GetNotification(i) );
	}

	for(int i=0; i < PROP_ID::PROP_ID_NUM; i++){
		this->board->AddNotification( this->window.GetNotification(i) );
	}

	for(int i=0; i < PROP_ID::PROP_ID_NUM; i++){
		this->gaster->AddNotification( this->window.GetNotification(i) );
	}
}


void Game::HandleWindowEvent(){
	sf::Event event;
	
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}
	}
	this->window.clear();
}

void Game::Update()
{
	constexpr int last_turn = 27;

	while (this->window.isOpen())
	{
        this->HandleWindowEvent();
		const DWORD current_tick = GetTickCount();

		if (this->player->GetPlayerHealth() > 0 && this->current_turn != last_turn) // If current_turn equals last_turn, the game finishes.
		{
			this->window.HandleInput();
			this->board->Update();

			if (!this->player->IsPlayerInTurn())
			{
				if (this->turn_tick < current_tick && this->player->GetButtonUseTick() < current_tick)
				{
					if( this->current_turn < this->turn_handlers.size() ){
                        this->turn_handlers[current_turn]();
                    }
				}
			}
			this->gaster->Update();
		}else{
			if (this->current_turn != last_turn){
				this->HandlePlayerDeath();
			}else{
				HandleGameEnd();
			}
		}

		if (this->current_turn != last_turn) // Player updates should stop on the last turn (in this case, the game finished).
		{
			this->player->Update();
		}

		this->window.display();
	}
}

void Game::HandlePlayerDeath(){
	if ( !this->gamefile->IsMusicPaused() )
	{
		this->gamefile->StopMusic();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->board->SetBoardWidth(165.f);
		this->player->Reset();
		this->gaster->Reset();
		this->gamefile->PlayMusic();
		this->current_turn = 2;
		this->turn_tick = 0;
	}
	this->window.draw( this->gamefile->GetGameOverSpirte() );
}

void Game::HandleGameEnd(){
	if ( this->gamefile->IsMusicPaused() )
	{
		this->gamefile->PlayMusic();
		this->gaster->Reset();
	}
	this->window.draw( this->gamefile->GetCreditsText() );
}

void Game::InitTurnHandlers(){
    DWORD current_tick = GetTickCount();
    this->turn_handlers = {
        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 1;
            this->turn_tick = current_tick + 4000;
            this->gaster->SetText("\n\n(￣▽￣)~*", 4000);
        },
        
        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 2;
            this->turn_tick = current_tick + 3000;
            this->gaster->SetText("测试用\n\n(=´o｀=)", 3000);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 3;
            this->turn_tick = current_tick + 5000;
            this->gaster->SetText("（若无其事）\n\n┗( ▔, ▔ )┛", 5000);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 4;
            this->turn_tick = current_tick + 2750;

            this->gaster->AddBlaster(sf::Vector2f(256.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 1000);
            this->gaster->AddBlaster(sf::Vector2f(530.f, 235.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 1000);
            this->gaster->AddBlaster(sf::Vector2f(181.f, 90.f), Blaster_Direction::Direction_Down, 1200, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, 301.f), Blaster_Direction::Direction_Left, 1200, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(211.f, 90.f), Blaster_Direction::Direction_Down, 1350, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, 271.f), Blaster_Direction::Direction_Left, 1350, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(241.f, 90.f), Blaster_Direction::Direction_Down, 1500, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, 241.f), Blaster_Direction::Direction_Left, 1500, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(274.f, 90.f), Blaster_Direction::Direction_Down, 1650, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, 208.f), Blaster_Direction::Direction_Left, 1650, Blaster_Type::Default_Blaster, 120);
            
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 5;
            this->turn_tick = current_tick + 720;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 6;
            this->turn_tick = current_tick + 720;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
            
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 7;
            this->turn_tick = current_tick + 1200;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(530.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);    
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->player->TogglePlayerTurn(true, "* 好吧\n\n (▼ヘ▼#)", 1000);
            this->board->SetBoardWidth(400.f);
            this->current_turn = 8;   
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 3100;

            // 向下炮台(7个等距排列)
            const float downY = 90.f;
            float downX[7] = {70.f, 130.f, 190.f, 250.f, 310.f, 370.f, 430.f};
            for (int i = 0; i < 7; i++) {
                this->gaster->AddBlaster(
                    sf::Vector2f(downX[i], downY),
                    Blaster_Direction::Direction_Down,
                    300 * i
                );
            }

            this->gaster->AddBlaster(
                sf::Vector2f(20.f, 350.f), 
                Blaster_Direction::Direction_Right,
                2100
            );
            this->gaster->AddBlaster(
                sf::Vector2f(622.f, 300.f), 
                Blaster_Direction::Direction_Left,
                2100
            );
            
            this->current_turn = 9;
        },


        [this](){
            DWORD current_tick = GetTickCount();
            this->current_turn = 10;
            this->gaster->ToggleGasterSurprised(true);
            this->turn_tick = current_tick + 10000;
            this->gaster->SetText("尝尝这个 \n\no(*｀ー´)o^", 4500);

            // 13组X坐标(间距30px，覆盖50-410px范围)
            float xPositions[13] = {50.f, 85.f, 120.f, 155.f, 190.f, 225.f, 260.f, 
                                295.f, 330.f, 365.f, 400.f, 435.f, 470.f};

            // 第一波：全蓝覆盖(4600ms)
            for(int i=0; i<13; i++) {
                this->gaster->AddBlaster(
                    sf::Vector2f(xPositions[i], 90.f),
                    Blaster_Direction::Direction_Down,
                    4600,
                    Blaster_Type::Blue_Blaster,
                    500
                );
            }

            // 第二波：全橙覆盖(5800ms)
            for(int i=0; i<13; i++) {
                this->gaster->AddBlaster(
                    sf::Vector2f(xPositions[i], 90.f),
                    Blaster_Direction::Direction_Down,
                    5800,
                    Blaster_Type::Orange_Blaster,
                    500
                );
            }

            // 第三波：蓝/默认交替(7000ms)
            for(int i=0; i<13; i++) {
                Blaster_Type type = (i % 2 == 0) ? Blaster_Type::Blue_Blaster 
                                                : Blaster_Type::Default_Blaster;
                this->gaster->AddBlaster(
                    sf::Vector2f(xPositions[i], 90.f),
                    Blaster_Direction::Direction_Down,
                    7000,
                    type,
                    500
                );
            }
        },

        

        [this](){
            DWORD current_tick = GetTickCount();
            this->gaster->ToggleGasterSurprised(false);
            this->player->TogglePlayerTurn(true, "* 感觉要寄", 700);
            this->current_turn = 11;
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 12;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 13;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 14;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 15;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 16;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 2510;
            this->current_turn = 17;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
            float xPositions[13] = {50.f, 80.f, 110.f, 140.f, 170.f, 200.f, 230.f, 
                                    260.f, 290.f, 320.f, 350.f, 380.f, 410.f};

                // 第一波：全蓝覆盖(4600ms)
                for(int i=0; i<13; i++) {
                    this->gaster->AddBlaster(
                        sf::Vector2f(xPositions[i], 90.f),
                        Blaster_Direction::Direction_Down,
                        800,
                        Blaster_Type::Blue_Blaster,
                        500
                    );
                }
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->player->TogglePlayerTurn(true, "* 她似乎在准备什么。。。", 700);
            this->board->SetBoardWidth(165.f);
            this->current_turn = 18;
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 2100;
            this->current_turn = 19;

            this->gaster->SetText("闹剧结束！\n\n\\(￣へ￣)/", 2000);
            this->gaster->ToggleGasterSurprised(true);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->gaster->ToggleGasterSurprised(false);
            this->turn_tick = current_tick + 720;
            this->current_turn = 20;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 21;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 22;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 720;
            this->current_turn = 23;

            this->gaster->AddBlaster(sf::Vector2f(player->GetPlayerPosition().x - 60.f, 90.f), Blaster_Direction::Direction_Down, 0, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, player->GetPlayerPosition().y - 60.f), Blaster_Direction::Direction_Left, 0, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 3200;
            this->current_turn = 24;
            this->gaster->AddBlaster(sf::Vector2f(181.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 301.f), Blaster_Direction::Direction_Left, 200, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(211.f, 90.f), Blaster_Direction::Direction_Down, 350, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 271.f), Blaster_Direction::Direction_Left, 350, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(241.f, 90.f), Blaster_Direction::Direction_Down, 500, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 241.f), Blaster_Direction::Direction_Left, 500, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(274.f, 90.f), Blaster_Direction::Direction_Down, 650, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 208.f), Blaster_Direction::Direction_Left, 650, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(325.f, 90.f), Blaster_Direction::Direction_Down, 1000, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 157.f), Blaster_Direction::Direction_Left, 1000, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(298.f, 90.f), Blaster_Direction::Direction_Down, 1150, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 187.f), Blaster_Direction::Direction_Left, 1150, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(265.f, 90.f), Blaster_Direction::Direction_Down, 1300, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 223.f), Blaster_Direction::Direction_Left, 1300, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(238.f, 90.f), Blaster_Direction::Direction_Down, 1550, Blaster_Type::Default_Blaster, 120);
            this->gaster->AddBlaster(sf::Vector2f(638.f, 253.f), Blaster_Direction::Direction_Left, 1550, Blaster_Type::Default_Blaster, 120);
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 4600;
            this->current_turn = 25;
            this->gaster->SetText("算了吧\n\no(´^｀)o", 4500);
            this->gamefile->StopMusic();
        },

        [this](){
            DWORD current_tick = GetTickCount();
            this->turn_tick = current_tick + 5100;
            this->current_turn = 26;
            this->gaster->ToggleGasterSurprised(true);
            this->gaster->SetText("你赢了\n\no(╥﹏╥)o", 5100);
            this->gaster->AddBlaster(sf::Vector2f(181.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->gaster->AddBlaster(sf::Vector2f(217.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->gaster->AddBlaster(sf::Vector2f(250.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->gaster->AddBlaster(sf::Vector2f(271.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->gaster->AddBlaster(sf::Vector2f(301.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
            this->gaster->AddBlaster(sf::Vector2f(325.f, 90.f), Blaster_Direction::Direction_Down, 200, Blaster_Type::Default_Blaster, 120, 100000);
        },

        [this](){
            this->current_turn = 27; // This turn means the game finished.
        }
    };
}
