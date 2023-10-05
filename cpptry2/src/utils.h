#ifndef UTILS_H
#define UTILS_H

void refreshInput();

void overWriteFile(const char* filePath, const char* content);
void addToFile(const char* filePath, const char* content);	

void My_mkfile(const char* filePath,const char* fileName);
void My_mkdir(const char* dirPath);
#endif // !UTILS_H