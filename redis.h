#include <stdlib.h>
#include "SimpleRedisClient.h"

class Redis {
private:
    static Redis* instance;
    SimpleRedisClient rc;

    Redis(); 
public:
    static Redis* getInstance() {
        if (instance == NULL)
            instance = new Redis();

        return instance;
    }

    int zadd(const char *key, int score, const char *member);
    int zrem(const char *key, const char *member);
    char* zscore(const char *key, const char *member);
    char** zrevrange(const char *key, int start, int end);
    int zrevrangesize();
    int zrevrank(const char *key, const char *member);
};

