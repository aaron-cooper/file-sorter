#include <filesystem>
#include <iostream>
#include <set>
#include "FileSorter.hpp"

int main()
{
	//right now the program relocate files from the current directory
	//to outputFolder by copying. I'm going to let the user choose
	//these values later via command line args, but that's not gonna
	//happen until I have more time.
	FileSorter sorter("./", "./outputFolder/", FileSorter::COPY);

	if (sorter.isValid())
	{
		sorter.relocateFiles();
	}
	else
	{
		std::cout << "was not valid" << std::endl;
	}

	
	return 0;
}