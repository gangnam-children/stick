#ifndef __controller__user__
#define __controller__user__

#include "../lib/json/lightjson.h"
#include "../lib/string/split.h"
#include "../lib/redis/redis.h"

#include "router.h"
#include "url_dispatcher.h"
#include "fcgi_stdio.h"
#include "../lib/log/Log.h"

void UserCreate(Request req);
void UserRead(Request req);
void UserUpdate(Request req);
void UserDelete(Request req);

#endif
