
#include "../GameViewModel.h"

std::function<void()> GameViewModel::get_next_step_command()
{
	return [this]()->void
		{
			this->m_player->GetNextCommand();
		};
}
