#include "request.h"

Request::Request(std::string route, std::string method, Json::Object parameter, Json::Object body) {
    route_ = route;
    method_ = method;
    parameter_ = parameter;
    body_ = body;
}

string Request::GetRoute() {
    return route_;
}

string Request::GetMethod() {
    return method_;
}

Json::Object& Request::GetParameter() {
    return parameter_;
}

Json::Object Request::GetBody() {
    return body_;
}
