//
//  main.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "lightjson.h"
#include "router.h"
#include "UrlParser.h"
#include "SimpleRedisClient.h"
#include "redis.h"
#include "Log.h"
#include "fcgi_stdio.h"

using namespace std;

void userCreate(Request req) {
    Redis* redis = Redis::getInstance();
    string key = req.getBody()["key"].toString();
    int score = req.getBody()["score"].toInt();
    string member = req.getBody()["user"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());

    char* log = new char[100];
    memset(log, 0x00, 100);
    sprintf(log, "user create - key:%s score:%d name:%s", key.c_str(), score, member.c_str());
    WRITELOG(log);
    delete log;

    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void userRead(Request req) {
    Redis* redis = Redis::getInstance();
    string key = req.getParameter()[":key"].toString();
    string member = req.getParameter()[":member"].toString();
    char* result = redis->zscore(key.c_str(), member.c_str());

    Json::Writer writer;
    Json::Object obj;
    obj["score"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void userUpdate(Request req) {
    Redis* redis = Redis::getInstance();
    string key = req.getBody()["key"].toString();
    int score = req.getBody()["score"].toInt();
    string member = req.getBody()["user"].toString();
    int result = redis->zadd(key.c_str(), score, member.c_str());

    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void userDelete(Request req) {
    Redis* redis = Redis::getInstance();
    string key = req.getBody()["key"].toString();
    string member = req.getBody()["user"].toString();
    int result = redis->zrem(key.c_str(), member.c_str());

    Json::Writer writer;
    Json::Object obj;
    obj["result"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void rankingIndividual(Request req) {
    Redis* redis = Redis::getInstance();
    string key = req.getParameter()[":key"].toString();
    string member = req.getParameter()[":member"].toString();
    int result = redis->zrevrank(key.c_str(), member.c_str()) + 1;

    Json::Writer writer;
    Json::Object obj;
    obj["rank"] = result;
    printf("Content-type: text/json \r\n\r\n %s", writer.encode(obj).c_str());
}

void rankingList(Request req) {
    Redis* redis = Redis::getInstance();
    string key = req.getParameter()[":key"].toString();
    int start = atoi(req.getParameter()[":start"].toString().c_str());
    int end = atoi(req.getParameter()[":end"].toString().c_str());
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
    Router* router = Router::getInstance();
    router->add(rUserCreate);
    router->add(rUserRead);
    router->add(rUserUpdate);
    router->add(rUserDelete);
    router->add(rRankingIndividual);
    router->add(rRankingList);
    WRITELOG("Load all functions");
}

int main(int argc, const char * argv[]) {
    Router* router = Router::getInstance();
    UrlParser* urlParser = UrlParser::GetInstance();
    loadFunctions();
    WRITELOG("Server Start");
    while (FCGI_Accept() >= 0) {
        Request req = urlParser->GetRequest();
        router->handle(req);
        //printf("Content-type: text/html \r\n\r\n <h1>TEST</h1><p>FCGI</p>");
    }
    return 0;
}
