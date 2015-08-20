#ifndef __controller__ranking__
#define __controller__ranking__

#include "../lib/json/lightjson.h"
#include "../lib/string/split.h"
#include "../lib/redis/redis.h"

#include "router.h"
#include "url_dispatcher.h"
#include "fcgi_stdio.h"
#include "../lib/log/Log.h"

void RankingIndividual(Request req);
void RankingList(Request req);

#endif
