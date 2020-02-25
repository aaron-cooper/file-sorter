#include <filesystem>
#include <iostream>
#include <set>

std::set<std::filesystem::path> getAllExtensions(std::filesystem::path toSearch)
{
	std::set<std::filesystem::path> extensions; //using std::set for efficient insertions and because I'll never insert more than
	                                  // 1 of the same extension
	
	for (std::filesystem::directory_entry dir : std::filesystem::recursive_directory_iterator(toSearch))
	{
		if (dir.is_regular_file() && dir.path().has_extension())
		{
			extensions.insert(dir.path().extension());
		}
	}

	return extensions;
}

int main()
{

	std::set<std::string> extensions;

	extensions = getAllExtensions(std::filesystem::current_path());

	for (std::string s : extensions)
	{
		std::cout << s << std::endl;
	}

	return 0;
}