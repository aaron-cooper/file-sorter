#include "FileSorter.hpp"


FileSorter::FileSorter(std::filesystem::path toSearch, std::filesystem::path destDir, FileSorter::RelocationMode mode) : toSearch(toSearch), destDir(destDir), rmode(mode)
{
	return;
}

bool FileSorter::isValid()
{
	return std::filesystem::exists(destDir) && std::filesystem::exists(toSearch);
}


/**
 * Return set of extensions on files in a directory.
 * 
 * This recurrsivly itterates over a directory compiling a set of all the
 * extensions that appear on the files within the directory. Each extension will
 * appear only once (hense the set). An extension on a file is simply any
 * characters that appear after but not including the last "." in a file name.
 * 
 * @return set containing the extensions of files
 */
std::set<std::filesystem::path> FileSorter::getAllExtensions()
{
	//using std::set for efficient insertions and because I'll never insert more than
	// 1 of the same extension
	std::set<std::filesystem::path> extensions;	

	//for each directory entry if it's a file with an extension attempt to add
	//the extension to the set.
	for (std::filesystem::directory_entry dir : std::filesystem::recursive_directory_iterator(toSearch))
	{
		if (dir.is_regular_file() && dir.path().has_extension())
		{
			std::string toInsert = dir.path().extension().string();
			extensions.insert(toInsert.substr(1)); //trim the '.' (first character)
		}
	}

	extensions.insert("no_extension");

	return extensions;
}