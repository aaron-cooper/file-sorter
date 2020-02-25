#include <filesystem>
#include <iostream>




int main()
{

	for (std::filesystem::directory_entry dir : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
	{
		std::cout << dir.path().string() << std::endl;
	}

	return 0;
}