#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <direct.h>

void FileManager::WriteFile(std::string fileName, std::vector<std::string> contents)
{
	for (std::string line : contents)
	{
		WriteFile(fileName, line + "\n");
	}
}

void FileManager::WriteFile(std::string fileName, std::string contents)
{
	std::ofstream file(fileName);
	if (file.is_open())
	{
		file << contents;
		file.close();
	}
	else std::cout << "Unable to open file";
}

std::vector<std::string> FileManager::ReadFile(std::string fileName)
{
	std::vector<std::string> lines;
	std::ifstream file(fileName);
	if (file.is_open())
	{

		std::string strInput{};
		while (std::getline(file, strInput))
		{
			if (!strInput.empty())
			{
				lines.push_back(strInput);
			}
		}
			
		file.close();
	}

	else std::cout << "Unable to open file";
	return lines;
}

int FileManager::mkDir(char* drName)
{
	return _mkdir(drName);
}
