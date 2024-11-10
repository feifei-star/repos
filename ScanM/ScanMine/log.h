#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>

#define MDEBUG(fmt, argv...)  do{printf("--%s --%s --%d -- " fmt "\n", __FILE__, \
                                 __FUNCTION__, __LINE__, ##argv); \
                                 fflush(stdout); }while(0);

#endif // LOG_H
