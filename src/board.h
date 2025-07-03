#ifndef BOARD_H
#define BOARD_H

#include "main.h"
#include "file_manager.h"
#include "common/frame.h"
#include "common/property_id.h"

enum Button_Type
{
	Fight_Button,
	Act_Button,
	Item_Button,
	Mercy_Button,
	None
};

class Board : public PropertyTrigger
{
	private:
		sf::Texture fight_button_texture;
		sf::Texture fight_button_hover_texture;
		sf::Sprite fight_button_sprite;
		sf::Texture act_button_texture;
		sf::Texture act_button_hover_texture;
		sf::Sprite act_button_sprite;
		sf::Texture item_button_texture;
		sf::Texture item_button_hover_texture;
		sf::Sprite item_button_sprite;
		sf::Texture mercy_button_texture;
		sf::Texture mercy_button_hover_texture;
		sf::Sprite mercy_button_sprite;
		sf::Texture hp_texture;
		sf::Sprite hp_sprite;
		sf::RectangleShape board_rectangle;
		// sf::RenderWindow *window_instance;
		sf::Font board_text_font;
		sf::Text board_text;
		sf::Text board_options_text;
		std::wstring board_text_buffer;
		sf::SoundBuffer text_update_sound_buffer;
		sf::Sound text_update_sound;
		DWORD board_text_position;
		DWORD board_text_tick;
		bool show_board_text;
		bool show_board_options_text;
		float board_width;
	
	public:
		explicit Board();

		sf::FloatRect GetButtonGlobalBounds(const char button_type) const;

		inline sf::FloatRect GetBoardGlobalBounds() const
		{
			return board_rectangle.getGlobalBounds();
		}

		inline sf::Vector2f GetBoardSize() const
		{
			return board_rectangle.getSize();
		}

		inline void SetBoardSize(const sf::Vector2f &new_size)
		{
			board_rectangle.setSize(new_size);
			sf::FloatRect bounds = board_rectangle.getLocalBounds();
                        board_rectangle.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f));    
		}

		inline void ShowBoardText(const bool toggle)
		{
			show_board_text = toggle;
		}

		inline void ShowBoardOptionsText(const bool toggle)
		{
			show_board_options_text = toggle;
		}

		inline bool IsBoardTextShown() const
		{
			return show_board_text;
		}

		inline void SetBoardOptionsText(const std::string &text)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide_text = converter.from_bytes(text);
			board_options_text.setString(wide_text);
		}

		inline void SetBoardWidth(const float width)
		{
			board_width = width;
		}

		inline float GetBoardWidth() const
		{
			return board_width;
		}

		void SetBoardText(const std::string &text, const DWORD delay = 0);
		void HoverButton(const char button_type);
		void Update();

		std::function<void(int)> GetNextCommand(){
			return [this](int cmd_id)->void
			{
				this->NextStep(cmd_id);
			};
		}

		void NextStep(int cmd_id);
};

#endif
