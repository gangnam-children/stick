#include "router.h"

Router::Router() {
    responseList_.clear();
}

void Router::Handle(Request& req) {
    for (int i = 0; i < responseList_.size(); i++) {
        if (responseList_[i].IsMatch(req)) {
            responseList_[i].Execute(req);
            break;
        }
    }
}

void Router::AddResponse(Response res) {
    responseList_.push_back(res);
}

Router* Router::GetInstance() {
    if (instance_ == NULL)
        instance_ = new Router();

    return instance_;
}

Router* Router::instance_ = NULL;

