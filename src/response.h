#ifndef __planet__response__
#define __planet__response__

#include "../lib/json/lightjson.h"
#include "../lib/string/split.h"

#include <vector>
#include <string>
#include "request.h"

class Response {
private:
    std::string route_;
    std::string method_;
    void(*handler_)(Request);
public:
    Response(string route, string method, void(*handler)(Request));
    string GetRoute();
    bool IsMatch(Request&);
    void Execute(Request);
};

#endif /* defined(__planet__response__) */
