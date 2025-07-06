#pragma once

#include "../main.h"
#include "file_manager.h"
#include "player/player.h"

class GameFile{
private:
    sf::Image game_icon;
    sf::Music game_music;
    sf::Texture game_over_texture;
    sf::Sprite game_over_sprite;
    sf::Font credits_text_font;
    sf::Text credits_text;
public:
    GameFile();
    GameFile(const GameFile& other) = delete;

    inline bool IsMusicPaused(){
        return this->game_music.getStatus() == sf::Music::Status::Stopped;
    }

    inline void StopMusic(){
        this->game_music.stop();
    }

    inline void PlayMusic(){
        this->game_music.play();
    }

    inline sf::Sprite GetGameOverSpirte(){
        return this->game_over_sprite;
    }

    inline sf::Text GetCreditsText(){
        return this->credits_text;
    }

    inline sf::Image GetGameIcon(){
        return this->game_icon;
    }

};


