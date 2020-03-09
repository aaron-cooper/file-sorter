#include <filesystem>
#include <iostream>
#include <set>



int main()
{

	std::set<std::filesystem::path> extensions;

	extensions = getAllExtensions(std::filesystem::current_path());
	createSetDirectories("testExtFolder", extensions);
	copyFilesToExtensionDirectories(std::filesystem::current_path(), "testExtFolder");
	return 0;
}