#ifndef __controller__ranking__
#define __controller__ranking__

#include "../lib/json/lightjson.h"
#include "../lib/string/split.h"
#include "../lib/redis/redis.h"

#include <redis3m/redis3m.hpp>
#include "router.h"
#include "url_dispatcher.h"
#include "fcgi_stdio.h"
#include "../lib/log/Log.h"
#include <cstdlib>

void RankingIndividual(Request req);
void RankingList(Request req);
void RankingRandom(Request req);

#endif
