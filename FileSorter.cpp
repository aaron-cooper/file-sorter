#include "FileSorter.hpp"


FileSorter::FileSorter(std::filesystem::path toSearch, std::filesystem::path destDir, FileSorter::RelocationMode mode) : toSearch(toSearch), destDir(destDir), rmode(mode)
{
	return;
}

bool FileSorter::isValid()
{
	return std::filesystem::exists(destDir) && std::filesystem::exists(toSearch);
}


void FileSorter::relocateFiles()
{
	extensions = getAllExtensions();
	createSetDirectories();
	copyFilesToExtensionDirectories();
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



/**
 * Create a directory for each element of a set of extensions.
 */
void FileSorter::createSetDirectories()
{
	std::filesystem::path toCreate;
	for (std::filesystem::path p : extensions)
	{
		toCreate = destDir;
		toCreate /= p;
		std::filesystem::create_directories(toCreate);
	}


	return;
}



/**
 * Function for copying files to their extension directory.
 * 
 * Functions are copied to a directory sharing the name of the file's extension.
 */
void FileSorter::copyFilesToExtensionDirectories()
{
	std::filesystem::path extensionParent = destDir;

	//for each file in toSearch
	if (extensionParent.is_relative())
	{
		std::filesystem::path absParent = std::filesystem::current_path();
		absParent /= extensionParent;
		extensionParent = absParent;		
	}

	//init for loop
	std::filesystem::recursive_directory_iterator iter(toSearch);
	std::filesystem::recursive_directory_iterator end = std::filesystem::end(iter);
	for (; iter != end ;iter++)
	{
		std::filesystem::directory_entry file = *iter;

		//if this is the directory where we're putting the files, skip it
		if (std::filesystem::equivalent(file.path(), extensionParent))
		{
			iter.disable_recursion_pending();
			continue;
		}

		if (file.is_regular_file())
		{
			std::filesystem::path destDir;

			if (file.path().has_extension())
			{
				destDir = extensionParent;
				destDir /= std::filesystem::path(file.path().extension().string().substr(1));
			}
			else
			{
				destDir = extensionParent;
				destDir /= "no_extension";
			}
			destDir /= file.path().filename();
			try {
				if (rmode == COPY)
				{
					std::filesystem::copy(file, destDir);
				}
				else if (rmode == MOVE)
				{
					std::filesystem::rename(file, destDir);
				}

			} catch (const std::filesystem::filesystem_error & e) {
				if (17 == e.code().value())
				std::cerr << "Could not copy file because a file of the same name is in the destination."
					<< std::endl
					<< "\tAttempted to copy: " << e.path1().stem() << std::endl
					<< "\tfrom " << e.path1().parent_path() << std::endl
					<< "\tCollided with file from: " << e.path2() << std::endl;
			}
		}
	}
}

