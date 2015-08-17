#ifndef __planet__request__
#define __planet__request__

#include "../lib/json/lightjson.h"

#include <string>

class Request {
private:
    std::string route_;
    std::string method_;
    Json::Object parameter_;
    Json::Object body_;
public:
    Request();
    Request(std::string route, std::string method, Json::Object parameter, Json::Object body);
    string GetRoute();
    string GetMethod();
    Json::Object& GetParameter();
    Json::Object GetBody();
};

#endif /* defined(__planet__request__) */
