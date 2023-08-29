#include <stdarg.h>
#include "comm.h"

#ifdef DEBUG

#define COLOR_OFF       "\x1B[0m"
#define COLOR_BLACK     "\x1B[1;30m"
#define COLOR_RED       "\x1B[1;31m"
#define COLOR_GREEN     "\x1B[1;32m"
#define COLOR_YELLOW    "\x1B[1;33m"
#define COLOR_BLUE      "\x1B[1;34m"
#define COLOR_CYAN      "\x1B[1;36m"


int db_print(int level, const char* format, ...)
{
	static char level2color[][10] = {
		COLOR_BLUE, COLOR_RED, COLOR_YELLOW, COLOR_OFF,
		COLOR_CYAN, COLOR_GREEN,
	};

	va_list args;
	time_t timep;
	struct tm p;

	char* color = level2color[level];

	time(&timep);
	localtime_s(&p, &timep);

	printf("%s""[%04d/%02d/%02d %02d:%02d:%02d]""%s",
		color, p.tm_year + 1900, p.tm_mon + 1, p.tm_mday,
		(8 + p.tm_hour) % 24, p.tm_min, p.tm_sec, COLOR_OFF);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	return 0;
}

#endif