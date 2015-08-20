#include "response.h"

Response::Response(std::string route, std::string method, void(*handler)(Request)) {
    route_ = route;
    method_ = method;
    handler_ = handler;
}

std::string Response::GetRoute() {
    return route_;
}

bool Response::IsMatch(Request& req) {
    if (req.GetMethod() != method_)
        return false;

    std::string route = "";
    int routeSize = 0;

    std::vector<std::string> params;
    std::vector<std::string> resRoute = split(route_, "/");

    for (std::string s : resRoute) {
        if (s[0] == ':') {
            params.push_back(s.erase(0, 1));
        } else {
            routeSize++;
            route += s + "/";
        }
    }

    std::vector<string> reqRoute = split(req.GetRoute(), "/");

    if (resRoute.size() != reqRoute.size())
        return false;

    for (int i = 0; i < routeSize; i++)
        if (resRoute[i] != reqRoute[i])
            return false;

    for (int i = routeSize; i < reqRoute.size(); i++) {
        Json::Object& reqParams = req.GetParameter();
        std::string paramKey = params[i - routeSize];
        std::string paramValue = reqRoute[i];
        reqParams[paramKey] = paramValue;
    }

    return true;
}

void Response::Execute(Request req) {
    WRITELOG("[EXECUTE FUNCTION] %s\n", req.GetMethod().c_str())
    handler_(req);
}
