#include <filesystem>
#include <iostream>




int main()
{
	std::filesystem::path p;

	p = std::filesystem::current_path();
	std::cout << p.string() << std::endl;

	return 0;
}