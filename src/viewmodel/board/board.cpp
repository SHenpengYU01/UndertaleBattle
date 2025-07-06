#include "board.h"

Board::Board() : board_width(165.f), board_text_position(0), board_text_tick(0), attack_bar_x(0)
{
	FileManager::LoadFromFile(this->fight_button_texture, "bin/sprites/fightbt.png");
	FileManager::LoadFromFile(this->fight_button_hover_texture, "bin/sprites/fightbt_hover.png");
	FileManager::LoadFromFile(this->act_button_texture, "bin/sprites/actbt.png");
	FileManager::LoadFromFile(this->act_button_hover_texture, "bin/sprites/actbt_hover.png");
	FileManager::LoadFromFile(this->item_button_texture, "bin/sprites/itembt.png");
	FileManager::LoadFromFile(this->item_button_hover_texture, "bin/sprites/itembt_hover.png");
	FileManager::LoadFromFile(this->mercy_button_texture, "bin/sprites/mercybt.png");
	FileManager::LoadFromFile(this->mercy_button_hover_texture, "bin/sprites/mercybt_hover.png");
	FileManager::LoadFromFile(this->hp_texture, "bin/sprites/hp.png");
	FileManager::LoadFromFile(this->board_text_font, "bin/fonts/fusion-pixel-10px-monospaced-zh_hans.ttf");
	FileManager::LoadFromFile(this->text_update_sound_buffer, "bin/audio/border_text.wav");

	FileManager::LoadFromFile(this->fight_eye_texture, "bin/sprites/fight_eye.png");

	if (!FileManager::IsAnyFileMissing())
	{
		this->hp_sprite.setTexture(this->hp_texture);
		this->hp_sprite.setPosition(sf::Vector2f(226.f, 404.f));

		this->board_rectangle.setPosition(sf::Vector2f(325.f, 302.f));
		this->board_rectangle.setSize(sf::Vector2f(165.f, 165.f));
        this->board_rectangle.setOrigin(sf::Vector2f(this->board_rectangle.getLocalBounds().width / 2.f, this->board_rectangle.getLocalBounds().height / 2.f));
		this->board_rectangle.setOutlineColor(sf::Color::White);
		this->board_rectangle.setFillColor(sf::Color(255, 255, 255, 0));
		this->board_rectangle.setOutlineThickness(5);

		this->attack_bar.setSize(sf::Vector2f(15.f, 175.f));
		this->attack_bar.setFillColor(sf::Color::Blue);
		this->attack_bar.setPosition(sf::Vector2f(20.f, 209.f));
		this->fight_button_sprite.setTexture(this->fight_button_texture);
		this->act_button_sprite.setTexture(this->act_button_texture);
		this->item_button_sprite.setTexture(this->item_button_texture);
		this->mercy_button_sprite.setTexture(this->mercy_button_texture);
		this->fight_button_sprite.setPosition(sf::Vector2f(34.f, 431.f));
		this->act_button_sprite.setPosition(sf::Vector2f(187.f, 431.f));
		this->item_button_sprite.setPosition(sf::Vector2f(347.f, 431.f));
		this->mercy_button_sprite.setPosition(sf::Vector2f(502.f, 431.f));

		this->board_text.setFont(this->board_text_font);
		this->board_text.setCharacterSize(30);
		this->board_text.setFillColor(sf::Color::White);
		this->board_text.setPosition(50.f, 220.f);
		this->board_options_text.setFont(this->board_text_font);
		this->board_options_text.setCharacterSize(30);
		this->board_options_text.setFillColor(sf::Color::White);
		this->board_options_text.setPosition(70.f, 220.f);

		this->show_board_text = false;
		this->show_board_options_text = false;
		this->text_update_sound.setBuffer(this->text_update_sound_buffer);

		this->show_fight_eye = false;
		this->fight_eye_sprite.setTexture(this->fight_eye_texture);
		this->fight_eye_sprite.setScale(sf::Vector2f(1.25f, 1.25f));
		this->fight_eye_sprite.setPosition(0.f, 224.f);
		this->stop_attack = true;
		this->stop_attack = false;


	}
}

void Board::SetBoardText(const std::string &text, const DWORD delay)
{
	this->board_text_tick = GetTickCount() + delay;
	this->board_text_position = 0;
	this->board_text.setString("");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide_text = converter.from_bytes(text);
	this->board_text_buffer = wide_text;
}

sf::FloatRect Board::GetButtonGlobalBounds(const char button_type) const
{
	switch (button_type)
	{
		case Button_Type::Fight_Button:
		{
			return this->fight_button_sprite.getGlobalBounds();
		}
		case Button_Type::Act_Button:
		{
			return this->act_button_sprite.getGlobalBounds();
		}
		case Button_Type::Item_Button:
		{
			return this->item_button_sprite.getGlobalBounds();
		}
		case Button_Type::Mercy_Button:
		{
			return this->mercy_button_sprite.getGlobalBounds();
		}
		default:
			return sf::FloatRect();
	}
}

void Board::HoverButton(const char button_type)
{
	switch (button_type)
	{
		case Button_Type::Fight_Button:
		{
			this->fight_button_sprite.setTexture(this->fight_button_hover_texture);
			this->act_button_sprite.setTexture(this->act_button_texture);
			this->item_button_sprite.setTexture(this->item_button_texture);
			this->mercy_button_sprite.setTexture(this->mercy_button_texture);
			break;
		}
		case Button_Type::Act_Button:
		{
			this->fight_button_sprite.setTexture(this->fight_button_texture);
			this->act_button_sprite.setTexture(this->act_button_hover_texture);
			this->item_button_sprite.setTexture(this->item_button_texture);
			this->mercy_button_sprite.setTexture(this->mercy_button_texture);
			break;
		}
		case Button_Type::Item_Button:
		{
			this->fight_button_sprite.setTexture(this->fight_button_texture);
			this->act_button_sprite.setTexture(this->act_button_texture);
			this->item_button_sprite.setTexture(this->item_button_hover_texture);
			this->mercy_button_sprite.setTexture(this->mercy_button_texture);
			break;
		}
		case Button_Type::Mercy_Button:
		{
			this->fight_button_sprite.setTexture(this->fight_button_texture);
			this->act_button_sprite.setTexture(this->act_button_texture);
			this->item_button_sprite.setTexture(this->item_button_texture);
			this->mercy_button_sprite.setTexture(this->mercy_button_hover_texture);
			break;
		}
		default:
		{
			this->fight_button_sprite.setTexture(this->fight_button_texture);
			this->act_button_sprite.setTexture(this->act_button_texture);
			this->item_button_sprite.setTexture(this->item_button_texture);
			this->mercy_button_sprite.setTexture(this->mercy_button_texture);
		}
	}
}

void Board::Update()
{
	const DWORD current_tick = GetTickCount();

	this->fire(PROP_ID::RECTANGLE_SHAPE, this->board_rectangle);
	this->fire(PROP_ID::SPRITE, this->hp_sprite);
	this->fire(PROP_ID::SPRITE, this->fight_button_sprite);
	this->fire(PROP_ID::SPRITE, this->act_button_sprite);
	this->fire(PROP_ID::SPRITE, this->item_button_sprite);
	this->fire(PROP_ID::SPRITE, this->mercy_button_sprite);

	
	if (this->show_board_text){
		if (this->board_text_position != this->board_text_buffer.size() && (current_tick > this->board_text_tick))
		{
			this->board_text_tick = current_tick + 50;
			this->board_text.setString(this->board_text.getString() + this->board_text_buffer[this->board_text_position]);
			this->board_text_position++;
			this->text_update_sound.play();
		}
		this->fire(PROP_ID::TEXT, this->board_text);
	}

	if (this->show_board_options_text){
		this->fire(PROP_ID::TEXT, this->board_options_text);
	}

	if(this->show_fight_eye){
		fire(PROP_ID::SPRITE, this->fight_eye_sprite);
		const DWORD current_tick = GetTickCount();
		static DWORD attack_bar_move_tick = 0;
		static sf::FloatRect bounds = this->board_rectangle.getGlobalBounds();
		const static float attack_end = bounds.left + bounds.width;
		if(this->stop_attack){  // show flashing attack bar
			static DWORD flash_tick = 0;
			DWORD current_tick = GetTickCount();
			if (current_tick > flash_tick)
			{
				flash_tick = current_tick + 200;

				if (this->flash_hit_color == false)
				{
					this->flash_hit_color = true;
					this->attack_bar.setFillColor(sf::Color(0, 0, 150));
				}else
				{
					this->flash_hit_color = false;
					this->attack_bar.setFillColor(sf::Color(0, 0, 255));
				}
			}
		}else if(attack_bar_move_tick < current_tick){  //move flashing attack bar
			attack_bar_x += 3.f;
			if(attack_bar_x > attack_end){
				attack_bar_x = bounds.left;
			}
			this->attack_bar.setPosition(sf::Vector2f(attack_bar_x, 209.f));
			attack_bar_move_tick = current_tick + 8;
		}
		fire(PROP_ID::RECTANGLE_SHAPE, this->attack_bar);
	}
<<<<<<< HEAD:src/viewmodel/board/board.cpp
}
=======
}
>>>>>>> yzy:src/viewmodel/board.cpp
