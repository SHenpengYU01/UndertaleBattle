#include "main.h"
#include "file_manager.h"
#include "game.h"

int main()
{
	Game game;

	if (FileManager::IsAnyFileMissing())
	{
		std::string missing_files("The game couldn't properly launch due to missing files:\n\n");

		if (FileManager::GetMissingFilesList(missing_files))
		{
			// MessageBox(0, missing_files.c_str(), "Something went wrong.", MB_OK);
			std::cerr << "错误: 缺少文件 - " << missing_files << std::endl;
		}
		exit(0);
	}
	else
	{
		game.Update();
	}
	return 0;
}