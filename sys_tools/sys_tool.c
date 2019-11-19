/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : sys_tool.c
   Author : tao.jing
   Date   : 19-10-3
   Brief  : 
**************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <stdint.h>
#include "sys_tool.h"

#include <stdint.h>

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#define MAX_PATH_LEN 256

#ifdef _WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName, accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

int dir_exists(const char* dir_path)
{
    if (ACCESS(dir_path, 0) == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int create_dir(const char* dir_path)
{
    unsigned long dirPathLen = strlen(dir_path);
    if (dirPathLen > MAX_PATH_LEN)
    {
        return -1;
    }
    char tmpDirPath[MAX_PATH_LEN] = {0};
    for (unsigned int i = 0; i < dirPathLen; ++i)
    {
        tmpDirPath[i] = dir_path[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
        {
            if (ACCESS(tmpDirPath, 0) != 0)
            {
                int ret = MKDIR(tmpDirPath);
                if (ret != 0)
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

const char* get_user_name()
{
    uid_t userid;
    struct passwd* pwd;
    userid = getuid();
    pwd = getpwuid(userid);
    return pwd->pw_name;
}

void make_cond_timeout_ms(struct timespec *p_tsp, unsigned int ms)
{
    struct timeval now;

    //get current time
    gettimeofday(&now, NULL);

    unsigned int time_s = ms / 1000;
    ms = ms % 1000;

    //convert current time to timespec
    p_tsp->tv_sec  = now.tv_sec;
    p_tsp->tv_nsec = now.tv_usec * 1000;

    //add wait time
    p_tsp->tv_sec  += time_s;
    p_tsp->tv_nsec += ms * 1000 * 1000;

    while ( p_tsp->tv_nsec > (long)1E9 )
    {
        p_tsp->tv_sec += 1;
        p_tsp->tv_nsec -= (long)1E9;
    }
}

void make_cond_timeout_s(struct timespec *p_tsp, unsigned int time_s)
{
    struct timeval now;

    //get current time
    gettimeofday(&now, NULL);

    //convert current time to timespec
    p_tsp->tv_sec  = now.tv_sec;
    p_tsp->tv_nsec = now.tv_usec * 1000;

    //add wait time
    p_tsp->tv_sec += time_s;
}