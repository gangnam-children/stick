#include "UrlParser.h"
#include "GlobalFunc.h"
#include <cstdlib>
#include <string.h>

UrlParser* UrlParser::GetInstance()
{
    static UrlParser sUrlParser;
    
    return &sUrlParser;
}

UrlParser::UrlParser()
{
}

Request UrlParser::GetRequest()
{
    string route = std::getenv("SCRIPT_NAME");
    string method = std::getenv("REQUEST_METHOD");
    Json::Object parameter;
    Json::Object body;
    Json::Reader reader;
    
    if (method == "GET") {
        std::vector<std::string> parameterArray = split(getenv("QUERY_STRING"), "&");
        
        for (auto i : parameterArray)
        {
            std::vector<std::string> p = split(i, "=");
            if (p.size() == 2)
                parameter[p[0]] = p[1];
        }
    }
    
    char buf[2048];
    memset(buf, 0, 2048);
    fread(buf, sizeof(char), 2048, stdin);
    body = reader.decode(buf);
    
    Request req(route, method, parameter, body);
    
    return req;
}
