#ifndef __server__UrlParser__
#define __server__UrlParser__

#include "request.h"

class UrlParser
{
public:
    Request GetRequest();
    static UrlParser* GetInstance();
private:
    UrlParser();
};


#endif /* defined(__server__UrlParser__) */
