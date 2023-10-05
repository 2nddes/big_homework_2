#include "utils.h"
#include<Windows.h>
#include<iostream>
#include<io.h>
#include<direct.h>
#include<fstream>

using namespace std;

void addToFile(const char* filePath, const char* content)
{
	ofstream outFile;
	outFile.open(filePath, ios::app);
	outFile << content;
	outFile.close();
}

void refreshInput()
{
	cin.clear();
	cin.ignore(1024, '\n');
}


void overWriteFile(const char* filePath, const char* content)
{
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile << content;
	outFile.close();
}

void My_mkfile(const char* filePath, const char* fileName)
{
	char path[100];
	strcpy_s(path, filePath);
	strcat_s(path, fileName);
	ofstream outFile;
	outFile.open(path, ios::out);
	outFile.close();
}

void My_mkdir(const char* dirPath)
{
	if (_access(dirPath, 0) == -1)
		_mkdir(dirPath);
}