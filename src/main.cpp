//#include "../lib/json/lightjson.h"
//#include "../lib/string/split.h" 
//#include "../lib/redis/redis.h" 
#include "router.h"
#include "url_dispatcher.h"

#include "user.h"
#include "ranking.h"

#include "fcgi_stdio.h"
#include "../lib/log/Log.h"

using namespace std;

void LoadFunctions();

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
    Response rUserCreate("/user/:api_key", "POST", UserCreate);
    Response rUserRead("/user/:api_key/:id", "GET", UserRead);
    Response rUserUpdate("/user/:api_key", "PUT", UserUpdate);
    Response rUserDelete("/user/:api_key/:id", "DELETE", UserDelete);
    Response rRankingIndividual("/ranking/:api_key/:id", "GET", RankingIndividual);
    Response rRankingList("/ranking/:api_key/:start/:end", "GET", RankingList);
    Router* router = Router::GetInstance();
    router->AddResponse(rUserCreate);
    router->AddResponse(rUserRead);
    router->AddResponse(rUserUpdate);
    router->AddResponse(rUserDelete);
    router->AddResponse(rRankingIndividual);
    router->AddResponse(rRankingList);
    WRITELOG("Load all functions\n");
}
