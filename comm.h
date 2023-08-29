#ifndef __COMM_H__
#define __COMM_H__
#include "header.h"

#define DEBUG
#ifdef DEBUG
#define DB_NORMAL	0
#define DB_ERROR	1
#define DB_WARNING	2

int db_print(int level, const char* format, ...);
#else
#define db_print(a, b, ...)
#endif

#define CalEuclidDis(x1, y1, x2, y2) (sqrt(((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2))))

#endif
