#include "Log.h"
#include<time.h>
#include<iostream>


#define LOG_PATH "/var/log/lighttpd/server.log"


Log* Log::GetInstance()
{
	static Log sLog;

	return &sLog;
}

Log::Log()
{
	mOutFile.open(LOG_PATH,std::ios_base::out | std::ios_base::app);

}
Log::~Log()
{	
	if(mOutFile.is_open() == true)
	{	
		mOutFile.close();
	}
}

void Log::trace( std::string file, int line, std::string func, std::string fmt, ...)
{
	time_t currentTime;
	struct tm t;
	time(&currentTime);
	t = *localtime(&currentTime);
	
	mOutFile <<"[ "<< t.tm_year + 1900 << "-" << t.tm_mon << "-" << t.tm_mday << " ";
	mOutFile << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << " ]  ";
	mOutFile << file << ":" << line << ":" << func << "  " << fmt <<std::endl;
}
