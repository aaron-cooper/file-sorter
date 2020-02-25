#include <filesystem>
#include <iostream>
#include <set>


/**
 * Return set of extensions on files in a directory.
 * 
 * This recurrsivly itterates over a directory compiling a set of all the
 * extensions that appear on the files within the directory. Each extension will
 * appear only once (hense the set). An extension on a file is simply any
 * characters that appear after and including the last "." in a file name.
 * 
 * @param[in] toSearch the path of the directory whose files' extensions will be
 *     returned
 * @return set containing the extensions of files
 */
std::set<std::filesystem::path> getAllExtensions(std::filesystem::path toSearch)
{
	//using std::set for efficient insertions and because I'll never insert more than
	// 1 of the same extension
	std::set<std::filesystem::path> extensions;	
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