#define _CRT_SECURE_NO_WARNINGS
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

std::string getTime()
{
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	string time = to_string(tm_t->tm_year + 1900) + "-" +
		to_string(tm_t->tm_mon + 1) + "-" +
		to_string(tm_t->tm_mday) + "_" +
		to_string(tm_t->tm_hour) + ":" +
		to_string(tm_t->tm_min) + ":" +
		to_string(tm_t->tm_sec);
	return time;
}

void clearFile(const char* filePath)
{
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile.close();
}

void overWriteFile(const char* filePath, const char* content)
{
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile << content;
	outFile.close();
}
//文件存在则不创建
void My_mkfile(const char* filePath, const char* fileName)
{
	char path[100];
	strcpy_s(path, filePath);
	strcat_s(path, "\\");
	strcat_s(path, fileName);
	if (_access(path, 0) == -1) {
		ofstream outFile;
		outFile.open(path, ios::out);
		outFile.close();
	}
}

void My_mkdir(const char* dirPath)
{
	if (_access(dirPath, 0) == -1)
		int i = _mkdir(dirPath);
}

int dateInput()
{
	int a[2][12] = { 31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31 };
	string temp;
	cin >> temp;
	refreshInput();
	int flag = 0;
	int len = (int)temp.size();
	while (1) {
		flag = 0;
		while (len != 8)
		{
			cout << "请输入正确的日期格式,例:20200808" << endl;
			cin >> temp;
			refreshInput();
			len = (int)temp.size();
		}
		int  year = 1000 * (temp[0] - '0') + 100 * (temp[1] - '0') + 10 * (temp[2] - '0') + temp[3] - '0';
		int  month = (temp[4] - '0') * 10 + temp[5] - '0';
		int day = (temp[6] - '0') * 10 + temp[7] - '0';
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if ((year > 2020 || year < 1900) || (month > 12 || month < 1) || (day > a[1][month - 1] || day < 1))
			{
				cout << "请输入正确的日期格式,例:20200808" << endl;
				flag = 1;
				cin >> temp;
				refreshInput();
			}
		}
		else
		{
			if ((year > 2020 || year < 1900) || (month > 12 || month < 1) || (day > a[0][month - 1] || day < 1))
			{
				cout << "请输入正确的日期格式,例:20200808" << endl;
				flag = 1;
				cin >> temp;
				refreshInput();
			}
		}
		if (!flag)
		{
			return temp[0] * 10000000 + temp[1] * 1000000 + temp[2] * 100000 + temp[3] * 10000 + temp[4] * 1000 + temp[5] * 100 + temp[6] * 10 + temp[7];
		}
	}

}
