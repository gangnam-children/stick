#ifndef __redis__
#define __redis__

#include <redis3m/redis3m.hpp>
#include <string>
#include <stdlib.h>
#include "SimpleRedisClient.h"

class Redis {
private:
    static Redis* instance;
    redis3m::simple_pool::ptr_t pool;
    SimpleRedisClient rc;

    Redis(); 
public:
    static Redis* GetInstance() {
        if (instance == NULL)
            instance = new Redis();

        return instance;
    }

    redis3m::connection::ptr_t GetConnection();
    void Release(redis3m::connection::ptr_t conn);

    int zadd(const char *key, int score, const char *member);
    int zrem(const char *key, const char *member);
    char* zscore(const char *key, const char *member);
    char** zrevrange(const char *key, int start, int end);
    int zrevrangesize();
    int zrevrank(const char *key, const char *member);
};

#endif

