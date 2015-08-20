#include "user.h"

void UserCreate(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["api_key"].toString();
    int score = req.GetBody()["score"].toInt();
    string member = req.GetBody()["id"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER CREATE] key:%s score:%d member:%s result:%d\n", key.c_str(), score, member.c_str(), result);
}

void UserRead(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["api_key"].toString();
    string member = req.GetParameter()["id"].toString();
    char* result = redis->zscore(key.c_str(), member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["score"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER READ] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}

void UserUpdate(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["api_key"].toString();
    int score = req.GetBody()["score"].toInt();
    string member = req.GetBody()["id"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER UPDATE] key:%s score:%d member:%s result:%d\n", key.c_str(), score, member.c_str(), result);
}

void UserDelete(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["api_key"].toString();
    string member = req.GetParameter()["id"].toString();
    int result = redis->zrem(key.c_str(), member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER DELETE] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}
