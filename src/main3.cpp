#include "../lib/json/lightjson.h"
#include "../lib/string/split.h"

#include "router.h"
#include "url_dispatcher.h"
#include "fcgi_stdio.h"

void LoadFunctions();
void testGET(Request req);
void testPOST(Request req);

int main() {
    Router* router = Router::GetInstance();
    UrlDispatcher* urlDispatcher = UrlDispatcher::GetInstance();
    LoadFunctions();

    while (FCGI_Accept() >= 0) {
        Request request = urlDispatcher->GetRequest();
        router->Handle(request);
    }
    return 0;
}

void LoadFunctions() {
    Response rTestGET("/test", "GET", testGET);
    Response rTestPOST("/test/:param", "POST", testPOST);
    Router* router = Router::GetInstance();
    router->AddResponse(rTestGET);
    router->AddResponse(rTestPOST);
}

void testGET(Request req) {
    string param = req.GetParameter()["param"].toString();
    printf("Content-type: text/html \r\n\r\n param : %s", param.c_str());
}

void testPOST(Request req) {
    string param = req.GetParameter()["param"].toString();
    string body = req.GetBody()["body"].toString();
    printf("Content-type: text/html \r\n\r\n param : %s\nbody : %s", param.c_str(), body.c_str());
}

