#include "FileSorter.hpp"


FileSorter::FileSorter(std::filesystem::path toSearch, std::filesystem::path destDir, FileSorter::RelocationMode mode) : toSearch(toSearch), destDir(destDir), rmode(mode)
{
	return;
}

