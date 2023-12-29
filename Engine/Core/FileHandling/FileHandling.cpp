#pragma once

//Libraries
//Inbuilt
//SourceCode
#include "FileHandling.h"
#include <iostream>

std::vector<char> FileHandling::ReadBinaryFile(const std::string FileName)
{
	std::cout << "Reading file: " << FileName << std::endl;
	// Open the file in binary mode and move the cursor to the end of the file
	std::ifstream file(FileName, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}
	// Get the position of the cursor in the file (which is the size of the file)
	// and use that to resize the buffer to that size
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> fileBuffer(fileSize);

	//Go to the beginning of the file and read all the bytes at once
	file.seekg(0);
	file.read(fileBuffer.data(), fileSize);

	file.close();
	
	return fileBuffer;
}
