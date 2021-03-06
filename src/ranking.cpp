#include "ranking.h"

void RankingIndividual(Request req) {
    Redis* redis = Redis::GetInstance();
    redis3m::connection::ptr_t conn = redis->GetConnection();
    string key = req.GetParameter()["api_key"].toString();
    string member = req.GetParameter()["id"].toString();
    int result = conn->run(redis3m::command("ZREVRANK") << key << member);
    redis->Release(conn);
  
    Json::Writer writer;
    Json::Object obj;
    obj["rank"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
    
    WRITELOG("[RANKING INDIVIDUAL] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}

void RankingList(Request req) {
    Redis* redis = Redis::GetInstance();
    redis3m::connection::ptr_t conn = redis->GetConnection();
    string key = req.GetParameter()["api_key"].toString();
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

void RankingRandom(Request req) {
    Redis* redis = Redis::GetInstance();
    redis3m::connection::ptr_t conn = redis->GetConnection();
    string key = req.GetParameter()["api_key"].toString();
    int id = rand() % 1000000;
    string member = to_string(id);
    int result = conn->run(redis3m::command("ZREVRANK") << key << member);
    redis->Release(conn);

    Json::Writer writer;
    Json::Object obj;
    obj["rank"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());

    WRITELOG("[RANKING INDIVIDUAL] key:%s member:%s result:%d\n", key.c_str(), member.c_str(), result);
}
