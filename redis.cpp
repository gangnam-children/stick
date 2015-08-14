#include "redis.h"
#include <cstdlib>

Redis::Redis() {
    rc.setHost("127.0.0.1");
    rc.auth("home");
    rc.LogLevel(0);
};

int Redis::zadd(const char *key, int score, const char *member) {
    return rc.zadd(key, score, member);
}

int Redis::zrem(const char *key, const char *member) {
    return rc.zrem(key, member);
}

char* Redis::zscore(const char *key, const char *member) {
    return rc.zscore(key, member);
}

char** Redis::zrevrange(const char *key, int start, int end) {
    return rc.zrevrange(key, start, end);
}

int Redis::zrevrangesize() {
    return rc.getMultiBulkDataAmount();
}

int Redis::zrevrank(const char *key, const char *member) {
    return atoi(rc.zrevrank(key, member));
}

Redis* Redis::instance = NULL;

