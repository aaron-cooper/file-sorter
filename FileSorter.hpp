#ifndef FILESORTER_H
#define FILESORTER_H

#include <filesystem>


class FileSorter {
public:
	enum RelocationMode {MOVE, COPY};

	FileSorter(std::filesystem::path toSearch, std::filesystem::path destDir, RelocationMode mode);

private:
	std::filesystem::path toSearch;
	std::filesystem::path destDir;
	RelocationMode rmode = COPY;

};









#endif