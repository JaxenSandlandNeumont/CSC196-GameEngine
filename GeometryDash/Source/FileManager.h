#pragma once
#include <string>
#include <vector>

class FileManager
{
public:
	FileManager() = default;

	void WriteFile(std::string fileName, std::string contents);
	void WriteFile(std::string fileName, std::vector<std::string> contents);
	std::vector<std::string> ReadFile(std::string fileName);

	int mkDir(char* drName);

private:

};