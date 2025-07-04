#ifndef _GASTER_H_
#define _GASTER_H_

#include "../main.h"
#include "file_manager.h"
#include "player.h"

#include "../common/frame.h"
#include "../common/property_id.h"


class Player;

enum Blaster_Direction
{
	Direction_Down,  // 炮台朝下方向
	Direction_Right, // 炮台朝右方向
	Direction_Left   // 炮台朝左方向
};

enum Blaster_Type
{
	Default_Blaster,  // 默认炮台类型
	Blue_Blaster,     // 蓝色特殊炮台
	Orange_Blaster    // 橙色特殊炮台
};

class Gaster: public PropertyTrigger
{
	private:
		sf::Font dialog_font;            // 对话框使用的字体
		sf::Text dialog;                 // SFML文本对象，用于显示对话框
		std::wstring dialog_text;        // 对话框显示的文本内容(宽字符)
		DWORD text_position;             // 文本显示位置坐标
		DWORD text_tick;                 // 文本显示计时器
		DWORD text_duration_tick;        // 文本显示总时长
		sf::Texture gaster_texture;      // Gaster默认纹理
		sf::Texture gaster_surprised_texture; // Gaster惊讶表情纹理
		sf::Sprite gaster_sprite;        // Gaster角色精灵
		std::array<sf::Texture, 3> blaster_texture;       // 炮台纹理数组(3种)
		std::array<sf::Texture, 2> blaster_firing_texture; // 炮台开火纹理数组(2种)
		std::array<sf::Texture, 3> blaster_laser_texture;  // 激光纹理数组(3种)
		sf::SoundBuffer blaster_intro;    // 炮台出现音效
		sf::SoundBuffer blaster_fire;     // 炮台开火音效
		sf::Texture speech_bubble_texture; // 对话框气泡纹理
		sf::Sprite speech_bubble_sprite;  // 对话框气泡精灵

		struct Blaster
		{
			DWORD spawn_interval;         // 生成间隔时间
			sf::Sprite blaster_sprite;   // 炮台精灵
			sf::Sprite laser_sprite;     // 激光精灵
			char direction;              // 炮台方向
			char blaster_type;           // 炮台类型
			bool state_firing;           // 是否正在开火
			bool switch_blaster_sprite;  // 是否切换炮台精灵
			bool blaster_intro;          // 是否播放出现音效
			DWORD switch_blaster_sprite_tick; // 精灵切换计时器
			DWORD fire_tick;             // 开火计时器
			DWORD fire_duration;         // 开火持续时间
			DWORD removal_tick;          // 移除计时器
			sf::Sound blaster_fire_sound; // 开火音效对象
		};

		std::deque<Blaster> blasters;

		Player *player_instance;

	public:
		explicit Gaster(Player *player_instance); // 构造函数，初始化Gaster实例

		// 设置对话框文本
		void SetText(const std::string &text, const DWORD text_duration);
		
		// 切换Gaster惊讶表情
		void ToggleGasterSurprised(const bool toggle);
		
		// 更新Gaster状态，每帧调用
		void Update();
		
		// 添加新炮台
		void AddBlaster(const sf::Vector2f &position, const char blaster_direction, 
			const DWORD spawn_interval = 0, 
			const char blaster_type = Blaster_Type::Default_Blaster, 
			const DWORD fire_duration = 1000, 
			const DWORD interval_before_firing = 750);
			
		// 重置Gaster所有状态
		void Reset();


};

#endif
