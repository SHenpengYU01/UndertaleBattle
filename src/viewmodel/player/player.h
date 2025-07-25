#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../board/board.h"
#include "../../common/frame.h"
#include "../../common/property_id.h"


class Board;

class Player : public PropertyTrigger
{
	private:
		sf::Font player_name_font;
		sf::Text player_name_text;
		sf::Text player_health_text;
		sf::Texture player_texture;
		sf::Texture player_dead_texture;
		sf::Sprite player_sprite;
		sf::Texture health_texture;
		sf::Texture health_texture_cover;
		sf::Sprite health_sprite;
		sf::Sprite health_sprite_cover;
		sf::Texture miss_attack_texture;
		sf::Sprite miss_attack_sprite;
		std::array<sf::Texture, 3> attack_texture;
		sf::SoundBuffer damage_buffer;
		sf::SoundBuffer death_buffer;
		sf::SoundBuffer player_attack_buffer;
		sf::SoundBuffer player_heal_buffer;
		sf::Sound player_heal;
		sf::Sound player_attack;
		sf::Sound damage_sound;

		sf::Texture enemy_health_texture;
		sf::Texture enemy_health_texture_cover;
		sf::Sprite enemy_health_sprite;
		sf::Sprite enemy_health_sprite_cover;
		sf::Text enemy_health_text;


		int health;
		int enemy_health;
		DWORD damage_tick;
		DWORD use_button_tick;
		bool flash_damage_color;
		bool player_turn;
		bool is_moving;
		char button_pressed;
		char button_hovered;
		// char heal_items_available;
		int heal_items_available_honey;
		int heal_items_available_water;
		
		char item_chosen;
		char mercy_chosen;

		Board *board_instance;

		void HoverButton(const char button_id);

	public:
		explicit Player(Board *board_instance);
		
		inline sf::Vector2f GetPlayerPosition() const
		{
			return player_sprite.getPosition();
		}

		inline sf::FloatRect GetGlobalBounds() const
		{
			return player_sprite.getGlobalBounds();
		}

		inline int GetPlayerHealth() const
		{
			return health;
		}

		inline bool IsPlayerInTurn() const
		{
			return player_turn;
		}

		inline void SetPlayerPosition(const float x, const float y)
		{
			player_sprite.setPosition(sf::Vector2f(x, y));
		}

		inline DWORD GetButtonUseTick() const
		{
			return use_button_tick;
		}

		inline bool IsPlayerMoving() const
		{
			return is_moving;
		}

		inline int GetEnemyHealth(){
			return enemy_health;
		}

		void TogglePlayerTurn(const bool toggle, const std::string &board_text = "None", const DWORD board_text_delay = 0);
		void TakeDamage(const int amount);
		void DamagedUpdate();
		void HitUpdate();
		void HoverButtonUpdate(int direction);
		
		void Update();
		void Reset();
		
		std::function<void(int)> GetNextCommand(){
			return [this](int cmd_id)->void
			{
				this->NextStep(cmd_id);
			};
		}
		
		void NextStep(int cmd_id);

		void Move(int cmd_id);

		void FightMiss();
	private:
		void PressButton();
		void PressFight();
		void PressAct();
		void PressItem();
		void PressMercy();
		void CancelButtonPressed();

		void DoFight();
		void DoAct();
		void DoItem();
		void DoMercy();
		
		void ChooseNextItem();
		void ChoosePrevItem();
		void UpdateItemOptions();

		void ChooseNextMercy();
		void ChoosePrevMercy();
		void UpdateMercyOptions();
};

#endif