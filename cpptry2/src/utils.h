#ifndef UTILS_H
#define UTILS_H

#include<string>


void refreshInput();

std::string getTime();

void clearFile(const char* filePath);

void overWriteFile(const char* filePath, const char* content);
void addToFile(const char* filePath, const char* content);	

void My_mkfile(const char* filePath,const char* fileName);
void My_mkdir(const char* dirPath);

int dateInput();

#endif // !UTILS_H