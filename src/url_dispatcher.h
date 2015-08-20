#ifndef __server__url__dispatcher__
#define __server__url__dispatcher__

#include "../lib/string/split.h"

#include <string.h>
#include "request.h"
#include "fcgi_stdio.h"

#include "../lib/log/Log.h" 

class UrlDispatcher {
public:
    Request GetRequest();
    static UrlDispatcher* GetInstance();
private:
    UrlDispatcher();
};

#endif /* defined(__server__url__dispatcher__) */
