#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define WRITELOG(fmt, ...)	Log::GetInstance()->trace( __FILE__, __LINE__, __PRETTY_FUNCTION__ , fmt, ##__VA_ARGS__);


class Log
{

public:
	static Log* GetInstance();
	void trace(std::string file, int line, std::string func, const char* fmt, ...);
private:
	Log();
	~Log();
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;
private:
	std::ofstream mOutFile;
};
