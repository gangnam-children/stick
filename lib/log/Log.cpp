#include "Log.h"
#include <time.h>
#include <stdarg.h>
#include <string.h>

#define LOG_PATH "/var/log/lighttpd/server.log"
#define MAX_TEXT_BUFFER_SIZE 1024

Log* Log::GetInstance()
{
	static Log sLog;

	return &sLog;
}

Log::Log()
{
	mOutFile.open(LOG_PATH, std::ios_base::out | std::ios_base::app);
}
Log::~Log()
{	
        if(mOutFile.is_open() == true)
	{	
                mOutFile.close();
	}
}

void Log::trace( std::string file, int line, std::string func, const char* fmt, ...)
{

	char buf[MAX_TEXT_BUFFER_SIZE] = { 0, };
	va_list ap;

	va_start(ap, fmt);
	vsprintf(buf + strlen(buf), fmt, ap);
	va_end(ap);

	time_t currentTime;
	struct tm t;
	time(&currentTime);
	t = *localtime(&currentTime);
	
	mOutFile << "[" << t.tm_year + 1900 << "-";
	mOutFile.width(2);
	mOutFile.fill('0');
	mOutFile << t.tm_mon;
	mOutFile << "-";
	mOutFile.width(2);
	mOutFile.fill('0');
	mOutFile << t.tm_mday;
	mOutFile << " ";
	mOutFile.width(2);
	mOutFile.fill('0');
	mOutFile << t.tm_hour;
	mOutFile << ":";
	mOutFile.width(2);
	mOutFile.fill('0');
	mOutFile << t.tm_min;
	mOutFile << ":";
	mOutFile.width(2);
	mOutFile.fill('0');
	mOutFile << t.tm_sec << "]  ";
	
	mOutFile << file << ":" << line << ":" << func << "  " << buf;
        mOutFile.flush();
}

