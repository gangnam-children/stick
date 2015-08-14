//
//  main.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include <stdlib.h>
#include "lightjson.h"
#include "router.h"
#include "UrlParser.h"
#include "fcgi_stdio.h"


void userCreate(Request req) {
    printf("Content-type: text/html \r\n\r\n <h1>user_create</h1>");
}

void userRead(Request req) {
    printf("Content-type: text/html \r\n\r\n <h1>user_read</h1>");
}

void userUpdate(Request req) {
    printf("Content-type: text/html \r\n\r\n <h1>user_update</h1>");
}

void userDelete(Request req) {
    printf("Content-type: text/html \r\n\r\n <h1>user_delete</h1>");
}

void rankingIndividual(Request req) {
    printf("Content-type: text/html \r\n\r\n <h1>ranking_individual</h1>");
}

void rankingList(Request req) {
    printf("Content-type: text/html \r\n\r\n <h1>ranking_list</h1>");
}

void loadFunctions() {
    Response rUserCreate("/user", "POST", userCreate);
    Response rUserRead("/user/:id", "GET", userRead);
    Response rUserUpdate("/user", "PUT", userUpdate);
    Response rUserDelete("/user", "DELETE", userDelete);
    Response rRankingIndividual("/ranking/:start/:limit", "GET", rankingIndividual);
    Response rRankingList("/ranking/:id", "GET", rankingList);
    Router* router = Router::getInstance();
    router->add(rUserCreate);
    router->add(rUserRead);
    router->add(rUserUpdate);
    router->add(rUserDelete);
    router->add(rRankingIndividual);
    router->add(rRankingList);
}

int main(int argc, const char * argv[]) {
    Router* router = Router::getInstance();
    UrlParser* urlParser = UrlParser::GetInstance();
    loadFunctions();
    while (FCGI_Accept() >= 0) {
        Request req = urlParser->GetRequest();
        router->handle(req);
        //printf("Content-type: text/html \r\n\r\n <h1>TEST</h1><p>FCGI</p>");
    }
    return 0;
}
