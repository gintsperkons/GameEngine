#pragma once

//Libraries
//Inbuilt
#include <fstream>
#include <vector>
#include <string>
//SourceCode
class FileHandling
{
	public:
		static std::vector<char> ReadBinaryFile(const std::string FileName);
};