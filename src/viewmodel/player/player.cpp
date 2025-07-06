#include "player.h"

Player::Player(Board *board_instance) : health(100), damage_tick(0), use_button_tick(0), enemy_health(250)
{
	FileManager::LoadFromFile(this->player_texture, "bin/sprites/fei.png");
	FileManager::LoadFromFile(this->player_dead_texture, "bin/sprites/heart-broken.png");
	FileManager::LoadFromFile(this->health_texture, "bin/sprites/health_bar.png");
	FileManager::LoadFromFile(this->health_texture_cover, "bin/sprites/health_bar_cover.png");

	FileManager::LoadFromFile(this->enemy_health_texture, "bin/sprites/health_bar_cover.png");
	FileManager::LoadFromFile(this->enemy_health_texture_cover, "bin/sprites/health_bar.png");

	FileManager::LoadFromFile(this->miss_attack_texture, "bin/sprites/miss.png");
	FileManager::LoadFromFile(this->attack_texture[0], "bin/sprites/slice_1.png");
	FileManager::LoadFromFile(this->attack_texture[1], "bin/sprites/slice_2.png");
	FileManager::LoadFromFile(this->attack_texture[2], "bin/sprites/slice_3.png");
	FileManager::LoadFromFile(this->player_name_font, "bin/fonts/fusion-pixel-10px-monospaced-zh_hans.ttf");
	FileManager::LoadFromFile(this->damage_buffer, "bin/audio/hurtsound.wav");
	FileManager::LoadFromFile(this->player_heal_buffer, "bin/audio/healsound.wav");
	FileManager::LoadFromFile(this->player_attack_buffer, "bin/audio/player_attack.wav");

	if (!FileManager::IsAnyFileMissing())
	{
		this->board_instance = board_instance;
		this->button_hovered = Button_Type::Fight_Button;
		this->button_pressed = Button_Type::None;
		this->item_chosen = Item_Type::Hajimi;
		this->mercy_chosen = Mercy_Type::Mercy;

		this->flash_damage_color = false;
		this->player_turn = false;
		this->is_moving = false;
		this->heal_items_available = 1;
		this->player_name_text.setFont(this->player_name_font);
		this->player_name_text.setCharacterSize(23);
		this->player_name_text.setFillColor(sf::Color::White);
		this->player_name_text.setPosition(32.f, 394.f);
		this->player_name_text.setString(L"博丽灵梦   LV 6");
		this->player_health_text.setFont(this->player_name_font);
		this->player_health_text.setCharacterSize(23);
		this->player_health_text.setFillColor(sf::Color::White);
		this->player_health_text.setPosition(377.f, 394.f);
		this->player_health_text.setString("100 / 100");
		this->player_sprite.setTexture(this->player_texture);

		this->player_sprite.setScale(sf::Vector2f(0.13f, 0.13f));

		this->health_sprite.setTexture(this->health_texture);
		this->health_sprite_cover.setTexture(this->health_texture_cover);
		this->health_sprite_cover.setPosition(sf::Vector2f(257.f, 399.f));
		this->health_sprite.setPosition(sf::Vector2f(257.f, 399.f));

		this->enemy_health_sprite.setTexture(this->enemy_health_texture);
		this->enemy_health_sprite_cover.setTexture(this->enemy_health_texture_cover);
		this->enemy_health_sprite_cover.setPosition(sf::Vector2f(60.f, 150.f));
		this->enemy_health_sprite.setPosition(sf::Vector2f(60.f, 150.f));
		this->enemy_health_text.setFont(this->player_name_font);
		this->enemy_health_text.setCharacterSize(23);
		this->enemy_health_text.setFillColor(sf::Color::Red);
		this->enemy_health_text.setPosition(180.f, 150.f);
		this->enemy_health_text.setString("250 / 250");

		// this->player_sprite.setColor(sf::Color(255, 0, 0));
		this->player_sprite.setPosition(sf::Vector2f(316.f, 295.f));
		this->damage_sound.setBuffer(this->damage_buffer);
		this->player_heal.setBuffer(this->player_heal_buffer);
		this->player_attack.setBuffer(this->player_attack_buffer);
		this->miss_attack_sprite.setTexture(this->miss_attack_texture);
		this->miss_attack_sprite.setPosition(sf::Vector2f(278.f, 80.f));
	}
}

void Player::HoverButton(const char button_id)
{
	switch (button_hovered)
	{
		case Button_Type::Fight_Button:
		{
			this->board_instance->HoverButton(Button_Type::Fight_Button);
			this->player_sprite.setPosition(sf::Vector2f(42.f, 445.f));
			break;
		}
		case Button_Type::Act_Button:
		{
			this->board_instance->HoverButton(Button_Type::Act_Button);
			this->player_sprite.setPosition(sf::Vector2f(196.f, 445.f));
			break;
		}
		case Button_Type::Item_Button:
		{
			this->board_instance->HoverButton(Button_Type::Item_Button);
			this->player_sprite.setPosition(sf::Vector2f(356.f, 445.f));
			break;
		}
		case Button_Type::Mercy_Button:
		{
			this->board_instance->HoverButton(Button_Type::Mercy_Button);
			this->player_sprite.setPosition(sf::Vector2f(510.f, 445.f));
			break;
		}
	}
}

void Player::TogglePlayerTurn(const bool toggle, const std::string &board_text, const DWORD board_text_delay)
{
	this->player_turn = toggle;

	const sf::Vector2f board_size = this->board_instance->GetBoardSize();

	if (toggle)
	{
		this->board_instance->SetBoardSize(sf::Vector2f(585.f, 165.f));
		this->button_pressed = Button_Type::None;
		this->HoverButton(this->button_hovered);
		this->board_instance->ShowBoardText(true);
		this->board_instance->SetBoardText(board_text, board_text_delay);
	}
	else
	{
		this->board_instance->SetBoardSize(sf::Vector2f(430.f, 165.f));
		this->player_sprite.setPosition(sf::Vector2f(316.f, 295.f));
		this->board_instance->HoverButton(Button_Type::None);
		this->board_instance->ShowBoardText(false);
	}
}

void Player::TakeDamage(const int amount)
{
	if (this->damage_tick < GetTickCount() && this->health > 0 && !this->player_turn)
	{
		this->damage_tick = GetTickCount() + 2000;

		if (this->health - amount < 0){
			this->damage_sound.setBuffer(this->death_buffer);
			this->player_sprite.setTexture(this->player_dead_texture, true);
			this->health = 0;
		}else{
			this->health -= amount;
		}

		this->damage_sound.play();

		this->health_sprite_cover.setScale(static_cast<float>(this->health) / 100.f, 1.f);
		this->player_health_text.setString(std::to_string(this->health) + " / 100");
	}
}

void Player::DamagedUpdate(){
	static DWORD flash_tick = 0;
	DWORD current_tick = GetTickCount();
	if (this->damage_tick > current_tick && current_tick > flash_tick)
	{
		flash_tick = current_tick + 200;

		if (this->flash_damage_color == false)
		{
			this->flash_damage_color = true;
			this->player_sprite.setColor(sf::Color(150, 0, 0));
		}else
		{
			this->flash_damage_color = false;
			this->player_sprite.setColor(sf::Color(255, 255, 255));
		}
	}
}

void Player::HitUpdate(){
	DWORD current_tick = GetTickCount();
	static DWORD flash_tick = current_tick + 200;
	if (current_tick > flash_tick)
	{
		flash_tick = current_tick + 200;
		this->TogglePlayerTurn(false);
		this->board_instance->ShowFightEye(false);
	}
}

void Player::HoverButtonUpdate(int direction){
	static DWORD button_hover_move_tick = 0;
	DWORD current_tick = GetTickCount();

	if (current_tick > button_hover_move_tick)
	{
		if (direction == CMD_ID::LEFT)
		{
			if (this->button_hovered == Button_Type::Fight_Button){
				this->button_hovered = Button_Type::Mercy_Button;
			}else{
				this->button_hovered--;
			}
			this->HoverButton(this->button_hovered);
			button_hover_move_tick = current_tick + 250;
		}

		else if (direction == CMD_ID::RIGHT)
		{
			if (this->button_hovered == Button_Type::Mercy_Button){
				this->button_hovered = Button_Type::Fight_Button;
			}else{
				this->button_hovered++;
			}
			this->HoverButton(this->button_hovered);
			button_hover_move_tick = current_tick + 250;
		}
	}

}


void Player::PressFight(){
	const DWORD current_tick = GetTickCount();
	this->button_pressed = Button_Type::Fight_Button;
	this->player_attack.play();
	this->board_instance->ShowFightEye(true);
	this->board_instance->ShowBoardText(false);
	this->board_instance->ShowBoardOptionsText(false);
	this->board_instance->stop_attack=false;
	this->use_button_tick = current_tick + 200;
}

void Player::PressAct(){
	const DWORD current_tick = GetTickCount();
	this->button_pressed = Button_Type::Act_Button;
	this->player_sprite.setPosition(sf::Vector2f(45.f, 233.f));
	this->board_instance->SetBoardOptionsText("* 检查");
	this->board_instance->ShowBoardOptionsText(true);
	this->board_instance->ShowBoardText(false);
	this->use_button_tick = current_tick + 200;
}

void Player::PressItem(){
	const DWORD current_tick = GetTickCount();
	this->button_pressed = Button_Type::Item_Button;
	this->player_sprite.setPosition(sf::Vector2f(45.f, 233.f));
	this->board_instance->SetBoardOptionsText("* 蜂蜜特饮\n  沃特尔");
	this->board_instance->ShowBoardOptionsText(true);
	this->board_instance->ShowBoardText(false);
	this->use_button_tick = current_tick + 200;
}

void Player::PressMercy(){
	const DWORD current_tick = GetTickCount();
	this->button_pressed = Button_Type::Mercy_Button;
	this->player_sprite.setPosition(sf::Vector2f(45.f, 233.f));
	this->mercy_chosen = Mercy_Type::Mercy;
	this->board_instance->SetBoardOptionsText("* 原谅\n  溜走");
	this->board_instance->ShowBoardOptionsText(true);
	this->board_instance->ShowBoardText(false);
	this->use_button_tick = current_tick + 200;
}

void Player::PressButton(){
	const sf::FloatRect player_bounds = this->player_sprite.getGlobalBounds();
	if (player_bounds.intersects(this->board_instance->GetButtonGlobalBounds(Button_Type::Fight_Button)))
	{
		this->PressFight();
	}
	else if (player_bounds.intersects(this->board_instance->GetButtonGlobalBounds(Button_Type::Act_Button)))
	{
		this->PressAct();
	}
	else if (player_bounds.intersects(this->board_instance->GetButtonGlobalBounds(Button_Type::Item_Button)))
	{
		this->PressItem();
	}
	else if (player_bounds.intersects(this->board_instance->GetButtonGlobalBounds(Button_Type::Mercy_Button)))
	{
		this->PressMercy();
	}
}

void Player::CancelButtonPressed(){
	if (!this->board_instance->IsBoardTextShown())
	{
		this->board_instance->ShowBoardOptionsText(false);
		this->board_instance->ShowBoardText(true);
		this->button_pressed = Button_Type::None;
		this->HoverButton(this->button_hovered);
	}
}

void Player::DoAct(){
	const DWORD current_tick = GetTickCount();
	if (this->use_button_tick < current_tick){
		if (!this->board_instance->IsBoardTextShown())
		{
			this->board_instance->ShowBoardOptionsText(false);
			this->board_instance->ShowBoardText(true);
			this->board_instance->SetBoardText("封兽鵺 - 攻击 ??? 防御 ???\n* 一看到别人在兴致勃勃做事，\n她就不由得想在暗地里阻挠别人，\n这就是她的性格.");
			this->HoverButton(this->button_hovered);
			this->use_button_tick = current_tick + 800;
		}
		else{
			this->TogglePlayerTurn(false);
			this->use_button_tick = current_tick + 1500;
		}
	}
}


void Player::DoItem(){
	const DWORD current_tick = GetTickCount();
	if (this->use_button_tick < current_tick)
	{
		if (!this->board_instance->IsBoardTextShown())
		{
			switch(this->item_chosen){
				case(Item_Type::Hajimi):
				if(this->heal_items_available){
					this->board_instance->SetBoardText("你喝了蜂蜜特饮\n  满血回归！");
					this->health = 100;
					this->player_heal.play();
					this->player_health_text.setString("100 / 100");
					this->heal_items_available = 0;
					this->health_sprite_cover.setScale(1.f, 1.f);
				}else{
					this->board_instance->SetBoardText("没有了。。。");
				}
				break;

				case(Item_Type::Water):
				if(this->heal_items_available){
					this->board_instance->SetBoardText("你喝了口水\n");
					this->health += 20;
					if( this->health > 100 ) this->health=100;
					this->player_heal.play();
					this->player_health_text.setString(std::to_string(this->health)+" / 100");
					this->heal_items_available = 0;
					this->health_sprite_cover.setScale(this->health/100.0, 1.f);
				}else{
					this->board_instance->SetBoardText("水喝完了。。。\n");
				}
				break;
			}
			this->board_instance->ShowBoardOptionsText(false);
			this->board_instance->ShowBoardText(true);
			this->HoverButton(this->button_hovered);
			this->use_button_tick = current_tick + 800;
		}else{
			this->TogglePlayerTurn(false);
			this->use_button_tick = current_tick + 1500;
		}	
	}
}


void Player::DoMercy(){
	const DWORD current_tick = GetTickCount();
	if (this->use_button_tick < current_tick)
	{
		if(!this->board_instance->IsBoardTextShown())
		{
			this->board_instance->ShowBoardOptionsText(false);
			this->board_instance->ShowBoardText(true);
			switch(this->mercy_chosen){
				case(Mercy_Type::Mercy):
				this->board_instance->SetBoardText("“原谅我？我错了吗”\n\nT^T");
				break;
				case(Mercy_Type::Flee):
				this->board_instance->SetBoardText("“休想溜走！\n\n╰_ ╯”");
				break;
			}
				this->HoverButton(this->button_hovered);
				this->use_button_tick = current_tick + 800;
		}else{
			this->TogglePlayerTurn(false);
			this->use_button_tick = current_tick + 1500;
		}
	}
}
	

void Player::DoFight(){
	const DWORD current_tick = GetTickCount();
	if(this->use_button_tick < current_tick){

		//calculate damage to enemy based on attack bar position and board middle
		float attack_bar_xpos = board_instance->GetAttackBarX();
		sf::FloatRect board_bounds = board_instance->GetBoardGlobalBounds();
		float board_mid = board_bounds.left + board_bounds.width/2;
		float board_10_len = 0.1*board_bounds.width;
		float board_25_len = 0.25*board_bounds.width;
		float board_40_len = 0.4*board_bounds.width;
		if(attack_bar_xpos >= board_mid - board_10_len && attack_bar_xpos <= board_mid + board_10_len){
			enemy_health -= 100;
		}else if(attack_bar_xpos >= board_mid - board_25_len && attack_bar_xpos <= board_mid + board_25_len){
			enemy_health -= 50;
		}else if(attack_bar_xpos >= board_mid - board_40_len && attack_bar_xpos <= board_mid + board_40_len){
			enemy_health -= 25;
		}else{
			this->FightMiss();
		}

		this->enemy_health_sprite_cover.setScale(static_cast<float>(this->health) / 250.f, 1.f);
		this->enemy_health_text.setString(std::to_string(this->enemy_health) + " / 250");

		this->board_instance->stop_attack = true;
		this->use_button_tick = current_tick + 2000;
		this->HitUpdate();
	}
}

void Player::FightMiss(){
	const DWORD current_tick = GetTickCount();
	if (this->use_button_tick > current_tick)
	{
		if (this->use_button_tick - 1900 > current_tick)
		{
			this->miss_attack_sprite.setTexture(this->attack_texture[0], true);
		}
		else if (this->use_button_tick - 1800 > current_tick)
		{
			this->miss_attack_sprite.setTexture(this->attack_texture[1], true);
		}
		else if (this->use_button_tick - 1700 > current_tick)
		{
			this->miss_attack_sprite.setTexture(this->attack_texture[2], true);
		}
		else
		{
			this->miss_attack_sprite.setTexture(this->miss_attack_texture, true);
		}
		this->fire(PROP_ID::SPRITE, this->miss_attack_sprite);
	}
}

void Player::UpdateMercyOptions(){
		this->board_instance->ShowBoardOptionsText(true);
		this->board_instance->ShowBoardText(false);
		switch(this->mercy_chosen){
			case(Mercy_Type::Mercy):
			this->board_instance->SetBoardOptionsText("* 原谅\n  溜走");
			break;
			case(Mercy_Type::Flee):
			this->board_instance->SetBoardOptionsText("  原谅\n* 溜走");
			break;
		}
}
	
void Player::ChooseNextMercy(){
	static DWORD mercy_option_tick = 0;
	const DWORD current_tick = GetTickCount();
	if(current_tick > mercy_option_tick){
		this->mercy_chosen ++;
		this->mercy_chosen %= Mercy_Type::Mercy_Type_Num;
		this->UpdateMercyOptions();
		mercy_option_tick = current_tick + 250;
	}
}

void Player::ChoosePrevMercy(){
	static DWORD mercy_option_tick = 0;
	const DWORD current_tick = GetTickCount();
	if(current_tick > mercy_option_tick){
		this->mercy_chosen = (this->mercy_chosen + Mercy_Type::Mercy_Type_Num - 1) % Mercy_Type::Mercy_Type_Num;
		this->UpdateMercyOptions();
		mercy_option_tick = current_tick + 250;
	}
}

void Player::UpdateItemOptions(){
	static DWORD item_option_tick = 0;
	const DWORD current_tick = GetTickCount();
	if(current_tick > item_option_tick){
		this->board_instance->ShowBoardOptionsText(true);
		this->board_instance->ShowBoardText(false);
		switch(this->item_chosen){
			case(Item_Type::Hajimi):
			this->board_instance->SetBoardOptionsText("* 蜂蜜特饮\n  沃特尔");
			break;
			case(Item_Type::Water):
			this->board_instance->SetBoardOptionsText("  蜂蜜特饮\n* 沃特尔");
			break;
		}
		item_option_tick = current_tick + 250;
	}
}

void Player::ChooseNextItem(){
	static DWORD item_option_tick = 0;
	const DWORD current_tick = GetTickCount();
	if(current_tick > item_option_tick){
		this->item_chosen ++;
		this->item_chosen %= Item_Type::Item_Type_Num;
		this->UpdateItemOptions();
		item_option_tick = current_tick + 250;
	}
}

void Player::ChoosePrevItem(){
	static DWORD item_option_tick = 0;
	const DWORD current_tick = GetTickCount();
	if(current_tick > item_option_tick){
		this->item_chosen = (this->item_chosen + Item_Type::Item_Type_Num - 1) % Item_Type::Item_Type_Num;
		this->UpdateItemOptions();
		item_option_tick = current_tick + 250;
	}
}
	
void Player::Update()
{
	this->is_moving = false;
	
	if (this->health > 0){
		this->DamagedUpdate();
	}
	this->fire(PROP_ID::SPRITE, this->health_sprite);
	this->fire(PROP_ID::SPRITE, this->health_sprite_cover);

	this->fire(PROP_ID::SPRITE, this->enemy_health_sprite);
	this->fire(PROP_ID::SPRITE, this->enemy_health_sprite_cover);
	this->fire(PROP_ID::TEXT, this->enemy_health_text);

	this->fire(PROP_ID::TEXT, this->player_health_text);
	this->fire(PROP_ID::TEXT, this->player_name_text);
}


void Player::Move(int cmd_id){
	const sf::Vector2f pos = this->player_sprite.getPosition();
	const sf::FloatRect dimensions = this->board_instance->GetBoardGlobalBounds();
	this->is_moving = false;  //重置移动状态
	
	switch (cmd_id) {
		case CMD_ID::LEFT:
			if ((pos.x - 3.f) > dimensions.left + 5.5f) {
				this->player_sprite.move(-3.f, 0.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::RIGHT:
			if ((pos.x + 3.f) < (dimensions.left + dimensions.width) - 20.5f) {
				this->player_sprite.move(3.f, 0.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::UP:
			if ((pos.y - 3.f) > dimensions.top + 5.5f) {
				this->player_sprite.move(0.f, -3.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::DOWN:
			if ((pos.y + 3.f) < (dimensions.top + dimensions.height) - 20.5f) {
				this->player_sprite.move(0.f, 3.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::LEFTUP:
			if ((pos.x - 3.f) > dimensions.left + 5.5f) {
				this->player_sprite.move(-3.f, 0.f);
				this->is_moving = true;
			}
			if ((pos.y - 3.f) > dimensions.top + 5.5f) {
				this->player_sprite.move(0.f, -3.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::LEFTDOWN:
			if ((pos.x - 3.f) > dimensions.left + 5.5f) {
				this->player_sprite.move(-3.f, 0.f);
				this->is_moving = true;
			}
			if ((pos.y + 3.f) < (dimensions.top + dimensions.height) - 20.5f) {
				this->player_sprite.move(0.f, 3.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::RIGHTUP:
			if ((pos.x + 3.f) < (dimensions.left + dimensions.width) - 20.5f) {
				this->player_sprite.move(3.f, 0.f);
				this->is_moving = true;
			}
			if ((pos.y - 3.f) > dimensions.top + 5.5f) {
				this->player_sprite.move(0.f, -3.f);
				this->is_moving = true;
			}
			break;
			
		case CMD_ID::RIGHTDOWN:
			if ((pos.x + 3.f) < (dimensions.left + dimensions.width) - 20.5f) {
				this->player_sprite.move(3.f, 0.f);
				this->is_moving = true;
			}
			if ((pos.y + 3.f) < (dimensions.top + dimensions.height) - 20.5f) {
				this->player_sprite.move(0.f, 3.f);
				this->is_moving = true;
			}
			break;
	}
}

void Player::NextStep(int cmd_id) {
	if (!this->player_turn) {
		Move(cmd_id);
		this->fire(PROP_ID::SPRITE, this->player_sprite);
	}else{
		if(this->button_pressed == Button_Type::None){
			switch(cmd_id){
				case(CMD_ID::LEFT):
					this->HoverButtonUpdate(CMD_ID::LEFT);
					break;
			
				case(CMD_ID::RIGHT):
					this->HoverButtonUpdate(CMD_ID::RIGHT);
					break;
				
				case(CMD_ID::Z):
					this->PressButton();
					break;
			}
		}else if(this->button_pressed == Button_Type::Fight_Button){
			switch(cmd_id){
				case(CMD_ID::Z):
				this->DoFight();
				break;
			}
		}else if(this->button_pressed == Button_Type::Act_Button){
			switch(cmd_id){
				case(CMD_ID::Z):
					this->DoAct();
					break;
				case(CMD_ID::X):
					this->CancelButtonPressed();
				break;
			}
		}else if(this->button_pressed == Button_Type::Item_Button){
			switch(cmd_id){
				case(CMD_ID::Z):
					this->DoItem();
					break;
				case(CMD_ID::X):
					this->CancelButtonPressed();
					break;
				case(CMD_ID::UP):
					this->ChoosePrevItem();
					break;
				case(CMD_ID::DOWN):
					this->ChooseNextItem();
					break;
			}
		}else if(this->button_pressed == Button_Type::Mercy_Button){
			switch(cmd_id){
				case(CMD_ID::Z):
					this->DoMercy();
					break;
				case(CMD_ID::X):
					this->CancelButtonPressed();
					break;
				case(CMD_ID::UP):
					this->ChoosePrevMercy();
					break;
				case(CMD_ID::DOWN):
					this->ChooseNextMercy();
					break;
			}
		}
		this->fire(PROP_ID::SPRITE, this->health_sprite);
		this->fire(PROP_ID::SPRITE, this->health_sprite_cover);
	}
}

void Player::Reset()
{
	this->health = 100;
	this->heal_items_available = 1;
	this->player_health_text.setString("100 / 100");
	this->is_moving = false;
	this->damage_tick = 0;
	this->button_pressed = Button_Type::None;
	this->button_hovered = Button_Type::Fight_Button;
	this->player_turn = false;
	this->flash_damage_color = false;
	this->player_sprite.setTexture(this->player_texture, true);
	this->health_sprite_cover.setScale(1.f, 1.f);
	this->player_sprite.setPosition(sf::Vector2f(316.f, 295.f));
	this->damage_sound.setBuffer(this->damage_buffer);
}
