#include "game.h"

Game::Game() : window(sf::VideoMode(642, 481), "Gaster Fight", sf::Style::Titlebar | sf::Style::Close)
{
	Game::initialize();
}

bool Game::initialize(){
    this->window.setFramerateLimit(60);
	// this->window.setIcon(20, 19, this->gamefile->GetGameIcon().getPixelsPtr());
	
	GameFile* gamefile = new GameFile();
	Board* board = new Board();
	Player* player = new Player(board);
	Gaster* gaster = new Gaster(player);
    this->m_GameViewModel = new GameViewModel(board, player, gamefile, gaster);
    this->m_GameViewModel->InitTurnHandlers();

	this->window.SetNextCommand( this->m_GameViewModel->m_player->GetNextCommand() );
	for(int i=0; i < PROP_ID::PROP_ID_NUM; i++){
		this->m_GameViewModel->m_player->AddNotification( this->window.GetNotification(i) );
	}

	for(int i=0; i < PROP_ID::PROP_ID_NUM; i++){
		this->m_GameViewModel->m_board->AddNotification( this->window.GetNotification(i) );
	}

	for(int i=0; i < PROP_ID::PROP_ID_NUM; i++){
		this->m_GameViewModel->m_gaster->AddNotification( this->window.GetNotification(i) );
	}
    return true;
}

void Game::HandleWindowEvent(){
    sf::Event event;
    while(this->window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                this->window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape){
                    this->window.close();
                }
                break;
            default:
                break;
        }
    }
}
void Game::Run(){
    constexpr int last_turn = 27;
    while(this->window.isOpen()){
        this->HandleWindowEvent();
        this->m_GameViewModel->Update();
        this->window.display();
    }
}
