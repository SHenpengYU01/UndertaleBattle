#include "gamefile.h"

GameFile::GameFile(){
    FileManager::LoadFromFile(this->game_icon, "bin/sprites/game.png");
	FileManager::LoadFromFile(this->game_music, "bin/audio/megalovania.ogg");
	FileManager::LoadFromFile(this->game_over_texture, "bin/sprites/game_over.png");
	FileManager::LoadFromFile(this->credits_text_font, "bin/fonts/determination_mono.ttf");

	if (!FileManager::IsAnyFileMissing())
	{

		this->game_music.setLoop(true);
		this->game_music.play();
		this->game_over_sprite.setTexture(this->game_over_texture);
		this->game_over_sprite.setPosition(sf::Vector2f(121.f, 30.f));
		this->credits_text.setFont(this->credits_text_font);
		this->credits_text.setCharacterSize(20);
		this->credits_text.setFillColor(sf::Color::White);
		this->credits_text.setPosition(50.f, 220.f);
		this->credits_text.setString("Credits:\n* Toby Fox for Undertale.\n* Brunoo16 for ut-gaster-fight.\n* And you for playing this fan-game.");
	}
}



