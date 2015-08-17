#include "../lib/json/lightjson.h"
#include "../lib/string/split.h" 
#include "../lib/redis/redis.h" 
#include "../lib/log/Log.h"

#include "router.h"
#include "url_dispatcher.h"
#include "fcgi_stdio.h"

using namespace std;

void userCreate(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetBody()["key"].toString();
    int score = req.GetBody()["score"].toInt();
    string member = req.GetBody()["user"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());

    char* log = new char[100];
    memset(log, 0x00, 100);
    WRITELOG("user create - key:%s score:%d name:%s\n", key.c_str(), score, member.c_str());
    delete log;

    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void userRead(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    string member = req.GetParameter()["member"].toString();
    char* result = redis->zscore(key.c_str(), member.c_str());

    Json::Writer writer;
    Json::Object obj;
    obj["score"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void userUpdate(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetBody()["key"].toString();
    int score = req.GetBody()["score"].toInt();
    string member = req.GetBody()["user"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());

    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void userDelete(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetBody()["key"].toString();
    string member = req.GetBody()["user"].toString();
    int result = redis->zrem(key.c_str(), member.c_str());

    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void rankingIndividual(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    string member = req.GetParameter()["member"].toString();
    int result = redis->zrevrank(key.c_str(), member.c_str()) + 1;

    Json::Writer writer;
    Json::Object obj;
    obj["rank"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void rankingList(Request req) {
    Redis* redis = Redis::GetInstance();
    string key = req.GetParameter()["key"].toString();
    int start = atoi(req.GetParameter()["start"].toString().c_str());
    int end = atoi(req.GetParameter()["end"].toString().c_str());
    char** result = redis->zrevrange(key.c_str(), start, end);
    int size = redis->zrevrangesize();

    Json::Writer writer;
    Json::Object obj;
    for (int i = 0; i < size / 2; i++) {
WRITELOG(result[i * 2]);
WRITELOG("::");
WRITELOG(result[i * 2 + 1]);
        obj[result[i * 2]] = result[i * 2 + 1];
    }
    printf("Content-type: text/html \r\n\r\n %s", writer.encode(obj).c_str());
}

void loadFunctions() {
    Response rUserCreate("/user", "POST", userCreate);
    Response rUserRead("/user/:key/:member", "GET", userRead);
    Response rUserUpdate("/user", "PUT", userUpdate);
    Response rUserDelete("/user", "DELETE", userDelete);
    Response rRankingIndividual("/ranking/:key/:member", "GET", rankingIndividual);
    Response rRankingList("/ranking/:key/:start/:end", "GET", rankingList);
    Router* router = Router::GetInstance();
    router->AddResponse(rUserCreate);
    router->AddResponse(rUserRead);
    router->AddResponse(rUserUpdate);
    router->AddResponse(rUserDelete);
    router->AddResponse(rRankingIndividual);
    router->AddResponse(rRankingList);
    WRITELOG("Load all functions\n");
}

int main(int argc, const char * argv[]) {
    Router* router = Router::GetInstance();
    UrlDispatcher* urlDispatcher = UrlDispatcher::GetInstance();
    loadFunctions();
    WRITELOG("Server Start\n");
    while (FCGI_Accept() >= 0) {
        Request req = urlDispatcher->GetRequest();
        router->Handle(req);
        //printf("Content-type: text/html \r\n\r\n <h1>TEST</h1><p>FCGI</p>");
    }
    return 0;
}
