#include <filesystem>
#include <iostream>
#include <set>



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

/**
 * Function for copying files to their extension directory.
 * 
 * Functions are copied to a directory sharing the name of the file's extension.
 * 
 * @param toSearch The path where the files that are to be moved are located
 * @param extensionParent The path where the extension folders are located.
 */
void copyFilesToExtensionDirectories(std::filesystem::path toSearch, std::filesystem::path extensionParent)
{
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
		if (file.path() == extensionParent)
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
				std::filesystem::copy(file, destDir);
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


int main()
{

	std::set<std::filesystem::path> extensions;

	extensions = getAllExtensions(std::filesystem::current_path());
	createSetDirectories("testExtFolder", extensions);
	copyFilesToExtensionDirectories(std::filesystem::current_path(), "testExtFolder");
	return 0;
}