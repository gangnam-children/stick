#ifndef __server__router__
#define __server__router__

#include <vector>
#include "response.h"
#include "request.h"

class Router {
private:
    std::vector<Response> responseList_;
    static Router* instance_;
    Router();
public:
    void Handle(Request& req);
    void AddResponse(Response res);
    static Router* GetInstance();
};

#endif /* defined(__server__router__) */
