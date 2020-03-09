#ifndef FILESORTER_H
#define FILESORTER_H

#include <filesystem>
#include <set>


class FileSorter {
public:
	enum RelocationMode {MOVE, COPY};

	FileSorter(std::filesystem::path toSearch, std::filesystem::path destDir, RelocationMode mode);
	bool isValid();
private:

	std::set<std::filesystem::path> getAllExtensions();
	void FileSorter::createSetDirectories();

	std::set<std::filesystem::path> extensions;
	std::filesystem::path toSearch;
	std::filesystem::path destDir;
	RelocationMode rmode = COPY;

};









#endif