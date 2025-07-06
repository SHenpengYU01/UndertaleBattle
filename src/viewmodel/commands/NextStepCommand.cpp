
#include "../GameViewModel.h"

std::function<void(int)> GameViewModel::get_next_step_command()
{
	return [this](int)->void
		{
			this->m_player->GetNextCommand();
		};
}
