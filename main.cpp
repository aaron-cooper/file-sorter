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

	//for each directory entry if it's a file with an extension attempt to add
	//the extension to the set.
	for (std::filesystem::directory_entry dir : std::filesystem::recursive_directory_iterator(toSearch))
	{
		if (dir.is_regular_file() && dir.path().has_extension())
		{
			std::string toInsert = dir.path().extension().string();
			extensions.insert(toInsert.substr(1, toInsert.length() - 1)); //trim the '.' at the beginning
		}
	}

	return extensions;
}


/**
 * Function for creating directories.
 * 
 * A set paths is passed to the function, for each of those paths a directory is
 * created.
 * 
 * @param parent the parent directory where the paths should be created
 * @param paths the set of paths for which directories should be created
 */
void createSetDirectories(std::filesystem::path parent, std::set<std::filesystem::path> paths)
{
	std::filesystem::path toCreate;
	for (std::filesystem::path p : paths)
	{
		toCreate = parent;
		toCreate /= p;
		std::filesystem::create_directories(toCreate);
	}


	return;
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