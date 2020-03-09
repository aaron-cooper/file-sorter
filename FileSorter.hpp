#ifndef FILESORTER_H
#define FILESORTER_H

#include <filesystem>
#include <set>
#include <iostream>


class FileSorter {
public:
	enum RelocationMode {MOVE, COPY};

	FileSorter(std::filesystem::path toSearch, std::filesystem::path destDir, RelocationMode mode);
	bool isValid();
	void relocateFiles();
private:

	std::set<std::filesystem::path> getAllExtensions();
	void FileSorter::createSetDirectories();
	void FileSorter::copyFilesToExtensionDirectories();

	std::set<std::filesystem::path> extensions;
	std::filesystem::path toSearch;
	std::filesystem::path destDir;
	RelocationMode rmode = COPY;

};









#endif