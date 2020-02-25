#include <filesystem>
#include <iostream>
#include <set>
#include <string>

std::set<std::string> getAllExtensions(std::filesystem::path toSearch)
{
	std::set<std::string> extensions; //using std::set for efficient insertions and because I'll never insert more than
	                                  // 1 of the same extension
	
	for (std::filesystem::directory_entry dir : std::filesystem::recursive_directory_iterator(toSearch))
	{
		if (dir.is_regular_file())
		{
			extensions.insert(dir.path().extension().string());
		}
	}

	return extensions;
}

int main()
{

	for (std::filesystem::directory_entry dir : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
	{
		std::cout << dir.path().string() << std::endl;
	}

	return 0;
}