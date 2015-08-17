#include "../lib/json/lightjson.h"
#include "../lib/string/split.h" 
#include "../lib/redis/redis.h" 
#include "../lib/log/Log.h"

#include "router.h"
#include "url_dispatcher.h"
#include "fcgi_stdio.h"

using namespace std;

void LoadFunctions();
void UserCreate(Request req);
void UserRead(Request req);
void UserUpdate(Request req);
void UserDelete(Request req);
void RankingIndividual(Request req);
void RankingList(Request req);

int main(int argc, const char * argv[]) {
    Router* router = Router::GetInstance();
    UrlDispatcher* urlDispatcher = UrlDispatcher::GetInstance();
    LoadFunctions();
    WRITELOG("Server Start\n");
    while (FCGI_Accept() >= 0) {
        Request req = urlDispatcher->GetRequest();
        router->Handle(req);
    }
    return 0;
}

void LoadFunctions() {
    Response rUserCreate("/user/:key", "POST", UserCreate);
    Response rUserRead("/user/:key/:member", "GET", UserRead);
    Response rUserUpdate("/user/:key", "PUT", UserUpdate);
    Response rUserDelete("/user/:key", "DELETE", UserDelete);
    Response rRankingIndividual("/ranking/:key/:member", "GET", RankingIndividual);
    Response rRankingList("/ranking/:key/:start/:end", "GET", RankingList);
    Router* router = Router::GetInstance();
    router->AddResponse(rUserCreate);
    router->AddResponse(rUserRead);
    router->AddResponse(rUserUpdate);
    router->AddResponse(rUserDelete);
    router->AddResponse(rRankingIndividual);
    router->AddResponse(rRankingList);
    WRITELOG("Load all functions\n");
}

void UserCreate(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    int score = req.GetBody()["score"].toInt();
    string member = req.GetBody()["member"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER CREATE] key:%s score:%d member:%s result:%d\n", key.c_str(), score, member.c_str(), result);
}

void UserRead(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    string member = req.GetParameter()["member"].toString();
    char* result = redis->zscore(key.c_str(), member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["score"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER READ] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}

void UserUpdate(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    int score = req.GetBody()["score"].toInt();
    string member = req.GetBody()["user"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER UPDATE] key:%s score:%d member:%s result:%d\n", key.c_str(), score, member.c_str(), result);
}

void UserDelete(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    string member = req.GetBody()["user"].toString();
    int result = redis->zrem(key.c_str(), member.c_str());
    
    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[USER DELETE] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}

void RankingIndividual(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    string member = req.GetParameter()["member"].toString();
    int result = redis->zrevrank(key.c_str(), member.c_str()) + 1;
    
    Json::Writer writer;
    Json::Object obj;
    obj["rank"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[RANKING INDIVIDUAL] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}

void RankingList(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    int start = atoi(req.GetParameter()["start"].toString().c_str());
    int end = atoi(req.GetParameter()["end"].toString().c_str());
    char** result = redis->zrevrange(key.c_str(), start, end);
    int size = redis->zrevrangesize();
    
    Json::Writer writer;
    Json::Object obj;
    for (int i = 0; i < size / 2; i++)
        obj[result[i * 2]] = result[i * 2 + 1];
    printf("Content-type: text/html \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[RANKING LIST] key:%s start:%d end:%d\n", key.c_str(), start, end);
}
